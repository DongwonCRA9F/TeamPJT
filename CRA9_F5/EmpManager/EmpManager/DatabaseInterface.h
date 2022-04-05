#pragma once

#include <string>
#include <vector>
#include "Employ.h"
#include "CommandParser.h"
#include "DatabaseSearchDbIndex.h"
#include "DatabaseUpdate.h"
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

	static DatabaseInterface& getInstance() {
		static DatabaseInterface _db;
		return _db;
	}
private:
	DatabaseInterface() {
		employDB.clear();

		databaseSearchDbIndex[static_cast<int>(enumEmploy::EMPLOYEENUM)] = new DatabaseSearchByEmployeeNum();
		databaseSearchDbIndex[static_cast<int>(enumEmploy::NAME)] = new DatabaseSearchByName();
		databaseSearchDbIndex[static_cast<int>(enumEmploy::CL)] = new DatabaseSearchByCl();
		databaseSearchDbIndex[static_cast<int>(enumEmploy::PHONENUM)] = new DatabaseSearchByPhone();
		databaseSearchDbIndex[static_cast<int>(enumEmploy::BIRTHDAY)] = new DatabaseSearchByBirthday();
		databaseSearchDbIndex[static_cast<int>(enumEmploy::CERTI)] = new DatabaseSearchByCerti();
	}

	vector<Employ> employDB;
	DatabaseSearchDbIndex* databaseSearchDbIndex[static_cast<int>(enumEmploy::Employ_MAX)];
	DatabaseUpdate databaseUpdate;

};
