/*
 * IInstructions.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: cyborg9
 */

#include "instruction/IInstructions.h"
#include <sstream>

/*!
 * \brief take machine code instruction and seperate into fields
 * \param code machine code instruction
 */
void IInstruction::parseFields(inscode code){
	fields.opcode	= code & 0b01111111;
	code >>= 7;
	fields.rd 	 	= code & 0b00011111;
	code >>= 5;
	fields.funct3	= code & 0b00000111;
	code >>= 3;
	fields.rs1 		= code & 0b00011111;
	code >>= 5;
	fields.immed 	= code & 0b111111111111;
	code >>= 12;
}

std::string IInstruction::asString(){
	std::stringstream ss;
	ss << getName() << " x" << fields.rd << ", x" << fields.rs1 << ", " << fields.immed;
	return ss.str();
}

INSTRUCTION_BOILERPLATE(JALR);
INSTRUCTION_BOILERPLATE(LB);
INSTRUCTION_BOILERPLATE(LH);
INSTRUCTION_BOILERPLATE(LW);
INSTRUCTION_BOILERPLATE(LBU);
INSTRUCTION_BOILERPLATE(LHU);
INSTRUCTION_BOILERPLATE(LWU);
INSTRUCTION_BOILERPLATE(LD);
INSTRUCTION_BOILERPLATE(ADDI);
INSTRUCTION_BOILERPLATE(SLTI);
INSTRUCTION_BOILERPLATE(SLTIU);
INSTRUCTION_BOILERPLATE(XORI);
INSTRUCTION_BOILERPLATE(ORI);
INSTRUCTION_BOILERPLATE(ANDI);
INSTRUCTION_BOILERPLATE(SLLI);
INSTRUCTION_BOILERPLATE(SRLI);
INSTRUCTION_BOILERPLATE(SRAI);

MATCHES_ON(JALR, 	fields.funct3 == 0b000 && fields.opcode == 0b1100111);
MATCHES_ON(LB, 		fields.funct3 == 0b000 && fields.opcode == 0b0000011);
MATCHES_ON(LH, 		fields.funct3 == 0b001 && fields.opcode == 0b0000011);
MATCHES_ON(LW, 		fields.funct3 == 0b010 && fields.opcode == 0b0000011);
MATCHES_ON(LBU,		fields.funct3 == 0b100 && fields.opcode == 0b0000011);
MATCHES_ON(LHU,		fields.funct3 == 0b101 && fields.opcode == 0b0000011);
MATCHES_ON(LWU,		fields.funct3 == 0b110 && fields.opcode == 0b0000011);
MATCHES_ON(LD,		fields.funct3 == 0b011 && fields.opcode == 0b0000011);
MATCHES_ON(ADDI, 	fields.funct3 == 0b000 && fields.opcode == 0b0010011);
MATCHES_ON(SLTI, 	fields.funct3 == 0b010 && fields.opcode == 0b0010011);
MATCHES_ON(SLTIU, 	fields.funct3 == 0b011 && fields.opcode == 0b0010011);
MATCHES_ON(XORI, 	fields.funct3 == 0b100 && fields.opcode == 0b0010011);
MATCHES_ON(ORI, 	fields.funct3 == 0b110 && fields.opcode == 0b0010011);
MATCHES_ON(ANDI, 	fields.funct3 == 0b111 && fields.opcode == 0b0010011);

MATCHES_ON(SLLI, 	fields.funct3 == 0b001 && fields.opcode == 0b0010011);
MATCHES_ON(SRLI, 	!(fields.immed & 0b010000000000) && fields.funct3 == 0b101 && fields.opcode == 0b0010011);
MATCHES_ON(SRAI, 	 (fields.immed & 0b010000000000) && fields.funct3 == 0b101 && fields.opcode == 0b0010011);


