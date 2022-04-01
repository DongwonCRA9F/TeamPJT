#pragma once


#include "pch.h"
#include "gtest/gtest.h"
#include "../EmpManager/CommandParser.h"

class CommandParserFixture : public ::testing::Test {
protected:
	void SetUp() override;
	void TearDown() override;
};