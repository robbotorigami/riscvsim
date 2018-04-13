/*
 * riscvcpu.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_RISCVCPU_H_
#define INCLUDE_CPUCORE_RISCVCPU_H_
#include <cstdint>
#include "cpucore/InstructionDecode.h"
#include "cpucore/InstructionFetch.h"
#include "cpucore/InstructionExecute.h"
#include "cpucore/InstructionMemory.h"
#include "cpucore/InstructionWriteback.h"
#include "cpucore/PipelineRegisters.h"

/*!
 * \brief Main container for the CPU
 */
class RISCVCpu{
public:
	RISCVCpu(Memory& mem);
	~RISCVCpu();

	void cycleSystem();

private:
	Memory& mem;
	IFStage* ifs;
	IDStage* ids;
	EXStage* exs;
	MEMStage* mems;
	WBStage* wbs;

	IFIDRegister ifidr;
	IDEXRegister idexr;
	EXMEMRegister exmemr;
	MEMWBRegister memwbr;

	Coupler<pcval_t>* c1;

	Signal<pcval_t> pcMEMIF;
	Signal<bool> pcSRCMEMIF;
	Signal<pcval_t> pcIFID;
	Signal<inscode> instructioncodeIFID;
	Signal<regaddress> regWritebackWBID;
	Signal<regdata> dataWritebackWBID;
	Signal<bool> regWriteWBID;
	Signal<Instruction*> instructionIDEX;
	Signal<pcval_t> pcIDEX;
	Signal<regdata> readData1IDEX;
	Signal<regdata> readData2IDEX;
	Signal<regdata> immediateIDEX;
	Signal<pcval_t> pcEXMEM;
	Signal<bool> zeroSignalEXMEM;
	Signal<regdata> aluResultEXMEM;
	Signal<regdata> writeDataEXMEM;
	Signal<Instruction*> instructionEXMEM;
	Signal<Instruction*> instructionMEMWB;
	Signal<regdata> aluResultMEMWB;
	Signal<regdata> readDataMEMWB;
};


#endif /* INCLUDE_CPUCORE_RISCVCPU_H_ */
