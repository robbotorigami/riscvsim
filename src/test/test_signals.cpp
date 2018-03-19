/*
 * test_signals.cpp
 *
 *  Created on: Mar 5, 2018
 *      Author: cyborg9
 */

#include "test/catch.hpp"
#include "cpucore/Signals.h"
#include "instruction/InstructionSignals.h"
#include "test/gen_testcodes.h"
#include "instruction/BInstructions.h"
#include "instruction/IInstructions.h"
#include "instruction/JInstructions.h"
#include "instruction/RInstructions.h"
#include "instruction/SInstructions.h"
#include "instruction/UInstructions.h"

#define INSTRUCTIONTESTS(NAME) \
	SECTION("TEST " #NAME){ \
		Instruction##NAME instance ##NAME; \
		ins = & instance##NAME;

#include <stdint.h>

TEST_CASE("Test that the mux functions correctly", "[signals][mux]"){
	Signal<bool> control;
	Signal<uint32_t> input1, input2, output;
	Mux<uint32_t> mux(input1, input2, control, output);

	SECTION("Ensure that both inputs make it through"){
		input1.setData(0xAA);
		input2.setData(0xBB);
		control.setData(false);
		REQUIRE(output.getData() == 0xAA);
		control.setData(true);
		REQUIRE(output.getData() == 0xBB);
	}
}

TEST_CASE("Test that the register functions correctly", "[signals][mux]"){
	Signal<uint32_t> sigin, sigout;
	Register<uint32_t> r(sigin, sigout);
	sigin = 202;
	r.clock(RISING);
	REQUIRE(sigout == 202);
	sigin = 404;
	REQUIRE(sigout == 202);
	r.clock(RISING);
	REQUIRE(sigout == 404);
}

TEST_CASE("Test that the adder functions correctly", "[signals][adder]"){
	Signal<uint32_t> input1, input2, output;
	Adder<uint32_t> a(input1, input2, output);
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			input1 = i;
			input2 = j;
			REQUIRE(output == i+j);
		}
	}
}

TEST_CASE("Test that the coupler functions correctly", "[signals][coupler]"){
	Signal<uint32_t> in, out;
	Coupler<uint32_t> c(in, out);
	for(int i = 0; i < 100; i++){
		in = i;
		REQUIRE(out == i);
	}
}

TEST_CASE("Test that the shifter functions correctly", "[signals][shifter]"){
	Signal<uint32_t> in, out;
	Shifter<uint32_t,1> s(in, out);
	for(int i = 0; i < 100; i++){
		in = i;
		REQUIRE(out == i <<1);
	}
}


TEST_CASE("Test that the instruction parser functions correctly", "[signals][parsing]"){
	std::vector<Instruction*> instructions;
	Signal<inscode> inscodeIn;
	Signal<Instruction*> instructionOut;
	InstructionParser ip(inscodeIn, instructionOut);

	SECTION("Parse R Instructions"){
		for(size_t i = 0; i < sizeof(rcodes)/sizeof(rcodes[0]); i++){
			inscodeIn = rcodes[i];
			Instruction* ins = instructionOut;
			REQUIRE(ins != nullptr);
			instructions.push_back(ins);
			REQUIRE(ins->asString() == rinstructions[i]);
		}
	}
	SECTION("Parse I Instructions"){
		for(size_t i = 0; i < sizeof(icodes)/sizeof(icodes[0]); i++){
			inscodeIn = icodes[i];
			Instruction* ins = instructionOut;
			REQUIRE(ins != nullptr);
			instructions.push_back(ins);
			REQUIRE(ins->asString() == iinstructions[i]);
		}
	}
	SECTION("Parse B Instructions"){
		for(size_t i = 0; i < sizeof(bcodes)/sizeof(bcodes[0]); i++){
			inscodeIn = bcodes[i];
			Instruction* ins = instructionOut;
			REQUIRE(ins != nullptr);
			instructions.push_back(ins);
			REQUIRE(ins->asString() == binstructions[i]);
		}
	}
	SECTION("Parse J Instructions"){
		for(size_t i = 0; i < sizeof(jcodes)/sizeof(jcodes[0]); i++){
			inscodeIn = jcodes[i];
			Instruction* ins = instructionOut;
			REQUIRE(ins != nullptr);
			instructions.push_back(ins);
			REQUIRE(ins->asString() == jinstructions[i]);
		}
	}
	SECTION("Parse S Instructions"){
		for(size_t i = 0; i < sizeof(scodes)/sizeof(scodes[0]); i++){
			inscodeIn = scodes[i];
			Instruction* ins = instructionOut;
			REQUIRE(ins != nullptr);
			instructions.push_back(ins);
			REQUIRE(ins->asString() == sinstructions[i]);
		}
	}
	SECTION("Parse U Instructions"){
		for(size_t i = 0; i < sizeof(ucodes)/sizeof(ucodes[0]); i++){
			inscodeIn = ucodes[i];
			Instruction* ins = instructionOut;
			REQUIRE(ins != nullptr);
			instructions.push_back(ins);
			REQUIRE(ins->asString() == uinstructions[i]);
		}
	}

	for(auto i : instructions){
		delete i;
	}
}

TEST_CASE("Test that the immediate parsing functions correctly", "[signals][parsing]"){
	Signal<Instruction*> instructionIn;
	Signal<regdata> immedOut;
	ImmediateGenerator immedGen(instructionIn, immedOut);

	SECTION("Parse R Instructions"){
		for(size_t i = 0; i < sizeof(rcodes)/sizeof(rcodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(rcodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(immedOut == rimmeds[i]);
			delete ins;
		}
	}
	SECTION("Parse I Instructions"){
		for(size_t i = 0; i < sizeof(icodes)/sizeof(icodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(icodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(immedOut == iimmeds[i]);
			delete ins;
		}
	}
	SECTION("Parse B Instructions"){
		for(size_t i = 0; i < sizeof(bcodes)/sizeof(bcodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(bcodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(immedOut == bimmeds[i]);
			delete ins;
		}
	}
	SECTION("Parse J Instructions"){
		for(size_t i = 0; i < sizeof(jcodes)/sizeof(jcodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(jcodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(immedOut == jimmeds[i]);
			delete ins;
		}
	}
	SECTION("Parse S Instructions"){
		for(size_t i = 0; i < sizeof(scodes)/sizeof(scodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(scodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(immedOut == simmeds[i]);
			delete ins;
		}
	}
	SECTION("Parse U Instructions"){
		for(size_t i = 0; i < sizeof(ucodes)/sizeof(ucodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(ucodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(immedOut == uimmeds[i]);
			delete ins;
		}
	}

}

TEST_CASE("Test that the read register parsing functions correctly", "[signals][parsing]"){
	Signal<Instruction*> instructionIn;
	Signal<regaddress> readReg1, readReg2;
	ReadRegisterGenerator rrgen(instructionIn, readReg1, readReg2);

	SECTION("Parse R Instructions"){
		for(size_t i = 0; i < sizeof(rcodes)/sizeof(rcodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(rcodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(readReg1 == rrs1s[i]);
			REQUIRE(readReg2 == rrs2s[i]);
			delete ins;
		}
	}
	SECTION("Parse I Instructions"){
		for(size_t i = 0; i < sizeof(icodes)/sizeof(icodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(icodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(readReg1 == irs1s[i]);
			REQUIRE(readReg2 == irs2s[i]);
			delete ins;
		}
	}
	SECTION("Parse B Instructions"){
		for(size_t i = 0; i < sizeof(bcodes)/sizeof(bcodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(bcodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(readReg1 == brs1s[i]);
			REQUIRE(readReg2 == brs2s[i]);
			delete ins;
		}
	}
	SECTION("Parse J Instructions"){
		for(size_t i = 0; i < sizeof(jcodes)/sizeof(jcodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(jcodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(readReg1 == jrs1s[i]);
			REQUIRE(readReg2 == jrs2s[i]);
			delete ins;
		}
	}
	SECTION("Parse S Instructions"){
		for(size_t i = 0; i < sizeof(scodes)/sizeof(scodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(scodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(readReg1 == srs1s[i]);
			REQUIRE(readReg2 == srs2s[i]);
			delete ins;
		}
	}
	SECTION("Parse U Instructions"){
		for(size_t i = 0; i < sizeof(ucodes)/sizeof(ucodes[0]); i++){
			Instruction* ins = InstructionFactory::parseInstruction(ucodes[i]);
			REQUIRE(ins != nullptr);
			instructionIn = ins;
			REQUIRE(readReg1 == urs1s[i]);
			REQUIRE(readReg2 == urs2s[i]);
			delete ins;
		}
	}

}

//TODO: only tests one of each group
TEST_CASE("Test that the memory controll signals work properly", "[signals][parsing]"){
	Signal<Instruction*> ins;
	Signal<bool> memRead, memWrite;
	Signal<BitCount_t> bitcount;

	MemoryControlGenerator mcGen(ins, memRead, memWrite, bitcount);

	INSTRUCTIONTESTS(BEQ)
		REQUIRE(!memRead);
		REQUIRE(!memWrite);
	}

	INSTRUCTIONTESTS(LW)
		REQUIRE(memRead);
		REQUIRE(!memWrite);
	}

	INSTRUCTIONTESTS(SB)
		REQUIRE(!memRead);
		REQUIRE(bitcount == BIT8);
	}

	INSTRUCTIONTESTS(SH)
		REQUIRE(!memRead);
		REQUIRE(bitcount == BIT16);
	}

	INSTRUCTIONTESTS(SW)
		REQUIRE(!memRead);
		REQUIRE(bitcount == BIT32);
	}

	INSTRUCTIONTESTS(SD)
		REQUIRE(!memRead);
		REQUIRE(bitcount == BIT64);
	}
}

TEST_CASE("Test that the store processing works correctly", "[signals][parsing]"){
	Signal<Instruction*> ins;
	Signal<regdata> input, output;

	input = 0x0123ABCDEF;

	StorePreprocessor spp(ins, input, output);

	INSTRUCTIONTESTS(SB)
		REQUIRE(output == 0xEF);
	}

	INSTRUCTIONTESTS(SH)
		REQUIRE(output == 0xCDEF);
	}

	INSTRUCTIONTESTS(SW)
		REQUIRE(output == 0x23ABCDEF);
	}

	INSTRUCTIONTESTS(SD)
		REQUIRE(output == 0x0123ABCDEF);
	}
}

//TODO: test all
TEST_CASE("Test that the load processing works correctly", "[signals][parsing]"){
	Signal<Instruction*> ins;
	Signal<regdata> input, output;

	input = 0x0123ABCDEF;

	LoadPostprocessor lpp(ins, input, output);

	INSTRUCTIONTESTS(LBU)
		REQUIRE(output == 0xEF);
	}

	INSTRUCTIONTESTS(LB)
		REQUIRE(output == 0xFFFFFFFFFFFFFFEF);
	}

	INSTRUCTIONTESTS(LHU)
		REQUIRE(output == 0xCDEF);
	}

	INSTRUCTIONTESTS(LH)
		REQUIRE(output == 0xFFFFFFFFFFFFCDEF);
	}

	INSTRUCTIONTESTS(LWU)
		REQUIRE(output == 0x23ABCDEF);
	}
	INSTRUCTIONTESTS(LW)
		REQUIRE(output == 0x0000000023ABCDEF);
	}
	INSTRUCTIONTESTS(LD)
		REQUIRE(output == 0x0123ABCDEF);
	}
}

