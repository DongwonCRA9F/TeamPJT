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
		return "ù��° Command ���ڰ� ����� ������ �ʾҽ��ϴ�.";
	}
};

class invalid_Options : public exception {
public:
	const char* what() const noexcept override
	{
		return "������� �ʴ� �ɼ��� ���Խ��ϴ�.";
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