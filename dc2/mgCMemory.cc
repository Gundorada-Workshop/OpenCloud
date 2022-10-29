#include <cassert>
#include <cstdio>
#include "mgCMemory.h"

void mgCMemory::Initialize()
{
	this->m_heap_size = 0;
	this->m_heap_start = nullptr;
	this->field_18 = nullptr;
	this->m_label[0] = '\0';
	this->m_stack_start = nullptr;
	this->m_stack_current_allocated = 0;
	this->m_stack_max_allocated = 0;
	this->field_1C = false;
}

void mgCMemory::SetHeapMem(void* heap, usize heap_size)
{
	// TODO
	assert(false);
}

void mgCMemory::ClearHeapMem()
{
	// TODO
	assert(false);
}

void mgCMemory::StartStackMode(int i1, int i2)
{
	// TODO
	assert(false);
}

void mgCMemory::EndStackMode()
{
	// TODO
	assert(false);
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
	usize misalignment = reinterpret_cast<usize>(current_address) & 0x3F;
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