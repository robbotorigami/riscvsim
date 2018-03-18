/*
 * test_instructiondecode.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */
#include "cpucore/InstructionDecode.h"
#include "test/catch.hpp"

#include "test/gen_testcodes.h"

TEST_CASE("Test Instruction Decode", "[cpucore][ID]"){
	Signal<pcval_t> pcIn, pcOut;
	Signal<inscode> inscodeIn;
	Signal<regaddress> writeRegisterIn;
	Signal<regdata> writeDataIn, readData1Out, readData2Out, immediateOut;
	Signal<Instruction*> instructionOut;
	Signal<bool> regWriteIn;

	IDStage ids(pcIn, inscodeIn, writeRegisterIn, writeDataIn, regWriteIn,
				instructionOut, pcOut, readData1Out, readData2Out, immediateOut);

	//Fill register file with dummy data
	std::vector<regdata> regvalues;
	for(int i = 0; i < 32; i++){
		regvalues.push_back(i*5);
		writeRegisterIn = i;
		writeDataIn = i*5;
		regWriteIn = true;
		ids.clock(RISING);
	}

	regWriteIn = false;

	SECTION("Test that pc is passed through"){
		for(int i = 0; i < 100; i++){
			pcIn = i;
			REQUIRE(pcOut == i);
		}
	}

	SECTION("Test that registers are decoded properly"){
		for(size_t i = 0; i < sizeof(rcodes)/sizeof(rcodes[0]); i++){
			inscodeIn = rcodes[i];
			Instruction* ins = instructionOut;
			REQUIRE(ins != nullptr);
			REQUIRE(ins->asString() == rinstructions[i]);
			REQUIRE(immediateOut == rimmeds[i]);
			REQUIRE(readData1Out == regvalues[rrs1s[i]]);
			REQUIRE(readData2Out == regvalues[rrs2s[i]]);

			delete ins;
		}
	}

	SECTION("Test that immediates are decoded properly"){
		for(size_t i = 0; i < sizeof(icodes)/sizeof(icodes[0]); i++){
			inscodeIn = icodes[i];
			Instruction* ins = instructionOut;
			REQUIRE(ins != nullptr);
			REQUIRE(ins->asString() == iinstructions[i]);
			REQUIRE(immediateOut == iimmeds[i]);
			REQUIRE(readData1Out == regvalues[irs1s[i]]);
			REQUIRE(readData2Out == regvalues[irs2s[i]]);

			delete ins;
		}
	}

}



