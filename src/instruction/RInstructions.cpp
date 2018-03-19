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

regdata RInstruction::getImmediate(){
	//No immediate in the opcode
	return 0;
}

regaddress RInstruction::getRS1(){
	return fields.rs1;
}

regaddress RInstruction::getRS2(){
	return fields.rs2;
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

//Perform relavent operation for AL ops, never branch
ALU_OPERATION(ADD, 			arg1+arg2, 		false);
ALU_OPERATION(SUB, 			arg1-arg2, 		false);
ALU_OPERATION(SLT, 			arg1<arg2, 		false);
ALU_OPERATION(SLTU, 		(uint64_t)arg1<(uint64_t)arg2, 		false);
ALU_OPERATION(XOR, 			arg1^arg2, 		false);
ALU_OPERATION(OR, 			arg1|arg2, 		false);
ALU_OPERATION(AND, 			arg1&arg2, 		false);
ALU_OPERATION(SLL,	 		arg1<<arg2, 		false);
//Bit shifting magic to ensure logical right shift
ALU_OPERATION(SRL, 			((uint64_t)arg1>>arg2), 		false);
ALU_OPERATION(SRA, 			arg1>>arg2, 		false);
//Word operators just need to be masked
ALU_OPERATION(ADDW, 		(uint32_t)arg1+(uint32_t)arg2, 		false);
ALU_OPERATION(SUBW, 		(uint32_t)arg1-(uint32_t)arg2, 		false);
//TODO: Bit shifting magic to make this work properly...
ALU_OPERATION(SLLW,	 			arg1<<arg2, 		false);
ALU_OPERATION(SRLW, 			((uint64_t)arg1>>arg2), 		false);
ALU_OPERATION(SRAW, 			arg1>>arg2, 		false);

ALU_SOURCE(ADD,		REGISTER, 	REGISTER)
ALU_SOURCE(SUB,		REGISTER, 	REGISTER)
ALU_SOURCE(SLL,		REGISTER, 	REGISTER)
ALU_SOURCE(SLT,		REGISTER, 	REGISTER)
ALU_SOURCE(SLTU,	REGISTER, 	REGISTER)
ALU_SOURCE(SRL,		REGISTER, 	REGISTER)
ALU_SOURCE(SRA,		REGISTER, 	REGISTER)
ALU_SOURCE(XOR,		REGISTER, 	REGISTER)
ALU_SOURCE(OR,		REGISTER, 	REGISTER)
ALU_SOURCE(AND,		REGISTER, 	REGISTER)
ALU_SOURCE(ADDW,	REGISTER, 	REGISTER)
ALU_SOURCE(SUBW,	REGISTER, 	REGISTER)
ALU_SOURCE(SLLW,	REGISTER, 	REGISTER)
ALU_SOURCE(SRLW,	REGISTER, 	REGISTER)
ALU_SOURCE(SRAW,	REGISTER, 	REGISTER)

//Always writeback, never memtoreg
WRITEBACK(ADD,		fields.rd, true, false)
WRITEBACK(SUB,		fields.rd, true, false)
WRITEBACK(SLL,		fields.rd, true, false)
WRITEBACK(SLT,		fields.rd, true, false)
WRITEBACK(SLTU,		fields.rd, true, false)
WRITEBACK(SRL,		fields.rd, true, false)
WRITEBACK(SRA,		fields.rd, true, false)
WRITEBACK(XOR,		fields.rd, true, false)
WRITEBACK(OR,		fields.rd, true, false)
WRITEBACK(AND,		fields.rd, true, false)
WRITEBACK(ADDW,		fields.rd, true, false)
WRITEBACK(SUBW,		fields.rd, true, false)
WRITEBACK(SLLW,		fields.rd, true, false)
WRITEBACK(SRLW,		fields.rd, true, false)
WRITEBACK(SRAW,		fields.rd, true, false)

