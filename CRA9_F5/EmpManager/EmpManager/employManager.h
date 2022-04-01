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

public:
	vector<string> runCommand(string input);
	vector<string> cmdResultTostrList(string cmd, CommandResult cmdResult);
};

