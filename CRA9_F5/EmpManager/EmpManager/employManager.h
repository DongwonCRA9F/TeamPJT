#pragma once

#include <string>
#include <vector>
#include "tempHeader.h"

using namespace std;


class EmployManager {

private:
	CommandParser cmdParser;
	CommandProcessor* cmdProcessor;

public:
	vector<Employ> runCommand(string input);
};
