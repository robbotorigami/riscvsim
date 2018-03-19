/*
 * InstructionFetch.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#include "cpucore/InstructionFetch.h"
#include "config.h"

IFStage::IFStage(Memory& mem, Signal<pcval_t>& pcALU, Signal<bool>& PCSrc,
		Signal<pcval_t>& pcOut, Signal<inscode>& instructionOut)
:mem(mem), pcALU(pcALU), PCSrc(PCSrc), pcOut(pcOut), instructionOut(instructionOut)
{
	pcMux = new Mux<pcval_t>(pcIncrement, pcALU, PCSrc, pcIn);
	ppc = new Register<pcval_t>(pcIn, pcIntermed);
	pc = new Register<pcval_t>(pcIntermed, pcVal);
	inssize = sizeof(pcval_t);
	pcIncrementer = new Adder<pcval_t>(pcVal, inssize, pcIncrement);
	im = new InstructionMemory(mem, pcVal, instruction);

	c1 = new Coupler<pcval_t>(pcVal, pcOut);
	c2 = new Coupler<inscode>(instruction, instructionOut);

	pcIn = 0;
	pcVal = 0;
	INFORMATION("PC: " << static_cast<pcval_t>(pcOut));
}

IFStage::~IFStage(){
	delete pcMux;
	delete pc;
	delete pcIncrementer;
	delete im;
	delete c1;
	delete c2;
}

void IFStage::clock(ClockEdge edge){
	if(edge == FALLING){
		ppc->clock(edge);
	}else{
		pc->clock(edge);
		INFORMATION("PC: " << static_cast<pcval_t>(pcOut));
	}
}
