#pragma once

#include "employManager.h"

vector<string> EmployManager::runCommand(string input) {
	vector<string> ret;

	// TODO

	return ret;
}

vector<string> EmployManager::cmdResultTostrList(string cmd, CommandResult cmdResult) {
	vector<string> ret;

	if (cmd == "ADD")
		return ret;

	if (cmdResult.count == 0) {
		ret.push_back(cmd + ",NONE");
		return ret;
	}

	for (auto& employ : cmdResult.list) {
		string str = cmd;
		str += ("," + to_string(employ.getEmployeeNum()));
		str += ("," + employ.getName().getFullName());
		str += ("," + clList[static_cast<int>(employ.getCl())]);
		str += ("," + employ.getPhoneNum().getPhoneNumber());
		str += ("," + employ.getBirthday().getBirthday());
		str += ("," + certiList[static_cast<int>(employ.getCerti())]);
		ret.push_back(str);
	}

	return ret;
}
