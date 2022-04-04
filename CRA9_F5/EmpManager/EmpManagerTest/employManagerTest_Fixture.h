#pragma once

#include "pch.h"
#include "gtest/gtest.h"
#include "../EmpManager/employManager.h"
#include "../EmpManager/employManager.cpp"

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