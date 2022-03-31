#pragma once
#include <iostream>
#include <string>
using namespace std;

enum CL {
	CL1 = 1,
	CL2 = 2,
	CL3 = 3,
	CL4 = 4,
	CL_MAX = 4
};

class PhoneNumber {
private:
	int middle;
	int last;
public:
	string getPhoneNumber() {
		return "010-" + to_string(middle) + to_string(last);
	}
	void setMiddle(int number) {
		middle = number;
	}
	void setLast(int number) {
		last = number;
	}

	int getMiddle() {
		return middle;
	}
	int getLast() {
		return last;
	}
};

class Birthday {
private:
	int year;
	int month;
	int day;
public:
	void setYear(int num) {
		year = num;
	}
	void setMonth(int num) {
		month = num;
	}
	void setDay(int num) {
		day = num;
	}
	void setYYYYMMDD(string YYYYMMDD) {
		//TODO: implement this.
		year = 0;
		month = 0;
		day = 0;
	}
};

enum Certi {
	ADV = 0,
	PRO = 1,
	EX = 2,
	Certi_MAX
};

class Employ {
	int employeeNum;
	string name;
	CL cl;
	PhoneNumber phoneNum;
	Birthday birthday;
	Certi certi;
};
