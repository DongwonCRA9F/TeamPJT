#pragma once

#include <string>
#include <vector>
#include "CommandParser.h"

#include "Employ.h"
#include "CommandResult.h"
#include "DatabaseInterface.h"

#ifdef _UNIT_TEST
#include "../EmpManagerTest/MockCommandProcessor.h"
#define private public
#else
#include "CommandProcessor.h"
#endif

using namespace std;

class EmployManager {
private:
	enumCommandList cmd;
	vector<string> conditions;
	vector<enumOptionList> options;
	CommandParser cmdParser;
	CommandProcessor* cmdProcessor;
	CommandResult cmdResult;

	vector<string> cmdList = { "ADD", "DEL", "SCH", "MOD" };
	vector<string> clList = { "NONE", "CL1", "CL2", "CL3", "CL4" };
	vector<string> certiList = { "ADV", "PRO", "EX" };


	CommandProcessor* getProcessor(enumCommandList cmd);
	string empNumTostr(int employNum);
public:
	vector<string> runCommand(string input);
	vector<string> cmdResultTostrList(enumCommandList cmd, CommandResult cmdResult);
};
