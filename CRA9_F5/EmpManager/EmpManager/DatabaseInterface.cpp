#include "DatabaseInterface.h"

#include <vector>
using namespace std;
bool DatabaseInterface::insertItem(TempEmployee employee)
{
	return true;
}

vector<TempEmployee> DatabaseInterface::selectItems(char option, DatabaseSearchItem item)
{
	vector<TempEmployee> employeeList;
	return employeeList;
}

vector<TempEmployee> DatabaseInterface::updateItems(char option, DatabaseSearchItem origin, DatabaseSearchItem update)
{
	vector<TempEmployee> employeeList;
	return employeeList;
}

vector<TempEmployee> DatabaseInterface::deleteItems(char option, DatabaseSearchItem item)
{
	vector<TempEmployee> employeeList;
	return employeeList;
}