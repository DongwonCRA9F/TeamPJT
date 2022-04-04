#include "pch.h"
#include "CommandProcessorTest_Fixture.h"
using  ::testing::Return;
using  ::testing::_;


TEST_F(CommandProcessorFixture, SCHTest1) {
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

	//SCHTest1
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	list_result.push_back(Employ(input_empVecStr1));
	list_result.push_back(Employ(input_empVecStr5));

	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));

	CR = cmdSCH.run(input_option, { "name", "VXIHXOTH JHOP" });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}

TEST_F(CommandProcessorFixture, SCHTest2) {
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

	//SCHTest2
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	list_result.push_back(Employ(input_empVecStr1));
	list_result.push_back(Employ(input_empVecStr2));
	list_result.push_back(Employ(input_empVecStr4));
	list_result.push_back(Employ(input_empVecStr5));

	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));

	CR = cmdSCH.run(input_option, { "cl", "CL4" });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}

TEST_F(CommandProcessorFixture, SCHTest3) {
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

	//SCHTest3
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	list_result.push_back(Employ(input_empVecStr3));
	list_result.push_back(Employ(input_empVecStr4));
	list_result.push_back(Employ(input_empVecStr5));

	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));

	CR = cmdSCH.run(input_option, { "birthday", "20080718" });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}