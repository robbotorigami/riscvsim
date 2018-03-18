/*
 * InstructionSignals.h
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_INSTRUCTION_INSTRUCTIONSIGNALS_H_
#define INCLUDE_INSTRUCTION_INSTRUCTIONSIGNALS_H_

#include <instruction/0_Instructions.h>
#include "cpucore/Signals.h"

class InstructionParser: public DrivenObject{
public:
	InstructionParser(Signal<inscode>& inscodeIn, Signal<Instruction*>& instructionOut);
	~InstructionParser();

	void computeSignals();
private:
	//! Instruction code input
	Signal<inscode>& inscodeIn;
	//! Instruction pointer output
	Signal<Instruction*>& instructionOut;
};

class ImmediateGenerator: public DrivenObject{
public:
	ImmediateGenerator(Signal<Instruction*>& instructionIn, Signal<regdata>& immediateOut);
	~ImmediateGenerator();

	void computeSignals();
private:
	//! Instruction pointer input
	Signal<Instruction*>& instructionIn;
	//! Immediate value output
	Signal<regdata>& immediateOut;
};

class ReadRegisterGenerator: public DrivenObject{
public:
	ReadRegisterGenerator(Signal<Instruction*>& instructionIn,
			Signal<regaddress>& readreg1, Signal<regaddress>& readreg2);
	~ReadRegisterGenerator();

	void computeSignals();
private:
	//! Instruction pointer input
	Signal<Instruction*>& instructionIn;
	//! Register read address output
	Signal<regaddress>& readreg1;
	//! Register read address output
	Signal<regaddress>& readreg2;
};

class ALU: public DrivenObject{
public:
	ALU(Signal<Instruction*>& instructionIn, Signal<regdata>& arg1, Signal<regdata>& arg2,
		Signal<regdata>& output, Signal<bool>& zeroSignal);
	~ALU();

	void computeSignals();
private:
	//! Instruction pointer input
	Signal<Instruction*>& instructionIn;
	//! ALU argument 1
	Signal<regdata>& arg1;
	//! ALU argument 2
	Signal<regdata>& arg2;
	//! Output of the ALU
	Signal<regdata>& output;
	//! Zero Signal output
	Signal<bool>& zeroSignal;
};

class IsLinkGenerator: public DrivenObject{
public:
	IsLinkGenerator(Signal<Instruction*>& instructionIn, Signal<bool>& output);
	~IsLinkGenerator();

	void computeSignals();
private:
	//! Instruction pointer input
	Signal<Instruction*>& instructionIn;
	//! Is a Link instruction
	Signal<bool>& output;
};


#endif /* INCLUDE_INSTRUCTION_INSTRUCTIONSIGNALS_H_ */
