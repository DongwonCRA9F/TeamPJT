#include "pch.h"
#include "CommandProcessorTest_Fixture.h"
using  ::testing::Return;
using  ::testing::_;

vector<vector<string>>* makeInputVectorMOD() {
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

TEST_F(CommandProcessorFixture, MODTest_사원번호) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVectorMOD();
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//MODTest_OK
	CommandProcessorMOD<MockDatabase> cmdMOD = CommandProcessorMOD<MockDatabase>();
	vector<Employ> list_result;
	const string SEARCH_COLUMN = "employNum";
	const string searchStr_OK = "03113260";
	const string UPDATE_COLUMN = "cl";
	const string updateStr_OK = "CL3";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::EMPLOYEENUM)] == searchStr_OK) {
			vector<string> tempEmp(aEmpVec.size());
			copy(aEmpVec.begin(), aEmpVec.end(), tempEmp.begin());
			tempEmp[static_cast<int>(enumEmploy::CL)] = "CL3";
			list_result.push_back(Employ(tempEmp));
		}
	}
	EXPECT_CALL(MockDatabase::getInstance(), updateItems(_, _, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdMOD.run(INPUT_OPTION, { SEARCH_COLUMN, searchStr_OK, UPDATE_COLUMN, updateStr_OK });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
	EXPECT_EQ((int)list_result.size(), 1); //result가 1개 이어야 함.(employNum은 키값으로 유니크함), 0이 되는 경우도 있지만 해당 테스트에서는 1
}

TEST_F(CommandProcessorFixture, MODTest_성명_noOption) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVectorMOD();
	EXPECT_CALL(MockDatabase::getInstance(), insertItem(_)).
		Times((int)input_ADD_List->size()).
		WillRepeatedly(Return(true));
	CommandResult CR;
	for (vector<string> aEmpVec : *input_ADD_List) {
		CR = cmdADD.run(INPUT_OPTION, aEmpVec);
		EXPECT_EQ(CR.count, 1);
	}

	//MODTest_OK
	CommandProcessorMOD<MockDatabase> cmdMOD = CommandProcessorMOD<MockDatabase>();
	vector<Employ> list_result;
	const string SEARCH_COLUMN = "name";
	const string searchStr_OK = "WN XV";
	const string UPDATE_COLUMN = "cl";
	const string updateStr_OK = "CL3";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::NAME)] == searchStr_OK) {
			vector<string> tempEmp(aEmpVec.size());
			copy(aEmpVec.begin(), aEmpVec.end(), tempEmp.begin());
			tempEmp[static_cast<int>(enumEmploy::CL)] = "CL3";
			list_result.push_back(Employ(tempEmp));
		}
	}
	EXPECT_CALL(MockDatabase::getInstance(), updateItems(_, _, _)).
		Times(1).
		WillOnce(Return(list_result));
	CR = cmdMOD.run(INPUT_OPTION, { SEARCH_COLUMN, searchStr_OK, UPDATE_COLUMN, updateStr_OK });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	EXPECT_EQ(CR, CR_exp);
}

TEST_F(CommandProcessorFixture, MODTest_성명_Option1) {
	const vector<enumOptionList> INPUT_OPTION = { enumOptionList::RecordPrint, enumOptionList::None, enumOptionList::None };
	//set env
	CommandProcessorADD<MockDatabase> cmdADD = CommandProcessorADD<MockDatabase>();
	vector<vector<string>>* input_ADD_List;
	input_ADD_List = makeInputVectorMOD();
	input_ADD_List->push_back({ "08123557", "WN XV", "CL1", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "18123557", "WN XV", "CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "78123558", "WN XV", "CL3", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "88123559", "WN XV", "CL4", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
	input_ADD_List->push_back({ "98123559", "WN XVV","CL2", "010-7986-5047", "20100614", "PRO" }); //테스트를 위해 추가함.
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

	//MODTest_OK
	CommandProcessorMOD<MockDatabase> cmdMOD = CommandProcessorMOD<MockDatabase>();
	vector<Employ> list_result;
	list_result.resize(5);
	vector<Employ> raw_result;
	const string SEARCH_COLUMN = "name";
	const string searchStr_OK = "WN XV";
	const string UPDATE_COLUMN = "cl";
	const string updateStr_OK = "CL3";
	for (vector<string> aEmpVec : *input_ADD_List) {
		if (aEmpVec[static_cast<int>(enumEmploy::NAME)] == searchStr_OK) {
			vector<string> tempEmp(aEmpVec.size());
			copy(aEmpVec.begin(), aEmpVec.end(), tempEmp.begin());
			tempEmp[static_cast<int>(enumEmploy::CL)] = "CL3";
			raw_result.push_back(Employ(tempEmp));
			if (tempEmp[static_cast<int>(enumEmploy::EMPLOYEENUM)] == "78123558")
				list_result.at(0) = Employ(tempEmp);
			if (tempEmp[static_cast<int>(enumEmploy::EMPLOYEENUM)] == "88123559")
				list_result.at(1) = Employ(tempEmp);
			if (tempEmp[static_cast<int>(enumEmploy::EMPLOYEENUM)] == "08123556")
				list_result.at(2) = Employ(tempEmp);
			if (tempEmp[static_cast<int>(enumEmploy::EMPLOYEENUM)] == "08123557")
				list_result.at(3) = Employ(tempEmp);
			if (tempEmp[static_cast<int>(enumEmploy::EMPLOYEENUM)] == "18123557") 
				list_result.at(4) = Employ(tempEmp);
		}
	}
	EXPECT_CALL(MockDatabase::getInstance(), updateItems(_, _, _)).
		Times(1).
		WillOnce(Return(raw_result));
	CR = cmdMOD.run(INPUT_OPTION, { SEARCH_COLUMN, searchStr_OK, UPDATE_COLUMN, updateStr_OK });
	CommandResult CR_exp = CommandResult((int)list_result.size(), list_result);
	vector<Employ> CR_sorted = CR.getDetailResults();
	ASSERT_EQ(CR_sorted.size(), CR_exp.list.size());
	for (int i = 0; i < CR_exp.list.size(); ++i) {
		EXPECT_EQ(CR_sorted[i], CR_exp.list[i]);
	}
}