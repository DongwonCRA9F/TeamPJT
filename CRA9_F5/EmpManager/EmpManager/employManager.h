#pragma once

#include <string>
#include <vector>
#include "CommandParser.h"
#include "CommandProcessor.h"
#include "Employ.h"

using namespace std;

class EmployManager {

private:
	CommandParser cmdParser;
	CommandProcessor* cmdProcessor;

public:
	vector<Employ> runCommand(string input);
};
