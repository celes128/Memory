#include "pch.h"
#include "CppUnitTest.h"

#include "../Memory/block.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Block) {
	public:		
		TEST_METHOD(block_alloc_free)
		{
			mem::block block;

			Assert::IsTrue(block.ptr == nullptr, L"1a");
			Assert::IsTrue(block.size == 0, L"1b");

			const size_t kSize = 256;
			auto result = mem::block_allocate(&block, kSize);

			if (ok(result)) {
				Assert::IsTrue(block.ptr != nullptr, L"2a");
				Assert::IsTrue(block.size == kSize, L"2b");

				mem::block_free(&block);
				Assert::IsTrue(block.ptr == nullptr, L"3a");
				Assert::IsTrue(block.size == 0, L"3b");
			}
		}
	};
}
