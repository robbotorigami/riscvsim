/*
 * BInstructions.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: cyborg9
 */
#include "instruction/JInstructions.h"
#include <sstream>

/*!
 * \brief take machine code instruction and seperate into fields
 * \param code machine code instruction
 */
void JInstruction::parseFields(inscode code){
	fields.opcode	= code & 0b01111111;
	code >>= 7;
	fields.rd  		= code & 0b00011111;
	code >>= 5;
	fields.immed1912= code & 0b11111111;
	code >>= 8;
	fields.immed11 	= code & 0b00000001;
	code >>= 1;
	fields.immed101	= code & 0b1111111111;
	code >>= 10;
	fields.immed20	= code & 0b00000001;
	code >>= 1;

	fields.immed = (fields.immed20 << 20) | (fields.immed1912 << 12) | (fields.immed11 << 11)
			| (fields.immed101 << 1);
}

std::string JInstruction::asString(){
	std::stringstream ss;
	ss << getName() << " x" << fields.rd << ", " << fields.immed;
	return ss.str();
}

INSTRUCTION_BOILERPLATE(JAL)

MATCHES_ON(JAL, 	fields.opcode == 0b1101111)



