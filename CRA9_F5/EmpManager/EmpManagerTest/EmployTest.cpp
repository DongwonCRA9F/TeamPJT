#pragma once
#include "pch.h"
#include "gtest/gtest.h"
#include "../EmpManager/Employ.h"
#include <string>
using namespace std;

namespace 
{
	class EmployTest : public ::testing::Test {
	public:
		EmployTest() {}

		bool makeEmployObject(int emNum, string name, enumCL cl, string phone, string birthday, enumCerti certi) {
			Employ em = Employ(emNum, Name(name), cl, PhoneNumber(phone), Birthday(birthday), certi);

			if (em.getEmployeeNum() != emNum) return false;
			if (em.getName().getFullName() != name) return false;
			if (em.getCl() != cl) return false;
			if (em.getPhoneNum().getPhoneNumber() != phone) return false;
			if (em.getBirthday().getBirthday() != birthday) return false;
			if (em.getCerti() != certi) return false;

			return true;
		}

	protected:
		void SetUp() override {};
		void TearDown() override {};

	private:

	};


	TEST_F(EmployTest, employ) {

		bool res = makeEmployObject(20551235, ("SANGKAP LEE"), enumCL::CL3, ("010-9999-9999"), ("19991212"), enumCerti::PRO);

		EXPECT_EQ(res, true);
	}

	TEST_F(EmployTest, name) {
		Name name = Name("SANGKAP LEE");

		EXPECT_EQ(name.getFirstName(), "SANGKAP");
		EXPECT_EQ(name.getLastName(), "LEE");
		EXPECT_EQ(name.getFullName(), "SANGKAP LEE");
	}

	TEST_F(EmployTest, phoneNum) {
		PhoneNumber phoneNum = PhoneNumber("010-9999-1234");

		EXPECT_EQ(phoneNum.getMiddle(), "9999");
		EXPECT_EQ(phoneNum.getLast(), "1234");
		EXPECT_EQ(phoneNum.getPhoneNumber(), "010-9999-1234");
	}

	TEST_F(EmployTest, birthday) {
		Birthday birthday = Birthday("19991210");

		EXPECT_EQ(birthday.getYear(), 1999);
		EXPECT_EQ(birthday.getMonth(), 12);
		EXPECT_EQ(birthday.getDay(), 10);
		EXPECT_EQ(birthday.getBirthday(), "19991210");
	}
}