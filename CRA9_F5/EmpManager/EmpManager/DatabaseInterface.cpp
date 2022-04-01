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
	vector<Employ> employeeList;
	return employeeList;
}

vector<Employ> DatabaseInterface::updateItems(enumOptionList option, DatabaseSearchItem origin, DatabaseSearchItem update)
{
	vector<Employ> employeeList;
	return employeeList;
}

vector<Employ> DatabaseInterface::deleteItems(enumOptionList option, DatabaseSearchItem item)
{
	vector<Employ> employeeList;
	return employeeList;
}