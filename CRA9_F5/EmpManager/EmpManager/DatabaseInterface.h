#pragma once

#include <string>
#include <vector>
#include "Employ.h"
#include "CommandParser.h"
#include "DatabaseSearch.h"
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

		databaseSearch[static_cast<int>(enumEmploy::EMPLOYEENUM)] = new DatabaseSearchByEmployeeNum();
		databaseSearch[static_cast<int>(enumEmploy::NAME)] = new DatabaseSearchByName();
		databaseSearch[static_cast<int>(enumEmploy::CL)] = new DatabaseSearchByCl();
		databaseSearch[static_cast<int>(enumEmploy::PHONENUM)] = new DatabaseSearchByPhone();
		databaseSearch[static_cast<int>(enumEmploy::BIRTHDAY)] = new DatabaseSearchByBirthday();
		databaseSearch[static_cast<int>(enumEmploy::CERTI)] = new DatabaseSearchByCerti();
	}

	vector<Employ> employDB;
	DatabaseSearch* databaseSearch[static_cast<int>(enumEmploy::Employ_MAX)];
	DatabaseUpdate databaseUpdate;

};
