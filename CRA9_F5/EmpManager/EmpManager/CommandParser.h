#pragma once

#include <string>
#include <vector>

using namespace std;


enum class enumCommandList{
	ADD = 0,
	DEL,
	SCH,
	MOD
};

enum class enumOptionList {
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

class invalid_Command : public exception {
public:
	const char* what() const noexcept override
	{
		return "첫번째 Command 인자가 제대로 들어오지 않았습니다.";
	}
};

class invalid_Options : public exception {
public:
	const char* what() const noexcept override
	{
		return "사용하지 않는 옵션이 들어왔습니다.";
	}
};


class CommandParser {
private:
	enumCommandList Command;
	vector<enumOptionList> CommandOption;
	vector<string> Conditions;

public:
	bool parsing(string InputArg, string delimiter);
	enumCommandList getCommand();
	vector<enumOptionList> getOptions();
	vector<string> getConditions();
};