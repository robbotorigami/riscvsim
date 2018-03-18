/*
 * InstructionSignals.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#include "instruction/InstructionSignals.h"

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



IsLinkGenerator::IsLinkGenerator(Signal<Instruction*>& instructionIn, Signal<bool>& output)
:instructionIn(instructionIn), output(output)
{
	instructionIn.registerDriven(this);
}
IsLinkGenerator::~IsLinkGenerator(){
	instructionIn.unregisterDriven(this);
}

void IsLinkGenerator::computeSignals(){
	std::string name = static_cast<Instruction*>(instructionIn)->getName();
	output = !name.compare(0, 3, "JAL");
}
