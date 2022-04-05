#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <map>

using namespace std;


enum class enumCommandList{
	NONE = -1,
	ADD = 0,
	DEL,
	SCH,
	MOD,
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
private:
	string errmsg;
public:
	invalid_Command(string msg) : errmsg(msg) {};
	const char* what() const noexcept override
	{
		return errmsg.c_str();
	}
};

class invalid_Options : public exception {
private:
	string errmsg;
public:
	invalid_Options(string msg) : errmsg(msg) {};
	const char* what() const noexcept override
	{
		return errmsg.c_str();
	}
};


class CommandParserChecker {
public:
	virtual bool ArgSizeCheck(const vector<string>& Condition) const = 0;
	virtual bool OptionCheck(const vector<enumOptionList>& OptionList, string ColumnName) const {
		if (OptionList[1] == enumOptionList::FindByLastNum_PhoneNum || OptionList[1] == enumOptionList::FindByMiddleNum_PhoneNum) {
			if (ColumnName != "phoneNum") {
				throw invalid_Options("PhoneNumber를 찾는 옵션이지만 Column이 phoneNum가 아닙니다.");
			}
		}

		if (OptionList[1] == enumOptionList::FindByFirstName_Name || OptionList[1] == enumOptionList::FindByLastName_Name) {
			if (ColumnName != "name") {
				throw invalid_Options("name을 찾는 옵션이지만 Column이 name이 아닙니다.");
			}
		}

		if (OptionList[1] == enumOptionList::FindByDay_Birthday || OptionList[1] == enumOptionList::FindByMonth_Birthday || OptionList[1] == enumOptionList::FindByYear_Birthday) {
			if (ColumnName != "birthday") {
				throw invalid_Options("birthday를 찾는 옵션이지만 Column이 birthday가 아닙니다.");
			}
		}
		return true;
	};
};

class AddCommandChecker : public CommandParserChecker {
public:
	virtual bool ArgSizeCheck(const vector<string>& Condition) const override {
		if (Condition.size() != 6) {
			throw invalid_argument("ADD의 condition 개수가 6개가 아닙니다.");
		}
		return true;
	};
	virtual bool OptionCheck(const vector<enumOptionList>& OptionList, string ColumnName) const override {
		for (const auto& opt : OptionList) {
			if (opt != enumOptionList::None) {
				throw invalid_Options("ADD cmd는 옵션을 사용하지 않습니다.");
			}
		}
		return true;
	};
};

class ModCommandChecker : public CommandParserChecker {
public:
	virtual bool ArgSizeCheck(const vector<string>& Condition) const override {
		if (Condition.size() != 4) {
			throw invalid_argument("MOD의 condition 개수가 4개가 아닙니다.");
		}
		return true;
	};
};

class DelCommandChecker : public CommandParserChecker {
public:
	virtual bool ArgSizeCheck(const vector<string>& Condition) const override {
		if (Condition.size() != 2) {
			throw invalid_argument("DEL의 condition 개수가 2개가 아닙니다.");
		}
		return true;
	};
};

class SchCommandChecker : public CommandParserChecker {
public:
	virtual bool ArgSizeCheck(const vector<string>& Condition) const override {
		if (Condition.size() != 2) {
			throw invalid_argument("Search의 condition 개수가 2개가 아닙니다.");
		}
		return true;
	};
};



class CommandParser {
private:
	enumCommandList Command;
	vector<enumOptionList> CommandOption;
	vector<string> Conditions;

	map<enumCommandList, unique_ptr<CommandParserChecker>> ValidChecker;

	const size_t CommandNum = 1;
	const size_t OptionNum = 3;

	void InitData();
	vector<string> Split(string input, string delimiter);
	enumOptionList SetOption_1(string optionString);
	enumOptionList SetOption_2(string optionString, string FirstColumn);
	enumOptionList SetOption_3(string optionString);

public:
	CommandParser() : Command(enumCommandList::NONE) {
		ValidChecker[enumCommandList::ADD] = make_unique<AddCommandChecker>();
		ValidChecker[enumCommandList::DEL] = make_unique<DelCommandChecker>();
		ValidChecker[enumCommandList::SCH] = make_unique<SchCommandChecker>();
		ValidChecker[enumCommandList::MOD] = make_unique<ModCommandChecker>();
	}
	bool parsing(string InputArg, const string delimiter);
	enumCommandList getCommand();
	vector<enumOptionList> getOptions();
	vector<string> getConditions();
};

