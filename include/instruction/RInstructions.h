/*
 * RInstructions.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_INSTRUCTION_RINSTRUCTIONS_H_
#define INCLUDE_INSTRUCTION_RINSTRUCTIONS_H_
#include "instruction/0_Instructions.h"

/*!
 * \brief Super class for all R instructions.
 * Implements parsing of fields for R type instructions.
 */
class RInstruction: public Instruction{
public:
	std::string asString();
	regdata getImmediate();
	regaddress getRS1();
	regaddress getRS2();

protected:
	void parseFields(inscode code);
	struct Fields{
		uint32_t funct7 : 7;
		uint32_t rs2 	: 5;
		uint32_t rs1 	: 5;
		uint32_t funct3 : 3;
		uint32_t rd		: 5;
		uint32_t opcode : 7;
	}fields;
};

INSTRUCTION(ADD, 	R);
INSTRUCTION(SUB, 	R);
INSTRUCTION(SLL, 	R);
INSTRUCTION(SLT, 	R);
INSTRUCTION(SLTU, 	R);
INSTRUCTION(XOR, 	R);
INSTRUCTION(SRL, 	R);
INSTRUCTION(SRA, 	R);
INSTRUCTION(OR, 	R);
INSTRUCTION(AND, 	R);
INSTRUCTION(ADDW, 	R);
INSTRUCTION(SUBW, 	R);
INSTRUCTION(SLLW, 	R);
INSTRUCTION(SRLW, 	R);
INSTRUCTION(SRAW, 	R);




#endif /* INCLUDE_INSTRUCTION_RINSTRUCTIONS_H_ */
