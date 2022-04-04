#pragma once
#include <iostream>
#include <vector>
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
		// TODO!! TODO!!
		return result;
	}
};
