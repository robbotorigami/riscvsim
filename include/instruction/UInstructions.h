/*
 * BInstructions.h
 *
 *  Created on: Mar 4, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_INSTRUCTION_UINSTRUCTIONS_H_
#define INCLUDE_INSTRUCTION_UINSTRUCTIONS_H_
#include "instruction/0_Instructions.h"

/*!
 * \brief Super class for all U instructions.
 * Implements parsing of fields for U type instructions.
 */
class UInstruction: public Instruction{
public:
	std::string asString();
	regdata getImmediate();
	regaddress getRS1();
	regaddress getRS2();

	ALUSrc_t getALUSrc();
protected:
	void parseFields(inscode code);
	struct Fields{
		uint32_t immed : 20;
		uint32_t rd    : 5;
		uint32_t opcode   : 7;
	}fields;
};

INSTRUCTION(LUI, 	U);
INSTRUCTION(AUIPC, 	U);




#endif /* INCLUDE_INSTRUCTION_BINSTRUCTIONS_H_ */
