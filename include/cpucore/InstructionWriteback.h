/*
 * InstructionWriteback.h
 *
 *  Created on: Mar 19, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_INSTRUCTIONWRITEBACK_H_
#define INCLUDE_CPUCORE_INSTRUCTIONWRITEBACK_H_
#include "cpucore/Signals.h"
#include "instruction/InstructionSignals.h"
#include "cpucore/cputypes.h"
#include "cpucore/Memory.h"
#include "instruction/0_Instructions.h"

/*!
 * \brief Object to hold the execution stage
 */
class WBStage: public ClockableObject{
public:
	WBStage(
	Signal<Instruction*>& instructionIn,
	Signal<regdata>& readdataIn,
	Signal<regdata>& aluResIn,
	Signal<regdata>& dataWritebackOut,
	Signal<regaddress>& regWritebackOut,
	Signal<bool>& regWriteOut
	);
	~WBStage();

	void clock(ClockEdge edge);
private:
	/////////// INTERNAL ///////////////
	Mux<regdata>* memRegSelector;
	WritebackGenerator* wbgen;
	InstructionSink* isink;

	Signal<bool> memToReg;

	/////////// EXTERNAL ///////////////
	Signal<Instruction*>& instructionIn;
	Signal<regdata>& readdataIn;
	Signal<regdata>& aluResIn;
	Signal<regdata>& dataWritebackOut;
	Signal<regaddress>& regWritebackOut;
	Signal<bool>& regWriteOut;
};




#endif /* INCLUDE_CPUCORE_INSTRUCTIONWRITEBACK_H_ */
