#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Employ.h"

using namespace std;

class CommandResult {
public:
	int count;
	vector<Employ> list;

	CommandResult(): count(0) {};

	CommandResult(int count_param, vector<Employ> list_param) {
		count = count_param;
		list.clear();
		for (auto aEmploy : list_param) {
			list.push_back(aEmploy);
		}
	};
	
	bool operator==(CommandResult CR) const {
		if (count != CR.count) return false;
		if(list != CR.list) return false;
		return true;
	}

	string getSimpleResults() {
		return count == 0 ? string("NONE") : to_string(count);
	}

	vector<Employ> getDetailResults() {
		vector<Employ> result;
		result.reserve(5);
		sort(list.begin(), list.end(), [this](Employ a, Employ b) {
			return MakeFullEmployeeNum(a.getEmployeeNum()) < MakeFullEmployeeNum(b.getEmployeeNum());
		});
		for (auto employee : list) {
			result.push_back(employee);
			if (result.size() >= 5)
				return result;
		}
		return result;
	}

	int MakeFullEmployeeNum(int partial_EmployNum) {
		if (partial_EmployNum < 69000000) {
			return partial_EmployNum + 2000000000;
		}
		return partial_EmployNum + 1900000000;
	}
};

