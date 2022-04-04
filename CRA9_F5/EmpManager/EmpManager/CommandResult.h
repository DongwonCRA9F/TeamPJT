#include <iostream>
#include <vector>
#include "Employ.h"

using namespace std;

class TempEmploy {};

class CommandResult {
public:
	int count;
	vector<Employ> list;
	bool operator==(CommandResult CR) const {
		return false;
	}

	string getSimpleResults() {
		return count == 0 ? string("NONE") : to_string(count);
	}
};