#pragma once
#include "common/types.h"

/**
 * A mgCMemory is a stack of 0x10-sized blocks.
 */
class mgCMemory
{
public:
	// 00139900
	void Initialize();

	// 00139930
	void SetHeapMem(void *heap, usize heap_size);

	// 001399D0
	void ClearHeapMem();

	// 00139AA0
	// FIXME: NAME: arguments (and specific numeric types?)
	void StartStackMode(int i1, int i2);

	// 00139BD0
	void EndStackMode();

	// 00139BD0
	// Shorthand for:
	// mem.stAlign64();
	// mem.stAlloc(n_blocks);
	void* stAlloc64(ssize n_blocks);

	// 00139C50
	// Tests an allocation of n_blocks blocks worth of memory;
	// While this method returns the address of where the allocated
	// memory would be, this method does not mark that memory as allocated.
	void* stAllocTest(ssize n_blocks);

	// 00139CB0
	// Allocates n_blocks blocks worth of memory.
	void* stAlloc(ssize n_blocks);

	// 00139D20
	// See stAlloc
	void* Alloc(ssize n_blocks);

	// 00139D90
	// Aligns the stack to a 0x40 boundary.
	void* stAlign64();

	// 00139E00
	// See stAlign64
	void* Align64();

	// Debug representation of the purpose of this memory.
	char label[0x10];
	usize heap_size;
	void* heap_start;
	// FIXME: NAME:
	void* field_18;
	// FIXME: NAME:
	bool field_1C;
	void* stack_start;
	usize stack_current_allocated;
	usize stack_max_allocated;
	// FIXME: NAME: UNKNOWNTYPE: (pointer - see StartStackMode?)
	void* field_2C;
};
