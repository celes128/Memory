#include "pch.h"
#include "block.h"

#include <cstdlib>
#include <cassert>

namespace mem {

	Result block_allocate(block *b, size_t Size)
	{
		assert(b);
		assert(Size != 0);

		auto p = malloc(Size);
		if (p) {
			b->ptr = p;
			b->size = Size;
			return kSuccess;
		}
		else {
			b->ptr = nullptr;
			b->size = 0;
			return kFailure;
		}
	}

	void block_free(block *b)
	{
		assert(b);

		if (b->ptr) {
			free(b->ptr);
			b->ptr = nullptr;
			b->size = 0;
		}
	}
}