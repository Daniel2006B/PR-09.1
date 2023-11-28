#include "pch.h"
#include "CppUnitTest.h"
#include "../PR-09.1/PR-09.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest091
{
	TEST_CLASS(UnitTest091)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			const int N = 4;
			Student* p = new Student[N];

			int result = LineSearchGoodMarks(p, N);
			
			cout << "Кількість студентів: " << N << endl;
			for (int i = 0; i < N; i++) {
				cout << "Студент " << i + 1 << ": " << p[i].prizv << ", Оцінка1: " << p[i].mark1 << ", Оцінка2: " << p[i].mark2 << endl;
			}
			Assert::AreEqual(result, 0); 
			delete[] p;

		}
	};
}
