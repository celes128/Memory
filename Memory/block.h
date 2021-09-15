#pragma once

#include "framework.h"

namespace mem {

	struct block {
		void	*ptr;
		size_t	size;


		block() : ptr(nullptr), size(0)
		{}

		block(const block &other) = delete;
		block & operator=(const block &other) = delete;
		block(const block &&other) = delete;
		block & operator=(const block &&other) = delete;
	};

	Result block_allocate(block *b, size_t Size);
	void block_free(block *b);
}