#include <iostream>
#include "CommandResult.h"

using namespace std;
class TempDataBase {};
class TempCommand {};

class CommandProcessor {
public:
	virtual CommandResult run(TempCommand cmd) = 0;
private:
	TempDataBase DB;
};

class CommandProcessorADD :public CommandProcessor {
public:
	CommandResult run(TempCommand cmd) override {
		CommandResult result;
		return result;
	}
};

class CommandProcessorMOD :public CommandProcessor {
public:
	CommandResult run(TempCommand cmd) override {
		CommandResult result;
		return result;
	}
};

class CommandProcessorSCH :public CommandProcessor {
public:
	CommandResult run(TempCommand cmd) override {
		CommandResult result;
		return result;
	}
};

class CommandProcessorDEL :public CommandProcessor {
public:
	CommandResult run(TempCommand cmd) override {
		CommandResult result;
		return result;
	}
};