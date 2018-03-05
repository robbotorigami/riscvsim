/*
 * SInstructions.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: cyborg9
 */
#include "instruction/SInstructions.h"
#include <sstream>

/*!
 * \brief take machine code instruction and seperate into fields
 * \param code machine code instruction
 */
void SInstruction::parseFields(inscode code){
	fields.opcode	= code & 0b01111111;
	code >>= 7;
	fields.immed2 	= code & 0b00011111;
	code >>= 5;
	fields.funct3	= code & 0b00000111;
	code >>= 3;
	fields.rs1 		= code & 0b00011111;
	code >>= 5;
	fields.rs2 		= code & 0b00011111;
	code >>= 5;
	fields.immed1 	= code & 0b01111111;
	code >>= 7;

	fields.immed = (fields.immed1 << 5) | fields.immed2;
}

std::string SInstruction::asString(){
	std::stringstream ss;
	ss << getName() << " x" << fields.rs2 << ", " << fields.immed << "(x" << fields.rs1 << ")";
	return ss.str();
}

INSTRUCTION_BOILERPLATE(SB)
INSTRUCTION_BOILERPLATE(SH)
INSTRUCTION_BOILERPLATE(SW)
INSTRUCTION_BOILERPLATE(SD)

MATCHES_ON(SB, 	fields.funct3 == 0b000 && fields.opcode == 0b0100011)
MATCHES_ON(SH, 	fields.funct3 == 0b001 && fields.opcode == 0b0100011)
MATCHES_ON(SW, 	fields.funct3 == 0b010 && fields.opcode == 0b0100011)
MATCHES_ON(SD, 	fields.funct3 == 0b011 && fields.opcode == 0b0100011)
