/*
 * InstructionSignals.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#include "instruction/InstructionSignals.h"
#include "config.h"

InstructionParser::InstructionParser(Signal<inscode>& inscodeIn, Signal<Instruction*>& instructionOut)
:inscodeIn(inscodeIn), instructionOut(instructionOut)
{
	inscodeIn.registerDriven(this);
}

InstructionParser::~InstructionParser(){
	inscodeIn.unregisterDriven(this);
}

void InstructionParser::computeSignals(){
	instructionOut = InstructionFactory::parseInstruction(inscodeIn);
	INFORMATION("Next Instuction: " << static_cast<Instruction*>(instructionOut)->asString());
}



ImmediateGenerator::ImmediateGenerator(Signal<Instruction*>& instructionIn, Signal<regdata>& immediateOut)
:instructionIn(instructionIn), immediateOut(immediateOut)
{
	instructionIn.registerDriven(this);
}
ImmediateGenerator::~ImmediateGenerator(){
	instructionIn.unregisterDriven(this);
}

void ImmediateGenerator::computeSignals(){
	immediateOut = static_cast<Instruction*>(instructionIn)->getImmediate();
}



ReadRegisterGenerator::ReadRegisterGenerator(Signal<Instruction*>& instructionIn,
		Signal<regaddress>& readreg1, Signal<regaddress>& readreg2)
:instructionIn(instructionIn), readreg1(readreg1), readreg2(readreg2)
{
	instructionIn.registerDriven(this);
}

ReadRegisterGenerator::~ReadRegisterGenerator(){
	instructionIn.unregisterDriven(this);
}

void ReadRegisterGenerator::computeSignals(){
	readreg1 = static_cast<Instruction*>(instructionIn)->getRS1();
	readreg2 = static_cast<Instruction*>(instructionIn)->getRS2();
}



ALU::ALU(Signal<Instruction*>& instructionIn, Signal<regdata>& arg1, Signal<regdata>& arg2,
		Signal<regdata>& output, Signal<bool>& zeroSignal)
:instructionIn(instructionIn), arg1(arg1), arg2(arg2), output(output), zeroSignal(zeroSignal)
{
	instructionIn.registerDriven(this);
	arg1.registerDriven(this);
	arg2.registerDriven(this);
}

ALU::~ALU(){
	instructionIn.unregisterDriven(this);
	arg1.unregisterDriven(this);
	arg2.unregisterDriven(this);
}

void ALU::computeSignals(){
	output = static_cast<Instruction*>(instructionIn)->getALUResult(arg1, arg2);
	zeroSignal = static_cast<Instruction*>(instructionIn)->getZeroSignal(arg1, arg2);
}


ArgumentSelectionGenerator::ArgumentSelectionGenerator(Signal<Instruction*>& instructionIn,
		Signal<bool>& arg1SelOut, Signal<bool>& arg2SelOut, Signal<bool>& pcSrcSel)
:instructionIn(instructionIn), arg1SelOut(arg1SelOut), arg2SelOut(arg2SelOut), pcSrcSel(pcSrcSel)
{
	instructionIn.registerDriven(this);
}

ArgumentSelectionGenerator::~ArgumentSelectionGenerator(){
	instructionIn.unregisterDriven(this);
}

void ArgumentSelectionGenerator::computeSignals(){
	arg1SelOut = static_cast<Instruction*>(instructionIn)->getALUSrc1();
	arg2SelOut = static_cast<Instruction*>(instructionIn)->getALUSrc2();
	pcSrcSel = static_cast<Instruction*>(instructionIn)->getName() == "JALR";
}

//////////////MEM///////////////


MemoryControlGenerator::MemoryControlGenerator(Signal<Instruction*>& instructionIn,Signal<bool>& memRead,
		Signal<bool>& memWrite, Signal<BitCount_t>& bitcount)
:instructionIn(instructionIn), memRead(memRead), memWrite(memWrite), bitcount(bitcount)
{
	instructionIn.registerDriven(this);
}
MemoryControlGenerator::~MemoryControlGenerator(){
	instructionIn.unregisterDriven(this);
}

void MemoryControlGenerator::computeSignals(){
	memRead = static_cast<Instruction*>(instructionIn)->getMemReadSignal();
	memWrite = static_cast<Instruction*>(instructionIn)->getMemWriteSignal();
	bitcount = static_cast<Instruction*>(instructionIn)->getMemoryType();
}

StorePreprocessor::StorePreprocessor(Signal<Instruction*>& instructionIn,
		Signal<regdata>& input, Signal<regdata>& output)
:instructionIn(instructionIn), input(input), output(output)
{
	instructionIn.registerDriven(this);
	input.registerDriven(this);
}
StorePreprocessor::~StorePreprocessor(){
	instructionIn.unregisterDriven(this);
	input.unregisterDriven(this);
}

void StorePreprocessor::computeSignals(){
	output = static_cast<Instruction*>(instructionIn)->preProcessStore(input);
}

LoadPostprocessor::LoadPostprocessor(Signal<Instruction*>& instructionIn,
		Signal<regdata>& input, Signal<regdata>& output)
:instructionIn(instructionIn), input(input), output(output)
{
	instructionIn.registerDriven(this);
	input.registerDriven(this);
}
LoadPostprocessor::~LoadPostprocessor(){
	instructionIn.unregisterDriven(this);
	input.unregisterDriven(this);
}

void LoadPostprocessor::computeSignals(){
	output = static_cast<Instruction*>(instructionIn)->postProcessLoad(input);
}


///////////////Write back////////////////

WritebackGenerator::WritebackGenerator(Signal<Instruction*>& instructionIn,
		Signal<bool>& regWriteOut, Signal<bool>& memtoReg, Signal<regaddress>& rdOut)
:instructionIn(instructionIn),
 regWriteOut(regWriteOut),
 memtoReg(memtoReg),
 rdOut(rdOut)
{
	instructionIn.registerDriven(this);
}
WritebackGenerator::~WritebackGenerator(){
	instructionIn.unregisterDriven(this);
}

void WritebackGenerator::computeSignals(){
	regWriteOut = static_cast<Instruction*>(instructionIn)->getRegWriteSignal();
	memtoReg = static_cast<Instruction*>(instructionIn)->getMemtoRegSignal();
	rdOut = static_cast<Instruction*>(instructionIn)->getRD();
}


InstructionSink::InstructionSink(Signal<Instruction*>& instructionIn)
{
	insReg = new Register<Instruction*>(instructionIn, insFinal);
}
InstructionSink::~InstructionSink(){
	delete insReg;
}

void InstructionSink::clock(ClockEdge edge){
	insReg->clock(edge);
	if(static_cast<Instruction*>(insFinal) != nullptr){
		delete static_cast<Instruction*>(insFinal);
	}
}
