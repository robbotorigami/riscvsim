/*
 * pipelineregisters.h
 *
 *  Created on: Apr 13, 2018
 *      Author: cyborg9
 */

#ifndef PIPELINEREGISTERS_H_
#define PIPELINEREGISTERS_H_
#include "cpucore/Signals.h"

#define FIELD(NAME, TYPE) \
	Register<TYPE> NAME; \
	Signal<TYPE> NAME ##In; \
	Signal<TYPE> NAME ##Out;

#define INITIALIZE(NAME) \
		NAME(NAME##In, NAME##Out)

/*!
 * \brief Data type to hold the values buffered between the IF and ID stages
 */
struct IFIDRegister: public ClockableObject, public DrivenObject{
	IFIDRegister();
	~IFIDRegister();
	void clock(ClockEdge edge);
	void computeSignals();

	Signal<bool> stall;
	Signal<bool> flush;

	//! The program counter value of this instruction
	FIELD(pcval, pcval_t)
	FIELD(instruction, inscode)
};


/*!
 * \brief Data type to hold the values buffered between the ID and EX stages
 */
struct IDEXRegister: public ClockableObject, public DrivenObject{
	IDEXRegister();
	~IDEXRegister();
	void clock(ClockEdge edge);
	void computeSignals();

	Signal<bool> stall;
	Signal<bool> flush;

	//! The program counter value of this instruction
	FIELD(pcval, pcval_t)
	FIELD(instruction, Instruction*)
	FIELD(readData1, regdata)
	FIELD(readData2, regdata)
	FIELD(immediate, regdata)
};


/*!
 * \brief Data type to hold the values buffered between the EX and MEM stages
 */
struct EXMEMRegister: public ClockableObject{
	EXMEMRegister();
	void clock(ClockEdge edge);

	Signal<bool> stall;
	bool stalled;

	//! The program counter value of this instruction
	FIELD(pcval, pcval_t)
	FIELD(instruction, Instruction*)
	FIELD(zeroSignal, bool)
	FIELD(aluRes, regdata)
	FIELD(writeData, regdata)
};

/*!
 * \brief Data type to hold the values buffered between the MEM and WB stages
 */
struct MEMWBRegister: public ClockableObject{
	MEMWBRegister();
	void clock(ClockEdge edge);

	//! The program counter value of this instruction
	FIELD(instruction, Instruction*)
	FIELD(aluRes, regdata)
	FIELD(readData, regdata)
	FIELD(pcSRC, regdata)
};


#endif /* PIPELINEREGISTERS_H_ */
