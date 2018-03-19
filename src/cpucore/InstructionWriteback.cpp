/*
 * InstructionWriteback.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: cyborg9
 */
#include "cpucore/InstructionWriteback.h"


WBStage::WBStage(
Signal<Instruction*>& instructionIn,
Signal<regdata>& readdataIn,
Signal<regdata>& aluResIn,
Signal<regdata>& dataWritebackOut,
Signal<regaddress>& regWritebackOut,
Signal<bool>& regWriteOut
)
:instructionIn(instructionIn),
 readdataIn(readdataIn),
 aluResIn(aluResIn),
 dataWritebackOut(dataWritebackOut),
 regWritebackOut(regWritebackOut),
 regWriteOut(regWriteOut)
{
	memRegSelector = new Mux<regdata>(aluResIn, readdataIn, memToReg, dataWritebackOut);
	wbgen = new WritebackGenerator(instructionIn, regWriteOut, memToReg, regWritebackOut);
	isink = new InstructionSink(instructionIn);
}

WBStage::~WBStage(){
	delete memRegSelector;
	delete wbgen;
	delete isink;
}

void WBStage::clock(ClockEdge edge){
	isink->clock(edge);
}
