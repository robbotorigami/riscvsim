/*
 * InstructionExecute.h
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_INSTRUCTIONEXECUTE_H_
#define INCLUDE_CPUCORE_INSTRUCTIONEXECUTE_H_
#include <instruction/0_Instructions.h>
#include <cstdint>
#include "cpucore/Signals.h"
#include "instruction/InstructionSignals.h"
#include "cpucore/cputypes.h"

/*!
 * \brief Data type to hold the values buffered between the ID and EX stages
 */
struct EXMEMRegister: public ClockableObject{
	void clock(ClockEdge edge);

	//! The program counter value of this instruction
	Register<pcval_t> pcval;
	Register<Instruction*> instruction;
	Register<regdata> readData1;
	Register<regdata> readData2;
	Register<regdata> immediate;
};

/*!
 * \brief Object to hold the execution stage
 */
class EXStage: public ClockableObject{
public:
	EXStage(
		Signal<pcval_t>& pcIn,
		Signal<regdata>& readData1In,
		Signal<regdata>& readData2In,
		Signal<regdata>& immediateIn,
		Signal<Instruction*>& instructionIn,
		Signal<pcval_t>& pcOut,
		Signal<bool>& zeroSignalOut,
		Signal<regdata>& aluResOut,
		Signal<regdata>& writeData
	);
	~EXStage();

	void clock(ClockEdge edge);
private:
	/////////// INTERNAL ///////////////
	//! The Arithematic Logic Unit
	ALU* alu;
	//! Control Signal Decoder
	ArgumentSelectionGenerator* asGen;
	//! PC incrememnt
	Adder<pcval_t>* ad;
	//! PC input selection
	Mux<pcval_t>* pcSelector;
	//! ALU arg1 selection
	Mux<regdata>* aluarg1Selector;
	//! ALU arg2 selection
	Mux<regdata>* aluarg2Selector;

	Coupler<regdata>* cu1;

	Converter<regdata, pcval_t>* c1;
	Signal<pcval_t> immedInConv;
	Converter<regdata, pcval_t>* c2;
	Signal<pcval_t> readDataInConv;
	Converter<pcval_t, regdata>* c3;
	Signal<regdata> pcInConv;

	Signal<pcval_t> pcArg1;
	Signal<regdata> aluArg1;
	Signal<regdata> aluArg2;

	Signal<bool> pcSrc;
	Signal<bool> aluSrc1;
	Signal<bool> aluSrc2;

	/////////// EXTERNAL ///////////////
	Signal<pcval_t>& pcIn;
	Signal<regdata>& readData1In;
	Signal<regdata>& readData2In;
	Signal<regdata>& immediateIn;
	Signal<Instruction*>& instructionIn;
	Signal<pcval_t>& pcOut;
	Signal<bool>& zeroSignalOut;
	Signal<regdata>& aluResOut;
	Signal<regdata>& writeData;
};







#endif /* INCLUDE_CPUCORE_INSTRUCTIONEXECUTE_H_ */
