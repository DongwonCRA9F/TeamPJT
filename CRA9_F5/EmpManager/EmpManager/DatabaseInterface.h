#pragma once

#include <string>
#include <vector>
#include "Employ.h"
#include "CommandParser.h"
using namespace std;

struct DatabaseSearchItem {
	string column;
	string value;
};

class DatabaseInterface
{
public:
	bool insertItem(Employ employee);
	vector<Employ> selectItems(enumOptionList option, DatabaseSearchItem item);
	vector<Employ> updateItems(enumOptionList option, DatabaseSearchItem origin, DatabaseSearchItem update);
	vector<Employ> deleteItems(enumOptionList option, DatabaseSearchItem item);

	size_t getCurRecordsCount() { return this->employDB.size(); }
private:
	const int MAX_RECORDS_COUNT = 100000;
	vector<Employ> employDB;
};
