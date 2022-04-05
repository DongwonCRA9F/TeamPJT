#include "pch.h"
#include "CommandProcessorTest_Fixture.h"
using  ::testing::Return;
using  ::testing::_;

TEST_F(CommandProcessorFixture, ADDTest_기본테스트) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times(1).
		WillRepeatedly(Return(true));

	vector<enumOptionList> input1_1 = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	vector<string> input1_2 = { "15123099","VXIHXOTH JHOP","CL3","010-3112-2609","19771211","ADV" };
	Employ em_input = Employ(input1_2);

	CommandResult CR = cmdADD.run(input1_1, input1_2);
	EXPECT_EQ(CR.count, 1);
}
TEST_F(CommandProcessorFixture, ADDTest_NULL정보허용안함) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>> input_NG_List;
	input_NG_List.push_back({ "",			"VXIHXOTH JHOP","CL3",	"010-3112-2609","19771211",	"ADV" });
	input_NG_List.push_back({ "15123099",	"VXIHXOTH JHOP","",		"010-3112-2609","19771211",	"ADV" });
	input_NG_List.push_back({ "15123099",	"VXIHXOTH JHOP","CL3",	"",				"19771211",	"ADV" });
	input_NG_List.push_back({ "15123099",	"",				"CL3",	"010-3112-2609","19771211",	"ADV" });
	input_NG_List.push_back({ "15123099",	"VXIHXOTH JHOP","CL3",	"010-3112-2609","",			"ADV" });
	input_NG_List.push_back({ "15123099",	"VXIHXOTH JHOP","CL3",	"010-3112-2609","19771211",	""    });
	for (vector<string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, ADDTest_사원번호) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>> input_OK_List;
	vector<vector<string>> input_NG_List;
	input_OK_List.push_back({ "05123099",	"VXIHXOTH JHOP","CL3",	"010-3112-2609","19771211",	"ADV" }); //OK: 입사연도 0_년이 잘 처리되는지 확인
	input_NG_List.push_back({ "1512309",	"VXIHXOTH JHOP","CL3",	"010-3112-2609","19771211",	"ADV" });
	input_NG_List.push_back({ "151230999",	"VXIHXOTH JHOP","CL3",	"010-3112-2609","19771211",	"ADV" });
	input_NG_List.push_back({ "1512309A",	"VXIHXOTH JHOP","CL3",	"010-3112-2609","19771211",	"ADV" });
	input_NG_List.push_back({ "15z23099",	"VXIHXOTH JHOP","CL3",	"010-3112-2609","19771211",	"ADV" });
	input_NG_List.push_back({ "68123099",	"VXIHXOTH JHOP","CL3",	"010-3112-2609","19771211",	"ADV" });
	input_NG_List.push_back({ "22123099",	"VXIHXOTH JHOP","CL3",	"010-3112-2609","19771211",	"ADV" });

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_OK_List.size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> input_OK : input_OK_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_OK);
		EXPECT_EQ(CR.count, 1);
	}
	for (vector<string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, ADDTest_성명) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>> input_OK_List;
	vector<vector<string>> input_NG_List;
	input_OK_List.push_back(	{ "15123099",	"SUNG MYEONG",			"CL3",	"010-3112-2609","19771211",	"ADV" }); //OK
	input_NG_List.push_back(	{ "15123099",	"SUNGG MYEONGGGGGG",	"CL3",	"010-3112-2609","19771211",	"ADV" }); //15자 초과(5 + 11 = 16)
	input_NG_List.push_back(	{ "15123099",	"SUNG MIDDLE MYEONG ",	"CL3",	"010-3112-2609","19771211",	"ADV" }); //띄어쓰기 2개
	input_NG_List.push_back(	{ "15123099",	"SUNGMYEONG",			"CL3",	"010-3112-2609","19771211",	"ADV" }); //띄어쓰기 없음
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG1",			"CL3",	"010-3112-2609","19771211",	"ADV" }); //숫자 포함 (이름)
	input_NG_List.push_back(	{ "15123099",	"SUNG2 MYEONG",			"CL3",	"010-3112-2609","19771211",	"ADV" }); //숫자 포함 (성)
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG!",			"CL3",	"010-3112-2609","19771211",	"ADV" }); //특수문자 포함 (이름)
	input_NG_List.push_back(	{ "15123099",	"SUNG? MYEONG",			"CL3",	"010-3112-2609","19771211",	"ADV" }); //특수문자 포함 (성)
	input_NG_List.push_back(	{ "15123099",	" SUNG MYEONG",			"CL3",	"010-3112-2609","19771211",	"ADV" }); //공백문자로 시작
	input_NG_List.push_back(	{ "15123099",	"SUNG_MYEONG",			"CL3",	"010-3112-2609","19771211",	"ADV" }); //특수문자 포함 (_)

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_OK_List.size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> input_OK : input_OK_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_OK);
		EXPECT_EQ(CR.count, 1);
	}
	for (vector<string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, ADDTest_경력개발단계) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>> input_OK_List;
	vector<vector<string>> input_NG_List;

	input_OK_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609","19771211",	"ADV" }); //OK
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL5",	"010-3112-2609","19771211",	"ADV" }); //숫자 이상 : CL5
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL0",	"010-3112-2609","19771211",	"ADV" }); //숫자 이상 : CL0
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL?",	"010-3112-2609","19771211",	"ADV" }); //숫자 이상 : CL?
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"GL3",	"010-3112-2609","19771211",	"ADV" }); //CL 이상 : GL
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL 3",	"010-3112-2609","19771211",	"ADV" }); //띄어쓰기
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"cl3",	"010-3112-2609","19771211",	"ADV" }); //소문자

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_OK_List.size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> input_OK : input_OK_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_OK);
		EXPECT_EQ(CR.count, 1);
	}
	EXPECT_EQ(CR.count, 1);
	for (vector<string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, ADDTest_전화번호) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>> input_OK_List;
	vector<vector<string>> input_NG_List;

	input_OK_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19771211",	"ADV" });//OK
	input_OK_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-0112-2609",	"19771211",	"ADV" });//OK:0으로 시작 (middle)
	input_OK_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-0112-0609",	"19771211",	"ADV" });//OK:0으로 시작 (last)
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"ADV" });//형식 이상 (middle 3자리)
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-260",		"19771211",	"ADV" });//형식 이상 (last 3자리)
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-31122-2609",	"19771211",	"ADV" });//형식 이상 (middle 5자리)
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-26092",	"19771211",	"ADV" });//형식 이상 (last 5자리)
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"011-3112-2609",	"19771211",	"ADV" });//010 아님
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"017-3112-2609",	"19771211",	"ADV" });//010 아님
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"810-3112-2609",	"19771211",	"ADV" });//010 아님
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-31A2-2609",	"19771211",	"ADV" });//숫자 아님
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2B09",	"19771211",	"ADV" });//숫자 아님
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-31?2-2609",	"19771211",	"ADV" });//숫자 아님
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-!609",	"19771211",	"ADV" });//숫자 아님
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"O10-3112-2609",	"19771211",	"ADV" });//숫자 0 대신 다른 문자: 영어 O
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-26O9",	"19771211",	"ADV" });//숫자 0 대신 다른 문자: 영어 O
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010=3112-2609",	"19771211",	"ADV" });//-대신 다른 문자
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112_2609",	"19771211",	"ADV" });//-대신 다른 문자
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609-1234","19771211","ADV" });//형식이상 : - 3개
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112",			"19771211",	"ADV" });//형식이상 : - 1개
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"010-31122609",		"19771211",	"ADV" });//형식이상 : - 1개
	input_NG_List.push_back(	{ "15123099",	"SUNG MYEONG",	"CL3",	"01031122609",		"19771211",	"ADV" });//형식이상 : - 0개

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_OK_List.size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> input_OK : input_OK_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_OK);
		EXPECT_EQ(CR.count, 1);
	}
	for (vector<string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, ADDTest_생년월일) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>> input_OK_List;
	vector<vector<string>> input_NG_List;

	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19771211",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19770101",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19771201",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19770131",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19770229",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19770331",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19770430",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19770531",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19770630",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19770731",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19770831",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19770930",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19771031",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19771130",		"ADV" });
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19771231",		"ADV" });
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"771211",		"ADV" });//형식 이상 (yymmdd)
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"00771211",		"ADV" });//형식 이상 (00yymmdd)
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"1977aa11",		"ADV" });//NG
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"197712BB",		"ADV" });//NG
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19??1211",		"ADV" });//NG
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"1977-12-11",	"ADV" });//NG
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"1977/12/11",	"ADV" });//NG
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"12111977",		"ADV" });//NG (DDMMYYYY)


	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_OK_List.size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> input_OK : input_OK_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_OK);
		EXPECT_EQ(CR.count, 1);
	}
	for (vector<string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, ADDTest_CERTI) {
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>> input_OK_List;
	vector<vector<string>> input_NG_List;

	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19771211",	"ADV"	});
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19771211",	"PRO"	});
	input_OK_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-3112-2609",	"19771211",	"EX"	});

	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"ADVANCED"	});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"PROFESSIONAL"	});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"EXPERT"	});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"adv"		});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"pro"		});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"ex"		});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"A"			});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"P"			});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"E"			});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"A?V"		});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"P/o"		});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"EXP"		});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"ADV "		});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	" PRO"		});
	input_NG_List.push_back({ "15123099",	"SUNG MYEONG",	"CL3",	"010-311-2609",		"19771211",	"E X"		});

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_OK_List.size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> input_OK : input_OK_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_OK);
		EXPECT_EQ(CR.count, 1);
	}
	for (vector<string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, input_NG), invalid_argument);
	}
}
