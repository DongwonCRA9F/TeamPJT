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

	TEST_F(EmployTest, employ_compare) {
		Employ em1 = Employ(17112609, Name("FB NTAWR"), enumCL::CL4, PhoneNumber("010 - 5645 - 6122"), Birthday("19861203"), enumCerti::PRO);
		Employ em1_1 = Employ(17112600, Name("FB NTAWR"), enumCL::CL4, PhoneNumber("010 - 5645 - 6122"), Birthday("19861203"), enumCerti::PRO);
		Employ em1_2 = Employ(17112600, Name("FB NTAWQ"), enumCL::CL4, PhoneNumber("010 - 5645 - 6122"), Birthday("19861203"), enumCerti::PRO);
		Employ em1_3 = Employ(17112600, Name("FB NTAWR"), enumCL::CL4, PhoneNumber("011 - 5645 - 6122"), Birthday("19861203"), enumCerti::PRO);
		Employ em1_4 = Employ(17112600, Name("FB NTAWR"), enumCL::CL4, PhoneNumber("010 - 5644 - 6122"), Birthday("19861203"), enumCerti::PRO);
		Employ em1_5 = Employ(17112600, Name("FB NTAWR"), enumCL::CL4, PhoneNumber("010 - 5645 - 6123"), Birthday("19861203"), enumCerti::PRO);
		Employ em1_6 = Employ(17112600, Name("FB NTAWR"), enumCL::CL4, PhoneNumber("010 - 5645 - 6122"), Birthday("19851203"), enumCerti::PRO);
		Employ em1_7 = Employ(17112600, Name("FB NTAWR"), enumCL::CL4, PhoneNumber("010 - 5645 - 6122"), Birthday("19860203"), enumCerti::PRO);
		Employ em1_8 = Employ(17112600, Name("FB NTAWR"), enumCL::CL4, PhoneNumber("010 - 5645 - 6122"), Birthday("19861231"), enumCerti::PRO);
		Employ em1_9 = Employ(17112600, Name("FB NTAWR"), enumCL::CL4, PhoneNumber("010 - 5645 - 6122"), Birthday("19861203"), enumCerti::EX);

		ASSERT_NE(em1, em1_1);
		ASSERT_NE(em1, em1_2);
		ASSERT_NE(em1, em1_3);
		ASSERT_NE(em1, em1_4);
		ASSERT_NE(em1, em1_5);
		ASSERT_NE(em1, em1_6);
		ASSERT_NE(em1, em1_7);
		ASSERT_NE(em1, em1_8);
		ASSERT_NE(em1, em1_9);

		vector<Employ> list1;
		vector<Employ> list2;
		ASSERT_EQ(list1, list2);

		list1.push_back(em1);
		list1.push_back(em1);
		list2.push_back(em1);
		list2.push_back(em1);
		ASSERT_EQ(list1, list2);

		list2.push_back(em1);
		ASSERT_NE(list1, list2);

		list2.pop_back();
		ASSERT_EQ(list1, list2);
	}
}