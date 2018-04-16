/*
 * InstructionSignals.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#include "instruction/InstructionSignals.h"
#include "instruction/IInstructions.h"
#include "config.h"

InstructionParser::InstructionParser(Signal<inscode>& inscodeIn, Signal<Instruction*>& instructionOut)
:inscodeIn(inscodeIn), instructionOut(instructionOut)
{
	inscodeIn.registerDriven(this);
	instructionOut = InstructionFactory::parseInstruction(19);
}

InstructionParser::~InstructionParser(){
	inscodeIn.unregisterDriven(this);
}

void InstructionParser::computeSignals(){
	instructionOut = InstructionFactory::parseInstruction(inscodeIn);
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
	if(edge == FALLING){
		if(static_cast<Instruction*>(insFinal) != nullptr){
			delete static_cast<Instruction*>(insFinal);
		}
	}
}

ForwardingModule::ForwardingModule(Signal<Instruction*>& EXMEMInstruction, Signal<Instruction*>& MEMWBInstruction,
		Signal<Instruction*>& IDEXInstruction, Signal<uint8_t>& selection1, Signal<uint8_t>& selection2)
:EXMEMInstruction(EXMEMInstruction), MEMWBInstruction(MEMWBInstruction),
 IDEXInstruction(IDEXInstruction), selection1(selection1), selection2(selection2)
{
	IDEXInstruction.registerDriven(this);
	EXMEMInstruction.registerDriven(this);
	MEMWBInstruction.registerDriven(this);
}

ForwardingModule::~ForwardingModule(){
	IDEXInstruction.unregisterDriven(this);
	EXMEMInstruction.unregisterDriven(this);
	MEMWBInstruction.unregisterDriven(this);
}

void ForwardingModule::computeSignals(){
	regaddress rs1 = static_cast<Instruction*>(IDEXInstruction)->getRS1();
	regaddress rs2 = static_cast<Instruction*>(IDEXInstruction)->getRS2();
	regaddress rd1 = static_cast<Instruction*>(EXMEMInstruction)->getRD();
	bool wb1 = static_cast<Instruction*>(EXMEMInstruction)->getRegWriteSignal();
	regaddress rd2 = static_cast<Instruction*>(MEMWBInstruction)->getRD();
	bool wb2 = static_cast<Instruction*>(MEMWBInstruction)->getRegWriteSignal();
	if(rd1 != 0 && wb1 && rd1 == rs1){
		selection1 = 1;
	}else if(rd2 != 0 && wb2 && rd2 == rs1){
		selection1 = 2;
	}else{
		selection1 = 0;
	}
	if(rd1 != 0 && wb1 && rd1 == rs2){
		selection2 = 1;
	}else if(rd2 != 0 && wb2 && rd2 == rs2){
		selection2 = 2;
	}else{
		selection2 = 0;
	}
}

ForwardingMux::ForwardingMux(Signal<regdata>& IDInput, Signal<regdata>& EXInput, Signal<regdata>& MEMInput,
		Signal<uint8_t>& selection, Signal<regdata>& output)
:IDInput(IDInput), EXInput(EXInput), MEMInput(MEMInput), selection(selection), output(output)
{
	IDInput.registerDriven(this);
	EXInput.registerDriven(this);
	MEMInput.registerDriven(this);
	selection.registerDriven(this);
}

ForwardingMux::~ForwardingMux(){
	IDInput.unregisterDriven(this);
	EXInput.unregisterDriven(this);
	MEMInput.unregisterDriven(this);
	selection.unregisterDriven(this);
}

void ForwardingMux::computeSignals(){
	if(selection == 0){
		output = static_cast<regdata>(IDInput);
	}else if (selection == 1){
		output = static_cast<regdata>(EXInput);
	}else if (selection == 2){
		output = static_cast<regdata>(MEMInput);
	}
}

