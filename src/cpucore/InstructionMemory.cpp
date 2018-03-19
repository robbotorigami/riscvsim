/*
 * InstructionMemory.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: cyborg9
 */
#include "cpucore/InstructionMemory.h"


MEMStage::MEMStage(
		Memory& mem,
		Signal<Instruction*>& instructionIn,
		Signal<bool>& zeroSignal,
		Signal<regdata>& aluResIn,
		Signal<regdata>& writeDataIn,
		Signal<Instruction*>& instructionOut,
		Signal<regdata>& aluResOut,
		Signal<regdata>& readDataOut,
		Signal<bool>& pcSRCOut
	)
:instructionIn(instructionIn),
 zeroSignal(zeroSignal),
 aluResIn(aluResIn),
 writeDataIn(writeDataIn),
 instructionOut(instructionOut),
 aluResOut(aluResOut),
 readDataOut(readDataOut),
 pcSRCOut(pcSRCOut)
{
	mcgen = new MemoryControlGenerator(instructionIn, memRead, memWrite, bitcount);
	spp = new StorePreprocessor(instructionIn, writeDataIn, processedSD);
	lpp = new LoadPostprocessor(instructionIn, unprocessedLD, readDataOut);
	dmem = new DataMemory(mem, aluResIn, processedSD, bitcount, memWrite, memRead, unprocessedLD);
	c1 = new Coupler<bool>(zeroSignal, pcSRCOut);
	c2 = new Coupler<regdata>(aluResIn, aluResOut);
	c3 = new Coupler<Instruction*>(instructionIn, instructionOut);
}

MEMStage::~MEMStage(){
	delete mcgen;
	delete spp;
	delete lpp;
	delete dmem;
	delete c1;
	delete c2;
	delete c3;
}

void MEMStage::clock(ClockEdge edge){
	dmem->clock(edge);
}
