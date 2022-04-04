#include <iostream>
#include "CommandResult.h"
#include "CommandParser.h"
#include "DatabaseInterface.h"

using namespace std;

class CommandProcessor {
public:
	CommandProcessor() {};
	virtual CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) = 0;
protected:
	CommandResult result;
};

template <typename DatabaseInterface>
class CommandProcessorADD :public CommandProcessor {
public:
	CommandProcessorADD() : CommandProcessor() {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		if(DatabaseInterface::getInstance().insertItem(Employ(ResultCondition)))
			result.count = 1;
		else
			result.count = 0;
		return result;
	}
};

template <typename DatabaseInterface>
class CommandProcessorMOD :public CommandProcessor {
public:
	CommandProcessorMOD() : CommandProcessor() {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
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
		vector<Employ> listSearched = DatabaseInterface::getInstance().updateItems(ResultOption[1], {ResultCondition[0], ResultCondition[1]}, {ResultCondition[2], ResultCondition[3]});
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

template <typename DatabaseInterface>
class CommandProcessorSCH :public CommandProcessor {
public:
	CommandProcessorSCH() : CommandProcessor() {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		vector<Employ> listSearched = DatabaseInterface::getInstance().selectItems(ResultOption[1], { ResultCondition[0], ResultCondition[1] });
		result.list.clear();
		result.count = 0;
		for (auto aEmploy : listSearched) {
			result.list.push_back(aEmploy);
			result.count++;
		}

		return result;
	}
};

template <typename DatabaseInterface>
class CommandProcessorDEL :public CommandProcessor {
public:
	CommandProcessorDEL() : CommandProcessor() {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		vector<Employ> listSearched = DatabaseInterface::getInstance().deleteItems(ResultOption[1], { ResultCondition[0], ResultCondition[1] });
		result.list.clear();
		result.count = 0;
		for (auto aEmploy : listSearched) {
			result.list.push_back(aEmploy);
			result.count++;
		}
		return result;
	}
};
