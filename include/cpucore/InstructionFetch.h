/*
 * InstructionFetch.h
 *
 *  Created on: Mar 16, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_INSTRUCTIONFETCH_H_
#define INCLUDE_CPUCORE_INSTRUCTIONFETCH_H_
#include <instruction/0_Instructions.h>
#include <cstdint>
#include "cpucore/Signals.h"
#include "cpucore/cputypes.h"
#include "cpucore/Memory.h"


/*!
 * \brief Object to hold the instruction fetch stage
 */
class IFStage: public ClockableObject{
public:
	IFStage(Memory& mem, Signal<pcval_t>& pcALU, Signal<bool>& PCSrc,
			Signal<pcval_t>& pcOut, Signal<inscode>& instructionOut);
	~IFStage();

	void clock(ClockEdge edge);
private:
	/////////// INTERNAL //////////////
	Register<pcval_t>* ppc;
	//! The program counter
	Register<pcval_t>* pc;
	//! Instruction Interface to memory
	InstructionMemory* im;
	//! Adder to compute the next program counter value
	Adder<pcval_t>* pcIncrementer;
	//! Mux to select value for the program counter
	Mux<pcval_t>* pcMux;
	//! The next value to store in the program counter
	Signal<pcval_t> pcIn;
	//! The current value of the program counter
	Signal<pcval_t> pcVal;
	//! The incremented value of the program counter
	Signal<pcval_t> pcIncrement;
	//! The constant value to increment the program counter
	Signal<pcval_t> inssize;
	//! The current instruction to be ran
	Signal<inscode> instruction;
	//! Coupler for internal and external signals
	Coupler<pcval_t>* c1;
	//! Coupler for internal and external signals
	Coupler<inscode>* c2;

	Signal<pcval_t> pcIntermed;

	/////////// EXTERNAL ///////////////
	//! The memory
	Memory& mem;
	//! PC value computed from ALU
	Signal<pcval_t>& pcALU;
	//! Selection to either branch or step by 4
	Signal<bool>& PCSrc;
	//! Program counter value
	Signal<pcval_t>& pcOut;
	//! Current instruction
	Signal<inscode>& instructionOut;

};



#endif /* INCLUDE_CPUCORE_INSTRUCTIONFETCH_H_ */
