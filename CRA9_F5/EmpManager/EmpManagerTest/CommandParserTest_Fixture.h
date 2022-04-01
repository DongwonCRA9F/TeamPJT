#pragma once


#include "pch.h"
#include "gtest/gtest.h"
#include "../EmpManager/CommandParser.h"

struct InputList {
	string InputString;

	enumCommandList ResultCommand;
	vector<enumOptionList> ResultOption;
	vector<string> ResultCondition;
};

class CommandParserFixture : public ::testing::Test {
protected:
	void SetUp() override;
	void TearDown() override;

	void MakeSampleInputList();

	vector<InputList> SampleInputList;
};