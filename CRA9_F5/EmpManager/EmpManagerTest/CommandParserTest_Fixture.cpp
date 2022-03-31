
#include "pch.h"
#include "CommandParserTest_Fixture.h"

void CommandParserFixture::SetUp() {
}

void CommandParserFixture::TearDown() {
}



TEST_F(CommandParserFixture, ParsingPositiveTest) {
	CommandParser cmdParser;

	cmdParser.parsing("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");
	EXPECT_EQ(cmdParser.getCommand(), enumCommandList::MOD);

	auto Options = cmdParser.getOptions();
	vector<enumOptionList> ExpectedOptionList = { enumOptionList::None, enumOptionList::None, enumOptionList::None };
	EXPECT_TRUE(equal(Options.begin(), Options.end(), ExpectedOptionList.begin()));

	auto Conditions = cmdParser.getConditions();
	vector<std::string> ExpectedConditionList = { "15123099","VXIHXOTH JHOP","CL3","010-3112-2609","19771211","ADV"};
	EXPECT_TRUE(equal(Conditions.begin(), Conditions.end(), ExpectedConditionList.begin()));
}
