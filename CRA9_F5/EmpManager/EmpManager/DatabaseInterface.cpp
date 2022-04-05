#include "DatabaseInterface.h"

#include <vector>
using namespace std;
bool DatabaseInterface::insertItem(Employ employee)
{
	vector<int> indexList = databaseSearch[static_cast<int>(enumEmploy::EMPLOYEENUM)]->search(employDB, enumOptionList::None, to_string(employee.getEmployeeNum()));
	if (indexList.size() != 0) return false;

	employDB.emplace_back(employee);

	return true;
}

vector<Employ> DatabaseInterface::selectItems(enumOptionList option, DatabaseSearchItem item)
{
	vector<Employ> result;
	vector<int> indexList = databaseSearch[static_cast<int>(employMap.find(item.column)->second)]->search(employDB, option, item.value);
	for (auto index : indexList) {
		result.emplace_back(employDB[index]);
	}

	return result;
}

vector<Employ> DatabaseInterface::updateItems(enumOptionList option, DatabaseSearchItem origin, DatabaseSearchItem update)
{
	return databaseUpdate[static_cast<int>(employMap.find(origin.column)->second)]->update(&employDB, option, origin.value, {update.column, update.value});
}

vector<Employ> DatabaseInterface::deleteItems(enumOptionList option, DatabaseSearchItem item)
{
	vector<Employ> employeeList;
	return employeeList;
}

Employ DatabaseInterface::deleteItem(int employNum)
{
	Employ employee;
	return employee;
}
