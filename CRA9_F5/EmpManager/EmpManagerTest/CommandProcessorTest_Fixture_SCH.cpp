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
	input_ADD_List->push_back({ "12117017", "LFIS JJIVL", "CL1", "010-7914-4067", "20120812", "PRO" });
	input_ADD_List->push_back({ "11125777", "TKOQKIS HC", "CL1", "010-6734-2289", "19991001", "PRO" });
	input_ADD_List->push_back({ "11109136", "QKAHCEX LTODDO", "CL4", "010-2627-8566", "19640130", "PRO" });
	input_ADD_List->push_back({ "05101762", "VCUHLE HMU", "CL4", "010-3988-9289", "20030819", "PRO" });
	return input_ADD_List;
}

TEST_F(CommandProcessorFixture, SCHTest_�����ȣ) {
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
	EXPECT_EQ((int)list_result.size(), 1); //result�� 1�� �̾�� ��.(employNum�� Ű������ ����ũ��), 0�� �Ǵ� ��쵵 ������ �ش� �׽�Ʈ������ 1

	//SCHTest_NG
	vector<vector<string>> input_NG_List;
	input_NG_List.push_back({ SEARCH_COLUMN, "0311326" });//NG: 7�ڸ�
	input_NG_List.push_back({ SEARCH_COLUMN, "031132600" });//NG: 9�ڸ�
	input_NG_List.push_back({ SEARCH_COLUMN, "1512309A" });//NG: A
	input_NG_List.push_back({ SEARCH_COLUMN, "15z23099" });//NG: z
	input_NG_List.push_back({ SEARCH_COLUMN, "68123099" });//NG: �Ի翬��
	input_NG_List.push_back({ SEARCH_COLUMN, "22123099" });//NG: �Ի翬��
	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_����_noOption) {
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
	input_NG_List.push_back({ SEARCH_COLUMN, "WNNNN XVVVVVVVVVV"});//15�� �ʰ�(5 + 11 = 16)
	input_NG_List.push_back({ SEARCH_COLUMN, "WN MIDDLE XV"		});//���� 2��
	input_NG_List.push_back({ SEARCH_COLUMN, "WNXV"				});//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, " WN XV"			});//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN XV1"			});//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN2 XV"			});//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN XV!"			});//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN? XV"			});//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN_XV"			});//Ư������ ����

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_����_Option1) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "name";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "08123557", "WN XV", "CL1", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "18123557", "WN XV", "CL2", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "78123558", "WN XV", "CL3", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "88123559", "WN XV", "CL4", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "98123559", "WN XVV","CL2", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "09123559", "WNN XV","CL2", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "21123559", "WN XV", "CL2", "010-7986-5047", "20100614", "EX" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "20123559", "WN XV", "CL2", "010-7986-5047", "20100614", "ADV" }); //�׽�Ʈ�� ���� �߰���.
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
TEST_F(CommandProcessorFixture, SCHTest_����_Option2_FirstName) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::FindByFirstName_Name, enumOptionList::None };
	const string SEARCH_COLUMN = "name";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "08123557", "WN XV", "CL1", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "18123557", "WN XV", "CL2", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "78123558", "WN XV", "CL3", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "88123559", "WN XV", "CL4", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "98123559", "WN XVV","CL2", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "09123559", "WNN XV","CL2", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "21123559", "WN XV", "CL2", "010-7986-5047", "20100614", "EX" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "20123559", "WN XV", "CL2", "010-7986-5047", "20100614", "ADV" }); //�׽�Ʈ�� ���� �߰���.
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1_��� 5���̸�
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

	//SCHTest_OK2_��� 5���ʰ�
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
	input_NG_List.push_back({ SEARCH_COLUMN, "" });
	input_NG_List.push_back({ SEARCH_COLUMN, "WNNNNXVVVVVVVVVV" });//15�� �ʰ�(5 + 11 = 16)
	input_NG_List.push_back({ SEARCH_COLUMN, "W N" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "W N N" });//���� 2��
	input_NG_List.push_back({ SEARCH_COLUMN, " WN" });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "1WN" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN2" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "!WN" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN?" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN_" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "_WN" });//Ư������ ����

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_����_Option2_LastName) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::FindByLastName_Name, enumOptionList::None };
	const string SEARCH_COLUMN = "name";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "08123557", "WN XV", "CL1", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "18123557", "WN XV", "CL2", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "78123558", "WN XV", "CL3", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "88123559", "WN XV", "CL4", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "98123559", "WN XVV", "CL2", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "09123559", "WNN XV","CL2", "010-7986-5047", "20100614", "PRO" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "21123559", "WN XV", "CL2", "010-7986-5047", "20100614", "EX" }); //�׽�Ʈ�� ���� �߰���.
	input_ADD_List->push_back({ "20123559", "WN XV", "CL2", "010-7986-5047", "20100614", "ADV" }); //�׽�Ʈ�� ���� �߰���.
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1_��� 5���̸�
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

	//SCHTest_OK2_��� 5���ʰ�
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
	input_NG_List.push_back({ SEARCH_COLUMN, "" });
	input_NG_List.push_back({ SEARCH_COLUMN, "WNNNNXVVVVVVVVVV" });//15�� �ʰ�(5 + 11 = 16)
	input_NG_List.push_back({ SEARCH_COLUMN, "W N" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "W N N" });//���� 2��
	input_NG_List.push_back({ SEARCH_COLUMN, " WN" });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "1WN" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN2" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "!WN" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN?" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "WN_" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "_WN" });//Ư������ ����

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_��°��ߴܰ�_noOption) {
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
TEST_F(CommandProcessorFixture, SCHTest_��°��ߴܰ�_Option1) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "cl";
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
TEST_F(CommandProcessorFixture, SCHTest_��ȭ��ȣ_noOption) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "phoneNum";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "91130827", "RPO JKK",		"CL4", "010-0231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "92130827", "RPO JKKK",		"CL4", "010-3231-0698", "20090201", "PRO" });
	input_ADD_List->push_back({ "93130827", "RPO JKKKK",	"CL4", "010-3231-1698", "20090201", "EX" });
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	const string SEARCH_STR_OK1 = "010-3231-1698";
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

	//SCHTest_OK2
	list_result.clear();
	const string SEARCH_STR_OK2 = "010-0231-1698"; //middle�� 0���� ����
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

	//SCHTest_OK3
	list_result.clear();
	const string SEARCH_STR_OK3 = "010-3231-0698"; //last�� 0���� ����
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == SEARCH_STR_OK3)
			list_result.push_back(Employ(aEmpVec));
	}
	EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, SEARCH_STR_OK3 });
	CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);

	//SCHTest_NG
	vector<vector<string>> input_NG_List;
	input_NG_List.push_back({ SEARCH_COLUMN, "010-323-1698" });//���� �̻� (middle 3�ڸ�)
	input_NG_List.push_back({ SEARCH_COLUMN, "010-3231-169" });//���� �̻� (last 3�ڸ�)
	input_NG_List.push_back({ SEARCH_COLUMN, "010-32312-1698" });//���� �̻� (middle 5�ڸ�)
	input_NG_List.push_back({ SEARCH_COLUMN, "010-3231-16989" });//���� �̻� (last 5�ڸ�)
	input_NG_List.push_back({ SEARCH_COLUMN, "011-3231-1698" });//010 �ƴ�
	input_NG_List.push_back({ SEARCH_COLUMN, "017-3231-1698" });//010 �ƴ�
	input_NG_List.push_back({ SEARCH_COLUMN, "810-3231-1698" });//010 �ƴ�
	input_NG_List.push_back({ SEARCH_COLUMN, "010-32A1-1698" });//���� �ƴ�
	input_NG_List.push_back({ SEARCH_COLUMN, "010-3231-1B98" });//���� �ƴ�
	input_NG_List.push_back({ SEARCH_COLUMN, "010-32?1-1698" });//���� �ƴ�
	input_NG_List.push_back({ SEARCH_COLUMN, "010-3231-!698" });//���� �ƴ�
	input_NG_List.push_back({ SEARCH_COLUMN, "O10-3231-1698" });//���� 0 ��� �ٸ� ����: ���� O
	input_NG_List.push_back({ SEARCH_COLUMN, "010-3231-16O8" });//���� 0 ��� �ٸ� ����: ���� O
	input_NG_List.push_back({ SEARCH_COLUMN, "010=3231-1698" });//-��� �ٸ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "010-3231_1698" });//-��� �ٸ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "010-3231-1698-1234" });//�����̻� : - 3��
	input_NG_List.push_back({ SEARCH_COLUMN, "010-3231" });//�����̻� : - 1��
	input_NG_List.push_back({ SEARCH_COLUMN, "010-32311698" });//�����̻� : - 1��
	input_NG_List.push_back({ SEARCH_COLUMN, "01032311698" });//�����̻� : - 0��

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_��ȭ��ȣ_Option1) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "phoneNum";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "13130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "15130827", "RPO JKL",		"CL4", "010-3231-1698", "20090202", "PRO" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "16130827", "RPO JKLM",		"CL4", "010-3231-1698", "20090203", "EX"  }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "17130827", "RPO JKLMN",	"CL4", "010-3231-1698", "20090204", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "18130827", "RPO JKLMNO",	"CL4", "010-3231-1698", "20090205", "PRO" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "71130827", "RPOP JK",		"CL3", "010-3231-1234", "20090206", "EX"  }); //�׽�Ʈ�� ���� ��ȭ��ȣ(middle)�� ���� employ �߰���.
	input_ADD_List->push_back({ "72130827", "RPOPQ JK",		"CL3", "010-3231-2345", "20090207", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(middle)�� ���� employ �߰���.
	input_ADD_List->push_back({ "73130827", "RPOPQR JK",	"CL3", "010-3231-3456", "20090207", "PRO" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(middle)�� ���� employ �߰���.
	input_ADD_List->push_back({ "74130827", "RPOPQRS JK",	"CL2", "010-1234-1698", "20090207", "EX" });  //�׽�Ʈ�� ���� ��ȭ��ȣ(last)�� ���� employ �߰���.
	input_ADD_List->push_back({ "75130827", "RPOPQRST JK",	"CL2", "010-2345-1698", "20090207", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(last)�� ���� employ �߰���.
	input_ADD_List->push_back({ "76130827", "RPOPQRSTU JK",	"CL2", "010-3456-1698", "20090207", "PRO" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(last)�� ���� employ �߰���.
	

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
	const string SEARCH_STR_OK = "010-3231-1698";
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
TEST_F(CommandProcessorFixture, SCHTest_��ȭ��ȣ_Option2_MiddleNum) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::FindByMiddleNum_PhoneNum, enumOptionList::None };
	const string SEARCH_COLUMN = "phoneNum";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "14130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "15130827", "RPO JKL",		"CL4", "010-3231-1698", "20090202", "PRO" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "16130827", "RPO JKLM",		"CL4", "010-3231-1698", "20090203", "EX" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "17130827", "RPO JKLMN",	"CL4", "010-3231-1698", "20090204", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "18130827", "RPO JKLMNO",	"CL4", "010-3231-1698", "20090205", "PRO" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "71130827", "RPOP JK",		"CL3", "010-3231-1234", "20090206", "EX" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(middle)�� ���� employ �߰���.
	input_ADD_List->push_back({ "72130827", "RPOPQ JK",		"CL3", "010-3231-1234", "20090207", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(middle)�� ���� employ �߰���.
	input_ADD_List->push_back({ "73130827", "RPOPQR JK",	"CL2", "010-1234-1698", "20090207", "EX" });  //�׽�Ʈ�� ���� ��ȭ��ȣ(last)�� ���� employ �߰���.
	input_ADD_List->push_back({ "74130827", "RPOPQRS JK",	"CL2", "010-1234-1698", "20090207", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(last)�� ���� employ �߰���.
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1_��� 5���̸�
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;

	const string SEARCH_STR_OK1 = "1234";
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

	//SCHTest_OK2_��� 5���ʰ�
	list_result.clear();
	const string SEARCH_STR_OK2 = "3231";
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
	input_NG_List.push_back({ SEARCH_COLUMN, ""		});
	input_NG_List.push_back({ SEARCH_COLUMN, "3 231" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "32 31" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "323 1" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "3 23 1" });//���� 2��
	input_NG_List.push_back({ SEARCH_COLUMN, "3 2 3 1" });//���� 3��
	input_NG_List.push_back({ SEARCH_COLUMN, " 3231" });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "3231 " });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "A231" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "323Z" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "3M31" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "!231" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "323?" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "3_31" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "32/1" });//Ư������ ����

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_��ȭ��ȣ_Option2_LastNum) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::FindByLastNum_PhoneNum, enumOptionList::None };
	const string SEARCH_COLUMN = "phoneNum";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "14130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "15130827", "RPO JKL",		"CL4", "010-3231-1698", "20090202", "PRO" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "16130827", "RPO JKLM",		"CL4", "010-3231-1698", "20090203", "EX" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "17130827", "RPO JKLMN",	"CL4", "010-3231-1698", "20090204", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "18130827", "RPO JKLMNO",	"CL4", "010-3231-1698", "20090205", "PRO" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "71130827", "RPOP JK",		"CL3", "010-3231-1234", "20090206", "EX" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(middle)�� ���� employ �߰���.
	input_ADD_List->push_back({ "72130827", "RPOPQ JK",		"CL3", "010-3231-1234", "20090207", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(middle)�� ���� employ �߰���.
	input_ADD_List->push_back({ "73130827", "RPOPQR JK",	"CL2", "010-1234-1698", "20090207", "EX" });  //�׽�Ʈ�� ���� ��ȭ��ȣ(last)�� ���� employ �߰���.
	input_ADD_List->push_back({ "74130827", "RPOPQRS JK",	"CL2", "010-1234-1698", "20090207", "ADV" }); //�׽�Ʈ�� ���� ��ȭ��ȣ(last)�� ���� employ �߰���.
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1_��� 5���̸�
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;

	const string SEARCH_STR_OK1 = "1234";
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

	//SCHTest_OK2_��� 5���ʰ�
	list_result.clear();
	const string SEARCH_STR_OK2 = "1698";
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
	input_NG_List.push_back({ SEARCH_COLUMN, "" });
	input_NG_List.push_back({ SEARCH_COLUMN, "3 231" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "32 31" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "323 1" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "3 23 1" });//���� 2��
	input_NG_List.push_back({ SEARCH_COLUMN, "3 2 3 1" });//���� 3��
	input_NG_List.push_back({ SEARCH_COLUMN, " 3231" });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "3231 " });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "A231" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "323Z" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "3M31" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "!231" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "323?" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "3_31" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "32/1" });//Ư������ ����

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
//������� �׽�Ʈ
TEST_F(CommandProcessorFixture, SCHTest_�������_noOption) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "birthday";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "91130827", "RPO JK",		"CL4", "010-3231-1698", "20091211", "ADV" });
	input_ADD_List->push_back({ "92130827", "RPO JK",		"CL4", "010-3231-1698", "20090101", "ADV" });
	input_ADD_List->push_back({ "93130827", "RPO JK",		"CL4", "010-3231-1698", "20091201", "ADV" });
	input_ADD_List->push_back({ "94130827", "RPO JK",		"CL4", "010-3231-1698", "20090131", "ADV" });
	input_ADD_List->push_back({ "95130827", "RPO JK",		"CL4", "010-3231-1698", "20090229", "ADV" });
	input_ADD_List->push_back({ "96130827", "RPO JK",		"CL4", "010-3231-1698", "20090331", "ADV" });
	input_ADD_List->push_back({ "97130827", "RPO JK",		"CL4", "010-3231-1698", "20090430", "ADV" });
	input_ADD_List->push_back({ "98130827", "RPO JK",		"CL4", "010-3231-1698", "20090531", "ADV" });
	input_ADD_List->push_back({ "99130827", "RPO JK",		"CL4", "010-3231-1698", "20090630", "ADV" });
	input_ADD_List->push_back({ "00130827", "RPO JK",		"CL4", "010-3231-1698", "20090731", "ADV" });
	input_ADD_List->push_back({ "01130827", "RPO JK",		"CL4", "010-3231-1698", "20090831", "ADV" });
	input_ADD_List->push_back({ "02130827", "RPO JK",		"CL4", "010-3231-1698", "20090930", "ADV" });
	input_ADD_List->push_back({ "03130827", "RPO JK",		"CL4", "010-3231-1698", "20091031", "ADV" });
	input_ADD_List->push_back({ "04130827", "RPO JK",		"CL4", "010-3231-1698", "20091130", "ADV" });
	input_ADD_List->push_back({ "05130827", "RPO JK",		"CL4", "010-3231-1698", "20091231", "ADV" });

	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
	Times((int)input_ADD_List->size()).
	WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;
	vector<string> searchStrOKList;
	CommandResult CR_exp;
	searchStrOKList.push_back("20090201");
	searchStrOKList.push_back("20091211");
	searchStrOKList.push_back("20090101");
	searchStrOKList.push_back("20091201");
	searchStrOKList.push_back("20090131");
	searchStrOKList.push_back("20090229");
	searchStrOKList.push_back("20090331");
	searchStrOKList.push_back("20090430");
	searchStrOKList.push_back("20090531");
	searchStrOKList.push_back("20090630");
	searchStrOKList.push_back("20090731");
	searchStrOKList.push_back("20090831");
	searchStrOKList.push_back("20090930");
	searchStrOKList.push_back("20091031");
	searchStrOKList.push_back("20091130");
	searchStrOKList.push_back("20091231");
	for (string searchStrOK : searchStrOKList) {
		list_result.clear();
		for (vector<string> aEmpVec : *input_ADD_List) {
			if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == searchStrOK)
				list_result.push_back(Employ(aEmpVec));
		}
		EXPECT_CALL(MockDatabase::getInstance(), selectItems(_, _)).
			Times(1).
			WillOnce(Return(list_result));
		CR = cmdSCH.run(INPUT_OPTION, { SEARCH_COLUMN, searchStrOK });
		CR_exp = CommandResult((int)list_result.size(), list_result);
		EXPECT_EQ(CR, CR_exp);
	}

	//SCHTest_NG
	vector<vector<string>> input_NG_List;
	input_NG_List.push_back({ SEARCH_COLUMN, "090201" });//���� �̻� (yymmdd)
	input_NG_List.push_back({ SEARCH_COLUMN, "00090231" });//���� �̻� (00yymmdd)
	input_NG_List.push_back({ SEARCH_COLUMN, "2009aa11" });//NG
	input_NG_List.push_back({ SEARCH_COLUMN, "200912BB" });//NG
	input_NG_List.push_back({ SEARCH_COLUMN, "20??0201" });//NG"19??1211",	
	input_NG_List.push_back({ SEARCH_COLUMN, "2009-02-01" });//NG"1977-12-11"
	input_NG_List.push_back({ SEARCH_COLUMN, "2009/02/01" });//NG"1977/12/11"
	input_NG_List.push_back({ SEARCH_COLUMN, "01022009" });//NG (DDMMYYYY)

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_�������_Option1) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::None, enumOptionList::None };
	const string SEARCH_COLUMN = "birthday";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "91130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });//�׽�Ʈ�� ���� �������(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "92130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "93130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "94130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "95130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "96130827", "RPO JK",		"CL4", "010-3231-1698", "20090302", "ADV" });//�׽�Ʈ�� ���� �������(yyyy)�� ���� employ �߰���.
	input_ADD_List->push_back({ "97130827", "RPO JK",		"CL4", "010-3231-1698", "20090403", "ADV" });
	input_ADD_List->push_back({ "98130827", "RPO JK",		"CL4", "010-3231-1698", "20090504", "ADV" });
	input_ADD_List->push_back({ "99130827", "RPO JK",		"CL4", "010-3231-1698", "20100202", "ADV" });//�׽�Ʈ�� ���� �������(mm)�� ���� employ �߰���.
	input_ADD_List->push_back({ "00130827", "RPO JK",		"CL4", "010-3231-1698", "20110203", "ADV" });
	input_ADD_List->push_back({ "01130827", "RPO JK",		"CL4", "010-3231-1698", "20120204", "ADV" });
	input_ADD_List->push_back({ "02130827", "RPO JK",		"CL4", "010-3231-1698", "20130301", "ADV" });//�׽�Ʈ�� ���� �������(dd)�� ���� employ �߰���.
	input_ADD_List->push_back({ "03130827", "RPO JK",		"CL4", "010-3231-1698", "20140401", "ADV" });
	input_ADD_List->push_back({ "04130827", "RPO JK",		"CL4", "010-3231-1698", "20150501", "ADV" });
	
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
	const string SEARCH_STR_OK = "20090201";
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
TEST_F(CommandProcessorFixture, SCHTest_�������_Option2_Year) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::FindByYear_Birthday, enumOptionList::None };
	const string SEARCH_COLUMN = "birthday";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "91130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });//�׽�Ʈ�� ���� �������(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "92130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "93130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "94130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "95130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "76130827", "RPO JK",		"CL4", "010-3231-1698", "20090302", "ADV" });//�׽�Ʈ�� ���� �������(yyyy)�� ���� employ �߰���.
	input_ADD_List->push_back({ "77130827", "RPO JK",		"CL4", "010-3231-1698", "20090302", "ADV" });
	input_ADD_List->push_back({ "78130827", "RPO JK",		"CL4", "010-3231-1698", "20090302", "ADV" });
	input_ADD_List->push_back({ "79130827", "RPO JK",		"CL4", "010-3231-1698", "20100202", "ADV" });//�׽�Ʈ�� ���� �������(mm)�� ���� employ �߰���.
	input_ADD_List->push_back({ "80130827", "RPO JK",		"CL4", "010-3231-1698", "20100202", "ADV" });
	input_ADD_List->push_back({ "81130827", "RPO JK",		"CL4", "010-3231-1698", "20100202", "ADV" });
	input_ADD_List->push_back({ "82130827", "RPO JK",		"CL4", "010-3231-1698", "20100301", "ADV" });//�׽�Ʈ�� ���� �������(dd)�� ���� employ �߰���.
	input_ADD_List->push_back({ "83130827", "RPO JK",		"CL4", "010-3231-1698", "20100301", "ADV" });
	input_ADD_List->push_back({ "84130827", "RPO JK",		"CL4", "010-3231-1698", "20100301", "ADV" });
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1_��� 5���̸�
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;

	const string SEARCH_STR_OK1 = "1978";
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

	//SCHTest_OK2_��� 5���ʰ�
	list_result.clear();
	const string SEARCH_STR_OK2 = "2009";
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
	input_NG_List.push_back({ SEARCH_COLUMN, "" });//null
	input_NG_List.push_back({ SEARCH_COLUMN, "2 009" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "20 09" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "200 9" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "2 00 9" });//���� 2��
	input_NG_List.push_back({ SEARCH_COLUMN, "2 0 0 9" });//���� 3��
	input_NG_List.push_back({ SEARCH_COLUMN, " 2009" });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "2009 " });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "A009" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "200Z" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "20O9" });//���� ���� (���� O)
	input_NG_List.push_back({ SEARCH_COLUMN, "!009" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "200?" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "2_09" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "20/9" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "20119" });//5����
	input_NG_List.push_back({ SEARCH_COLUMN, "009" });//3����
	input_NG_List.push_back({ SEARCH_COLUMN, "09" });//2����
	
	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_�������_Option2_Month) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::FindByMonth_Birthday, enumOptionList::None };
	const string SEARCH_COLUMN = "birthday";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "91130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });//�׽�Ʈ�� ���� �������(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "92130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "93130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "94130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "95130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "76130827", "RPO JK",		"CL4", "010-3231-1698", "20090302", "ADV" });//�׽�Ʈ�� ���� �������(yyyy)�� ���� employ �߰���.
	input_ADD_List->push_back({ "77130827", "RPO JK",		"CL4", "010-3231-1698", "20090302", "ADV" });
	input_ADD_List->push_back({ "78130827", "RPO JK",		"CL4", "010-3231-1698", "20090302", "ADV" });
	input_ADD_List->push_back({ "79130827", "RPO JK",		"CL4", "010-3231-1698", "20100202", "ADV" });//�׽�Ʈ�� ���� �������(mm)�� ���� employ �߰���.
	input_ADD_List->push_back({ "80130827", "RPO JK",		"CL4", "010-3231-1698", "20100202", "ADV" });
	input_ADD_List->push_back({ "81130827", "RPO JK",		"CL4", "010-3231-1698", "20100202", "ADV" });
	input_ADD_List->push_back({ "82130827", "RPO JK",		"CL4", "010-3231-1698", "20100301", "ADV" });//�׽�Ʈ�� ���� �������(dd)�� ���� employ �߰���.
	input_ADD_List->push_back({ "83130827", "RPO JK",		"CL4", "010-3231-1698", "20100301", "ADV" });
	input_ADD_List->push_back({ "84130827", "RPO JK",		"CL4", "010-3231-1698", "20100301", "ADV" });
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1_��� 5���̸�
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;

	const string SEARCH_STR_OK1 = "04";
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

	//SCHTest_OK2_��� 5���ʰ�
	list_result.clear();
	const string SEARCH_STR_OK2 = "02";
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
	input_NG_List.push_back({ SEARCH_COLUMN, "" });//null
	input_NG_List.push_back({ SEARCH_COLUMN, "0 2" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "0  2" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, " 02" });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "02 " });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "A2" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "0Z" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "O2" });//���� ���� (���� O)
	input_NG_List.push_back({ SEARCH_COLUMN, "!2" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "0?" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "_2" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "0/" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "002" });//3����
	input_NG_List.push_back({ SEARCH_COLUMN, "2" });//1����

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
TEST_F(CommandProcessorFixture, SCHTest_�������_Option2_Day) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::FindByDay_Birthday, enumOptionList::None };
	const string SEARCH_COLUMN = "birthday";
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVector();
	input_ADD_List->push_back({ "91130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });//�׽�Ʈ�� ���� �������(��ü)�� ���� employ �߰���.
	input_ADD_List->push_back({ "92130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "93130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "94130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "95130827", "RPO JK",		"CL4", "010-3231-1698", "20090201", "ADV" });
	input_ADD_List->push_back({ "76130827", "RPO JK",		"CL4", "010-3231-1698", "20090302", "ADV" });//�׽�Ʈ�� ���� �������(yyyy)�� ���� employ �߰���.
	input_ADD_List->push_back({ "77130827", "RPO JK",		"CL4", "010-3231-1698", "20090302", "ADV" });
	input_ADD_List->push_back({ "78130827", "RPO JK",		"CL4", "010-3231-1698", "20090302", "ADV" });
	input_ADD_List->push_back({ "79130827", "RPO JK",		"CL4", "010-3231-1698", "20100202", "ADV" });//�׽�Ʈ�� ���� �������(mm)�� ���� employ �߰���.
	input_ADD_List->push_back({ "80130827", "RPO JK",		"CL4", "010-3231-1698", "20100202", "ADV" });
	input_ADD_List->push_back({ "81130827", "RPO JK",		"CL4", "010-3231-1698", "20100202", "ADV" });
	input_ADD_List->push_back({ "82130827", "RPO JK",		"CL4", "010-3231-1698", "20100301", "ADV" });//�׽�Ʈ�� ���� �������(dd)�� ���� employ �߰���.
	input_ADD_List->push_back({ "83130827", "RPO JK",		"CL4", "010-3231-1698", "20100301", "ADV" });
	input_ADD_List->push_back({ "84130827", "RPO JK",		"CL4", "010-3231-1698", "20100301", "ADV" });
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//SCHTest_OK1_��� 5���̸�
	CommandProcessorSCH<MockDatabase> cmdSCH = CommandProcessorSCH<MockDatabase>();
	vector<Employ> list_result;

	const string SEARCH_STR_OK1 = "18";
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

	//SCHTest_OK2_��� 5���ʰ�
	list_result.clear();
	const string SEARCH_STR_OK2 = "01";
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
	input_NG_List.push_back({ SEARCH_COLUMN, "" });//null
	input_NG_List.push_back({ SEARCH_COLUMN, "0 2" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, "0  2" });//����
	input_NG_List.push_back({ SEARCH_COLUMN, " 02" });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "02 " });//���鹮�ڷ� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "A2" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "0Z" });//���� ����
	input_NG_List.push_back({ SEARCH_COLUMN, "O2" });//���� ���� (���� O)
	input_NG_List.push_back({ SEARCH_COLUMN, "!2" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "0?" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "_2" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "0/" });//Ư������ ����
	input_NG_List.push_back({ SEARCH_COLUMN, "002" });//3����
	input_NG_List.push_back({ SEARCH_COLUMN, "2" });//1����

	for (vector < string> input_NG : input_NG_List) {
		EXPECT_THROW(cmdSCH.run(INPUT_OPTION, input_NG), invalid_argument);
	}
}
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
