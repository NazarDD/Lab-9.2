#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab 9.2/Lab 9.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YourProjectTests
{
    TEST_CLASS(StudentFunctionsTest)
    {
    public:
        TEST_METHOD(TestCalculatePercentageWith45PhysicsGrade)
        {
            const int N = 3;
            Student* students = new Student[N];
            students[0] = { 1, "Smith", 2, PC_Science, 4, 5, { 4 } };
            students[1] = { 2, "Johnson", 3, IT, 5, 4, { 5 } };
            students[2] = { 3, "Williams", 1, Math_Economic, 3, 3, { 4 } };

            double result = CalculatePercentageWith45PhysicsGrade(students, N);
            double expected = 66.66666;

            Assert::AreEqual(result, expected, 0.01);
        }

        TEST_METHOD(TestSortStudents)
        {
            const int N = 3;
            Student* students = new Student[N];
            students[0] = { 1, "Smith", 2, PC_Science, 4, 5, { 4 } };
            students[1] = { 2, "Johnson", 3, IT, 5, 4, { 5 } };
            students[2] = { 3, "Williams", 1, Math_Economic, 3, 3, { 4 } };

            SortStudents(students, N);

            Assert::IsTrue(students[0].Sort_Number <= students[1].Sort_Number);
            Assert::IsTrue(students[1].Sort_Number <= students[2].Sort_Number);
        }

        TEST_METHOD(TestBuildIndexArray)
        {
            const int N = 3;
            Student* students = new Student[N];
            students[0] = { 1, "Smith", 2, PC_Science, 4, 5, { 4 } };
            students[1] = { 2, "Johnson", 3, IT, 5, 4, { 5 } };
            students[2] = { 3, "Williams", 1, Math_Economic, 3, 3, { 4 } };

            int* indexArray = new int[N];
            BuildIndexArray(students, N, indexArray);

            Assert::AreEqual(indexArray[0], 0);
            Assert::AreEqual(indexArray[1], 1);
            Assert::AreEqual(indexArray[2], 2);
        }

    };
}
