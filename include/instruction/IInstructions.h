/*
 * RInstructions.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_INSTRUCTION_RINSTRUCTIONS_H_
#define INCLUDE_INSTRUCTION_RINSTRUCTIONS_H_
#include <instruction/Instructions.h>

/*!
 * \brief Super class for all I instructions.
 * Implements parsing of fields for I type instructions.
 */
class IInstruction: public Instruction{
public:
	std::string asString();

protected:
	void parseFields(inscode code);
	struct Fields{
		uint32_t immed  : 12;
		uint32_t rs1 	: 5;
		uint32_t funct3 : 3;
		uint32_t rd		: 5;
		uint32_t opcode : 7;
	}fields;
};

INSTRUCTION(JALR, 	I);
INSTRUCTION(LB, 	I);
INSTRUCTION(LH, 	I);
INSTRUCTION(LW, 	I);
INSTRUCTION(LBU, 	I);
INSTRUCTION(LHU, 	I);
INSTRUCTION(LWU,	I);
INSTRUCTION(LD, 	I);
INSTRUCTION(ADDI, 	I);
INSTRUCTION(SLTI, 	I);
INSTRUCTION(SLTIU, 	I);
INSTRUCTION(XORI, 	I);
INSTRUCTION(ORI, 	I);
INSTRUCTION(ANDI, 	I);
INSTRUCTION(SLLI,	I);
INSTRUCTION(SRLI,	I);
INSTRUCTION(SRAI,	I);



#endif /* INCLUDE_INSTRUCTION_RINSTRUCTIONS_H_ */
