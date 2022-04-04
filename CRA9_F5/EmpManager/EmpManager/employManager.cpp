#pragma once

#include "employManager.h"

vector<string> EmployManager::runCommand(string input) {
	vector<string> ret;

	try {
		if (!cmdParser.parsing(input, ",")) {
			throw exception();
		}
	}
	catch (const invalid_Command& e) {
		cout << e.what() << endl;
		return ret;
	}
	catch (const invalid_Options& e) {
		cout << e.what() << endl;
		return ret;
	}
	catch (const exception& e) {
		cout << "비정상적인 종료가 감지되었습니다" << endl;
		return ret;
	}

	cmd = cmdParser.getCommand();
	options = cmdParser.getOptions();
	conditions = cmdParser.getConditions();

	switch (cmd) {
		case enumCommandList::ADD :
			cmdProcessor = new CommandProcessorADD();
			break;
		case enumCommandList::DEL :
			cmdProcessor = new CommandProcessorDEL();
			break;
		case enumCommandList::MOD :
			cmdProcessor = new CommandProcessorMOD();
			break;
		case enumCommandList::SCH :
			cmdProcessor = new CommandProcessorSCH();
			break;
	}

	cmdResult = cmdProcessor->run(options, conditions);

	if (cmd == enumCommandList::ADD)
		return ret;

	if (options[0] == enumOptionList::None)
		ret.push_back(cmdList[static_cast<int>(cmd)] + "," + cmdResult.getSimpleResults());
	else
		ret = cmdResultTostrList(cmd, cmdResult);

	return ret;
}

vector<string> EmployManager::cmdResultTostrList(enumCommandList cmd, CommandResult cmdResult) {
	vector<string> ret;

	if (cmdResult.count == 0) {
		ret.push_back(cmdList[static_cast<int>(cmd)] + "," + cmdResult.getSimpleResults());
		return ret;
	}

	for (auto& employ : cmdResult.list) {
		string str = cmdList[static_cast<int>(cmd)];
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
