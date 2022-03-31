#pragma once
#include <string>
#include <vector>
using namespace std;

class Employ {
	// Temp Employ for build
	string employeeNum;
	string name;
	string ci;
	string phoneNumber;
	string birthDay;
	string certi;
};

enum class enumCommandList {
	// Temp cmdParser for build
	ADD = 0,
	DEL,
	SCH,
	MOD
};

enum class enumOptionList {
	// Temp cmdParser for build
	None = 0,

	RecordPrint = 1,

	FindByFirstName_Name,
	FindByLastName_Name,

	FindByMiddleNum_PhoneNum,
	FindByLastNum_PhoneNum,

	FindByYear_Birthday,
	FindByMonth_Birthday,
	FindByDay_Birthday,
};

class CommandParser {
	// Temp cmdParser for build
private:
	enumCommandList Command;
	vector<enumOptionList> CommandOption;
	vector<string> Conditions;

public:
	bool parsing(string InputArg);
	enumCommandList getCommand();
	vector<enumOptionList> getOptions();
	vector<string> getConditions();
};

class CommandResult {
public:
	int count;
	vector<Employ> list;
};

class TempDataBase { };
class TempCommand { };

class CommandProcessor {
	// Temp cmdProcessor for build
public:
	CommandResult run(TempCommand cmd) {

	}
private:
	TempDataBase DB;
};