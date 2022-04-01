#include "pch.h"
#include "employManagerTest_Fixture.h"
#include "../EmpManager/employManager.h"

void EmployManagerFixture::SetUp() {
	makeSampleEmpList();
	makeSampleOutList();
}

void EmployManagerFixture::TearDown() {
}

void EmployManagerFixture::makeSampleEmpList() {
}

void EmployManagerFixture::makeSampleOutList() {
}

TEST_F(EmployManagerFixture, empListTostrListTest) 
{
	EXPECT_EQ(sampleOutList, empManager.empListTostrList(sampleEmpList));
}