#include <cassert>
#include <cstdio>
#include "mgCMemory.h"

void mgCMemory::Initialize()
{
	this->m_heap_size = 0;
	this->m_heap_start = nullptr;
	this->m_heap_mem_head = nullptr;
	this->m_label[0] = '\0';
	this->m_stack_start = nullptr;
	this->m_stack_current_allocated = 0;
	this->m_stack_max_allocated = 0;
	this->field_1C = false;
}

void mgCMemory::SetHeapMem(void* heap, usize heap_size)
{
	// TODO: This is a bit weird; heap memory has to be investigated further
	this->m_heap_size = heap_size;

	if (heap == nullptr || heap_size < 0x10) {
		this->Initialize();
		return;
	}

	this->m_heap_mem_head = static_cast<SHeapMemHead*>(heap);
	this->m_heap_mem_head->field_0 = 0;
	this->m_heap_mem_head->field_4 = 1;
	uptr top = reinterpret_cast<uptr>(this->m_heap_start) + (this->m_heap_size * 0x10 - sizeof(SHeapMemHead));
	this->m_heap_mem_head->field_C = reinterpret_cast<SHeapMemHead*>(top);

	this->m_heap_mem_head->field_C->field_0 = 0;
	this->m_heap_mem_head->field_C->field_4 = 0;
	this->m_heap_mem_head->field_C->field_C = 0;
}

void mgCMemory::ClearHeapMem()
{
	void* heap_start = this->m_heap_start;
	usize heap_size = this->m_heap_size;
	this->Initialize();

	this->SetHeapMem(heap_start, heap_size);
}

void* mgCMemory::StartStackMode(int i1, int i2)
{
	// FIXME: very messy, probably doesn't work, the 0x10 align in original code
	// may be due to the size of SHeapMemHead, which would be different in Windows
	this->field_2C = nullptr;
	i2 += 1;

	SHeapMemHead *heap_mem_head = this->m_heap_mem_head;
	if (heap_mem_head == nullptr)
	{
		return nullptr;
	}

	SHeapMemHead* t2 = nullptr;
	SHeapMemHead* t3 = nullptr;
	usize t0 = 0;
	int a2 = 2;
	int v1 = 3;

	do {
		if (heap_mem_head->field_C == nullptr)
		{
			break;
		}

		uptr t5 = (heap_mem_head->field_4 * 0x10 + reinterpret_cast<uptr>(&heap_mem_head));
		t0 = reinterpret_cast<uptr>(heap_mem_head->field_C) - t5;
		usize t6 = t0 >> 4;
		if (t0 <= 0) {
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
	{
		return nullptr;
	}

	this->field_2C = t2;
	this->field_2C->field_C = heap_mem_head->field_C;
	heap_mem_head->field_C = this->field_2C;
	this->field_2C->field_4 = 1;

	this->field_2C->field_0 = this->field_2C + 1;
	// NOTE: Custom 0x10 alignment (not in original code)
	this->field_2C->field_0 = reinterpret_cast<void*>((reinterpret_cast<uptr>(this->field_2C->field_0) + 0xF) & ~0xF);

	this->m_stack_start = this->field_2C->field_0;

	this->m_stack_max_allocated = t0;
	return this->field_2C->field_0;
}

void mgCMemory::EndStackMode()
{
	if (this->field_2C == nullptr)
	{
		return;
	}

	usize a1 = this->m_stack_current_allocated;
	this->field_2C->field_4 += a1;
	this->field_2C = nullptr;
	this->m_stack_start = nullptr;
	this->m_stack_max_allocated = 0;
	this->m_stack_current_allocated = 0;
}

void* mgCMemory::stAlloc64(ssize n_blocks)
{
	this->stAlign64();
	return this->stAlloc(n_blocks);
}

void* mgCMemory::stAllocTest(ssize n_blocks)
{
	if (!this->field_1C) {
		return nullptr;
	}

	usize current_allocated = this->m_stack_current_allocated;
	usize max_allocated = this->m_stack_max_allocated;
	usize new_allocated = current_allocated + n_blocks;
	if (new_allocated >= max_allocated)
	{
		printf("stack over %Iu/%Iu at %s\n", new_allocated, max_allocated, &this->m_label);
	}

	return static_cast<char*>(this->m_stack_start) + (current_allocated * 0x10);
}

void* mgCMemory::stAlloc(ssize n_blocks)
{
	if (!this->field_1C) {
		return nullptr;
	}

	if (n_blocks <= 0) {
		return nullptr;
	}

	usize current_allocated = this->m_stack_current_allocated;
	usize max_allocated = this->m_stack_max_allocated;
	usize new_allocated = current_allocated + n_blocks;
	if (new_allocated >= max_allocated)
	{
		printf("stack over %Iu/%Iu at %s\n", new_allocated, max_allocated, &this->m_label);
	}

	void *result = static_cast<char*>(this->m_stack_start) + (current_allocated * 0x10);
	this->m_stack_current_allocated = new_allocated;
	return result;
}

void* mgCMemory::Alloc(ssize n_blocks)
{
	return this->stAlloc(n_blocks);
}

void mgCMemory::stAlign64()
{
	if (!this->field_1C) {
		return;
	}

	usize current_allocated = this->m_stack_current_allocated;
	void* current_address = static_cast<char*>(this->m_stack_start) + (current_allocated * 0x10);
	usize misalignment = reinterpret_cast<uptr>(current_address) & 0x3F;
	if (misalignment != 0)
	{
		this->m_stack_current_allocated += (misalignment + 0xF) << 4;
	}

	if (this->m_stack_current_allocated >= this->m_stack_max_allocated)
	{
		this->m_stack_max_allocated = this->m_stack_current_allocated;
	}
}

void mgCMemory::Align64()
{
	this->stAlign64();
}

void mgCMemory::stSetBuffer(void* stack_start, usize capacity)
{
	this->m_stack_start = stack_start;
	this->m_stack_current_allocated = 0;
	this->m_stack_max_allocated = capacity;
}