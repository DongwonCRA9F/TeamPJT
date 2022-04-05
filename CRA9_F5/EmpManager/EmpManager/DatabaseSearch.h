#pragma once
#include <string>
#include <vector>
#include "Employ.h"
#include "CommandParser.h"

class DatabaseSearch
{
public:
	DatabaseSearch() {};
	virtual vector<int> search(vector<Employ> db, enumOptionList option, string value) = 0;
};

class DatabaseSearchByEmployeeNum : public DatabaseSearch
{
public:
	vector<int> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<int> employeeIndexList;
		for (int i = 0; i < db.size(); i++) {
			if (db[i].getEmployeeNum() != stoi(value)) { continue; }
			employeeIndexList.emplace_back(i);
		}

		return employeeIndexList;
	}
};

class DatabaseSearchByName : public DatabaseSearch
{
public:
	vector<int> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<int> employeeIndexList;
		for (int i = 0; i < db.size(); i++) {
			if (option == enumOptionList::None) {
				if (db[i].getName().getFullName() != value) { continue; }
			}
			else if (option == enumOptionList::FindByFirstName_Name) {
				if (db[i].getName().getFirstName() != value) { continue; }
			}
			else if (option == enumOptionList::FindByLastName_Name) {
				if (db[i].getName().getLastName() != value) { continue; }
			}

			employeeIndexList.emplace_back(i);
		}
		return employeeIndexList;
	}
};

class DatabaseSearchByCl : public DatabaseSearch
{
public:
	vector<int> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<int> employeeIndexList;
		for (int i = 0; i < db.size(); i++) {
			if (db[i].getCl() != clMap.find(value)->second) { continue; }

			employeeIndexList.emplace_back(i);
		}

		return employeeIndexList;
	}
};

class DatabaseSearchByPhone : public DatabaseSearch
{
public:
	vector<int> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<int> employeeIndexList;
		for (int i = 0; i < db.size(); i++) {
			if (option == enumOptionList::None) {
				if (db[i].getPhoneNum().getPhoneNumber() != value) { continue; }
			}
			else if (option == enumOptionList::FindByMiddleNum_PhoneNum) {
				if (db[i].getPhoneNum().getMiddle() != value) { continue; }
			}
			else if (option == enumOptionList::FindByLastNum_PhoneNum) {
				if (db[i].getPhoneNum().getLast() != value) { continue; }
			}

			employeeIndexList.emplace_back(i);
		}

		return employeeIndexList;
	}
};

class DatabaseSearchByBirthday : public DatabaseSearch
{
public:
	vector<int> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<int> employeeIndexList;
		for (int i = 0; i < db.size(); i++) {
			if (option == enumOptionList::None) {
				if (db[i].getBirthday().getBirthday() != value) { continue; }
			}
			else if (option == enumOptionList::FindByYear_Birthday) {
				if (to_string(db[i].getBirthday().getYear()) != value) { continue; }
			}
			else if (option == enumOptionList::FindByMonth_Birthday) {
				if (to_string(db[i].getBirthday().getMonth()) != value) { continue; }
			}
			else if (option == enumOptionList::FindByDay_Birthday) {
				if (to_string(db[i].getBirthday().getDay()) != value) { continue; }
			}

			employeeIndexList.emplace_back(i);
		}

		return employeeIndexList;
	}
};

class DatabaseSearchByCerti : public DatabaseSearch
{
public:
	vector<int> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<int> employeeIndexList;
		for (int i = 0; i < db.size(); i++) {
			if (db[i].getCerti() != certiMap.find(value)->second) { continue; }

			employeeIndexList.emplace_back(i);
		}

		return employeeIndexList;
	}
};
