#pragma once

#include "employManager.h"

vector<string> EmployManager::runCommand(string input) {
	vector<string> ret;

	// Parsing �۾�
	try {
		if (!cmdParser.parsing("ADD,n, , ,01122329,DN WD,CL4,010-7174-5680,20071117,PRO", ",")) {
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
		cout << "���������� ���ᰡ �����Ǿ����ϴ�" << endl;
		return ret;
	}

	cmd = cmdParser.getCommand();
	options = cmdParser.getOptions();
	conditions = cmdParser.getConditions();

	// Command �� ���� cmdProcessor ȣ��
	switch (cmd) {
		case enumCommandList::ADD :
			cmdProcessor = new CommandProcessorADD();
			cmdResult = cmdProcessor->run(options, conditions);
			break;
		case enumCommandList::DEL :
			cmdProcessor = new CommandProcessorDEL();
			cmdResult = cmdProcessor->run(options, conditions);
			if (options[0] == enumOptionList::None)
				ret.push_back("DEL," + cmdResult.getSimpleResults());
			else
				ret = cmdResultTostrList("DEL", cmdResult);
			break;
		case enumCommandList::MOD :
			cmdProcessor = new CommandProcessorMOD();
			cmdResult = cmdProcessor->run(options, conditions);
			if (options[0] == enumOptionList::None)
				ret.push_back("MOD," + cmdResult.getSimpleResults());
			else
				ret = cmdResultTostrList("MOD", cmdResult);
			break;
		case enumCommandList::SCH :
			cmdProcessor = new CommandProcessorSCH();
			cmdResult = cmdProcessor->run(options, conditions);
			if (options[0] == enumOptionList::None)
				ret.push_back("SCH," + cmdResult.getSimpleResults());
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
		ret.push_back(cmd + "," + cmdResult.getSimpleResults());
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
