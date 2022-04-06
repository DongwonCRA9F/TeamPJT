#include <iostream>
#include <cctype>
#include <sstream>
#include "CommandResult.h"
#include "CommandParser.h"
#include "DatabaseInterface.h"

using namespace std;

class CommandProcessor {
public:
	CommandProcessor() {};
	virtual CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) = 0;
protected:
	bool is_digit(string str) {
		return atoi(str.c_str()) != 0 || str.compare("0") == 0;
	}
	bool IsValidEmployNum(string str) {
		if (str.length() != 8) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}
		int year = stoi(str.substr(0, 2));
		if (year > 21 && year < 69) return false;

		return true;
	}
	bool IsValidName(string str) {
		int count_space = 0;
		if (str.length() < 3 || str.length() > 15) return false;
		for (auto c : str) {
			if (!isalpha(c)) {
				if (isspace(c)) count_space++;
				else return false;
			}			
		}
		if (count_space != 1) return false;
		if (str.substr(0, 1) == " " || str.substr(str.length() - 1, 1) == " ") {
			return false;
		}
		return true;
	}
	bool IsValidNameFirstLast(string str) {
		int count_space = 0;
		if (str.length() < 1 || str.length() > 13) return false;
		for (auto c : str) {
			if (!isalpha(c)) {
				return false;
			}
		}
		return true;
	}

	bool IsValidCl(string str) {
		if (str.length() != 3) return false;
		if (str.substr(0, 2) != "CL") return false;
		if (!is_digit(str.substr(2, 1))) return false;
		int cl_level = stoi(str.substr(2, 1));
		if (cl_level == 0 || cl_level > 4) return false;
		return true;
	}
	bool IsValidPhoneNum(string full) {
		istringstream ss(full);
		string str_buffer;
		vector<string> phoneNum;
		phoneNum.clear();

		while (getline(ss, str_buffer, '-')) {
			phoneNum.push_back(str_buffer);
		}

		if (phoneNum.size() != 3) return false;
		for (string num_str : phoneNum) {
			for (char c : num_str) {
				if (!isdigit(c))
					return false;
			}
		}

		if (phoneNum[0] != "010") return false;
		if (phoneNum[1].length() != 4) return false;
		if (phoneNum[2].length() != 4) return false;

		return true;
	}

	bool IsValidPhoneNumMiddleLast(string str) {
		if (str.length() != 4) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}

		return true;
 	}

	bool IsValidBirthday(string str) {
		if (str.length() != 8) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}
		int year = stoi(str.substr(0, 4));
		int month = stoi(str.substr(4, 2));
		int day = stoi(str.substr(6, 24));
		if (year < 1900 || year > 2022) return false;
		if (month < 1 || month > 12) return false;
		if (day < 1 || day > 31) return false;

		return true;
	}
	bool IsValidBirthdayYear(string str) {
		if (str.length() != 4) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}
		int year = stoi(str);
		if (year < 1900 || year > 2022) return false;
		
		return true;
	}
	bool IsValidBirthdayMonth(string str) {
		if (str.length() != 2) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}
		int month = stoi(str);
		if (month < 1 || month > 12) return false;

		return true;
	}
	bool IsValidBirthdayDay(string str) {
		if (str.length() != 2) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}
		int day = stoi(str);
		if (day < 1 || day > 31) return false;

		return true;
	}

	bool IsValidCerti(string str) {
		if (str.length() < 2 || str.length() > 3) return false;
		if (str!="ADV" && str != "PRO" && str != "EX") return false;
		return true;
	}
	CommandResult result;
};

template <typename DatabaseInterface>
class CommandProcessorADD :public CommandProcessor {
public:
	CommandProcessorADD() : CommandProcessor() {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		if(!IsValidEmployNum(ResultCondition[static_cast<int>(enumEmploy::EMPLOYEENUM)])) {
			throw invalid_argument("[CommandProcessorADD] invalid_argument. (EMPLOYEENUM)\n");
		}
		if (!IsValidName(ResultCondition[static_cast<int>(enumEmploy::NAME)])) {
			throw invalid_argument("[CommandProcessorADD] invalid_argument. (NAME)\n");
		}
		if (!IsValidCl(ResultCondition[static_cast<int>(enumEmploy::CL)])) {
			throw invalid_argument("[CommandProcessorADD] invalid_argument. (CL)\n");
		}
		if (!IsValidPhoneNum(ResultCondition[static_cast<int>(enumEmploy::PHONENUM)])) {
			throw invalid_argument("[CommandProcessorADD] invalid_argument. (PHONENUM)\n");
		}
		if (!IsValidBirthday(ResultCondition[static_cast<int>(enumEmploy::BIRTHDAY)])) {
			throw invalid_argument("[CommandProcessorADD] invalid_argument. (BIRTHDAY)\n");
		}
		if (!IsValidCerti(ResultCondition[static_cast<int>(enumEmploy::CERTI)])) {
			throw invalid_argument("[CommandProcessorADD] invalid_argument. (CERTI)\n");
		}

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
		if(ResultCondition[0] == "employNum" && !IsValidEmployNum(ResultCondition[1])) {
			throw invalid_argument("[CommandProcessorSCH] invalid_argument. (EMPLOYEENUM)\n");
		}
		if (ResultCondition[0] == "name") {
			if (ResultOption[1] == enumOptionList::None) {
				if (!IsValidName(ResultCondition[1]))
					throw invalid_argument("[CommandProcessorSCH] invalid_argument. (NAME)\n");
			}
			else {
				if (!IsValidNameFirstLast(ResultCondition[1]))
					throw invalid_argument("[CommandProcessorSCH] invalid_argument. (NAME)\n");
			}
		}
		if (ResultCondition[0] == "cl" && !IsValidCl(ResultCondition[1])) {
			throw invalid_argument("[CommandProcessorSCH] invalid_argument. (CL)\n");
		}
		if (ResultCondition[0] == "phoneNum") {
			if (ResultOption[1] == enumOptionList::None) {
				if (!IsValidPhoneNum(ResultCondition[1]))
					throw invalid_argument("[CommandProcessorSCH] invalid_argument. (PHONENUM)\n");
			}
			else {
				if (!IsValidPhoneNumMiddleLast(ResultCondition[1]))
					throw invalid_argument("[CommandProcessorSCH] invalid_argument. (PHONENUM)\n");
			}
		}
		if (ResultCondition[0] == "birthday") {
			if (ResultOption[1] == enumOptionList::None) {
				if (!IsValidBirthday(ResultCondition[1]))
					throw invalid_argument("[CommandProcessorSCH] invalid_argument. (BIRTHDAY)\n");
			}
			else if(ResultOption[1] == enumOptionList::FindByYear_Birthday) {
				if (!IsValidBirthdayYear(ResultCondition[1]))
					throw invalid_argument("[CommandProcessorSCH] invalid_argument. (BIRTHDAY)\n");
			}
			else if (ResultOption[1] == enumOptionList::FindByMonth_Birthday) {
				if (!IsValidBirthdayMonth(ResultCondition[1]))
					throw invalid_argument("[CommandProcessorSCH] invalid_argument. (BIRTHDAY)\n");

			} 
			else if (ResultOption[1] == enumOptionList::FindByDay_Birthday) {
				if (!IsValidBirthdayDay(ResultCondition[1]))
					throw invalid_argument("[CommandProcessorSCH] invalid_argument. (BIRTHDAY)\n");
			}
			else {
				throw invalid_argument("[CommandProcessorSCH] invalid_argument. (BIRTHDAY)\n");
			}
		}
		if (ResultCondition[0] == "certi" && !IsValidCerti(ResultCondition[1])) {
			throw invalid_argument("[CommandProcessorSCH] invalid_argument. (CERTI)\n");
		}

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
