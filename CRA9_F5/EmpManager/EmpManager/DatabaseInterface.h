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
	virtual bool insertItem(Employ employee);
	virtual vector<Employ> selectItems(enumOptionList option, DatabaseSearchItem item);
	virtual vector<Employ> updateItems(enumOptionList option, DatabaseSearchItem origin, DatabaseSearchItem update);
	virtual vector<Employ> deleteItems(enumOptionList option, DatabaseSearchItem item);
	virtual Employ deleteItem(int employNum);

	size_t getCurRecordsCount() { return this->employDB.size(); }
private:
	vector<Employ> employDB;
};
