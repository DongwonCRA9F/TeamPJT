#pragma once
//#include "pch.h"
#include "gtest/gtest.h"
#include "../EmpManager/CommandProcessor.h"


class CommandProcessorFixture : public ::testing::Test {
protected:
	void SetUp() override;
	void TearDown() override;
};