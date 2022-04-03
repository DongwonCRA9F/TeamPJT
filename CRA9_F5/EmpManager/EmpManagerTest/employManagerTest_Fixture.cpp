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

TEST_F(EmployManagerFixture, cmdResultTostrListTest)
{
	vector<string> emptyList;
	Name name{ "VXIHXOTH JHOP" };
	PhoneNumber phoneNum{ "010-3112-2609" };
	Birthday birthday{ "19771211" };
	sampleCmdResult.list.push_back(Employ{ 15123099 , name, enumCL::CL2 , phoneNum, birthday, enumCerti::ADV });
	sampleCmdResult.count = 1;
	sampleOutList.push_back("SCH,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");

	EXPECT_EQ(sampleOutList, empManager.cmdResultTostrList("SCH", sampleCmdResult));
	EXPECT_EQ(emptyList, empManager.cmdResultTostrList("ADD", sampleCmdResult));
}

TEST_F(EmployManagerFixture, runAddTest)
{
	// ADD의 경우 빈 string vector 반환
	vector<string> emptyList;
	EXPECT_EQ(emptyList, empManager.runCommand("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV"));
}

TEST_F(EmployManagerFixture, runDelNoOptionTest)
{
	sampleOutList.push_back("DEL,1");
	EXPECT_EQ(sampleOutList, empManager.runCommand("DEL, , , ,employeeNum,18115040"));
}

TEST_F(EmployManagerFixture, runDelOptionTest)
{
	sampleOutList.push_back("DEL,08117441,BMU MPOSXU,CL3,010-2703-3153,20010215,ADV");
	EXPECT_EQ(sampleOutList, empManager.runCommand("DEL,-p,-l, ,name,MPOSXU"));
}

TEST_F(EmployManagerFixture, runSchNoOptionTest)
{
	sampleOutList.push_back("SCH,01122329,DN WD,CL4,010-7174-5680,20071117,PRO");
	EXPECT_EQ(sampleOutList, empManager.runCommand("SCH, , , ,certi,ADV"));
}

TEST_F(EmployManagerFixture, runSchOptionTest)
{
	sampleOutList.push_back("SCH,88114052,NQ LVARW,CL4,010-4528-3059,19911021,PRO");
	EXPECT_EQ(sampleOutList, empManager.runCommand("SCH,-p, , ,certi,PRO"));
}

TEST_F(EmployManagerFixture, runModNoOptionTest)
{
	sampleOutList.push_back("MOD,1");
	EXPECT_EQ(sampleOutList, empManager.runCommand("MOD, , , ,name,VCUHLE HMU,birthday,19910808"));
}

TEST_F(EmployManagerFixture, runModOptionTest)
{
	sampleOutList.push_back("MOD,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO");
	EXPECT_EQ(sampleOutList, empManager.runCommand("MOD,-p, , ,name,FB NTAWR,birthday,20050520"));
}
