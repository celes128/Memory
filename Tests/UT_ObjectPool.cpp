#include "pch.h"
#include "CppUnitTest.h"

#include "../Memory/ObjectPool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	struct vec2 {
		int x, y;
	};

	TEST_CLASS(ObjectPool) {
	public:
		TEST_METHOD(ObjectPool_1)
		{
			mem::ObjectPool<vec2> pool;

			const size_t kCount = 3;

			auto error = pool.Create(kCount);

			Assert::IsTrue(error == 0, L"1");

			vec2 *pv[kCount];
			for (size_t i = 0; i < kCount; i++) {
				error = pool.AllocOneElement(&pv[i]);
				Assert::IsTrue(error == 0, L"2");

				pv[i]->x = i;
				pv[i]->y = i;
			}

			for (size_t i = 0; i < kCount; i++) {
				Assert::IsTrue(pv[i]->x == i, L"3a");
				Assert::IsTrue(pv[i]->y == i, L"3b");
			}			

			vec2 *p = nullptr;
			error = pool.AllocOneElement(&p);
			Assert::IsTrue(error, L"4");

			pool.FreeOneElement(&pv[1]);

			error = pool.AllocOneElement(&pv[1]);
			Assert::IsTrue(error == 0, L"5");

			pv[1]->x = 9;
			pv[1]->y = 11;

			Assert::IsTrue(pv[0]->x == 0, L"6ax");
			Assert::IsTrue(pv[0]->y == 0, L"6ay");
			Assert::IsTrue(pv[1]->x == 9, L"6bx");
			Assert::IsTrue(pv[1]->y == 11, L"6by");
			Assert::IsTrue(pv[2]->x == 2, L"6cx");
			Assert::IsTrue(pv[2]->y == 2, L"6cy");

			pool.Destroy();
		}
	};
}
