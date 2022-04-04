#include "pch.h"
#include "CommandProcessorTest_Fixture.h"
using  ::testing::Return;
using  ::testing::_;

void CommandProcessorFixture::SetUp() {
	/*
	CommandProcessor* cmd = new CommandProcessorADD();
	CommandResult CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "15123099", "VXIHXOTH JHOP", "CL3", "010-3112-2609", "19771211", "ADV" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "20080718", "ADV" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "88114052", "NQ LVARW", "CL4", "010-4528-3059", "19911021", "PRO" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "19129568", "SRERLALH HMEF", "CL2", "010-3091-9521", "19640910", "PRO" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "17111236", "VSID TVO", "CL1", "010-3669-1077", "20120718", "PRO" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "18117906", "TWU QSOLT", "CL4", "010-6672-7186", "20030413", "PRO" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "08123556", "WN XV", "CL1", "010-7986-5047", "20100614", "PRO" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "02117175", "SBILHUT LDEXRI", "CL4", "010-2814-1699", "19950704", "ADV" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "03113260", "HH LTUPF", "CL2", "010-5798-5383", "19791018", "PRO" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "14130827", "RPO JK", "CL4", "010-3231-1698", "20090201", "ADV" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "01122329", "DN WD", "CL4", "010-7174-5680", "20071117", "PRO" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "08108827", "RTAH VNUP", "CL4", "010-9031-2726", "19780417", "ADV" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "85125741", "FBAH RTIJ", "CL1", "010-8900-1478", "19780228", "ADV" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "08117441", "BMU MPOSXU", "CL3", "010-2703-3153", "20010215", "ADV" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "10127115", "KBU MHU", "CL3", "010-3284-4054", "19660814", "ADV" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "12117017", "LFIS JJIVL", "CL1", "010-7914-4067", "20120812", "PRO " });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "11125777", "TKOQKIS HC", "CL1", "010-6734-2289", "19991001", "PRO" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "11109136", "QKAHCEX LTODDO", "CL4", "010-2627-8566", "19640130", "PRO" });
	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "05101762", "VCUHLE HMU", "CL4", "010-3988-9289", "20030819", "PRO" });
	*/
}		
void CommandProcessorFixture::TearDown() {
}

TEST_F(CommandProcessorFixture, MODTest1) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<enumOptionList> input_option = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	vector<string> input_empVecStr1 = { "15123099","VXIHXOTH JHOP","CL3","010-3112-2609","19771211","ADV" };
	vector<string> input_empVecStr2 = { "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" };
	vector<string> input_empVecStr3 = { "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "20080718", "ADV" };
	vector<string> input_empVecStr4 = { "88114052", "NQ LVARW", "CL4", "010-4528-3059", "19911021", "PRO" };
	
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times(4).
		WillRepeatedly(Return(true));
	CommandResult CR;
	CR = cmdADD.run(input_option, input_empVecStr1);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr2);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr3);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr4);
	ASSERT_EQ(CR.count, 1);
		
	//TEST #1
	CommandProcessorMOD<MockDatabase> cmdMOD = CommandProcessorMOD<MockDatabase>();
	vector<Employ> list_org, list_mod;
	list_org.push_back(Employ(	{ "15123099","VXIHXOTH JHOP",			"CL3","010-3112-2609","19771211","ADV" }));
	Employ em1_mod = Employ(	{ "15123099","VXIHXOTH JHOP MODIFIED",	"CL3","010-3112-2609","19771211","ADV" });
	list_mod.push_back(em1_mod);
	EXPECT_CALL(MockDatabase::getInstance(), updateItems(_, _, _)).
		Times(1).
		WillOnce(Return(list_mod));
	CR = cmdMOD.run(input_option,  { "name", "VXIHXOTH JHOP", "name", "VXIHXOTH JHOP MODIFIED"});
	CommandResult CR_exp = CommandResult(1, list_mod);
	EXPECT_EQ(CR, CR_exp);
}

TEST_F(CommandProcessorFixture, MODTest2) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<enumOptionList> input_option = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	vector<string> input_empVecStr1 = { "15123099","VXIHXOTH JHOP","CL3","010-3112-2609","19771211","ADV" };
	vector<string> input_empVecStr2 = { "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" };
	vector<string> input_empVecStr3 = { "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "20080718", "ADV" };
	vector<string> input_empVecStr4 = { "88114052", "NQ LVARW", "CL4", "010-4528-3059", "19911021", "PRO" };

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times(4).
		WillRepeatedly(Return(true));
	CommandResult CR;
	CR = cmdADD.run(input_option, input_empVecStr1);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr2);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr3);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr4);
	ASSERT_EQ(CR.count, 1);

	//TEST #2
	CommandProcessorMOD<MockDatabase> cmdMOD = CommandProcessorMOD<MockDatabase>();
	vector<Employ> list_org, list_result;
	list_org.push_back(Employ(	{ "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" }));
	list_org.push_back(Employ(	{ "88114052", "NQ LVARW", "CL4", "010-4528-3059", "19911021", "PRO" }));
	Employ em2_mod = Employ(	{ "17112609", "FB NTAWR", "CL4", "010-1234-5678", "19861203", "PRO" });
	Employ em4_mod = Employ(	{ "88114052", "NQ LVARW", "CL4", "010-1234-5678", "19911021", "PRO" });
	list_result.push_back(em2_mod);
	list_result.push_back(em4_mod);
	EXPECT_CALL(MockDatabase::getInstance(), updateItems(_, _, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdMOD.run(input_option, { "cl", "CL4", "phoneNum", "010-1234-5678" });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}

TEST_F(CommandProcessorFixture, MODTest3) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<enumOptionList> input_option = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	vector<string> input_empVecStr1 = { "15123099","VXIHXOTH JHOP","CL3","010-3112-2609","19771211","ADV" };
	vector<string> input_empVecStr2 = { "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" };
	vector<string> input_empVecStr3 = { "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "20080718", "ADV" };
	vector<string> input_empVecStr4 = { "88114052", "NQ LVARW", "CL4", "010-4528-3059", "19911021", "PRO" };

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times(4).
		WillRepeatedly(Return(true));
	CommandResult CR;
	CR = cmdADD.run(input_option, input_empVecStr1);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr2);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr3);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr4);
	ASSERT_EQ(CR.count, 1);

	//TEST #3
	CommandProcessorMOD<MockDatabase> cmdMOD = CommandProcessorMOD<MockDatabase>();
	vector<Employ> list_org, list_result;
	list_org.push_back(Employ(	{ "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "20080718", "ADV" }));
	Employ em3_mod = Employ(	{ "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "19990123", "ADV" });
	list_result.push_back(em3_mod);
	EXPECT_CALL(MockDatabase::getInstance(), updateItems(_, _, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdMOD.run(input_option, { "phoneNum", "010-4581-2050", "birthday", "19990123" });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}

TEST_F(CommandProcessorFixture, DELTest1) {
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<enumOptionList> input_option = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	vector<string> input_empVecStr1 = { "15123099","VXIHXOTH JHOP","CL3","010-3112-2609","19771211","ADV" };
	vector<string> input_empVecStr2 = { "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" };
	vector<string> input_empVecStr3 = { "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "20080718", "ADV" };
	vector<string> input_empVecStr4 = { "88114052", "NQ LVARW", "CL4", "010-4528-3059", "20080718", "PRO" };
	vector<string> input_empVecStr5 = { "15678901","VXIHXOTH JHOP","CL4","010-1234-5678","20080718","EX" };

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times(5).
		WillRepeatedly(Return(true));
	CommandResult CR;
	CR = cmdADD.run(input_option, input_empVecStr1);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr2);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr3);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr4);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr5);
	ASSERT_EQ(CR.count, 1);

	//DELTest1
	CommandProcessorDEL<MockDatabase> cmdDEL = CommandProcessorDEL<MockDatabase>();
	vector<Employ> list_result;
	list_result.push_back(Employ(input_empVecStr1));
	list_result.push_back(Employ(input_empVecStr5));

	EXPECT_CALL(MockDatabase::getInstance(), deleteItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));

	CR = cmdDEL.run(input_option, { "name", "VXIHXOTH JHOP" });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}


TEST_F(CommandProcessorFixture, DELTest2) {
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<enumOptionList> input_option = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	vector<string> input_empVecStr1 = { "15123099","VXIHXOTH JHOP","CL3","010-3112-2609","19771211","ADV" };
	vector<string> input_empVecStr2 = { "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" };
	vector<string> input_empVecStr3 = { "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "20080718", "ADV" };
	vector<string> input_empVecStr4 = { "88114052", "NQ LVARW", "CL4", "010-4528-3059", "20080718", "PRO" };
	vector<string> input_empVecStr5 = { "15678901","VXIHXOTH JHOP","CL4","010-1234-5678","20080718","EX" };

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times(5).
		WillRepeatedly(Return(true));
	CommandResult CR;
	CR = cmdADD.run(input_option, input_empVecStr1);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr2);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr3);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr4);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr5);
	ASSERT_EQ(CR.count, 1);

	//DELTest2
	CommandProcessorDEL<MockDatabase> cmdDEL = CommandProcessorDEL<MockDatabase>();
	vector<Employ> list_result;
	list_result.push_back(Employ(input_empVecStr2));
	list_result.push_back(Employ(input_empVecStr4));
	list_result.push_back(Employ(input_empVecStr5));

	EXPECT_CALL(MockDatabase::getInstance(), deleteItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));

	CR = cmdDEL.run(input_option, { "cl", "CL4" });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}


TEST_F(CommandProcessorFixture, DELTest3) {
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<enumOptionList> input_option = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	vector<string> input_empVecStr1 = { "15123099","VXIHXOTH JHOP","CL3","010-3112-2609","19771211","ADV" };
	vector<string> input_empVecStr2 = { "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" };
	vector<string> input_empVecStr3 = { "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "20080718", "ADV" };
	vector<string> input_empVecStr4 = { "88114052", "NQ LVARW", "CL4", "010-4528-3059", "20080718", "PRO" };
	vector<string> input_empVecStr5 = { "15678901","VXIHXOTH JHOP","CL4","010-1234-5678","20080718","EX" };

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times(5).
		WillRepeatedly(Return(true));
	CommandResult CR;
	CR = cmdADD.run(input_option, input_empVecStr1);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr2);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr3);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr4);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr5);
	ASSERT_EQ(CR.count, 1);

	//DELTest3
	CommandProcessorDEL<MockDatabase> cmdDEL = CommandProcessorDEL<MockDatabase>();
	vector<Employ> list_result;
	list_result.push_back(Employ(input_empVecStr3));
	list_result.push_back(Employ(input_empVecStr4));
	list_result.push_back(Employ(input_empVecStr5));

	EXPECT_CALL(MockDatabase::getInstance(), deleteItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));

	CR = cmdDEL.run(input_option, { "birthday", "20080718" });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}
