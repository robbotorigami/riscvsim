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
 * \brief Super class for all U instructions.
 * Implements parsing of fields for U type instructions.
 */
class JInstruction: public Instruction{
public:
	std::string asString();

protected:
	void parseFields(inscode code);
	struct Fields{
		uint32_t immed20  : 1;
		uint32_t immed101 : 10;
		uint32_t immed11  : 1;
		uint32_t immed1912: 8;
		uint32_t rd    : 5;
		uint32_t opcode   : 7;
		uint32_t immed : 20;
	}fields;
};

INSTRUCTION(JAL, 	J);




#endif /* INCLUDE_INSTRUCTION_BINSTRUCTIONS_H_ */
