/*
 * BInstructions.h
 *
 *  Created on: Mar 4, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_INSTRUCTION_BINSTRUCTIONS_H_
#define INCLUDE_INSTRUCTION_BINSTRUCTIONS_H_
#include <instruction/Instructions.h>

/*!
 * \brief Super class for all B instructions.
 * Implements parsing of fields for B type instructions.
 */
class BInstruction: public Instruction{
public:
	std::string asString();

protected:
	void parseFields(inscode code);
	struct Fields{
		uint32_t immed12  : 1;
		uint32_t immed105 : 6;
		uint32_t rs2 	  : 5;
		uint32_t rs1 	  : 5;
		uint32_t funct3   : 3;
		uint32_t immed41  : 4;
		uint32_t immed11  : 1;
		uint32_t opcode   : 7;
		uint32_t immed    : 13;
	}fields;
};

INSTRUCTION(BEQ, 	B);
INSTRUCTION(BNE, 	B);
INSTRUCTION(BLT, 	B);
INSTRUCTION(BGE, 	B);
INSTRUCTION(BLTU, 	B);
INSTRUCTION(BGEU, 	B);




#endif /* INCLUDE_INSTRUCTION_BINSTRUCTIONS_H_ */
