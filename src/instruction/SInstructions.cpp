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

regdata SInstruction::getImmediate(){
	//Sign extend the immediate to 16 bit, then let c sign extend when promoting to 32/64
	int16_t immed = ((uint16_t)fields.immed << 4);
	immed >>= 4;
	return immed;
}

regaddress SInstruction::getRS1(){
	return fields.rs1;
}

regaddress SInstruction::getRS2(){
	return fields.rs2;
}


INSTRUCTION_BOILERPLATE(SB)
INSTRUCTION_BOILERPLATE(SH)
INSTRUCTION_BOILERPLATE(SW)
INSTRUCTION_BOILERPLATE(SD)

MATCHES_ON(SB, 	fields.funct3 == 0b000 && fields.opcode == 0b0100011)
MATCHES_ON(SH, 	fields.funct3 == 0b001 && fields.opcode == 0b0100011)
MATCHES_ON(SW, 	fields.funct3 == 0b010 && fields.opcode == 0b0100011)
MATCHES_ON(SD, 	fields.funct3 == 0b011 && fields.opcode == 0b0100011)

ALU_OPERATION(SB, 	arg1+arg2,	false)
ALU_OPERATION(SH, 	arg1+arg2,	false)
ALU_OPERATION(SW, 	arg1+arg2,	false)
ALU_OPERATION(SD, 	arg1+arg2,	false)

ALU_SOURCE(SB, 	REGISTER,	IMMEDIATE)
ALU_SOURCE(SH, 	REGISTER,	IMMEDIATE)
ALU_SOURCE(SW, 	REGISTER,	IMMEDIATE)
ALU_SOURCE(SD, 	REGISTER,	IMMEDIATE)

STORE_OPERATION(SB, val & 0xFF, 				BIT8);
STORE_OPERATION(SH, val & 0xFFFF, 				BIT16);
STORE_OPERATION(SW, val & 0xFFFFFFFF, 			BIT32);
STORE_OPERATION(SD, val & 0xFFFFFFFFFFFFFFFF, 	BIT64);

//Never writeback
WRITEBACK(SB, 0, false, false)
WRITEBACK(SH, 0, false, false)
WRITEBACK(SW, 0, false, false)
WRITEBACK(SD, 0, false, false)
