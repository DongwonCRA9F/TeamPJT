#include "pch.h"
#include "CommandProcessorTest_Fixture.h"
using  ::testing::Return;
using  ::testing::_;

void CommandProcessorFixture::SetUp() {
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
	list_org.push_back(Employ(	{ "15123099","VXIHXOTH JHOP",		"CL3","010-3112-2609","19771211","ADV" }));
	Employ em1_mod = Employ(	{ "15123099","VXIHXOTH JHOPMOD",	"CL3","010-3112-2609","19771211","ADV" });
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


TEST_F(CommandProcessorFixture, DELgreaterthan5) {
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<enumOptionList> input_option = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	vector<string> input_empVecStr1 = { "15123099","VXIHXOTH JHOP","CL3","010-3112-2609","19771211","ADV" };
	vector<string> input_empVecStr2 = { "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" };
	vector<string> input_empVecStr3 = { "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "20080718", "ADV" };
	vector<string> input_empVecStr4 = { "88114052", "NQ LVARW", "CL4", "010-4528-3059", "20080718", "PRO" };
	vector<string> input_empVecStr5 = { "99115601","VXIHXOTH JHOP","CL4","010-1234-5678","20080718","EX" };
	vector<string> input_empVecStr6 = { "16678201","VXIHXOTH HBO","CL4","010-1234-5678","20080718","PRO" };
	vector<string> input_empVecStr7 = { "12625901","LVARW JHOP","CL4","010-1234-5678","20080718","PRO" };
	vector<string> input_empVecStr8 = { "06688301","NTAWR JHOP","CL4","010-1234-5678","20080718","EX" };

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times(8).
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
	CR = cmdADD.run(input_option, input_empVecStr6);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr7);
	ASSERT_EQ(CR.count, 1);
	CR = cmdADD.run(input_option, input_empVecStr8);
	ASSERT_EQ(CR.count, 1);

	//DELgreaterthan5
	CommandProcessorDEL<MockDatabase> cmdDEL = CommandProcessorDEL<MockDatabase>();
	vector<Employ> sorted_result;
	sorted_result.push_back(Employ(input_empVecStr4));
	sorted_result.push_back(Employ(input_empVecStr5));
	sorted_result.push_back(Employ(input_empVecStr8));
	sorted_result.push_back(Employ(input_empVecStr7));
	sorted_result.push_back(Employ(input_empVecStr6));

	vector<Employ> raw_result;
	raw_result.push_back(Employ(input_empVecStr3));
	raw_result.push_back(Employ(input_empVecStr4));
	raw_result.push_back(Employ(input_empVecStr5));
	raw_result.push_back(Employ(input_empVecStr6));
	raw_result.push_back(Employ(input_empVecStr7));
	raw_result.push_back(Employ(input_empVecStr8));

	EXPECT_CALL(MockDatabase::getInstance(), deleteItems(_, _)).
		Times(1).
		WillOnce(Return(raw_result));

	CR = cmdDEL.run(input_option, { "birthday", "20080718" });
	CommandResult CR_exp = CommandResult((int)sorted_result.size(), sorted_result);
	vector<Employ> CR_sorted = CR.getDetailResults();
	ASSERT_EQ(CR_sorted.size(), CR_exp.list.size());

	for (int i = 0; i < CR_exp.list.size(); ++i) {
		EXPECT_EQ(CR_sorted[i], CR_exp.list[i]);
	}
}