#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class enumCL {
	CL1 = 1,
	CL2 = 2,
	CL3 = 3,
	CL4 = 4,
	CL_MAX = 4
};

class PhoneNumber {
public:
	PhoneNumber() {}
	PhoneNumber(string phoneNumber)	{
		setPhoneNumber(phoneNumber);
	}

	void setPhoneNumber(string phoneNumber) {
		string tempPhoneNumber = phoneNumber + delim;
		size_t pos = 0, i = 0;
		while ((pos = tempPhoneNumber.find(delim)) != string::npos)	{
			this->phoneNumber[i++] = tempPhoneNumber.substr(0, pos);
			tempPhoneNumber.erase(0, pos + delim.length());
		}
	}

	string getPhoneNumber() {
		return this->phoneNumber[FIRST] + delim + this->phoneNumber[MIDDLE] + delim + this->phoneNumber[LAST];
	}

	string getMiddle() { return phoneNumber[MIDDLE]; }
	string getLast() {	return phoneNumber[LAST]; }

	bool operator==(PhoneNumber p) const {
		if (phoneNumber[MIDDLE] != p.phoneNumber[MIDDLE]) return false;
		if (phoneNumber[LAST] != p.phoneNumber[LAST]) return false;
		return true;
	}
	bool operator!=(PhoneNumber p) const {
		return !(*this == p);
	}

private:
	enum {
		FIRST,
		MIDDLE,
		LAST
	};
	string phoneNumber[3];

	const string delim = "-";
};

class Birthday {
public:
	Birthday() {
		year = 0;
		month = 0;
		day = 0;
	}
	Birthday(string YYYYMMDD) {
		setYYYYMMDD(YYYYMMDD);
	}
	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	string getBirthday(){ return "" + to_string(year) + to_string(month) + to_string(day); }

	void setYYYYMMDD(string YYYYMMDD) {
		year = stoi(YYYYMMDD.substr(yearOffset, yearCount));
		month = stoi(YYYYMMDD.substr(monthOffset, monthCount));
		day = stoi(YYYYMMDD.substr(dayOffset, dayCount));
	}

	bool operator==(Birthday b) const {
		if (year != b.year) return false;
		if (month != b.month) return false;
		if (day != b.day) return false;
		return true;
	}
	bool operator!=(Birthday b) const {
		return !(*this==b);
	}

private:
	int year;
	const int yearOffset = 0;
	const int yearCount = 4;

	int month;
	const int monthOffset = yearOffset + yearCount;
	const int monthCount = 2;

	int day;
	const int dayOffset = monthOffset + monthCount;
	const int dayCount = 2;

};

class Name {
public:
	Name() {}
	Name(string fullName) {
		setName(fullName);
	}
	
	void setName(string fullName) {
		string tempfullName = fullName + delim;
		size_t pos = 0, i = 0;
		while ((pos = tempfullName.find(delim)) != string::npos) {
			this->name[i++] = tempfullName.substr(0, pos);
			tempfullName.erase(0, pos + delim.length());
		}
	}
	string getFullName() { return name[FIRST] + delim + name[LAST]; }
	string getFirstName() { return name[FIRST]; }
	string getLastName() { return name[LAST]; }

	bool operator==(Name n) const {
		if (name[FIRST] != n.name[FIRST]) return false;
		if (name[LAST] != n.name[LAST]) return false;
		return true;
	}
	bool operator!=(Name n) const {
		return !(*this == n);
	}

private:
	enum {
		FIRST,
		LAST
	};
	string name[2];
	const string delim = " ";
};

enum class enumCerti {
	ADV = 0,
	PRO,
	EX,
	Certi_MAX
};

class Employ {
public:
	Employ() {}
	Employ(int employeeNum, Name name, enumCL cl, PhoneNumber phoneNum, Birthday birthday, enumCerti certi)
	: employeeNum(employeeNum), name(name), cl(cl), phoneNum(phoneNum), birthday(birthday), certi(certi){

	}
	Employ(vector<string> ConditionStr)
	:employeeNum(stoi(ConditionStr[0])), name(ConditionStr[1]), phoneNum(ConditionStr[3]), birthday(ConditionStr[4]) {
		if(ConditionStr[2] == "CL1") cl = enumCL::CL1;
		else if (ConditionStr[2] == "CL2") cl = enumCL::CL2;
		else if (ConditionStr[2] == "CL3") cl = enumCL::CL3;
		else cl = enumCL::CL4;

		if (ConditionStr[5] == "ADV") certi = enumCerti::ADV;
		else if (ConditionStr[5] == "PRO") certi = enumCerti::PRO;
		else certi = enumCerti::EX;
	}
	int getEmployeeNum() { return employeeNum; }
	Name getName() { return name; }
	enumCL getCl() { return cl; }
	PhoneNumber getPhoneNum() { return phoneNum; }
	Birthday getBirthday() { return birthday; }
	enumCerti getCerti() { return certi; }

	bool operator==(Employ e) const {
		if (employeeNum != e.employeeNum) return false;
		if (name != e.name) return false;
		if (cl != e.cl) return false;
		if (phoneNum != e.phoneNum) return false;
		if (birthday != e.birthday) return false;
		if (certi != e.certi) return false;
		return true;
	}
	bool operator!=(Employ e) const{
		return !(*this == e);
	}

private:
	int employeeNum;
	Name name;
	enumCL cl;
	PhoneNumber phoneNum;
	Birthday birthday;
	enumCerti certi;
};
