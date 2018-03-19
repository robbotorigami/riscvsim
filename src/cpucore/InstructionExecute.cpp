/*
 * InstructionExecute.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: cyborg9
 */

#include "cpucore/InstructionExecute.h"


EXStage::EXStage(
		Signal<pcval_t>& pcIn,
		Signal<regdata>& readData1In,
		Signal<regdata>& readData2In,
		Signal<regdata>& immediateIn,
		Signal<Instruction*>& instructionIn,
		Signal<pcval_t>& pcOut,
		Signal<bool>& zeroSignalOut,
		Signal<regdata>& aluResOut,
		Signal<regdata>& writeData
	)
:pcIn(pcIn), readData1In(readData1In), readData2In(readData2In),
 immediateIn(immediateIn), instructionIn(instructionIn),
 pcOut(pcOut), zeroSignalOut(zeroSignalOut), aluResOut(aluResOut), writeData(writeData)
{
	c1 = new Converter<regdata, pcval_t>(immediateIn, immedInConv);
	c2 = new Converter<regdata, pcval_t>(readData1In, readDataInConv);
	c3 = new Converter<pcval_t, regdata>(pcIn, pcInConv);
	cu1 = new Coupler<regdata>(readData2In, writeData);
	asGen = new ArgumentSelectionGenerator(instructionIn, aluSrc1, aluSrc2, pcSrc);
	pcSelector = new Mux<pcval_t>(pcIn, readDataInConv, pcSrc, pcArg1);
	ad = new Adder<pcval_t>(pcArg1, immedInConv, pcOut);

	aluarg1Selector = new Mux<regdata>(readData1In, pcInConv, aluSrc1, aluArg1);
	aluarg2Selector = new Mux<regdata>(readData2In, immediateIn, aluSrc2, aluArg2);
	alu = new ALU(instructionIn, aluArg1, aluArg2, aluResOut, zeroSignalOut);
}

EXStage::~EXStage(){
	delete asGen;
	delete pcSelector;
	delete ad;
	delete aluarg1Selector;
	delete aluarg2Selector;
	delete alu;

	delete c1;
	delete c2;
	delete c3;
	delete cu1;
}

void EXStage::clock(ClockEdge edge){

}
