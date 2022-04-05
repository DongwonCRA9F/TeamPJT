#pragma once
#include "pch.h"
#include "gtest/gtest.h"
#include "../EmpManager/DatabaseInterface.cpp"
#include "../EmpManager/Employ.h"
#include <string>
#include <time.h>
using namespace std;

namespace
{
	class DBInterfaceTest : public ::testing::Test {
	public:
		DBInterfaceTest() {}
		DatabaseInterface db = DatabaseInterface::getInstance();

	protected:
		void SetUp() override {};
		void TearDown() override {};
	};

	TEST_F(DBInterfaceTest, InsertTestPositive_Basic)
	{
		Employ em = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em));
	}

	TEST_F(DBInterfaceTest, InsertTestPositive_CheckRecordsCount)
	{
		Employ em1 = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		EXPECT_EQ(db.getCurRecordsCount(), 5);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicByEmployeeNum)
	{
		Employ em = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em));

		vector<Employ> emList = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(em, emList[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiByEmployeeNum)
	{
		Employ em1 = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(em1, emList1[0]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "employeeNum", "20551236" });

		EXPECT_EQ(em2, emList2[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicByName)
	{
		Employ em = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em));

		vector<Employ> emList = db.selectItems(enumOptionList::None, { "name", "SANGKAP LEE" });

		EXPECT_EQ(em, emList[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiByName)
	{
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE3"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE4"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE5"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "name", "SANGKAP LEE1" });

		EXPECT_EQ(em1, emList1[0]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "name", "SANGKAP LEE2" });

		EXPECT_EQ(em2, emList2[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiOberlapByName)
	{
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE1"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "name", "SANGKAP LEE1" });

		EXPECT_EQ(emList1.size(), 2);
		EXPECT_EQ(em1, emList1[0]);
		EXPECT_EQ(em2, emList1[1]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "name", "SANGKAP LEE2" });

		EXPECT_EQ(emList2.size(), 3);
		EXPECT_EQ(em3, emList2[0]);
		EXPECT_EQ(em4, emList2[1]);
		EXPECT_EQ(em5, emList2[2]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicByCl)
	{
		Employ em = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em));

		vector<Employ> emList = db.selectItems(enumOptionList::None, { "cl", "CL3" });

		EXPECT_EQ(em, emList[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiByCl)
	{
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE2"), enumCL::CL2, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE3"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE4"), enumCL::CL4, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE5"), enumCL::CL1, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "cl", "CL2" });

		EXPECT_EQ(em2, emList1[0]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "cl", "CL3" });

		EXPECT_EQ(em3, emList2[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiOberlapByCl)
	{
		Employ em0 = Employ(20551234, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ em6 = Employ(20551240, Name("SANGKAP LEE2"), enumCL::CL4, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "cl", "CL2" });

		EXPECT_EQ(emList1.size(), 2);
		EXPECT_EQ(em1, emList1[0]);
		EXPECT_EQ(em2, emList1[1]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "cl", "CL3" });

		EXPECT_EQ(emList2.size(), 3);
		EXPECT_EQ(em3, emList2[0]);
		EXPECT_EQ(em4, emList2[1]);
		EXPECT_EQ(em5, emList2[2]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicByPhoneNum)
	{
		Employ em = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em));

		vector<Employ> emList = db.selectItems(enumOptionList::None, { "phoneNum", "010-9999-9999" });

		EXPECT_EQ(em, emList[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiByPhoneNum)
	{
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9991"), Birthday("19991212"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE2"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991212"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE3"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991212"), enumCerti::PRO);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE4"), enumCL::CL4, PhoneNumber("010-9999-9994"), Birthday("19991212"), enumCerti::PRO);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE5"), enumCL::CL1, PhoneNumber("010-9999-9995"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "phoneNum", "010-9999-9991" });

		EXPECT_EQ(em1, emList1[0]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "phoneNum", "010-9999-9992" });

		EXPECT_EQ(em2, emList2[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiOberlapByPhoneNum)
	{
		Employ em0 = Employ(20551234, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9991"), Birthday("19991212"), enumCerti::PRO);
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991212"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991212"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991212"), enumCerti::PRO);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991212"), enumCerti::PRO);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991212"), enumCerti::PRO);
		Employ em6 = Employ(20551240, Name("SANGKAP LEE2"), enumCL::CL4, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "phoneNum", "010-9999-9992" });

		EXPECT_EQ(emList1.size(), 2);
		EXPECT_EQ(em1, emList1[0]);
		EXPECT_EQ(em2, emList1[1]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "phoneNum", "010-9999-9993" });

		EXPECT_EQ(emList2.size(), 3);
		EXPECT_EQ(em3, emList2[0]);
		EXPECT_EQ(em4, emList2[1]);
		EXPECT_EQ(em5, emList2[2]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicByBirthday)
	{
		Employ em = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em));

		vector<Employ> emList = db.selectItems(enumOptionList::None, { "birthday", "19991212" });

		EXPECT_EQ(em, emList[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiByBirthday)
	{
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9991"), Birthday("19991212"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE2"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE3"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::PRO);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE4"), enumCL::CL4, PhoneNumber("010-9999-9994"), Birthday("19991215"), enumCerti::PRO);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE5"), enumCL::CL1, PhoneNumber("010-9999-9995"), Birthday("19991216"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "birthday", "19991212" });

		EXPECT_EQ(em1, emList1[0]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "birthday", "19991213" });

		EXPECT_EQ(em2, emList2[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiOberlapByBirthday)
	{
		Employ em0 = Employ(20551234, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9991"), Birthday("19991212"), enumCerti::PRO);
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::PRO);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::PRO);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::PRO);
		Employ em6 = Employ(20551240, Name("SANGKAP LEE2"), enumCL::CL4, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "birthday", "19991213" });

		EXPECT_EQ(emList1.size(), 2);
		EXPECT_EQ(em1, emList1[0]);
		EXPECT_EQ(em2, emList1[1]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "birthday", "19991214" });

		EXPECT_EQ(emList2.size(), 3);
		EXPECT_EQ(em3, emList2[0]);
		EXPECT_EQ(em4, emList2[1]);
		EXPECT_EQ(em5, emList2[2]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicByCerti)
	{
		Employ em = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(em));

		vector<Employ> emList = db.selectItems(enumOptionList::None, { "certi", "PRO" });

		EXPECT_EQ(em, emList[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiByCerti)
	{
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9991"), Birthday("19991212"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE2"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::EX);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE3"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::ADV);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE4"), enumCL::CL4, PhoneNumber("010-9999-9994"), Birthday("19991215"), enumCerti::ADV);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE5"), enumCL::CL1, PhoneNumber("010-9999-9995"), Birthday("19991216"), enumCerti::ADV);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "certi", "PRO" });

		EXPECT_EQ(em1, emList1[0]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "certi", "EX" });

		EXPECT_EQ(em2, emList2[0]);
	}

	TEST_F(DBInterfaceTest, SelectTestPositive_BasicMultiOberlapByCerti)
	{
		Employ em0 = Employ(20551234, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9991"), Birthday("19991212"), enumCerti::ADV);
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em6 = Employ(20551240, Name("SANGKAP LEE2"), enumCL::CL4, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::ADV);

		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));

		vector<Employ> emList1 = db.selectItems(enumOptionList::None, { "certi", "PRO" });

		EXPECT_EQ(emList1.size(), 2);
		EXPECT_EQ(em1, emList1[0]);
		EXPECT_EQ(em2, emList1[1]);

		vector<Employ> emList2 = db.selectItems(enumOptionList::None, { "certi", "EX" });

		EXPECT_EQ(emList2.size(), 3);
		EXPECT_EQ(em3, emList2[0]);
		EXPECT_EQ(em4, emList2[1]);
		EXPECT_EQ(em5, emList2[2]);
	}

	TEST_F(DBInterfaceTest, UpdatePositive_BasicByEmployeeNumChangeEmployeeNum)
	{
		Employ emOrigin = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ emUpdate = Employ(19551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(emOrigin));

		vector<Employ> emListOrigin = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emOrigin, emListOrigin[0]);

		vector<Employ> emListPrev = db.updateItems(enumOptionList::None, { "employeeNum", "20551235" }, { "employeeNum", "19551235" });

		EXPECT_EQ(emOrigin, emListPrev[0]);

		vector<Employ> emListUpdate = db.selectItems(enumOptionList::None, { "employeeNum", "19551235" });

		EXPECT_EQ(emUpdate, emListUpdate[0]);
	}

	TEST_F(DBInterfaceTest, UpdatePositive_BasicByEmployeeNumChangeName)
	{
		Employ emOrigin = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ emUpdate = Employ(20551235, Name("SANGKAP KIM"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(emOrigin));

		vector<Employ> emListOrigin = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emOrigin, emListOrigin[0]);

		vector<Employ> emListPrev = db.updateItems(enumOptionList::None, { "employeeNum", "20551235" }, { "name", "SANGKAP KIM" });

		EXPECT_EQ(emOrigin, emListPrev[0]);

		vector<Employ> emListUpdate = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emUpdate, emListUpdate[0]);
	}

	TEST_F(DBInterfaceTest, UpdatePositive_BasicByEmployeeNumChangeCl)
	{
		Employ emOrigin = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ emUpdate = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL2, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(emOrigin));

		vector<Employ> emListOrigin = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emOrigin, emListOrigin[0]);

		vector<Employ> emListPrev = db.updateItems(enumOptionList::None, { "employeeNum", "20551235" }, { "cl", "CL2" });

		EXPECT_EQ(emOrigin, emListPrev[0]);

		vector<Employ> emListUpdate = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emUpdate, emListUpdate[0]);
	}

	TEST_F(DBInterfaceTest, UpdatePositive_BasicByEmployeeNumChangePhoneNumber)
	{
		Employ emOrigin = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ emUpdate = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-8888"), Birthday("19991212"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(emOrigin));

		vector<Employ> emListOrigin = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emOrigin, emListOrigin[0]);

		vector<Employ> emListPrev = db.updateItems(enumOptionList::None, { "employeeNum", "20551235" }, { "phoneNum", "010-9999-8888" });

		EXPECT_EQ(emOrigin, emListPrev[0]);

		vector<Employ> emListUpdate = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emUpdate, emListUpdate[0]);
	}

	TEST_F(DBInterfaceTest, UpdatePositive_BasicByEmployeeNumChangeBirthday)
	{
		Employ emOrigin = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ emUpdate = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991210"), enumCerti::PRO);

		EXPECT_TRUE(db.insertItem(emOrigin));

		vector<Employ> emListOrigin = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emOrigin, emListOrigin[0]);

		vector<Employ> emListPrev = db.updateItems(enumOptionList::None, { "employeeNum", "20551235" }, { "birthday", "19991210" });

		EXPECT_EQ(emOrigin, emListPrev[0]);

		vector<Employ> emListUpdate = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emUpdate, emListUpdate[0]);
	}

	TEST_F(DBInterfaceTest, UpdatePositive_BasicByEmployeeNumChangeCerti)
	{
		Employ emOrigin = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
		Employ emUpdate = Employ(20551235, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::EX);

		EXPECT_TRUE(db.insertItem(emOrigin));

		vector<Employ> emListOrigin = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emOrigin, emListOrigin[0]);

		vector<Employ> emListPrev = db.updateItems(enumOptionList::None, { "employeeNum", "20551235" }, { "certi", "EX" });

		EXPECT_EQ(emOrigin, emListPrev[0]);

		vector<Employ> emListUpdate = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });

		EXPECT_EQ(emUpdate, emListUpdate[0]);
	}

	TEST_F(DBInterfaceTest, UpdatePositive_BasicByEmployeeNumChangeCertiMulti)
	{
		Employ em0 = Employ(20551234, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9991"), Birthday("19991212"), enumCerti::ADV);
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em6 = Employ(20551240, Name("SANGKAP LEE2"), enumCL::CL4, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::ADV);

		EXPECT_TRUE(db.insertItem(em0));
		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));
		EXPECT_TRUE(db.insertItem(em6));


		vector<Employ> emListUpdate = db.updateItems(enumOptionList::None, { "certi", "EX" }, { "certi", "PRO" });

		vector<Employ> emListSel1 = db.selectItems(enumOptionList::None, { "certi", "PRO" });

		EXPECT_EQ(emListSel1.size(), 5);

		vector<Employ> emListSel0 = db.selectItems(enumOptionList::None, { "certi", "EX" });

		EXPECT_EQ(emListSel0.size(), 0);
	}

	TEST_F(DBInterfaceTest, DeletePositive_BasicByEmployeeNum)
	{
		Employ em0 = Employ(20551234, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9991"), Birthday("19991212"), enumCerti::ADV);
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em6 = Employ(20551240, Name("SANGKAP LEE2"), enumCL::CL4, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::ADV);

		EXPECT_TRUE(db.insertItem(em0));
		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));
		EXPECT_TRUE(db.insertItem(em6));

		EXPECT_EQ(db.getCurRecordsCount(), 7);
		vector<Employ> emDel = db.deleteItems(enumOptionList::None, { "employeeNum", "20551235" });
		EXPECT_EQ(em1, emDel[0]);
		EXPECT_EQ(db.getCurRecordsCount(), 6);

		vector<Employ> emSel = db.selectItems(enumOptionList::None, { "employeeNum", "20551235" });
		EXPECT_EQ(emSel.size(), 0);
	}

	TEST_F(DBInterfaceTest, DeletePositive_BasicByName)
	{
		Employ em0 = Employ(20551234, Name("SANGKAP LEE1"), enumCL::CL1, PhoneNumber("010-9999-9991"), Birthday("19991212"), enumCerti::ADV);
		Employ em1 = Employ(20551235, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em2 = Employ(20551236, Name("SANGKAP LEE1"), enumCL::CL2, PhoneNumber("010-9999-9992"), Birthday("19991213"), enumCerti::PRO);
		Employ em3 = Employ(20551237, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em4 = Employ(20551238, Name("SANGKAP LEE2"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em5 = Employ(20551239, Name("SANGKAP LEE3"), enumCL::CL3, PhoneNumber("010-9999-9993"), Birthday("19991214"), enumCerti::EX);
		Employ em6 = Employ(20551240, Name("SANGKAP LEE3"), enumCL::CL4, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::ADV);

		EXPECT_TRUE(db.insertItem(em0));
		EXPECT_TRUE(db.insertItem(em1));
		EXPECT_TRUE(db.insertItem(em2));
		EXPECT_TRUE(db.insertItem(em3));
		EXPECT_TRUE(db.insertItem(em4));
		EXPECT_TRUE(db.insertItem(em5));
		EXPECT_TRUE(db.insertItem(em6));

		EXPECT_EQ(db.getCurRecordsCount(), 7);
		vector<Employ> emDel = db.deleteItems(enumOptionList::None, { "name", "SANGKAP LEE2" });
		EXPECT_EQ(em3, emDel[0]);
		EXPECT_EQ(db.getCurRecordsCount(), 5);

		vector<Employ> emSel = db.selectItems(enumOptionList::None, { "name", "SANGKAP LEE2" });
		EXPECT_EQ(emSel.size(), 0);

		vector<Employ> emSel1 = db.selectItems(enumOptionList::None, { "name", "SANGKAP LEE1" });
		EXPECT_EQ(emSel1.size(), 3);

		vector<Employ> emSel2 = db.selectItems(enumOptionList::None, { "name", "SANGKAP LEE3" });
		EXPECT_EQ(emSel2.size(), 2);
	}
}