#pragma once

#include "CommandParser.h"

void CommandParser::InitData()
{
	Command = enumCommandList::NONE;
	CommandOption.erase(CommandOption.begin(), CommandOption.end());
	Conditions.erase(Conditions.begin(), Conditions.end());
}

bool CommandParser::parsing(string InputArg, const string delimiter) {
	InitData();

	vector<string> SplitedString;
	size_t prevPos = 0;
	size_t curPos = 0;
	curPos = InputArg.find(delimiter);
	while (curPos != string::npos) {
		SplitedString.push_back(InputArg.substr(prevPos, curPos - prevPos));
		prevPos = curPos + 1;
		curPos = InputArg.find(delimiter, curPos + 1);
	}
	SplitedString.push_back(InputArg.substr(prevPos));


	if (SplitedString[0] == "ADD") Command = enumCommandList::ADD;
	else if (SplitedString[0] == "MOD") Command = enumCommandList::MOD;
	else if (SplitedString[0] == "DEL") Command = enumCommandList::DEL;
	else if (SplitedString[0] == "SCH") Command = enumCommandList::SCH;
	else {
		throw invalid_Command();
	}

	Conditions.assign(SplitedString.begin() + 4, SplitedString.end());

	if (SplitedString[1] == " ") CommandOption.push_back(enumOptionList::None);
	else if (SplitedString[1] == "-p") CommandOption.push_back(enumOptionList::RecordPrint);
	else {
		throw invalid_Options();
	}

	if (SplitedString[2] == " ") CommandOption.push_back(enumOptionList::None);
	else if (SplitedString[2] == "-f") CommandOption.push_back(enumOptionList::FindByFirstName_Name);
	else if (SplitedString[2] == "-l") {
		if (Conditions[0] == "name")
			CommandOption.push_back(enumOptionList::FindByLastName_Name);
		else if (Conditions[0] == "phoneNum")
				CommandOption.push_back(enumOptionList::FindByLastNum_PhoneNum);
		else {
			throw invalid_Options();
		}
	}
	else if (SplitedString[2] == "-m") {
		if (Conditions[0] == "birthday")
			CommandOption.push_back(enumOptionList::FindByMonth_Birthday);
		else if (Conditions[0] == "phoneNum")
			CommandOption.push_back(enumOptionList::FindByMiddleNum_PhoneNum);
		else {
			throw invalid_Options();
		}
	}
	else if (SplitedString[2] == "-y") CommandOption.push_back(enumOptionList::FindByYear_Birthday);
	else if (SplitedString[2] == "-d") CommandOption.push_back(enumOptionList::FindByDay_Birthday);
	else {
		throw invalid_Options();
	}

	if (SplitedString[3] == " ") CommandOption.push_back(enumOptionList::None);
	else {
		throw invalid_Options();
	}


	// valid 검사

	if (Command == enumCommandList::ADD) {
		for (const auto& opt : CommandOption) {
			if (opt != enumOptionList::None) {
				throw invalid_Options();
			}
		}
		if (Conditions.size() != 6) {
			throw invalid_argument("ADD의 condition 개수가 6개가 아닙니다.");
		}
	}
	if (Command == enumCommandList::MOD) {
		if (Conditions.size() != 4) {
			throw invalid_argument("MOD의 condition 개수가 4개가 아닙니다.");
		}
	}

	if (Command == enumCommandList::DEL) {
		if (Conditions.size() != 2) {
			throw invalid_argument("DEL의 condition 개수가 2개가 아닙니다.");
		}
	}
	if (Command == enumCommandList::SCH) {
		if (Conditions.size() != 2) {
			throw invalid_argument("Search의 conditions의 개수가 2개가 아닙니다.");
		}
	}

	if (CommandOption[1] == enumOptionList::FindByLastNum_PhoneNum || CommandOption[1] == enumOptionList::FindByMiddleNum_PhoneNum) {
		if (Conditions[0] != "phoneNum") {
			throw invalid_Options();
		}
	}

	if (CommandOption[1] == enumOptionList::FindByFirstName_Name || CommandOption[1] == enumOptionList::FindByLastName_Name) {
		if (Conditions[0] != "name") {
			throw invalid_Options();
		}
	}

	if (CommandOption[1] == enumOptionList::FindByDay_Birthday || CommandOption[1] == enumOptionList::FindByMonth_Birthday || CommandOption[1] == enumOptionList::FindByYear_Birthday) {
		if (Conditions[0] != "birthday") {
			throw invalid_Options();
		}
	}


	return true;
}

enumCommandList CommandParser::getCommand()
{
	return Command;
}

vector<enumOptionList> CommandParser::getOptions()
{
	return CommandOption;
}

vector<string> CommandParser::getConditions()
{
	return Conditions;
}
