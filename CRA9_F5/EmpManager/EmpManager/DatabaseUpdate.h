#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "Employ.h"
#include "CommandParser.h"
using namespace std;
struct UpdateItem
{
	string updateColumn;
	string updateValue;
};

class DatabaseUpdate
{
public:
	DatabaseUpdate()
	{
		updateItemFunc[static_cast<int>(enumEmploy::EMPLOYEENUM)] = &DatabaseUpdate::updateEmployeeNum;
		updateItemFunc[static_cast<int>(enumEmploy::NAME)] = &DatabaseUpdate::updateName;
		updateItemFunc[static_cast<int>(enumEmploy::CL)] = &DatabaseUpdate::updateCl;
		updateItemFunc[static_cast<int>(enumEmploy::PHONENUM)] = &DatabaseUpdate::updatePhoneNum;
		updateItemFunc[static_cast<int>(enumEmploy::BIRTHDAY)] = &DatabaseUpdate::updateBirthday;
		updateItemFunc[static_cast<int>(enumEmploy::CERTI)] = &DatabaseUpdate::updateCerti;
	};

	Employ updateItem(Employ origin, UpdateItem item) {
		return (this->*updateItemFunc[static_cast<int>(employMap.find(item.updateColumn)->second)])(origin, item.updateValue);
	}
private:
	Employ(DatabaseUpdate::*updateItemFunc[static_cast<int>(enumEmploy::Employ_MAX)])(Employ origin, string value);
	Employ updateEmployeeNum(Employ origin, string value)
	{
		return Employ(stoi(value), origin.getName(), origin.getCl(), origin.getPhoneNum(), origin.getBirthday(), origin.getCerti());
	}
	Employ updateName(Employ origin, string value)
	{
		return Employ(origin.getEmployeeNum(), Name(value), origin.getCl(), origin.getPhoneNum(), origin.getBirthday(), origin.getCerti());
	}
	Employ updateCl(Employ origin, string value)
	{
		return Employ(origin.getEmployeeNum(), origin.getName(), clMap.find(value)->second, origin.getPhoneNum(), origin.getBirthday(), origin.getCerti());
	}
	Employ updatePhoneNum(Employ origin, string value)
	{
		return Employ(origin.getEmployeeNum(), origin.getName(), origin.getCl(), PhoneNumber(value), origin.getBirthday(), origin.getCerti());
	}
	Employ updateBirthday(Employ origin, string value)
	{
		return Employ(origin.getEmployeeNum(), origin.getName(), origin.getCl(), origin.getPhoneNum(), Birthday(value), origin.getCerti());
	}
	Employ updateCerti(Employ origin, string value)
	{
		return Employ(origin.getEmployeeNum(), origin.getName(), origin.getCl(), origin.getPhoneNum(), origin.getBirthday(), certiMap.find(value)->second);
	}
};
