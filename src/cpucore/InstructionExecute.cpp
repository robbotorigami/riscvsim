/*
 * InstructionExecute.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: cyborg9
 */

#include "cpucore/InstructionExecute.h"
#include "cpucore/Analytics.h"


EXStage::EXStage(
		Signal<pcval_t>& pcIn,
		Signal<regdata>& readData1In,
		Signal<regdata>& readData2In,
		Signal<regdata>& immediateIn,
		Signal<Instruction*>& instructionIn,
		Signal<Instruction*>& instructionEXMEMIn,
		Signal<Instruction*>& instructionMEMWBIn,
		Signal<regdata>& writeDataEXMEMIn,
		Signal<regdata>& writeDataMEMWBIn,
		Signal<Instruction*>& instructionOut,
		Signal<pcval_t>& pcOut,
		Signal<bool>& zeroSignalOut,
		Signal<regdata>& aluResOut,
		Signal<regdata>& writeData
	)
:pcIn(pcIn), readData1In(readData1In), readData2In(readData2In),
 immediateIn(immediateIn), instructionIn(instructionIn),
 instructionEXMEMIn(instructionEXMEMIn), instructionMEMWBIn(instructionMEMWBIn),
 writeDataEXMEMIn(writeDataEXMEMIn), writeDataMEMWBIn(writeDataMEMWBIn),
 instructionOut(instructionOut),
 pcOut(pcOut), zeroSignalOut(zeroSignalOut), aluResOut(aluResOut), writeData(writeData)
{
	c1 = new Converter<regdata, pcval_t>(immediateIn, immedInConv);
	c2 = new Converter<regdata, pcval_t>(freadData1, readDataInConv);
	c3 = new Converter<pcval_t, regdata>(pcIn, pcInConv);
	cu1 = new Coupler<regdata>(freadData2, writeData);
	cu2 = new Coupler<Instruction*>(instructionIn, instructionOut);
	asGen = new ArgumentSelectionGenerator(instructionIn, aluSrc1, aluSrc2, pcSrc);
	pcSelector = new Mux<pcval_t>(pcIn, readDataInConv, pcSrc, pcArg1);
	ad = new Adder<pcval_t>(pcArg1, immedInConv, pcOut);

	aluarg1Selector = new Mux<regdata>(freadData1, pcInConv, aluSrc1, aluArg1);
	aluarg2Selector = new Mux<regdata>(freadData2, immediateIn, aluSrc2, aluArg2);
	alu = new ALU(instructionIn, aluArg1, aluArg2, aluResOut, zeroSignalOut);

	fm = new ForwardingModule(instructionEXMEMIn, instructionMEMWBIn, instructionIn, fmsig1, fmsig2);
	fmux1 = new ForwardingMux(readData1In, writeDataEXMEMIn, writeDataMEMWBIn, fmsig1, freadData1);
	fmux2 = new ForwardingMux(readData2In, writeDataEXMEMIn, writeDataMEMWBIn, fmsig2, freadData2);

	cu3 = new Coupler<uint8_t>(fmsig1, Analytics::forwarded1);
	cu4 = new Coupler<uint8_t>(fmsig2, Analytics::forwarded2);
}

EXStage::~EXStage(){
	delete asGen;
	delete pcSelector;
	delete ad;
	delete aluarg1Selector;
	delete aluarg2Selector;
	delete alu;

	delete fm;
	delete fmux1;
	delete fmux2;

	delete c1;
	delete c2;
	delete c3;
	delete cu1;
	delete cu2;
	delete cu3;
	delete cu4;
}

void EXStage::clock(ClockEdge edge){

}
