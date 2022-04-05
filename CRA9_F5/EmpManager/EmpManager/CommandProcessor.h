#include <iostream>
#include <cctype>
#include <sstream>
#include "CommandResult.h"
#include "CommandParser.h"
#include "DatabaseInterface.h"

using namespace std;

class InputChecker {
public:
	virtual bool isValid(string str) = 0;
	virtual void checkInputValidity(enumOptionList option2, string value) = 0;
};
class InputCheckEmployNum : public InputChecker {
public:
	virtual bool isValid(string str) override {
		if (str.length() != 8) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}
		int year = stoi(str.substr(0, 2));
		if (year > 21 && year < 69) return false;
		return true;
	}
	virtual void checkInputValidity(enumOptionList option2, string value) override {
		if (option2 != enumOptionList::None)
			throw invalid_argument(string("[EmployNum] option2: " + strEmploy[static_cast<int>(option2)]+ string(", value : ") + value));
		if (!isValid(value)) {
			throw invalid_argument(string("[EmployNum] value:") + value);
		}
	}
};
class InputCheckName : public InputChecker {
	bool isValidFirstLast(string str) {
		int count_space = 0;
		if (str.length() < 1 || str.length() > 13) return false;
		for (auto c : str) {
			if (!isalpha(c)) {
				return false;
			}
		}
		return true;
	}
public:
	virtual bool isValid(string str) override {
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
	virtual void checkInputValidity(enumOptionList option2, string value) override {
		if (option2 != enumOptionList::None && option2 != enumOptionList::FindByFirstName_Name && option2 != enumOptionList::FindByLastName_Name)
			throw invalid_argument(string("[Name] invalid:option2: " + strEmploy[static_cast<int>(option2)] + string(", value : ") + value));
		switch (option2) {
		case enumOptionList::None:
			if (!isValid(value)) {
				throw invalid_argument(string("[Name] option2: None, value:") + value);
			}
			break;
		case enumOptionList::FindByFirstName_Name:
			if (!isValidFirstLast(value)) {
				throw invalid_argument(string("[Name] option2: FirstName, value:") + value);
			}
			break;
		case enumOptionList::FindByLastName_Name:
			if (!isValidFirstLast(value)) {
				throw invalid_argument(string("[Name] option2: LastName, value:") + value);
			}
			break;
		}
	}
};
class InputCheckCl : public InputChecker {
public:
	virtual bool isValid(string str) override {
		if (str.length() != 3) return false;
		if (str.substr(0, 2) != "CL") return false;
		if (!is_digit(str.substr(2, 1))) return false;
		int cl_level = stoi(str.substr(2, 1));
		if (cl_level == 0 || cl_level > 4) return false;
		return true;
	}
	virtual void checkInputValidity(enumOptionList option2, string value) override {
		if (option2 != enumOptionList::None)
			throw invalid_argument(string("[CL] invalid:option2: " + strEmploy[static_cast<int>(option2)] + string(", value : ") + value));
		if (!isValid(value)) {
			throw invalid_argument(string("[CL] value:") + value);
		}
	}
protected:
	bool is_digit(string str) {
		return atoi(str.c_str()) != 0 || str.compare("0") == 0;
	};
};

class InputCheckPhoneNum : public InputChecker {
public:
	virtual bool isValid(string str) override {
		istringstream ss(str);
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
	virtual void checkInputValidity(enumOptionList option2, string value) override {
		if (option2 != enumOptionList::None && option2 != enumOptionList::FindByMiddleNum_PhoneNum && option2 != enumOptionList::FindByLastNum_PhoneNum)
			throw invalid_argument(string("[PhoneNum] invalid:option2: " + strEmploy[static_cast<int>(option2)] + string(", value : ") + value));
		switch (option2) {
		case enumOptionList::None:
			if (!isValid(value)) {
				throw invalid_argument(string("[PhoneNum] option2: None, value:") + value);
			}
			break;
		case enumOptionList::FindByMiddleNum_PhoneNum:
			if (!isValidPhoneNumMiddleLast(value)) {
				throw invalid_argument(string("[PhoneNum] option2: Middle, value:") + value);
			}
			break;
		case enumOptionList::FindByLastNum_PhoneNum:
			if (!isValidPhoneNumMiddleLast(value)) {
				throw invalid_argument(string("[PhoneNum] option2: Last, value:") + value);
			}
			break;
		}
	}
private:
	bool isValidPhoneNumMiddleLast(string str) {
		if (str.length() != 4) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}

		return true;
	}
};
class InputCheckBirthday : public InputChecker {
public:
	virtual bool isValid(string str) override {
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
	virtual void checkInputValidity(enumOptionList option2, string value) override {
		if (option2 != enumOptionList::None && option2 != enumOptionList::FindByYear_Birthday &&
			option2 != enumOptionList::FindByMonth_Birthday && option2 != enumOptionList::FindByDay_Birthday)
			throw invalid_argument(string("[Birthday] invalid:option2: " + strEmploy[static_cast<int>(option2)] + string(", value : ") + value));
		switch (option2) {
		case enumOptionList::None:
			if (!isValid(value)) {
				throw invalid_argument(string("[Birthday] option2: None, value:") + value);
			}
			break;
		case enumOptionList::FindByYear_Birthday:
			if (!isValidBirthdayYear(value)) {
				throw invalid_argument(string("[Birthday] option2: Year, value:") + value);
			}
			break;
		case enumOptionList::FindByMonth_Birthday:
			if (!isValidBirthdayMonth(value)) {
				throw invalid_argument(string("[Birthday] option2: Month, value:") + value);
			}
			break;
		case enumOptionList::FindByDay_Birthday:
			if (!isValidBirthdayDay(value)) {
				throw invalid_argument(string("[Birthday] option2: day, value:") + value);
			}
			break;
		}
	}
private:
	bool isValidBirthdayYear(string str) {
		if (str.length() != YEAR_STR_LENGTH) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}
		if (stoi(str) < YEAR_FIRST || stoi(str) > YEAR_LAST) return false;
		return true;
	}
	bool isValidBirthdayMonth(string str) {
		if (str.length() != MONTH_STR_LENGTH) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}
		if (stoi(str) < MONTH_FIRST || stoi(str) > MONTH_LAST) return false;
		return true;
	}
	bool isValidBirthdayDay(string str) {
		if (str.length() != DAY_STR_LENGTH) return false;
		for (auto c : str) {
			if (!isdigit(c)) return false;
		}
		if (stoi(str) < DAY_FIRST || stoi(str) > DAY_LAST) return false;
		return true;
	}
	const int YEAR_STR_LENGTH = 4;
	const int YEAR_FIRST = 1900; //approximate
	const int YEAR_LAST = 2022; //now
	const int MONTH_STR_LENGTH = 2;
	const int MONTH_FIRST = 1;
	const int MONTH_LAST = 12;
	const int DAY_STR_LENGTH = 2;
	const int DAY_FIRST = 1;
	const int DAY_LAST = 31;
};
class InputCheckCerti : public InputChecker {
public:
	virtual bool isValid(string str) override {
		const int CERTI_STR_LENGTH_MIN = 2;
		const int CERTI_STR_LENGTH_MAX = 3;
		if (str.length() < CERTI_STR_LENGTH_MIN || str.length() > CERTI_STR_LENGTH_MAX) return false;
		if (str != "ADV" && str != "PRO" && str != "EX") return false;
		return true;
	}
	virtual void checkInputValidity(enumOptionList option2, string value) override {
		if (option2 != enumOptionList::None)
			throw invalid_argument(string("[CERTI] invalid:option2: " + strEmploy[static_cast<int>(option2)] + string(", value : ") + value));
		if (!isValid(value)) {
			throw invalid_argument(string("[CERTI] value:") + value);
		}
	}
};

class CommandProcessor {
public:
	CommandProcessor() {
	};
	virtual CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) = 0;
protected:
	
	InputChecker* getInputChecker(enumEmploy em) {
		switch (em) {
		case enumEmploy::EMPLOYEENUM:
			return new InputCheckEmployNum();
		case enumEmploy::NAME:
			return new InputCheckName();
		case enumEmploy::CL:
			return new InputCheckCl();
		case enumEmploy::PHONENUM:
			return new InputCheckPhoneNum();
		case enumEmploy::BIRTHDAY:
			return new InputCheckBirthday();
		case enumEmploy::CERTI:
			return new InputCheckCerti();
		}
	}

	InputChecker* getInputChecker(string emStr) {
		if (emStr == "employNum") {
			return new InputCheckEmployNum();
		} else if (emStr == "name"){
			return new InputCheckName();
		}
		else if (emStr == "cl") {
			return new InputCheckCl();
		}
		else if (emStr == "phoneNum") {
			return new InputCheckPhoneNum();
		}
		else if (emStr == "birthday") {
			return new InputCheckBirthday();
		}
		else if (emStr == "certi") {
			return new InputCheckCerti();
		}
		return new InputCheckEmployNum();
	}

	InputChecker* IC;
	CommandResult result;
};

template <typename DatabaseInterface>
class CommandProcessorADD :public CommandProcessor {
public:
	CommandProcessorADD() : CommandProcessor() {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		for (int i = static_cast<int>(enumEmploy::EMPLOYEENUM); i < static_cast<int>(enumEmploy::Employ_MAX); i++) {
			IC = getInputChecker(static_cast<enumEmploy>(i));
			if (!IC->isValid(ResultCondition[i])) {
				throw invalid_argument(string("[invalid_argument] column:") + strEmploy[i] + string(", value:") + ResultCondition[i]);
			}
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
		vector<Employ> listSearched = DatabaseInterface::getInstance().updateItems(ResultOption[1], {ResultCondition[0], ResultCondition[1]}, {ResultCondition[2], ResultCondition[3]});
		try {
			IC = getInputChecker(ResultCondition[0]);
			IC->checkInputValidity(ResultOption[1], ResultCondition[1]);
			IC = getInputChecker(ResultCondition[2]);
			IC->checkInputValidity(enumOptionList::None, ResultCondition[3]);
		}
		catch (invalid_argument& e) {
			cerr << "Invalid argument: " << e.what() << endl;
			throw invalid_argument(e);
		}
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
class CommandProcessorSCH :public CommandProcessor {
public:
	CommandProcessorSCH() : CommandProcessor() {};
	CommandResult run(vector<enumOptionList> ResultOption, vector<string> ResultCondition) override {
		try {
			IC = getInputChecker(ResultCondition[0]);
			IC->checkInputValidity(ResultOption[1], ResultCondition[1]);
		}
		catch (invalid_argument& e) {
			cerr << "Invalid argument: " << e.what() << endl;
			throw invalid_argument(e);
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
		try {
			IC = getInputChecker(ResultCondition[0]);
			IC->checkInputValidity(ResultOption[1], ResultCondition[1]);
		}
		catch (invalid_argument& e) {
			cerr << "Invalid argument: " << e.what() << endl;
			throw invalid_argument(e);
		}
		result.list.clear();
		result.count = 0;
		for (auto aEmploy : listSearched) {
			result.list.push_back(aEmploy);
			result.count++;
		}
		return result;
	}
};