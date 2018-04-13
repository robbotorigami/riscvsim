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

}

void IFIDRegister::clock(ClockEdge edge){
	pcval.clock(edge);
	instruction.clock(edge);
}

IDEXRegister::IDEXRegister():
INITIALIZE(pcval),
INITIALIZE(instruction),
INITIALIZE(readData1),
INITIALIZE(readData2),
INITIALIZE(immediate)
{

}

void IDEXRegister::clock(ClockEdge edge){
	pcval.clock(edge);
	instruction.clock(edge);
	readData1.clock(edge);
	readData2.clock(edge);
	immediate.clock(edge);

	if(edge == FALLING)
		INFORMATION("EX STAGE INS: " << static_cast<Instruction*>(instructionOut)->asString());
}

EXMEMRegister::EXMEMRegister():
INITIALIZE(pcval),
INITIALIZE(instruction),
INITIALIZE(zeroSignal),
INITIALIZE(aluRes),
INITIALIZE(writeData)
{

}

void EXMEMRegister::clock(ClockEdge edge){
	pcval.clock(edge);
	instruction.clock(edge);
	zeroSignal.clock(edge);
	aluRes.clock(edge);
	writeData.clock(edge);

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
			INFORMATION("WB STAGE INS: " << static_cast<Instruction*>(instructionOut)->asString());
}



