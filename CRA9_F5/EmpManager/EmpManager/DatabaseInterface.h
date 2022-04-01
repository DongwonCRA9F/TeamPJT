#pragma once

#include <string>
#include <vector>
using namespace std;

struct TempEmployee
{
	string employeeNum;
	string name;
	string ci;
	string phoneNumber;
	string birthDay;
	string certi;
};
struct DatabaseSearchItem
{
	string column;
	string value;
};

class DatabaseInterface
{
public:
	bool insertItem(TempEmployee employee);
	vector<TempEmployee> selectItems(char option, DatabaseSearchItem item);
	vector<TempEmployee> updateItems(char option, DatabaseSearchItem origin, DatabaseSearchItem update);
	vector<TempEmployee> deleteItems(char option, DatabaseSearchItem item);
private:
	int maxItems;
};
