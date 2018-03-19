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

regdata JInstruction::getImmediate(){
	//Sign extend the immediate to 32 bit, then let c sign extend when promoting to 32/64
	int32_t immed = ((uint32_t)fields.immed << 11);
	immed >>= 11;
	return immed;
}

regaddress JInstruction::getRS1(){
	return 0;
}

regaddress JInstruction::getRS2(){
	return 0;
}


INSTRUCTION_BOILERPLATE(JAL)

MATCHES_ON(JAL, 	fields.opcode == 0b1101111)

//ALU return PC+4, always branch
ALU_OPERATION(JAL, arg1+4, true);

ALU_SOURCE(JAL, PROGRAMCOUNTER, IMMEDIATE)

//Writeback to rd always, never memtoreg
WRITEBACK(JAL, fields.rd, true, false)


