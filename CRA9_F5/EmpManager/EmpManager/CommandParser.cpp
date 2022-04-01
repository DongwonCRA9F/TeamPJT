#pragma once

#include "CommandParser.h"

bool CommandParser::parsing(string InputArg, string delimiter)
{
	return true;
}

enumCommandList CommandParser::getCommand()
{
	return enumCommandList::ADD;
}

vector<enumOptionList> CommandParser::getOptions()
{
	return {enumOptionList::None, enumOptionList::FindByDay_Birthday, enumOptionList::None};
}

vector<string> CommandParser::getConditions()
{
	return {"Dummy", "Dummy" , "Dummy" , "Dummy" };
}
