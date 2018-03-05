/*
 * RInstructions.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#include "instruction/RInstructions.h"
#include <sstream>

/*!
 * \brief take machine code instruction and seperate into fields
 * \param code machine code instruction
 */
void RInstruction::parseFields(inscode code){
	fields.opcode	= code & 0b01111111;
	code >>= 7;
	fields.rd 	 	= code & 0b00011111;
	code >>= 5;
	fields.funct3	= code & 0b00000111;
	code >>= 3;
	fields.rs1 		= code & 0b00011111;
	code >>= 5;
	fields.rs2 		= code & 0b00011111;
	code >>= 5;
	fields.funct7 	= code & 0b01111111;
	code >>= 7;
}

std::string RInstruction::asString(){
	std::stringstream ss;
	ss << getName() << " x" << fields.rd << ", x" << fields.rs1 << ", x" << fields.rs2;
	return ss.str();
}

INSTRUCTION_BOILERPLATE(ADD)
INSTRUCTION_BOILERPLATE(SUB)
INSTRUCTION_BOILERPLATE(SLL)
INSTRUCTION_BOILERPLATE(SLT)
INSTRUCTION_BOILERPLATE(SLTU)
INSTRUCTION_BOILERPLATE(XOR)
INSTRUCTION_BOILERPLATE(SRL)
INSTRUCTION_BOILERPLATE(SRA)
INSTRUCTION_BOILERPLATE(OR)
INSTRUCTION_BOILERPLATE(AND)
INSTRUCTION_BOILERPLATE(ADDW)
INSTRUCTION_BOILERPLATE(SUBW)
INSTRUCTION_BOILERPLATE(SLLW)
INSTRUCTION_BOILERPLATE(SRLW)
INSTRUCTION_BOILERPLATE(SRAW)

MATCHES_ON(ADD, 	fields.funct7 == 0b0000000 && fields.funct3 == 0b000 && fields.opcode == 0b0110011)
MATCHES_ON(SUB, 	fields.funct7 == 0b0100000 && fields.funct3 == 0b000 && fields.opcode == 0b0110011)
MATCHES_ON(SLL, 	fields.funct7 == 0b0000000 && fields.funct3 == 0b001 && fields.opcode == 0b0110011)
MATCHES_ON(SLT, 	fields.funct7 == 0b0000000 && fields.funct3 == 0b010 && fields.opcode == 0b0110011)
MATCHES_ON(SLTU,	fields.funct7 == 0b0000000 && fields.funct3 == 0b011 && fields.opcode == 0b0110011)
MATCHES_ON(XOR, 	fields.funct7 == 0b0000000 && fields.funct3 == 0b100 && fields.opcode == 0b0110011)
MATCHES_ON(SRL, 	fields.funct7 == 0b0000000 && fields.funct3 == 0b101 && fields.opcode == 0b0110011)
MATCHES_ON(SRA, 	fields.funct7 == 0b0100000 && fields.funct3 == 0b101 && fields.opcode == 0b0110011)
MATCHES_ON(OR,  	fields.funct7 == 0b0000000 && fields.funct3 == 0b110 && fields.opcode == 0b0110011)
MATCHES_ON(AND, 	fields.funct7 == 0b0000000 && fields.funct3 == 0b111 && fields.opcode == 0b0110011)
MATCHES_ON(ADDW,	fields.funct7 == 0b0000000 && fields.funct3 == 0b000 && fields.opcode == 0b0111011)
MATCHES_ON(SUBW,	fields.funct7 == 0b0100000 && fields.funct3 == 0b000 && fields.opcode == 0b0111011)
MATCHES_ON(SLLW,	fields.funct7 == 0b0000000 && fields.funct3 == 0b001 && fields.opcode == 0b0111011)
MATCHES_ON(SRLW,	fields.funct7 == 0b0000000 && fields.funct3 == 0b101 && fields.opcode == 0b0111011)
MATCHES_ON(SRAW,	fields.funct7 == 0b0100000 && fields.funct3 == 0b101 && fields.opcode == 0b0111011)


