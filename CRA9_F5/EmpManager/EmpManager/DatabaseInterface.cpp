#include "DatabaseInterface.h"

#include <vector>
using namespace std;

bool DatabaseInterface::insertItem(Employ employee)
{
	vector<int> indexList = databaseSearchDbIndex[static_cast<int>(enumEmploy::EMPLOYEENUM)]->search(employDB, enumOptionList::None, to_string(employee.getEmployeeNum()));
	if (indexList.size() != 0) return false;

	employDB.emplace_back(employee);

	return true;
}

vector<Employ> DatabaseInterface::selectItems(enumOptionList option, DatabaseSearchItem item)
{
	vector<Employ> result;
	if (checkValidColumn(option, item.column) == false) return result;

	vector<int> indexList = databaseSearchDbIndex[static_cast<int>(employMap.find(item.column)->second)]->search(employDB, option, item.value);
	for (auto index : indexList) {
		result.emplace_back(employDB[index]);
	}

	return result;
}

vector<Employ> DatabaseInterface::updateItems(enumOptionList option, DatabaseSearchItem origin, DatabaseSearchItem update)
{
	vector<Employ> result;
	if (checkValidColumn(option, origin.column)==false) return result; 

	vector<int> indexList = databaseSearchDbIndex[static_cast<int>(employMap.find(origin.column)->second)]->search(employDB, option, origin.value);
	for (auto index : indexList) {
		result.emplace_back(employDB[index]);
	}

	for (auto index : indexList) {
		employDB[index] = databaseUpdate.updateItem(employDB[index], { update.column, update.value });
	}

	return result;
}

vector<Employ> DatabaseInterface::deleteItems(enumOptionList option, DatabaseSearchItem item)
{
	vector<Employ> result;
	if (checkValidColumn(option, item.column) == false) return result;

	vector<int> indexList = databaseSearchDbIndex[static_cast<int>(employMap.find(item.column)->second)]->search(employDB, option, item.value);
	for (auto index : indexList) {
		result.emplace_back(employDB[index]);
	}

	int eraseCount = 0;
	for (auto index : indexList) {
		employDB.erase(employDB.begin() + index - eraseCount);
		eraseCount++;
	}

	return result;
}

Employ DatabaseInterface::deleteItem(int employNum)
{
	vector<int> indexList = databaseSearchDbIndex[static_cast<int>(enumEmploy::EMPLOYEENUM)]->search(employDB, enumOptionList::None, to_string(employNum));
	Employ employee = employDB[indexList[0]];
	employDB.erase(employDB.begin() + indexList[0]);
	return employee;
}

bool DatabaseInterface::checkValidColumn(enumOptionList option, string column)
{
	auto it = employMap.find(column);

	if (it == employMap.end()) {
		throw InvalidColumnException("Invalid Column");
		return false;
	}

	if (option == enumOptionList::None) { return true; }

	if (it->second == enumEmploy::BIRTHDAY) {
		if (option != enumOptionList::FindByYear_Birthday
			&& option != enumOptionList::FindByMonth_Birthday
			&& option != enumOptionList::FindByDay_Birthday) {
			throw InvalidColumnException("Invalid match : Search Option - Column");
			return false;
		}
	}
	else if (it->second == enumEmploy::NAME) {
		if (option != enumOptionList::FindByFirstName_Name
			&& option != enumOptionList::FindByLastName_Name) {
			throw InvalidColumnException("Invalid match : Search Option - Column");
			return false;
		}
	}
	else if (it->second == enumEmploy::PHONENUM) {
		if (option != enumOptionList::FindByMiddleNum_PhoneNum
			&& option != enumOptionList::FindByLastNum_PhoneNum) {
			throw InvalidColumnException("Invalid match : Search Option - Column");
			return false;
		}
	}
	else {
		throw InvalidColumnException("Invalid match : Search Option - Column");
		return false;
	}


	return true;
}