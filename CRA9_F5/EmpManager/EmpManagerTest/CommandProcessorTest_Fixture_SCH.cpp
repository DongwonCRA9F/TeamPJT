#include "pch.h"
#include "CommandProcessorTest_Fixture.h"
using  ::testing::Return;
using  ::testing::_;

vector<vector<string>>* makeInputVector() {
	vector<vector<string>>* input_ADD_List = new vector<vector<string>>();
	input_ADD_List->push_back({ "15123099", "VXIHXOTH JHOP", "CL3", "010-3112-2609", "19771211", "ADV" });
	input_ADD_List->push_back({ "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" });
	input_ADD_List->push_back({ "18115040", "TTETHU HBO", "CL3", "010-4581-2050", "20080718", "ADV" });
	input_ADD_List->push_back({ "88114052", "NQ LVARW", "CL4", "010-4528-3059", "19911021", "PRO" });
	input_ADD_List->push_back({ "19129568", "SRERLALH HMEF", "CL2", "010-3091-9521", "19640910", "PRO" });
	input_ADD_List->push_back({ "17111236", "VSID TVO", "CL1", "010-3669-1077", "20120718", "PRO" });
	input_ADD_List->push_back({ "18117906", "TWU QSOLT", "CL4", "010-6672-7186", "20030413", "PRO" });
	input_ADD_List->push_back({ "08123556", "WN XV", "CL1", "010-7986-5047", "20100614", "PRO" });
	input_ADD_List->push_back({ "02117175", "SBILHUT LDEXRI", "CL4", "010-2814-1699", "19950704", "ADV" });
	input_ADD_List->push_back({ "03113260", "HH LTUPF", "CL2", "010-5798-5383", "19791018", "PRO" });
	input_ADD_List->push_back({ "14130827", "RPO JK", "CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "01122329", "DN WD", "CL4", "010-7174-5680", "20071117", "PRO" });
	input_ADD_List->push_back({ "08108827", "RTAH VNUP", "CL4", "010-9031-2726", "19780417", "ADV" });
	input_ADD_List->push_back({ "85125741", "FBAH RTIJ", "CL1", "010-8900-1478", "19780228", "ADV" });
	input_ADD_List->push_back({ "08117441", "BMU MPOSXU", "CL3", "010-2703-3153", "20010215", "ADV" });
	input_ADD_List->push_back({ "10127115", "KBU MHU", "CL3", "010-3284-4054", "19660814", "ADV" });
	input_ADD_List->push_back({ "12117017", "LFIS JJIVL", "CL1", "010-7914-4067", "20120812", "PRO " });
	input_ADD_List->push_back({ "11125777", "TKOQKIS HC", "CL1", "010-6734-2289", "19991001", "PRO" });
	input_ADD_List->push_back({ "11109136", "QKAHCEX LTODDO", "CL4", "010-2627-8566", "19640130", "PRO" });
	input_ADD_List->push_back({ "05101762", "VCUHLE HMU", "CL4", "010-3988-9289", "20030819", "PRO" });
	return input_ADD_List;
}

TEST_F(CommandProcessorFixture, SCHTest_사원번호) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "employNum";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}
	
	//SCHTest_OK
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	const string searchStr_OK = "03113260";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == searchStr_OK)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, searchStr_OK });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
	EXPECT_EQ((int)list_result.size(), 1); //result가 1개 이어야 함.(employNum은 키값으로 유니크함), 0이 되는 경우도 있지만 해당 테스트에서는 1

	//SCHTest_NG
	vector<vector<string>> input_NG_List;
	input_NG_List.push_back({ SEARCH_COLUMN, "0311326" });//NG: 7자리
	input_NG_List.push_back({ SEARCH_COLUMN, "031132600" });//NG: 9자리
	input_NG_List.push_back({ SEARCH_COLUMN, "1512309A" });//NG: A
	input_NG_List.push_back({ SEARCH_COLUMN, "15z23099" });//NG: z
	input_NG_List.push_back({ SEARCH_COLUMN, "68123099" });//NG: 입사연도
	input_NG_List.push_back({ SEARCH_COLUMN, "22123099" });//NG: 입사연도
	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_성명_noOption) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "name";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	const string SEARCH_STR_OK = "WN XV";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_OK)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_OK });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_NG
	vector<vector<string>> input_NG_List;
	input_NG_List.push_back({ SEARCH_COLUMN, "WNNNN XVVVVVVVVVV"});//15자 초과(5 + 11 = 16)
	input_NG_List.push_back({ SEARCH_COLUMN, "WN MIDDLE XV"		});//띄어쓰기 2개
	input_NG_List.push_back({ SEARCH_COLUMN, "WNXV"				});//띄어쓰기 없음
	input_NG_List.push_back({ SEARCH_COLUMN, " WN XV"			});//공백문자로 시작
	input_NG_List.push_back({ SEARCH_COLUMN, "WN XV1"			});//숫자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "WN2 XV"			});//숫자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "WN XV!"			});//특수문자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "WN? XV"			});//특수문자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "WN_XV"			});//특수문자 포함

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_성명_Option1) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "name";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "08123557", "WN XV", "CL1", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "18123557", "WN XV", "CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "78123558", "WN XV", "CL3", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "88123559", "WN XV", "CL4", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "98123559", "WN XVV" "CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "09123559", "WNN XV","CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "21123559", "WN XV", "CL2", "010-7986-5047", "20100614", "EX" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "20123559", "WN XV", "CL2", "010-7986-5047", "20100614", "ADV" }); //테스트를 위해 추가함.
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	const string SEARCH_STR_OK = "WN XV";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_OK)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_OK });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}
TEST_F(CommandProcessorFixture, SCHTest_성명_Option2_FirstName) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::FindByFirstName_Name, enumOptionList::None };
	const string SEARCH_COLUMN = "name";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "08123557", "WN XV", "CL1", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "18123557", "WN XV", "CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "78123558", "WN XV", "CL3", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "88123559", "WN XV", "CL4", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "98123559", "WN XVV" "CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "09123559", "WNN XV","CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "21123559", "WN XV", "CL2", "010-7986-5047", "20100614", "EX" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "20123559", "WN XV", "CL2", "010-7986-5047", "20100614", "ADV" }); //테스트를 위해 추가함.
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1_결과 5개미만
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	
	const string SEARCH_STR_OK1 = "VXIHXOTH";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_OK1)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_OK1 });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_OK2_결과 5개초과
	list_result.clear();
	const string SEARCH_STR_OK2 = "WN";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_OK2)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_OK2 });
	CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_NG
	vector<vector<string>> input_NG_List;
	input_NG_List.push_back({ SEARCH_COLUMN, "WNNNNXVVVVVVVVVV" });//15자 초과(5 + 11 = 16)
	input_NG_List.push_back({ SEARCH_COLUMN, "W N" });//띄어쓰기
	input_NG_List.push_back({ SEARCH_COLUMN, "W N N" });//띄어쓰기 2개
	input_NG_List.push_back({ SEARCH_COLUMN, " WN" });//공백문자로 시작
	input_NG_List.push_back({ SEARCH_COLUMN, "1WN" });//숫자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "WN2" });//숫자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "!WN" });//특수문자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "WN?" });//특수문자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "WN_" });//특수문자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "_WN" });//특수문자 포함

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_성명_Option2_LastName) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::FindByLastName_Name, enumOptionList::None };
	const string SEARCH_COLUMN = "name";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "08123557", "WN XV", "CL1", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "18123557", "WN XV", "CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "78123558", "WN XV", "CL3", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "88123559", "WN XV", "CL4", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "98123559", "WN XVV" "CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "09123559", "WNN XV","CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "21123559", "WN XV", "CL2", "010-7986-5047", "20100614", "EX" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "20123559", "WN XV", "CL2", "010-7986-5047", "20100614", "ADV" }); //테스트를 위해 추가함.
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1_결과 5개미만
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;

	const string SEARCH_STR_OK1 = "NTAWR";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_OK1)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_OK1 });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_OK2_결과 5개초과
	list_result.clear();
	const string SEARCH_STR_OK2 = "XV";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_OK2)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_OK2 });
	CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_NG
	vector<vector<string>> input_NG_List;
	input_NG_List.push_back({ SEARCH_COLUMN, "WNNNNXVVVVVVVVVV" });//15자 초과(5 + 11 = 16)
	input_NG_List.push_back({ SEARCH_COLUMN, "W N" });//띄어쓰기
	input_NG_List.push_back({ SEARCH_COLUMN, "W N N" });//띄어쓰기 2개
	input_NG_List.push_back({ SEARCH_COLUMN, " WN" });//공백문자로 시작
	input_NG_List.push_back({ SEARCH_COLUMN, "1WN" });//숫자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "WN2" });//숫자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "!WN" });//특수문자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "WN?" });//특수문자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "WN_" });//특수문자 포함
	input_NG_List.push_back({ SEARCH_COLUMN, "_WN" });//특수문자 포함

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_경력개발단계_noOption) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "cl";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	const string SEARCH_STR_OK = "CL4";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_OK)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_OK });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_NG
	vector<vector<string>> input_NG_List;
	input_NG_List.push_back({ SEARCH_COLUMN, "CL5" });
	input_NG_List.push_back({ SEARCH_COLUMN, "CL0" });
	input_NG_List.push_back({ SEARCH_COLUMN, "CL?" });
	input_NG_List.push_back({ SEARCH_COLUMN, "GL3" });
	input_NG_List.push_back({ SEARCH_COLUMN, "CL 3"});
	input_NG_List.push_back({ SEARCH_COLUMN, "cl3" });
	
	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_경력개발단계_Option1) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "name";
	const string SEARCH_STR_CL1 = "CL1";
	const string SEARCH_STR_CL2 = "CL2";
	const string SEARCH_STR_CL3 = "CL3";
	const string SEARCH_STR_CL4 = "CL4";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR, CR_exp;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK_CL1
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_CL1)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_CL1 });
	CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_OK_CL2
	list_result.clear();
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_CL2)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_CL2 });
	CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_OK_CL3
	list_result.clear();
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_CL3)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_CL3 });
	CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_OK_CL4
	list_result.clear();
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_CL4)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_CL4 });
	CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}
//전화번호 테스트
//생년월일 테스트
TEST_F(CommandProcessorFixture, SCHTest_CERTI_noOption) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "certi";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	const string SEARCH_STR_OK = "PRO";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_OK)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_OK });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_NG
	vector<vector<string>> input_NG_List;
	input_NG_List.push_back({ SEARCH_COLUMN, "ADVANCED" });
	input_NG_List.push_back({ SEARCH_COLUMN, "PROFESSIONAL" });
	input_NG_List.push_back({ SEARCH_COLUMN, "EXPERT" });
	input_NG_List.push_back({ SEARCH_COLUMN, "adv" });
	input_NG_List.push_back({ SEARCH_COLUMN, "pro" });
	input_NG_List.push_back({ SEARCH_COLUMN, "ex" });
	input_NG_List.push_back({ SEARCH_COLUMN, "A" });
	input_NG_List.push_back({ SEARCH_COLUMN, "P" });
	input_NG_List.push_back({ SEARCH_COLUMN, "E" });
	input_NG_List.push_back({ SEARCH_COLUMN, "A?V" });
	input_NG_List.push_back({ SEARCH_COLUMN, "P/o" });
	input_NG_List.push_back({ SEARCH_COLUMN, "EXP" });
	input_NG_List.push_back({ SEARCH_COLUMN, "ADV " });
	input_NG_List.push_back({ SEARCH_COLUMN, " PRO" });
	input_NG_List.push_back({ SEARCH_COLUMN, "E X" });

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_CERTI_Option1) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "certi";
	const string SEARCH_STR_ADV = "ADV";
	const string SEARCH_STR_PRO = "PRO";
	const string SEARCH_STR_EX = "EX";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR, CR_exp;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK_ADV
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_ADV)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_ADV });
	CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_OK_PRO
	list_result.clear();
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_PRO)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_PRO });
	CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_OK_EX
	list_result.clear();
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_EX)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_EX });
	CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}