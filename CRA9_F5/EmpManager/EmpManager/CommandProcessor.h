#include <iostream>
#include "CommandResult.h"
#include "CommandParser.h"

using namespace std;
class TempDataBase {};

class CommandProcessor {
public:
	virtual CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) = 0;
protected:
	TempDataBase DB;
	CommandResult result;
};

class CommandProcessorADD :public CommandProcessor {
public:
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		result.count = 0;
		return result;
	}
};

class CommandProcessorMOD :public CommandProcessor {
public:
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		result.list.clear();
		result.count = 1;
		return result;
	}
};

class CommandProcessorSCH :public CommandProcessor {
public:
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		result.list.clear();
		result.count = 1;
		return result;
	}
};

class CommandProcessorDEL :public CommandProcessor {
public:
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		result.list.clear();
		result.count = 1;
		return result;
	}
};