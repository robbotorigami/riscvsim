/*
 * pipelineregisters.h
 *
 *  Created on: Apr 13, 2018
 *      Author: cyborg9
 */

#ifndef PIPELINEREGISTERS_H_
#define PIPELINEREGISTERS_H_
#include "cpucore/Signals.h"

/*!
 * \brief Data type to hold the values buffered between the IF and ID stages
 */
struct IFIDRegister: public ClockableObject{
	IFIDRegister();
	void clock(ClockEdge edge);

	//! The program counter value of this instruction
	Register<pcval_t> pcval;
	Signal<pcval_t> pcvalIn;
	Signal<pcval_t> pcvalOut;

	Register<inscode> instruction;
	Signal<inscode> instructionIn;
	Signal<inscode> instructionOut;
};


#endif /* PIPELINEREGISTERS_H_ */
