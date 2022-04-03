#pragma once

#include <string>
#include <vector>
#include "CommandParser.h"
#include "CommandProcessor.h"
#include "Employ.h"
#include "CommandResult.h"

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
	vector<string> clList = { "CL1", "CL2", "CL3", "CL4" };
	vector<string> certiList = { "ADV", "PRO", "EX" };

public:
	vector<string> runCommand(string input);
	vector<string> cmdResultTostrList(string cmd, CommandResult cmdResult);
};

