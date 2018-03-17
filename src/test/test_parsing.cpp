/*
 * test_parsing.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */
#include <array>
#include <instruction/Instructions.h>
#include "test/catch.hpp"

using namespace std;

#include "test/gen_testcodes.h"

TEST_CASE("Parse R Instructions", "[parsing][r]"){
	for(size_t i = 0; i < sizeof(rcodes)/sizeof(rcodes[0]); i++){
		Instruction* ins = InstructionFactory::parseInstruction(rcodes[i]);
		REQUIRE(ins != nullptr);
		REQUIRE(ins->asString() == rinstructions[i]);
	}
}

TEST_CASE("Parse I Instructions", "[parsing][i]"){
	for(size_t i = 0; i < sizeof(icodes)/sizeof(icodes[0]); i++){
		Instruction* ins = InstructionFactory::parseInstruction(icodes[i]);
		CAPTURE(icodes[i]);
		CAPTURE(iinstructions[i]);
		REQUIRE(ins != nullptr);
		REQUIRE(ins->asString() == iinstructions[i]);
	}
}


TEST_CASE("Parse B Instructions", "[parsing][b]"){
	for(size_t i = 0; i < sizeof(bcodes)/sizeof(bcodes[0]); i++){
		Instruction* ins = InstructionFactory::parseInstruction(bcodes[i]);
		CAPTURE(bcodes[i]);
		CAPTURE(binstructions[i]);
		REQUIRE(ins != nullptr);
		REQUIRE(ins->asString() == binstructions[i]);
	}
}

TEST_CASE("Parse J Instructions", "[parsing][j]"){
	for(size_t i = 0; i < sizeof(jcodes)/sizeof(jcodes[0]); i++){
		Instruction* ins = InstructionFactory::parseInstruction(jcodes[i]);
		CAPTURE(jcodes[i]);
		CAPTURE(jinstructions[i]);
		REQUIRE(ins != nullptr);
		REQUIRE(ins->asString() == jinstructions[i]);
	}
}

TEST_CASE("Parse S Instructions", "[parsing][s]"){
	for(size_t i = 0; i < sizeof(scodes)/sizeof(scodes[0]); i++){
		Instruction* ins = InstructionFactory::parseInstruction(scodes[i]);
		CAPTURE(scodes[i]);
		CAPTURE(sinstructions[i]);
		REQUIRE(ins != nullptr);
		REQUIRE(ins->asString() == sinstructions[i]);
	}
}

TEST_CASE("Parse U Instructions", "[parsing][u]"){
	for(size_t i = 0; i < sizeof(ucodes)/sizeof(ucodes[0]); i++){
		Instruction* ins = InstructionFactory::parseInstruction(ucodes[i]);
		CAPTURE(ucodes[i]);
		CAPTURE(uinstructions[i]);
		REQUIRE(ins != nullptr);
		REQUIRE(ins->asString() == uinstructions[i]);
	}
}
