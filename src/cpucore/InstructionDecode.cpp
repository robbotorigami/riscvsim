/*
 * InstructionDecode.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#include "cpucore/InstructionDecode.h"

IDStage::IDStage(Signal<pcval_t>& pcIn, Signal<inscode>& inscodeIn,
		Signal<regaddress>& writeRegisterIn, Signal<regdata>& writeDataIn,
		Signal<bool>& regWriteIn,
		Signal<Instruction*>& instructionOut, Signal<pcval_t>& pcOut,
		Signal<regdata>& readData1Out, Signal<regdata>& readData2Out,
		Signal<regdata>& immediateOut)
:pcIn(pcIn),
 inscodeIn(inscodeIn),
 writeRegisterIn(writeRegisterIn),
 writeDataIn(writeDataIn),
 regWriteIn(regWriteIn),
 instructionOut(instructionOut),
 pcOut(pcOut),
 readData1Out(readData1Out),
 readData2Out(readData2Out),
 immediateOut(immediateOut)
{
	instructionParser = new InstructionParser(inscodeIn, instruction);
	rrGen = new ReadRegisterGenerator(instruction, readReg1, readReg2);
	rf = new RegisterFile(readReg1, readReg2, writeRegisterIn, writeDataIn, readData1Out, readData2Out, regWriteIn);
	immedGen = new ImmediateGenerator(instruction, immediateOut);
	pccoupler = new Coupler<pcval_t>(pcIn, pcOut);
	inscoupler = new Coupler<Instruction*>(instruction, instructionOut);
}

IDStage::~IDStage(){
	delete instructionParser;
	delete rrGen;
	delete rf;
	delete immedGen;
	delete pccoupler;
	delete inscoupler;
}

void IDStage::clock(ClockEdge edge){
	rf->clock(edge);
}



