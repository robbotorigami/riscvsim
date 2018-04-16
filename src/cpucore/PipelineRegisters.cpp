/*
 * PipelineRegisters.cpp
 *
 *  Created on: Apr 13, 2018
 *      Author: cyborg9
 */

#include "cpucore/PipelineRegisters.h"
#include "config.h"


IFIDRegister::IFIDRegister():
INITIALIZE(pcval),
INITIALIZE(instruction)
{
	flush.registerDriven(this);
}

IFIDRegister::~IFIDRegister(){
	flush.unregisterDriven(this);
}

void IFIDRegister::clock(ClockEdge edge){
	if(!stall){
		pcval.clock(edge);
		instruction.clock(edge);
	}

	if(edge == FALLING){
		Instruction* tmp = InstructionFactory::parseInstruction(instructionIn);
		INFORMATION("IF STAGE INS:  " << tmp->asString());
		delete tmp;
		tmp = InstructionFactory::parseInstruction(instructionOut);
		INFORMATION("ID STAGE INS:  " << tmp->asString());
		delete tmp;
	}
}

void IFIDRegister::computeSignals(){
	if(flush){
		instructionIn = NOP_CODE;
		instruction.clock(RISING);
		instruction.clock(FALLING);
	}
}

IDEXRegister::IDEXRegister():
INITIALIZE(pcval),
INITIALIZE(instruction),
INITIALIZE(readData1),
INITIALIZE(readData2),
INITIALIZE(immediate)
{
	flush.registerDriven(this);
}

IDEXRegister::~IDEXRegister(){
	flush.unregisterDriven(this);
}

void IDEXRegister::clock(ClockEdge edge){
	if(!stall){
		pcval.clock(edge);
		instruction.clock(edge);
		readData1.clock(edge);
		readData2.clock(edge);
		immediate.clock(edge);
	}

	if(edge == FALLING)
		INFORMATION("EX STAGE INS:  " << static_cast<Instruction*>(instructionOut)->asString());
}

void IDEXRegister::computeSignals(){
	if(flush){
		Instruction* tmp1 = instructionIn;
		Instruction* tmp2 = instructionOut;
		instructionIn = NOP;
		instruction.clock(RISING);
		instruction.clock(FALLING);
		delete tmp1;
		delete tmp2;
	}
}

EXMEMRegister::EXMEMRegister():
INITIALIZE(pcval),
INITIALIZE(instruction),
INITIALIZE(zeroSignal),
INITIALIZE(aluRes),
INITIALIZE(writeData)
{
	stalled = false;
}

void EXMEMRegister::clock(ClockEdge edge){
	if(stalled && !stall && edge == RISING){
		instructionOut = NOP;
		stalled = false;
	}
	if(!stall){
		pcval.clock(edge);
		instruction.clock(edge);
		zeroSignal.clock(edge);
		aluRes.clock(edge);
		writeData.clock(edge);
	}else{
		stalled = true;
	}

	if(edge == FALLING)
			INFORMATION("MEM STAGE INS: " << static_cast<Instruction*>(instructionOut)->asString());
}

MEMWBRegister::MEMWBRegister():
INITIALIZE(instruction),
INITIALIZE(aluRes),
INITIALIZE(readData),
INITIALIZE(pcSRC)
{

}

void MEMWBRegister::clock(ClockEdge edge){
	instruction.clock(edge);
	aluRes.clock(edge);
	readData.clock(edge);
	pcSRC.clock(edge);

	if(edge == FALLING)
			INFORMATION("WB STAGE INS:  " << static_cast<Instruction*>(instructionOut)->asString());
}



