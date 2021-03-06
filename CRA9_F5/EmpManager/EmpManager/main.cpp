#include <iostream>
#include <fstream>
#include <string>

#include "employManager.h"

using namespace std;

int main(int argc, char* argv[]) {
	vector<string> ret;
	string inputStr;

	// parameter 유효성 검사
	if (argc != 3)
		exit(0);

	ifstream inputFile(argv[1]);
	if (!inputFile) {
		cout << "ERROR, file is not exists" << endl;
		exit(0);
	}

	ofstream outputFile(argv[2]);
	EmployManager empManager;

	while (getline(inputFile, inputStr)) {
		ret = empManager.runCommand(inputStr);
		for (auto & val : ret)
			outputFile << val << endl;
	}

	inputFile.close();
	outputFile.close();

	return 0;
}
