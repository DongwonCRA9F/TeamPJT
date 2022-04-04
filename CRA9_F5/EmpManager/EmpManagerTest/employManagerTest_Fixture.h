#pragma once

#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../EmpManager/employManager.h"

using namespace testing;

class EmployManagerFixture : public ::testing::Test {

protected:
	void SetUp() override;
	void TearDown()override;

	EmployManager empManager;
	CommandResult sampleCmdResult;
	vector<Employ> sampleEmpList;
	vector<string> sampleOutList;



	void makeSampleEmpList();
	void makeSampleOutList();
};