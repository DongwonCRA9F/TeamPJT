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
		DatabaseInterface db;

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

	TEST_F(DBInterfaceTest, InsertTestPositive_CheckManyRecords)
	{
		int recordsCount = 200000;
		for (int i = 0; i < recordsCount; i++)
		{
			Employ em = Employ(20000000 + i, Name("SANGKAP LEE"), enumCL::CL3, PhoneNumber("010-9999-9999"), Birthday("19991212"), enumCerti::PRO);
			EXPECT_TRUE(db.insertItem(em));
		}

		EXPECT_EQ(db.getCurRecordsCount(), recordsCount);
	}
}