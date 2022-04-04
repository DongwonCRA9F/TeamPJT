#pragma once

#include "CommandParser.h"

void CommandParser::InitData()
{
	Command = enumCommandList::NONE;
	CommandOption.erase(CommandOption.begin(), CommandOption.end());
	Conditions.erase(Conditions.begin(), Conditions.end());
}

vector<string> CommandParser::Split(string input, string delimiter)
{
	vector<string> SplitedResult;
	size_t prevPos = 0;
	size_t curPos = 0;

	curPos = input.find(delimiter);
	while (curPos != string::npos) {
		SplitedResult.push_back(input.substr(prevPos, curPos - prevPos));
		prevPos = curPos + 1;
		curPos = input.find(delimiter, curPos + 1);
	}
	SplitedResult.push_back(input.substr(prevPos));

	return SplitedResult;
}

bool CommandParser::SetCommand(string cmd)
{
	if (cmd == "ADD") Command = enumCommandList::ADD;
	else if (cmd == "MOD") Command = enumCommandList::MOD;
	else if (cmd == "DEL") Command = enumCommandList::DEL;
	else if (cmd == "SCH") Command = enumCommandList::SCH;
	else {
		return false;
	}

	return true;
}

enumOptionList CommandParser::SetOption_1(string optionString)
{
	if (optionString == " ") return enumOptionList::None;
	else if (optionString == "-p") return enumOptionList::RecordPrint;
	else {
		throw invalid_Options("ù��° Option�� ������� �ʴ� �ɼ��� ���Խ��ϴ�.");
	}
	return enumOptionList::None;
}

enumOptionList CommandParser::SetOption_2(string optionString, string FirstColumn)
{
	if (optionString == " ") return enumOptionList::None;
	else if (optionString == "-f") return enumOptionList::FindByFirstName_Name;
	else if (optionString == "-l") {
		if (FirstColumn == "name")
			return enumOptionList::FindByLastName_Name;
		else if (FirstColumn == "phoneNum")
			return enumOptionList::FindByLastNum_PhoneNum;
		else {
			throw invalid_Options("-l�ɼǰ� column Name�� ��Ī���� �ʽ��ϴ�.");
		}
	}
	else if (optionString == "-m") {
		if (FirstColumn == "birthday")
			return enumOptionList::FindByMonth_Birthday;
		else if (FirstColumn == "phoneNum")
			return enumOptionList::FindByMiddleNum_PhoneNum;
		else {
			throw invalid_Options("-m�ɼǰ� column Name�� ��Ī���� �ʽ��ϴ�.");
		}
	}
	else if (optionString == "-y") return enumOptionList::FindByYear_Birthday;
	else if (optionString == "-d") return enumOptionList::FindByDay_Birthday;
	else {
		throw invalid_Options("ù��° Option�� ������� �ʴ� �ɼ��� ���Խ��ϴ�.");
	}
	return enumOptionList::None;
}

enumOptionList CommandParser::SetOption_3(string optionString)
{
	if (optionString == " ") return enumOptionList::None;
	else {
		throw invalid_Options("�� ��° �ɼǿ� ������� �ʴ� �ɼ��� ���Խ��ϴ�.");
	}
	return enumOptionList::None;
}

bool CommandParser::parsing(string InputArg, const string delimiter) {
	InitData();

	vector<string> SplitedString = Split(InputArg, delimiter);

	if (SplitedString.size() <= CommandNum + OptionNum) {
		throw invalid_argument("Split�Ϸ��� argument ������ �ʹ� �۽��ϴ�.");
	}

	if (SetCommand(SplitedString[0]) == false) {
		throw invalid_Command("������� ���� cmd�� ���Խ��ϴ�.");
	}

	Conditions.assign(SplitedString.begin() + CommandNum + OptionNum, SplitedString.end());


	try {
		CommandOption.push_back(SetOption_1(SplitedString[1]));
		CommandOption.push_back(SetOption_2(SplitedString[2], Conditions[0]));
		CommandOption.push_back(SetOption_3(SplitedString[3]));
	}
	catch (invalid_Options& e){
		throw e;
	}






	// valid �˻�

	CommandParserChecker* ValidChecker;

	if (Command == enumCommandList::ADD) ValidChecker = new AddCommandChecker();
	else if (Command == enumCommandList::MOD) ValidChecker = new ModCommandChecker();
	else if (Command == enumCommandList::DEL) ValidChecker = new DelCommandChecker();
	else if (Command == enumCommandList::SCH) ValidChecker = new SchCommandChecker();
	else return false;

	try {
		ValidChecker->OptionCheck(CommandOption, Conditions[0]);
		ValidChecker->ArgSizeCheck(Conditions);
	}
	catch (invalid_argument& e) {
		throw e;
	}
	catch (invalid_Options& e) {
		throw e;
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
