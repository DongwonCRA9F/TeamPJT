#include "pch.h"
#include "employManagerTest_Fixture.h"
#include "../EmpManager/employManager.h"

void EmployManagerFixture::SetUp() {
	makeSampleEmpList();
	makeSampleOutList();

	empManager.cmdProcessor = new CommandProcessor();
}

void EmployManagerFixture::TearDown() {
}

void EmployManagerFixture::makeSampleEmpList() {
}

void EmployManagerFixture::makeSampleOutList() {
}

TEST_F(EmployManagerFixture, empNumTostrTest)
{
	EXPECT_EQ("00428511", empManager.empNumTostr(428511));
	EXPECT_EQ("09204567", empManager.empNumTostr(9204567));
	EXPECT_EQ("20428511", empManager.empNumTostr(20428511));
}

TEST_F(EmployManagerFixture, cmdResultTostrListTest)
{
	vector<string> emptyList;
	Name name{ "VXIHXOTH JHOP" };
	PhoneNumber phoneNum{ "010-3112-2609" };
	Birthday birthday{ "19771211" };
	sampleCmdResult.list.push_back(Employ{ 15123099 , name, enumCL::CL3 , phoneNum, birthday, enumCerti::ADV });
	sampleCmdResult.count = 1;
	sampleOutList.push_back("SCH,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");

	EXPECT_EQ(sampleOutList, empManager.cmdResultTostrList(enumCommandList::SCH, sampleCmdResult));

	sampleCmdResult.list.pop_back();
	sampleCmdResult.count = 0;
	sampleOutList.pop_back();
	sampleOutList.push_back("SCH,NONE");
	EXPECT_EQ(sampleOutList, empManager.cmdResultTostrList(enumCommandList::SCH, sampleCmdResult));
}

TEST_F(EmployManagerFixture, runAddTest)
{
	vector<string> emptyList;
	EXPECT_CALL(*(empManager.cmdProcessor), run(_, _)).Times(1).WillOnce(Return(CommandResult(0, { Employ{} })));
	EXPECT_EQ(emptyList, empManager.runCommand("ADD, , , ,18117906,TWU QSOLT,CL4,010-6672-7186,20030413,PRO"));
}

TEST_F(EmployManagerFixture, runDelNoOptionTest)
{
	sampleOutList.push_back("DEL,1");

	Name name{ "VXIHXOTH JHOP" };
	PhoneNumber phoneNum{ "010-3112-2609" };
	Birthday birthday{ "19771211" };
	EXPECT_CALL(*(empManager.cmdProcessor), run(_, _)).Times(1).WillOnce(Return(CommandResult(1, { Employ{ 15123099 , name, enumCL::CL2 , phoneNum, birthday, enumCerti::ADV } })));

	EXPECT_EQ(sampleOutList, empManager.runCommand("DEL, , , ,employeeNum,15123099"));
}

TEST_F(EmployManagerFixture, runDelOptionTest)
{
	sampleOutList.push_back("DEL,18117441,BMU MPOSXU,CL3,010-2703-3153,20011215,ADV");

	Name name{ "BMU MPOSXU" };
	PhoneNumber phoneNum{ "010-2703-3153" };
	Birthday birthday{ "20011215" };

	EXPECT_CALL(*(empManager.cmdProcessor), run(_, _)).Times(1).WillOnce(Return(CommandResult(1, { Employ{ 18117441 , name, enumCL::CL3 , phoneNum, birthday, enumCerti::ADV } })));
	EXPECT_EQ(sampleOutList, empManager.runCommand("DEL,-p,-l, ,name,MPOSXU"));
}

TEST_F(EmployManagerFixture, runSchNoOptionTest)
{
	sampleOutList.push_back("SCH,1");

	Name name{ "DN WD" };
	PhoneNumber phoneNum{ "010-7174-5680" };
	Birthday birthday{ "20071117" };

	EXPECT_CALL(*(empManager.cmdProcessor), run(_, _)).Times(1).WillOnce(Return(CommandResult(1, { Employ{ 11122329 , name, enumCL::CL4 , phoneNum, birthday, enumCerti::PRO } })));

	EXPECT_EQ(sampleOutList, empManager.runCommand("SCH, , , ,certi,PRO"));
}

TEST_F(EmployManagerFixture, runSchOptionTest)
{
	sampleOutList.push_back("SCH,88114052,NQ LVARW,CL4,010-4528-3059,19911021,PRO");

	Name name{ "NQ LVARW" };
	PhoneNumber phoneNum{ "010-4528-3059" };
	Birthday birthday{ "19911021" };

	EXPECT_CALL(*(empManager.cmdProcessor), run(_, _)).Times(1).WillOnce(Return(CommandResult(1, { Employ{ 88114052 , name, enumCL::CL4 , phoneNum, birthday, enumCerti::PRO } })));

	EXPECT_EQ(sampleOutList, empManager.runCommand("SCH,-p, , ,certi,PRO"));
}

TEST_F(EmployManagerFixture, runModNoOptionTest)
{
	sampleOutList.push_back("MOD,1");
	Name name{ "NQ LVARW" };
	PhoneNumber phoneNum{ "010-4528-3059" };
	Birthday birthday{ "19911021" };

	EXPECT_CALL(*(empManager.cmdProcessor), run(_, _)).Times(1).WillOnce(Return(CommandResult(1, { Employ{ 88114052 , name, enumCL::CL4 , phoneNum, birthday, enumCerti::PRO } })));

	EXPECT_EQ(sampleOutList, empManager.runCommand("MOD, , , ,name,NQ LVARW,birthday,19911021"));
}

TEST_F(EmployManagerFixture, runModOptionTest)
{
	sampleOutList.push_back("MOD,17112609,NQ LVARW,CL4,010-5645-6122,19861023,PRO");

	Name name{ "NQ LVARW" };
	PhoneNumber phoneNum{ "010-5645-6122" };
	Birthday birthday{ "19861023" };

	EXPECT_CALL(*(empManager.cmdProcessor), run(_, _)).Times(1).WillOnce(Return(CommandResult(1, { Employ{ 17112609 , name, enumCL::CL4 , phoneNum, birthday, enumCerti::PRO } })));

	EXPECT_EQ(sampleOutList, empManager.runCommand("MOD,-p, , ,name,NQ LVARW,birthday,19861023"));
}
