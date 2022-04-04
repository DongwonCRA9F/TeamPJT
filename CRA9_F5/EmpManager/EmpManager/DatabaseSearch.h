#pragma once
#include <string>
#include <vector>
#include "Employ.h"
#include "CommandParser.h"

class DatabaseSearch
{
public:
	DatabaseSearch() {};
	virtual vector<Employ> search(vector<Employ> db, enumOptionList option, string value) = 0;
};

class DatabaseSearchByEmployeeNum : public DatabaseSearch
{
public:
	vector<Employ> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<Employ> employeeList;
		for (auto employee : db) {
			if (employee.getEmployeeNum() == stoi(value)) {
				employeeList.push_back(employee);
			}
		}

		return employeeList;
	}
};

class DatabaseSearchByName : public DatabaseSearch
{
public:
	vector<Employ> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<Employ> employeeList;
		for (auto employee : db) {
			if (option == enumOptionList::None) {
				if (employee.getName().getFullName() == value) {
					employeeList.push_back(employee);
				}
			}
			else if (option == enumOptionList::FindByFirstName_Name) {
				if (employee.getName().getFirstName() == value) {
					employeeList.push_back(employee);
				}
			}
			else if (option == enumOptionList::FindByLastName_Name) {
				if (employee.getName().getLastName() == value) {
					employeeList.push_back(employee);
				}
			}
		}
		return employeeList;
	}
};

class DatabaseSearchByCl : public DatabaseSearch
{
public:
	vector<Employ> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<Employ> employeeList;
		for (auto employee : db) {
			if (employee.getCl() == clMap.find(value)->second) {
				employeeList.push_back(employee);
			}
		}

		return employeeList;
	}
};

class DatabaseSearchByPhone : public DatabaseSearch
{
public:
	vector<Employ> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<Employ> employeeList;
		for (auto employee : db) {
			if (option == enumOptionList::None) {
				if (employee.getPhoneNum().getPhoneNumber() == value) {
					employeeList.push_back(employee);
				}
			}
			else if (option == enumOptionList::FindByMiddleNum_PhoneNum) {
				if (employee.getPhoneNum().getMiddle() == value) {
					employeeList.push_back(employee);
				}
			}
			else if (option == enumOptionList::FindByLastNum_PhoneNum) {
				if (employee.getPhoneNum().getLast() == value) {
					employeeList.push_back(employee);
				}
			}
		}

		return employeeList;
	}
};

class DatabaseSearchByBirthday : public DatabaseSearch
{
public:
	vector<Employ> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<Employ> employeeList;
		for (auto employee : db) {
			if (option == enumOptionList::None) {
				if (employee.getBirthday().getBirthday() == value) {
					employeeList.push_back(employee);
				}
			}
			else if (option == enumOptionList::FindByYear_Birthday) {
				if (to_string(employee.getBirthday().getYear()) == value) {
					employeeList.push_back(employee);
				}
			}
			else if (option == enumOptionList::FindByMonth_Birthday) {
				if (to_string(employee.getBirthday().getMonth()) == value) {
					employeeList.push_back(employee);
				}
			}
			else if (option == enumOptionList::FindByDay_Birthday) {
				if (to_string(employee.getBirthday().getDay()) == value) {
					employeeList.push_back(employee);
				}
			}
		}

		return employeeList;
	}
};

class DatabaseSearchByCerti : public DatabaseSearch
{
public:
	vector<Employ> search(vector<Employ> db, enumOptionList option, string value) override
	{
		vector<Employ> employeeList;
		for (auto employee : db) {
			if (employee.getCerti() == certiMap.find(value)->second) {
				employeeList.push_back(employee);
			}
		}

		return employeeList;
	}
};
