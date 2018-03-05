/*
 * test_parsing.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */
#include <instruction/Instructions.h>
#include "test/catch.hpp"
#include <array>

using namespace std;

TEST_CASE("Parse R Instructions", "[parsing]"){
	inscode codes[] = {0x00f680b3,
			0x407305b3, 0x00821133, 0x0053a633, 0x00953833, 0x004744b3,
			0x003350b3, 0x40f651b3, 0x0037e133, 0x00a6f7b3, 0x00b4013b,
			0x40e4843b, 0x002291bb, 0x0073553b, 0x4092513b};
	string instructions[] = {
		"ADD x1, x13, x15",
		"SUB x11, x6, x7",
		"SLL x2, x4, x8",
		"SLT x12, x7, x5",
		"SLTU x16, x10, x9",
		"XOR x9, x14, x4",
		"SRL x1, x6, x3",
		"SRA x3, x12, x15",
		"OR x2, x15, x3",
		"AND x15, x13, x10",
		"ADDW x2, x8, x11",
		"SUBW x8, x9, x14",
		"SLLW x3, x5, x2",
		"SRLW x10, x6, x7",
		"SRAW x2, x4, x9"
	};

	for(size_t i = 1; i < sizeof(codes)/sizeof(codes[0]); i++){
		Instruction* ins = InstructionFactory::parseInstruction(codes[i]);
		REQUIRE(ins->asString() == instructions[i]);
	}

}

