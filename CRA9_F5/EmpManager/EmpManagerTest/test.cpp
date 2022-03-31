#include "pch.h"

#include "../../EmpManager/EmpManager/SampleClass.h"


TEST(TestCaseName, TestName) {
	SampleClass a;

	EXPECT_EQ(a.Add(1, 2), 3);
}