#include <cassert>
#include <cstdio>
#include "common/log.h"
#include "mgCMemory.h"

set_log_channel("mgCMemory");

void mgCMemory::Initialize()
{
	log_trace("Initialize()");

	m_heap_size = 0;
	m_heap_start = nullptr;
	m_heap_mem_head = nullptr;
	m_label[0] = '\0';
	m_stack_start = nullptr;
	m_stack_current_allocated = 0;
	m_stack_max_allocated = 0;
	m_unk_field_1C = false;
}

void mgCMemory::SetHeapMem(void* heap, usize heap_size)
{
	log_trace("SetHeapMem({}, {})", fmt::ptr(heap), heap_size);

	// TODO: This is a bit weird; heap memory has to be investigated further
	m_heap_size = heap_size;

	if (heap == nullptr || heap_size < 0x10)
	{
		Initialize();
		return;
	}

	m_heap_mem_head = static_cast<SHeapMemHead*>(heap);
	m_heap_mem_head->field_0 = 0;
	m_heap_mem_head->field_4 = 1;
	uptr top = reinterpret_cast<uptr>(m_heap_start) + (m_heap_size * 0x10 - sizeof(SHeapMemHead));
	m_heap_mem_head->field_C = reinterpret_cast<SHeapMemHead*>(top);

	m_heap_mem_head->field_C->field_0 = 0;
	m_heap_mem_head->field_C->field_4 = 0;
	m_heap_mem_head->field_C->field_C = 0;
}

void mgCMemory::ClearHeapMem()
{
	log_trace("ClearHeapMem()");

	void* heap_start = m_heap_start;
	usize heap_size = m_heap_size;
	Initialize();

	SetHeapMem(heap_start, heap_size);
}

void* mgCMemory::StartStackMode(int i1, int i2)
{
	log_trace("StartStackMode({}, {})", i1, i2);

	// FIXME: very messy, probably doesn't work, the 0x10 align in original code
	// may be due to the size of SHeapMemHead, which would be different in Windows
	m_unk_field_2C = nullptr;
	i2 += 1;

	SHeapMemHead *heap_mem_head = m_heap_mem_head;

	if (heap_mem_head == nullptr)
		return nullptr;

	SHeapMemHead* t2 = nullptr;
	SHeapMemHead* t3 = nullptr;
	usize t0 = 0;
	int a2 = 2;
	int v1 = 3;

	do 
	{
		if (heap_mem_head->field_C == nullptr)
			break;

		uptr t5 = (heap_mem_head->field_4 * 0x10 + reinterpret_cast<uptr>(&heap_mem_head));
		t0 = reinterpret_cast<uptr>(heap_mem_head->field_C) - t5;
		usize t6 = t0 >> 4;

		if (t0 <= 0) 
		{
			t6 += 0xF;
			t6 >>= 4;
		}
		t0 = t6 - 1;

		if (i1 == 1 && t6 >= 2)
		{
			t2 = reinterpret_cast<SHeapMemHead*>(t5);
			t3 = heap_mem_head;
			break;
		}

		if (i1 == 2 && 0 < t6)
		{
			t2 = reinterpret_cast<SHeapMemHead*>(t5);
			t3 = heap_mem_head;
			t6 = 0;
		}

		if (i1 == 3 && i2 < t6)
		{
			t2 = reinterpret_cast<SHeapMemHead*>(t5);
			t3 = heap_mem_head;
			break;
		}

		heap_mem_head = heap_mem_head->field_C;
	} while (true);

	if (t2 == nullptr)
		return nullptr;

	m_unk_field_2C = t2;
	m_unk_field_2C->field_C = heap_mem_head->field_C;
	heap_mem_head->field_C = m_unk_field_2C;
	m_unk_field_2C->field_4 = 1;

	m_unk_field_2C->field_0 = m_unk_field_2C + 1;
	// NOTE: Custom 0x10 alignment (not in original code)
	m_unk_field_2C->field_0 = reinterpret_cast<void*>((reinterpret_cast<uptr>(m_unk_field_2C->field_0) + 0xF) & ~0xF);

	m_stack_start = m_unk_field_2C->field_0;

	m_stack_max_allocated = t0;
	return m_unk_field_2C->field_0;
}

void mgCMemory::EndStackMode()
{
	log_trace("EndStackMode()");

	if (m_unk_field_2C == nullptr)
		return;

	usize a1 = m_stack_current_allocated;
	m_unk_field_2C->field_4 += static_cast<u32>(a1);
	m_unk_field_2C = nullptr;
	m_stack_start = nullptr;
	m_stack_max_allocated = 0;
	m_stack_current_allocated = 0;
}

void* mgCMemory::stAlloc64(ssize n_blocks)
{
	log_trace("stAlloc64({})", n_blocks);

	stAlign64();
	return stAlloc(n_blocks);
}

void* mgCMemory::stAllocTest(ssize n_blocks)
{
	log_trace("stAllocTest({})", n_blocks);

	if (!m_unk_field_1C)
		return nullptr;

	usize current_allocated = m_stack_current_allocated;
	usize max_allocated = m_stack_max_allocated;
	usize new_allocated = current_allocated + n_blocks;

	if (new_allocated >= max_allocated)
		log_error("stack over %Iu/%Iu at %s\n", new_allocated, max_allocated, m_label);

	return static_cast<char*>(m_stack_start) + (current_allocated * 0x10);
}

void* mgCMemory::stAlloc(ssize n_blocks)
{
	log_trace("stAlloc({})", n_blocks);

	if (!m_unk_field_1C)
		return nullptr;

	if (n_blocks <= 0)
		return nullptr;

	usize current_allocated = m_stack_current_allocated;
	usize max_allocated = m_stack_max_allocated;
	usize new_allocated = current_allocated + n_blocks;

	if (new_allocated >= max_allocated)
		log_error("stack over %Iu/%Iu at %s\n", new_allocated, max_allocated, m_label);

	void *result = static_cast<char*>(m_stack_start) + (current_allocated * 0x10);
	m_stack_current_allocated = new_allocated;

	return result;
}

void* mgCMemory::Alloc(ssize n_blocks)
{
	log_trace("Alloc({})", n_blocks);

	return stAlloc(n_blocks);
}

void mgCMemory::stAlign64()
{
	log_trace("stAlign64()");

	if (!m_unk_field_1C)
		return;

	usize current_allocated = m_stack_current_allocated;
	void* current_address = static_cast<char*>(m_stack_start) + (current_allocated * 0x10);
	usize misalignment = reinterpret_cast<uptr>(current_address) & 0x3F;

	if (misalignment != 0)
		m_stack_current_allocated += (misalignment + 0xF) << 4;

	if (m_stack_current_allocated >= m_stack_max_allocated)
		m_stack_max_allocated = m_stack_current_allocated;
}

void mgCMemory::Align64()
{
	log_trace("Align64()");

	stAlign64();
}

void mgCMemory::stSetBuffer(void* stack_start, usize capacity)
{
	log_trace("stSetBuffer({}, {})", fmt::ptr(stack_start), capacity);

	m_stack_start = stack_start;
	m_stack_current_allocated = 0;
	m_stack_max_allocated = capacity;
}