#pragma once
#include "pch.h"
#include "../EmpManager/Employ.h"
#include "../EmpManager/CommandProcessor.h"
#include "MockDatabase.h"

class CommandProcessorFixture : public ::testing::Test {
protected:
	void SetUp() override;
	void TearDown() override;
};
