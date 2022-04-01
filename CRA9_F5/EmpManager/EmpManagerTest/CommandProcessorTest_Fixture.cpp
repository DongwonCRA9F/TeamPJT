#include "pch.h"
#include "CommandProcessorTest_Fixture.h"



void CommandProcessorFixture::SetUp() {

	//ADD, , , , 15123099, VXIHXOTH JHOP, CL3, 010 - 3112 - 2609, 19771211, ADV
	//	ADD, , , , 17112609, FB NTAWR, CL4, 010 - 5645 - 6122, 19861203, PRO
	//	ADD, , , , 18115040, TTETHU HBO, CL3, 010 - 4581 - 2050, 20080718, ADV
	//	ADD, , , , 88114052, NQ LVARW, CL4, 010 - 4528 - 3059, 19911021, PRO
	//	ADD, , , , 19129568, SRERLALH HMEF, CL2, 010 - 3091 - 9521, 19640910, PRO
	//	ADD, , , , 17111236, VSID TVO, CL1, 010 - 3669 - 1077, 20120718, PRO
	//	ADD, , , , 18117906, TWU QSOLT, CL4, 010 - 6672 - 7186, 20030413, PRO
	//	ADD, , , , 08123556, WN XV, CL1, 010 - 7986 - 5047, 20100614, PRO
	//	ADD, , , , 02117175, SBILHUT LDEXRI, CL4, 010 - 2814 - 1699, 19950704, ADV
	//	ADD, , , , 03113260, HH LTUPF, CL2, 010 - 5798 - 5383, 19791018, PRO
	//	ADD, , , , 14130827, RPO JK, CL4, 010 - 3231 - 1698, 20090201, ADV
	//	ADD, , , , 01122329, DN WD, CL4, 010 - 7174 - 5680, 20071117, PRO
	//	ADD, , , , 08108827, RTAH VNUP, CL4, 010 - 9031 - 2726, 19780417, ADV
	//	ADD, , , , 85125741, FBAH RTIJ, CL1, 010 - 8900 - 1478, 19780228, ADV
	//	ADD, , , , 08117441, BMU MPOSXU, CL3, 010 - 2703 - 3153, 20010215, ADV
	//	ADD, , , , 10127115, KBU MHU, CL3, 010 - 3284 - 4054, 19660814, ADV
	//	ADD, , , , 12117017, LFIS JJIVL, CL1, 010 - 7914 - 4067, 20120812, PRO
	//	ADD, , , , 11125777, TKOQKIS HC, CL1, 010 - 6734 - 2289, 19991001, PRO
	//	ADD, , , , 11109136, QKAHCEX LTODDO, CL4, 010 - 2627 - 8566, 19640130, PRO
	//	ADD, , , , 05101762, VCUHLE HMU, CL4, 010 - 3988 - 9289, 20030819, PRO
}
void CommandProcessorFixture::TearDown() {
}
TEST_F(CommandProcessorFixture, ADDTest) {
	CommandProcessor* cmd = new CommandProcessorADD();
	CommandResult CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "15123099","VXIHXOTH JHOP","CL3","010-3112-2609","19771211","ADV" });
}
TEST_F(CommandProcessorFixture, MODTest) {
	CommandProcessor* cmd = new CommandProcessorMOD();
	CommandResult CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "cl","CL3", "phoneNum","010-9777-6055" });
	//CommandResult CR_exp = {3, 
	//EXPECT_EQ(CR, {});

	//CommandResult CR = cmd->run({ enumOptionList::RecordPrint, enumOptionList::FindByLastNum_PhoneNum, enumOptionList::None }, { "phoneNum", "010-9777-6055", "certi", "EX" });



	//vector<enumOptionList> ResultOption;
	//ResultOption.push_back(enumOptionList::None);

	//vector<string> ResultCondition;

	//CommandResult CR_exp;
	//CR_exp.count = 1;
	//CR_exp.list.clear();
	//EXPECT_EQ(CR, CR_exp);
}
TEST_F(CommandProcessorFixture, SCHTest) {
	CommandProcessor* cmd = new CommandProcessorMOD();
	CommandResult CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "birthday", "19900906" });
}
TEST_F(CommandProcessorFixture, DELTest) {
	CommandProcessor* cmd = new CommandProcessorDEL();
	CommandResult CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "name", "KYUMOK KIM" });

	CR = cmd->run({ enumOptionList::None, enumOptionList::None, enumOptionList::None }, { "phoneNum", "010-9777-6055" });

	CR = cmd->run({ enumOptionList::None, enumOptionList::FindByFirstName_Name, enumOptionList::None }, { "name", "KYUMOK" });
}


