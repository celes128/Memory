#include "pch.h"
#include "block.h"

#include <cstdlib>

#include <cassert>

namespace mem {

	int	block_allocate(block *b, size_t Size)
	{
		assert(b != nullptr);
		assert(Size != 0);

		auto p = malloc(Size);
		if (p) {
			b->ptr = p;
			b->size = Size;
			return 0;// success
		}
		else {
			b->ptr = nullptr;
			b->size = 0;
			return -1;// failure
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