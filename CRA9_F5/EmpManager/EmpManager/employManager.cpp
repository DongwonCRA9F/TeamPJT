#pragma once

#include "employManager.h"

vector<string> EmployManager::runCommand(string input) {
	vector<string> ret;

	// Parsing 작업
	try {
		if (!cmdParser.parsing("ADD,n, , ,01122329,DN WD,CL4,010-7174-5680,20071117,PRO", ",")) {
			// Parsing 실패.
		}
	}
	catch (const invalid_Command& e) {
		cout << e.what() << endl;
	}
	catch (const invalid_Options& e) {
		cout << e.what() << endl;
	}

	cmd = cmdParser.getCommand();
	options = cmdParser.getOptions();
	conditions = cmdParser.getConditions();

	// Command 에 따라 cmdProcessor 호출
	switch (cmd) {
		case enumCommandList::ADD :
			cmdProcessor = new CommandProcessorADD();
			cmdResult = cmdProcessor->run(options, conditions);
			break;
		case enumCommandList::DEL :
			cmdProcessor = new CommandProcessorDEL();
			cmdResult = cmdProcessor->run(options, conditions);
			if (options[0] == enumOptionList::None)
				ret.push_back("DEL," + to_string(cmdResult.count));
			else
				ret = cmdResultTostrList("DEL", cmdResult);
			break;
		case enumCommandList::MOD :
			cmdProcessor = new CommandProcessorMOD();
			cmdResult = cmdProcessor->run(options, conditions);
			if (options[0] == enumOptionList::None)
				ret.push_back("MOD," + to_string(cmdResult.count));
			else
				ret = cmdResultTostrList("MOD", cmdResult);
			break;
		case enumCommandList::SCH :
			cmdProcessor = new CommandProcessorSCH();
			cmdResult = cmdProcessor->run(options, conditions);
			if (options[0] == enumOptionList::None)
				ret.push_back("SCH," + to_string(cmdResult.count));
			else
				ret = cmdResultTostrList("SCH", cmdResult);
			break;
	}

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
