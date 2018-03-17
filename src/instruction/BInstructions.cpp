/*
 * BInstructions.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: cyborg9
 */
#include "instruction/BInstructions.h"
#include <sstream>

/*!
 * \brief take machine code instruction and seperate into fields
 * \param code machine code instruction
 */
void BInstruction::parseFields(inscode code){
	fields.opcode	= code & 0b01111111;
	code >>= 7;
	fields.immed11 	= code & 0b00000001;
	code >>= 1;
	fields.immed41	= code & 0b00001111;
	code >>= 4;
	fields.funct3	= code & 0b00000111;
	code >>= 3;
	fields.rs1 		= code & 0b00011111;
	code >>= 5;
	fields.rs2 		= code & 0b00011111;
	code >>= 5;
	fields.immed105	= code & 0b00111111;
	code >>= 6;
	fields.immed12 	= code & 0b00000001;
	code >>= 1;

	fields.immed = (fields.immed12 << 12) | (fields.immed11 << 11) | (fields.immed105 << 5)
			| (fields.immed41 << 1);
}

std::string BInstruction::asString(){
	std::stringstream ss;
	//Sign extend when printing
	int16_t immed = ((uint16_t)fields.immed << 3);
	immed >>= 3;
	ss << getName() << " x" << fields.rs1 << ", x" << fields.rs2 << ", " << immed;
	return ss.str();
}

INSTRUCTION_BOILERPLATE(BEQ)
INSTRUCTION_BOILERPLATE(BNE)
INSTRUCTION_BOILERPLATE(BLT)
INSTRUCTION_BOILERPLATE(BGE)
INSTRUCTION_BOILERPLATE(BLTU)
INSTRUCTION_BOILERPLATE(BGEU)

MATCHES_ON(BEQ, 	fields.funct3 == 0b000 && fields.opcode == 0b1100011)
MATCHES_ON(BNE, 	fields.funct3 == 0b001 && fields.opcode == 0b1100011)
MATCHES_ON(BLT, 	fields.funct3 == 0b100 && fields.opcode == 0b1100011)
MATCHES_ON(BGE, 	fields.funct3 == 0b101 && fields.opcode == 0b1100011)
MATCHES_ON(BLTU, 	fields.funct3 == 0b110 && fields.opcode == 0b1100011)
MATCHES_ON(BGEU, 	fields.funct3 == 0b111 && fields.opcode == 0b1100011)



