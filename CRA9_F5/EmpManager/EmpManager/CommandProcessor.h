#include <iostream>
#include "CommandResult.h"
#include "CommandParser.h"
#include "DatabaseInterface.h"

using namespace std;
class TempDataBase {};

class CommandProcessor {
public:
	CommandProcessor(DatabaseInterface* DB) { DB_ = DB; };
	virtual CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) = 0;
protected:
	DatabaseInterface* DB_ = nullptr;
	CommandResult result;
};

class CommandProcessorADD :public CommandProcessor {
public:
	CommandProcessorADD(DatabaseInterface* DB) : CommandProcessor(DB) {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		if (DB_ == nullptr) {
			cout << "ERROR: DB is not registered!" << endl;
		}
		if(DB_->insertItem(Employ(ResultCondition)))
			result.count = 1;
		else
			result.count = 0;
		return result;
	}
};

class CommandProcessorMOD :public CommandProcessor {
public:
	CommandProcessorMOD(DatabaseInterface* DB) : CommandProcessor(DB) {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		if (DB_ == nullptr) {
			cout << "ERROR: DB is not registered!" << endl;
		}
#if 0
		vector<Employ> listSearched = DB_->selectItems(enumOptionList::None, { ResultCondition[0], ResultCondition[1] });

		//TODO: option2(ResultOption[1]) 
		if (ResultOption[1] == enumOptionList::FindByFirstName_Name) {
		} else if (ResultOption[1] == enumOptionList::FindByLastName_Name) {
		} else if (ResultOption[1] == enumOptionList::FindByMiddleNum_PhoneNum) {
		} else if (ResultOption[1] == enumOptionList::FindByLastNum_PhoneNum) {
		} else if (ResultOption[1] == enumOptionList::FindByYear_Birthday) {
		} else if (ResultOption[1] == enumOptionList::FindByMonth_Birthday) {
		} else if (ResultOption[1] == enumOptionList::FindByDay_Birthday) {
		}

		result.list.clear();
		result.count = 0;
		for (auto aEmploy : listSearched) {
			result.list.push_back(DB_->updateItems(enumOptionList::None, aEmploy.getEmployeeNum(), ResultCondition[2], ResultCondition[3]));
			result.count++;
		}
#else
		vector<Employ> listSearched = DB_->updateItems(ResultOption[1], { ResultCondition[0], ResultCondition[1] }, { ResultCondition[2], ResultCondition[3] });
		result.list.clear();
		result.count = 0;
		for (auto aEmploy : listSearched) {
			result.list.push_back(aEmploy);
			result.count++;
		}
#endif
		return result;
	}
};

class CommandProcessorSCH :public CommandProcessor {
public:
	CommandProcessorSCH(DatabaseInterface* DB) : CommandProcessor(DB) {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		if (DB_ == nullptr) {
			cout << "ERROR: DB is not registered!" << endl;
		}
		vector<Employ> listSearched = DB_->selectItems(ResultOption[1], { ResultCondition[0], ResultCondition[1] });
		result.list.clear();
		result.count = 0;
		for (auto aEmploy : listSearched) {
			result.list.push_back(aEmploy);
			result.count++;
		}

		return result;
	}
};

class CommandProcessorDEL :public CommandProcessor {
public:
	CommandProcessorDEL(DatabaseInterface* DB) : CommandProcessor(DB) {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		if (DB_ == nullptr) {
			cout << "ERROR: DB is not registered!" << endl;
		}
		vector<Employ> listSearched = DB_->deleteItems(ResultOption[1], { ResultCondition[0], ResultCondition[1] });
		result.list.clear();
		result.count = 0;
		for (auto aEmploy : listSearched) {
			result.list.push_back(aEmploy);
			result.count++;
		}
		return result;
	}
};
