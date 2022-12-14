#pragma once
#include <array>

#include "common/types.h"

// Is this what DC2 does to convert sizes to memory alloc sizes?
#define BYTES_TO_BLOCKS(size) \
	(size + 0x2F) / 0x10
#define BYTES_TO_BLOCKS_STRICT(size) \
	size / 0x10 + 1


struct SHeapMemHead
{
	// FIXME: NAME:
	void* field_0;
	// FIXME: NAME: UNKNOWNTYPE:
	u32 field_4;
	// FIXME: NAME: UNKNOWNTYPE:
	u32 field_8;
	// FIXME: NAME:
	SHeapMemHead* field_C;
};

/**
 * A mgCMemory is a stack of 0x10-sized blocks.
 */
class mgCMemory
{
public:
	// 00139930
	void SetHeapMem(void *heap, usize heap_size);

	// 001399D0
	void ClearHeapMem();

	// 00139AA0
	// FIXME: NAME: arguments (and specific numeric types?)
	void* StartStackMode(int i1, int i2);

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
	void stAlign64();

	// 00139E00
	// See stAlign64
	void Align64();

	// 00139E70
	// Sets the buffer for this memory.
	void stSetBuffer(void* stack_start, usize capacity);

	// Debug representation of the purpose of this memory.
	std::array<char, 0x10> m_label{ 0 };
	usize m_heap_size{ 0 };
	void* m_heap_start{ nullptr };
	SHeapMemHead* m_heap_mem_head{ nullptr };
	// FIXME: NAME:
	bool m_unk_field_1C{ false };
	void* m_stack_start{ nullptr };
	usize m_stack_current_allocated{ 0 };
	usize m_stack_max_allocated{ 0 };
	// FIXME: NAME:
	SHeapMemHead* m_unk_field_2C{ nullptr };
};
