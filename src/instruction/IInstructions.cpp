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
	//Sign Extend this thing out
	int16_t immed = fields.immed;
	immed <<= 4;
	immed >>= 4;
	if(!getName().compare(0, 1, "L")){
		//This is a load instruction so the syntax is a little wonky
		std::stringstream ss;
		ss << getName() << " x" << fields.rd << ", " << immed << "(x" << fields.rs1 << ")";
		return ss.str();
	}

	if(!getName().compare(0, 4, "SLLI") || !getName().compare(0, 4, "SRLI") || !getName().compare(0, 4, "SRAI")){
		//This is a shift instruction, so mask the bits in the immediate out
		std::stringstream ss;
		ss << getName() << " x" << fields.rd << ", x" << fields.rs1 << ", " << (immed & 0x03F);
		return ss.str();
	}
	std::stringstream ss;
	ss << getName() << " x" << fields.rd << ", x" << fields.rs1 << ", " << immed;
	return ss.str();
}

regdata IInstruction::getImmediate(){
	//Sign extend the immediate to 16 bit, then let c sign extend when promoting to 32/64
	int16_t immed = fields.immed;
	immed <<= 4;
	immed >>= 4;

	if(!getName().compare(0, 4, "SLLI") || !getName().compare(0, 4, "SRLI") || !getName().compare(0, 4, "SRAI")){
		//This is a shift instruction, so mask the bits in the immediate out
		immed = (immed & 0x03F);
	}
	return immed;
}

regaddress IInstruction::getRS1(){
	return fields.rs1;
}

regaddress IInstruction::getRS2(){
	return 0;
}

ALUSrc_t IInstruction::getALUSrc(){
	return IMMEDIATE;
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

//ALU is irrelevant for JALR, but always branch
ALU_OPERATION(JALR, 		arg1+arg2,		true);
//Compute address as sum of two args for load, never branch
ALU_OPERATION(LB, 			arg1+arg2, 		false);
ALU_OPERATION(LH, 			arg1+arg2, 		false);
ALU_OPERATION(LW, 			arg1+arg2, 		false);
ALU_OPERATION(LBU, 			arg1+arg2, 		false);
ALU_OPERATION(LHU, 			arg1+arg2, 		false);
ALU_OPERATION(LWU, 			arg1+arg2, 		false);
ALU_OPERATION(LD, 			arg1+arg2, 		false);
//Perform relavent operation for AL ops, never branch
ALU_OPERATION(ADDI, 		arg1+arg2, 		false);
ALU_OPERATION(SLTI, 		arg1<arg2, 		false);
ALU_OPERATION(SLTIU, 		(uint64_t)arg1<(uint64_t)arg2, 		false);
ALU_OPERATION(XORI, 		arg1^arg2, 		false);
ALU_OPERATION(ORI, 			arg1|arg2, 		false);
ALU_OPERATION(ANDI, 		arg1&arg2, 		false);
ALU_OPERATION(SLLI, 		arg1<<arg2, 		false);
//Bit shifting magic to ensure logical right shift
ALU_OPERATION(SRLI, 		(arg1>>arg2)&~((uint64_t)~0 << (arg2+1)), 		false);
ALU_OPERATION(SRAI, 		arg1>>arg2, 		false);
