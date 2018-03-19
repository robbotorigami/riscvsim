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

regdata UInstruction::getImmediate(){
	//Sign extend the immediate to 32 bit, then let c sign extend when promoting to 32/64
	int32_t immed = ((uint32_t)fields.immed << 12);
	immed >>= 12;
	return immed;
}

regaddress UInstruction::getRS1(){
	return 0;
}

regaddress UInstruction::getRS2(){
	return 0;
}

INSTRUCTION_BOILERPLATE(LUI)
INSTRUCTION_BOILERPLATE(AUIPC)

MATCHES_ON(LUI, 	fields.opcode == 0b0110111)
MATCHES_ON(AUIPC, 	fields.opcode == 0b0010111)

//Just return the immediate shifted appropriately, never branch
ALU_OPERATION(LUI, 	 arg2<<12,        false)
//Same as LUI but add PC
ALU_OPERATION(AUIPC, arg1 + (arg2<<12), false)

ALU_SOURCE(LUI,   REGISTER, IMMEDIATE)
ALU_SOURCE(AUIPC, PROGRAMCOUNTER, IMMEDIATE)

//Always writeback, never memtoreg
WRITEBACK(LUI, fields.rd, true, false)
WRITEBACK(AUIPC, fields.rd, true, false)
