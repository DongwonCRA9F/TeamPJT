#pragma once
#include "gmock/gmock.h"

using namespace testing;

class CommandProcessor {
public:
	virtual CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition);

	MOCK_METHOD(CommandResult, run, (vector<enumOptionList>, vector<string>));
protected:
	CommandResult result;
};
template <typename DatabaseInterface>
class CommandProcessorADD :public CommandProcessor {
public:

};
template <typename DatabaseInterface>
class CommandProcessorMOD :public CommandProcessor {
public:

};
template <typename DatabaseInterface>
class CommandProcessorSCH :public CommandProcessor {
public:

};
template <typename DatabaseInterface>
class CommandProcessorDEL :public CommandProcessor {
public:

};
