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
#include <cstdint>

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

class ArgumentSelectionGenerator: public DrivenObject{
public:
	ArgumentSelectionGenerator(Signal<Instruction*>& instructionIn,
			Signal<bool>& arg1SelOut, Signal<bool>& arg2SelOut, Signal<bool>& pcSrcSel);
	~ArgumentSelectionGenerator();

	void computeSignals();
private:
	//! Instruction pointer input
	Signal<Instruction*>& instructionIn;
	//! Argument 1 Selection output
	Signal<bool>& arg1SelOut;
	//! Argument 2 Selection output
	Signal<bool>& arg2SelOut;
	//! PC or Register control signal
	Signal<bool>& pcSrcSel;
};

class MemoryControlGenerator: public DrivenObject{
public:
	MemoryControlGenerator(Signal<Instruction*>& instructionIn,Signal<bool>& memRead,
			Signal<bool>& memWrite, Signal<BitCount_t>& bitcount);
	~MemoryControlGenerator();

	void computeSignals();
private:
	//! Instruction pointer input
	Signal<Instruction*>& instructionIn;
	Signal<bool>& memRead;
	Signal<bool>& memWrite;
	Signal<BitCount_t>& bitcount;
};

class StorePreprocessor: public DrivenObject{
public:
	StorePreprocessor(Signal<Instruction*>& instructionIn, Signal<regdata>& input, Signal<regdata>& output);
	~StorePreprocessor();

	void computeSignals();
private:
	Signal<Instruction*>& instructionIn;
	Signal<regdata>& input;
	Signal<regdata>& output;
};

class LoadPostprocessor: public DrivenObject{
public:
	LoadPostprocessor(Signal<Instruction*>& instructionIn, Signal<regdata>& input, Signal<regdata>& output);
	~LoadPostprocessor();

	void computeSignals();
private:
	Signal<Instruction*>& instructionIn;
	Signal<regdata>& input;
	Signal<regdata>& output;
};

class WritebackGenerator: public DrivenObject{
public:
	WritebackGenerator(Signal<Instruction*>& instructionIn,
			Signal<bool>& regWriteOut, Signal<bool>& memtoReg, Signal<regaddress>& rdOut);
	~WritebackGenerator();

	void computeSignals();

private:
	Signal<Instruction*>& instructionIn;
	Signal<bool>& regWriteOut;
	Signal<bool>& memtoReg;
	Signal<regaddress>& rdOut;
};

class InstructionSink: public ClockableObject{
public:
	InstructionSink(Signal<Instruction*>& instructionIn);
	~InstructionSink();

	void clock(ClockEdge edge);

private:
	Register<Instruction*>* insReg;
	Signal<Instruction*> insFinal;
};


class ForwardingModule: public DrivenObject{
public:
	ForwardingModule(Signal<Instruction*>& EXMEMInstruction, Signal<Instruction*>& MEMWBInstruction,
			Signal<Instruction*>& IDEXInstruction, Signal<uint8_t>& selection1, Signal<uint8_t>& selection2);
	~ForwardingModule();

	void computeSignals();

private:
	Signal<Instruction*>& EXMEMInstruction;
	Signal<Instruction*>& MEMWBInstruction;
	Signal<Instruction*>& IDEXInstruction;
	Signal<uint8_t>& selection1;
	Signal<uint8_t>& selection2;
};

class ForwardingMux: public DrivenObject{
public:
	ForwardingMux(Signal<regdata>& IDInput, Signal<regdata>& EXInput, Signal<regdata>& MEMInput,
			Signal<uint8_t>& selection, Signal<regdata>& output);
	~ForwardingMux();

	void computeSignals();

private:
	Signal<regdata>& IDInput;
	Signal<regdata>& EXInput;
	Signal<regdata>& MEMInput;
	Signal<uint8_t>& selection;
	Signal<regdata>& output;
};

#endif /* INCLUDE_INSTRUCTION_INSTRUCTIONSIGNALS_H_ */
