/*
 * BInstructions.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: cyborg9
 */
#include "instruction/UInstructions.h"
#include <sstream>

/*!
 * \brief take machine code instruction and seperate into fields
 * \param code machine code instruction
 */
void UInstruction::parseFields(inscode code){
	fields.opcode	= code & 0b01111111;
	code >>= 7;
	fields.rd  		= code & 0b00011111;
	code >>= 5;
	fields.immed 	= code & 0x0FFFFF;
	code >>= 20;
}

std::string UInstruction::asString(){
	std::stringstream ss;
	ss << getName() << " x" << fields.rd << ", " << fields.immed;
	return ss.str();
}

INSTRUCTION_BOILERPLATE(LUI)
INSTRUCTION_BOILERPLATE(AUIPC)

MATCHES_ON(LUI, 	fields.opcode == 0b0110111)
MATCHES_ON(AUIPC, 	fields.opcode == 0b0010111)



