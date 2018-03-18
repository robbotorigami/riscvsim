/*
 * InstructionDecode.h
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_INSTRUCTIONDECODE_H_
#define INCLUDE_CPUCORE_INSTRUCTIONDECODE_H_
#include <instruction/0_Instructions.h>
#include <cstdint>
#include "cpucore/Signals.h"
#include "instruction/InstructionSignals.h"
#include "cpucore/cputypes.h"
#include "cpucore/RegisterFile.h"

/*!
 * \brief Data type to hold the values buffered between the ID and EX stages
 */
struct IDEXRegister: public ClockableObject{
	void clock(ClockEdge edge);

	//! The program counter value of this instruction
	Register<pcval_t> pcval;
	Register<Instruction*> instruction;
	Register<regdata> readData1;
	Register<regdata> readData2;
	Register<regdata> immediate;
};

/*!
 * \brief Object to hold the instruction decode stage
 */
class IDStage: public ClockableObject{
public:
	IDStage(Signal<pcval_t>& pcIn, Signal<inscode>& inscodeIn,
			Signal<regaddress>& writeRegisterIn, Signal<regdata>& writeDataIn,
			Signal<bool>& regWriteIn,
			Signal<Instruction*>& instructionOut, Signal<pcval_t>& pcOut,
			Signal<regdata>& readData1Out, Signal<regdata>& readData2Out,
			Signal<regdata>& immediateOut);
	~IDStage();

	void clock(ClockEdge edge);
private:
	/////////// INTERNAL //////////////
	//! Register File
	RegisterFile* rf;
	//! Decoder from inscode to instruction object
	InstructionParser* instructionParser;
	//! Generate a full scale immediate from the opcode
	ImmediateGenerator* immedGen;
	//! Generate the register file read signals from the opcode
	ReadRegisterGenerator* rrGen;

	//! Current Instruction
	Signal<Instruction*> instruction;
	//! Read Register 1 Signal
	Signal<regaddress> readReg1;
	//! Read Register 2 Signal
	Signal<regaddress> readReg2;

	//! Output value coupler
	Coupler<pcval_t>* pccoupler;
	//! Output value coupler
	Coupler<Instruction*>* inscoupler;

	/////////// EXTERNAL ///////////////
	//! The program counter input
	Signal<pcval_t>& pcIn;
	//! The instruction code input
	Signal<inscode>& inscodeIn;
	//! The register to be written to
	Signal<regaddress>& writeRegisterIn;
	//! The data to be written
	Signal<regdata>& writeDataIn;
	//! Whether or not to write to the register
	Signal<bool>& regWriteIn;
	//! The instruction value output
	Signal<Instruction*>& instructionOut;
	//! The program counter value output
	Signal<pcval_t>& pcOut;
	//! The data from the first read register
	Signal<regdata>& readData1Out;
	//! The data from the second read register
	Signal<regdata>& readData2Out;
	//! The immediate value output
	Signal<regdata>& immediateOut;
};







#endif /* INCLUDE_CPUCORE_INSTRUCTIONDECODE_H_ */
