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
	CommandParserChecker* ValidChecker;

	try {
		if (SplitedString.size() <= CommandNum + OptionNum) {
			throw invalid_argument("Split�Ϸ��� argument ������ �ʹ� �۽��ϴ�.");
		}

		if (SplitedString[0] == "ADD") {
			Command = enumCommandList::ADD;
			ValidChecker = new AddCommandChecker();
		}
		else if (SplitedString[0] == "MOD") {
			Command = enumCommandList::MOD;
			ValidChecker = new ModCommandChecker();
		}
		else if (SplitedString[0] == "DEL") {
			Command = enumCommandList::DEL;
			ValidChecker = new DelCommandChecker();
		}
		else if (SplitedString[0] == "SCH") {
			Command = enumCommandList::SCH;
			ValidChecker = new SchCommandChecker();
		}
		else {
			throw invalid_Command("������� ���� cmd�� ���Խ��ϴ�.");
		}

		CommandOption.push_back(SetOption_1(SplitedString[1]));
		CommandOption.push_back(SetOption_2(SplitedString[2], SplitedString[4]));
		CommandOption.push_back(SetOption_3(SplitedString[3]));

		Conditions.assign(SplitedString.begin() + CommandNum + OptionNum, SplitedString.end());

		ValidChecker->OptionCheck(CommandOption, Conditions[0]);
		ValidChecker->ArgSizeCheck(Conditions);
	}
	catch (invalid_Command& e) {
		throw e;
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
