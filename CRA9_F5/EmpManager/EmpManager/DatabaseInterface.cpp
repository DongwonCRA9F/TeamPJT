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
	vector<int> indexList = databaseSearchDbIndex[static_cast<int>(employMap.find(item.column)->second)]->search(employDB, option, item.value);
	for (auto index : indexList) {
		result.emplace_back(employDB[index]);
	}

	return result;
}

vector<Employ> DatabaseInterface::updateItems(enumOptionList option, DatabaseSearchItem origin, DatabaseSearchItem update)
{
	vector<Employ> result;
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
