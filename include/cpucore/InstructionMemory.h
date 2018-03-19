/*
 * InstructionMemory.h
 *
 *  Created on: Mar 19, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_INSTRUCTIONMEMORY_H_
#define INCLUDE_CPUCORE_INSTRUCTIONMEMORY_H_
#include "cpucore/Signals.h"
#include "instruction/InstructionSignals.h"
#include "cpucore/cputypes.h"
#include "cpucore/Memory.h"
#include "instruction/0_Instructions.h"

/*!
 * \brief Object to hold the execution stage
 */
class MEMStage: public ClockableObject{
public:
	MEMStage(
		Memory& mem,
		Signal<Instruction*>& instructionIn,
		Signal<bool>& zeroSignal,
		Signal<regdata>& aluResIn,
		Signal<regdata>& writeDataIn,
		Signal<Instruction*>& instructionOut,
		Signal<regdata>& aluResOut,
		Signal<regdata>& readDataOut,
		Signal<bool>& pcSRCOut
	);
	~MEMStage();

	void clock(ClockEdge edge);
private:
	/////////// INTERNAL ///////////////
	DataMemory* dmem;
	MemoryControlGenerator* mcgen;
	StorePreprocessor* spp;
	LoadPostprocessor* lpp;
	Coupler<bool>* c1;
	Coupler<regdata>* c2;
	Coupler<Instruction*>* c3;

	Signal<bool> memWrite;
	Signal<bool> memRead;
	Signal<BitCount_t> bitcount;
	Signal<regdata> processedSD;
	Signal<regdata> unprocessedLD;

	/////////// EXTERNAL ///////////////
	Signal<Instruction*>& instructionIn;
	Signal<bool>& zeroSignal;
	Signal<regdata>& aluResIn;
	Signal<regdata>& writeDataIn;
	Signal<Instruction*>& instructionOut;
	Signal<regdata>& aluResOut;
	Signal<regdata>& readDataOut;
	Signal<bool>& pcSRCOut;
};




#endif /* INCLUDE_CPUCORE_INSTRUCTIONMEMORY_H_ */
