#include <assert.h>
#include "mgCMemory.h"

void mgCMemory::Initialize()
{
	assert(false);
}

void mgCMemory::SetHeapMem(void* heap, usize heap_size)
{

}

void mgCMemory::ClearHeapMem()
{
	assert(false);
}

void mgCMemory::StartStackMode(int i1, int i2)
{
	assert(false);
}

void mgCMemory::EndStackMode()
{
	assert(false);
}

void* mgCMemory::stAlloc64(ssize n_blocks)
{
	assert(false);
	return nullptr;
}

void* mgCMemory::stAllocTest(ssize n_blocks)
{
	assert(false);
	return nullptr;
}

void* mgCMemory::stAlloc(ssize n_blocks)
{
	assert(false);
	return nullptr;
}

void* mgCMemory::Alloc(ssize n_blocks)
{
	assert(false);
	return nullptr;
}

void mgCMemory::stAlign64()
{
	assert(false);
}

void mgCMemory::Align64()
{
	assert(false);
}

void mgCMemory::stSetBuffer(void* stack_start, usize capacity)
{
	this->stack_start = stack_start;
	this->stack_current_allocated = 0;
	this->stack_max_allocated = capacity;
}