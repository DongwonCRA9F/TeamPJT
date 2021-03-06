
#include "pch.h"
#include "CommandParserTest_Fixture.h"

void CommandParserFixture::SetUp() {
}

void CommandParserFixture::TearDown() {
}

void CommandParserFixture::MakeSampleInputList() {
	SampleInputList.reserve(12);
	SampleInputList.push_back(InputList{"ADD, , , ,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO", 
		enumCommandList::ADD , { enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "18050301","KYUMOK KIM","CL2","010-9777-6055","19980906","PRO"} });
	SampleInputList.push_back(InputList{ "DEL, , , ,name,KYUMOK KIM",
		enumCommandList::DEL , { enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "name", "KYUMOK KIM"} });
	SampleInputList.push_back(InputList{ "MOD, , , ,cl,CL3,phoneNum,010-9777-5455",
		enumCommandList::MOD , { enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "cl","CL3", "phoneNum","010-9777-5455"} });
	SampleInputList.push_back(InputList{ "DEL, , , ,phoneNum,010-9777-6055",
		enumCommandList::DEL , { enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "phoneNum", "010-9777-6055"} });
	SampleInputList.push_back(InputList{ "SCH, , , ,birthday,19900906",
		enumCommandList::SCH , { enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "birthday", "19900906"} });

	SampleInputList.push_back(InputList{ "MOD,-p,-l, ,phoneNum,010-9777-6055,certi,EX",
		enumCommandList::MOD , { enumOptionList::RecordPrint, enumOptionList::FindByLastNum_PhoneNum, enumOptionList::None }, { "phoneNum", "010-9777-6055", "certi", "EX"}});
	SampleInputList.push_back(InputList{ "DEL, ,-f, ,name,KYUMOK",
		enumCommandList::DEL , { enumOptionList::None, enumOptionList::FindByFirstName_Name, enumOptionList::None }, { "name", "KYUMOK"} });

	SampleInputList.push_back(InputList{ "SCH,-p,-m, ,phoneNum,9777",
		enumCommandList::SCH, {enumOptionList::RecordPrint, enumOptionList::FindByMiddleNum_PhoneNum, enumOptionList::None}, {"phoneNum", "9777"} });
	SampleInputList.push_back(InputList{ "DEL, ,-l, ,phoneNum,9777",
		enumCommandList::DEL, {enumOptionList::None, enumOptionList::FindByLastNum_PhoneNum, enumOptionList::None}, {"phoneNum", "9777"} });

	SampleInputList.push_back(InputList{ "MOD, ,-d, ,birthday,06,certi,EX",
		enumCommandList::MOD, {enumOptionList::None, enumOptionList::FindByDay_Birthday, enumOptionList::None}, {"birthday", "06", "certi", "EX"}});
	SampleInputList.push_back(InputList{ "DEL, ,-m, ,birthday,06",
		enumCommandList::DEL, {enumOptionList::None, enumOptionList::FindByMonth_Birthday, enumOptionList::None}, {"birthday", "06"} });
	SampleInputList.push_back(InputList{ "SCH, ,-y, ,birthday,1990",
		enumCommandList::SCH, {enumOptionList::None, enumOptionList::FindByYear_Birthday, enumOptionList::None}, {"birthday", "1990"} });

}


TEST_F(CommandParserFixture, ParsingPositiveTest) {
	CommandParser cmdParser;
	MakeSampleInputList();
	
	for (auto& SampleInput : SampleInputList) {
		cmdParser.parsing(SampleInput.InputString, ",");
		EXPECT_EQ(cmdParser.getCommand(), SampleInput.ResultCommand) << SampleInput.InputString << "에서 Command값이 제대로 뽑히지 않았습니다.";

		auto Options = cmdParser.getOptions();
		EXPECT_TRUE(Options.size() == SampleInput.ResultOption.size() &&
			equal(Options.begin(), Options.end(), SampleInput.ResultOption.begin())) << SampleInput.InputString << "에서 Option값이 제대로 뽑히지 않았습니다.";

		auto Conditions = cmdParser.getConditions();
		EXPECT_TRUE(Conditions.size() == SampleInput.ResultCondition.size() &&
			equal(Conditions.begin(), Conditions.end(), SampleInput.ResultCondition.begin())) << SampleInput.InputString << "에서 Condition값이 제대로 뽑히지 않았습니다.";
	}
}

TEST_F(CommandParserFixture, ParsingNegativeTest) {
	CommandParser cmdParser;

	EXPECT_THROW(cmdParser.parsing("InvalidCmd, , , ,1,2,3", ","), invalid_Command) << "Cmd 가 제대로 들어오지 않았지만 통과하였습니다";
	EXPECT_THROW(cmdParser.parsing("DEL,invliadOpt,-f, ,name,KYUMOK", ","), invalid_Options) << "Option이 제대로 들어오지 않았지만 통과하였습니다.";
	EXPECT_THROW(cmdParser.parsing("MOD, ,invliadOpt, ,cl,CL3,phoneNum,010-9777-5455", ","), invalid_Options) << "Option이 제대로 들어오지 않았지만 통과하였습니다.";
	EXPECT_THROW(cmdParser.parsing("SCH, , ,hs,birthday,19900906", ","), invalid_Options) << "Option이 제대로 들어오지 않았지만 통과하였습니다.";
	EXPECT_THROW(cmdParser.parsing("ADD,-p,-f, ,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO", ","), invalid_Options) << "ADD cmd에는 option이 있을 수 없습니다.";

	EXPECT_THROW(cmdParser.parsing("MOD, ,-f, ,cl,CL3,phoneNum,010-9777-5455", ","), invalid_Options) << "Option이 잘못 들어갔지만 throw하지 않았습니다";
	EXPECT_THROW(cmdParser.parsing("DEL, ,-l, ,employeeNum,8291123", ","), invalid_Options) << "Option이 잘못 들어갔지만 throw하지 않았습니다";
	EXPECT_THROW(cmdParser.parsing("MOD, ,-m, ,cl,CL3,phoneNum,010-9777-5455", ","), invalid_Options) << "Option이 잘못 들어갔지만 throw하지 않았습니다";
	EXPECT_THROW(cmdParser.parsing("MOD, ,-l, ,birthday,19950909,phoneNum,010-9777-5455", ","), invalid_Options) << "Option이 잘못 들어갔지만 throw하지 않았습니다";
	EXPECT_THROW(cmdParser.parsing("DEL, ,-y, ,certi,PRO", ","), invalid_Options) << "Option이 잘못 들어갔지만 throw하지 않았습니다";
	EXPECT_THROW(cmdParser.parsing("SCH, ,-d, ,cl,CL3", ","), invalid_Options) << "Option이 잘못 들어갔지만 throw하지 않았습니다";
	EXPECT_THROW(cmdParser.parsing("SCH, ,-m, ,certi,ADV", ","), invalid_Options) << "Option이 잘못 들어갔지만 throw하지 않았습니다";

	EXPECT_THROW(cmdParser.parsing("ADD, , , ,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906", ","), invalid_argument) << "ADD cmd의 arg 값이 부족하지만 throw하지 않았습니다.";
	EXPECT_THROW(cmdParser.parsing("MOD, , , ,cl,CL3,phoneNum,010-9777-5455,234d", ","), invalid_argument) << "MOD cmd의 arg 값이 너무 많지만 throw하지 않았습니다.";

	
}