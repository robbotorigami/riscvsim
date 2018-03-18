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
	EXStage();
	~EXStage();

	void clock(ClockEdge edge);
private:
	/////////// INTERNAL //////////////

	/////////// EXTERNAL ///////////////

};







#endif /* INCLUDE_CPUCORE_INSTRUCTIONEXECUTE_H_ */
