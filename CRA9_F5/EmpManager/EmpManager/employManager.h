#pragma once

#include <string>
#include <vector>
#include "CommandParser.h"
#include "CommandProcessor.h"
#include "Employ.h"

using namespace std;

class EmployManager {

private:
	enumCommandList cmd;
	vector<string> conditions;
	vector<enumOptionList> options;
	CommandParser cmdParser;
	CommandProcessor* cmdProcessor;

public:
	vector<string> runCommand(string input);
	vector<string> empListTostrList(vector<Employ> empList);
};

