/*
 * SInstructions.h
 *
 *  Created on: Mar 4, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_INSTRUCTION_SINSTRUCTIONS_H_
#define INCLUDE_INSTRUCTION_SINSTRUCTIONS_H_
#include "instruction/0_Instructions.h"

/*!
 * \brief Super class for all S instructions.
 * Implements parsing of fields for S type instructions.
 */
class SInstruction: public Instruction{
public:
	std::string asString();
	regdata getImmediate();
	regaddress getRS1();
	regaddress getRS2();

protected:
	void parseFields(inscode code);
	struct Fields{
		uint32_t immed1 : 7;
		uint32_t rs2 	: 5;
		uint32_t rs1 	: 5;
		uint32_t funct3 : 3;
		uint32_t immed2	: 5;
		uint32_t opcode : 7;
		uint32_t immed  : 12;
	}fields;
};

STORE_INSTRUCTION(SB, 	S);
STORE_INSTRUCTION(SH, 	S);
STORE_INSTRUCTION(SW, 	S);
STORE_INSTRUCTION(SD, 	S);


#endif /* INCLUDE_INSTRUCTION_SINSTRUCTIONS_H_ */
