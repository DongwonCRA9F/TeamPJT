#include "DatabaseInterface.h"

#include <vector>
using namespace std;
bool DatabaseInterface::insertItem(Employ employee)
{
	employDB.push_back(employee);
	
	return true;
}

vector<Employ> DatabaseInterface::selectItems(enumOptionList option, DatabaseSearchItem item)
{
	return databaseSearch[static_cast<int>(employMap.find(item.column)->second)]->search(employDB, option, item.value);
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
