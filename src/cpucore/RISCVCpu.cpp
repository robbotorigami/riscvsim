/*
 * RISCVCpu.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: cyborg9
 */
#include "cpucore/RISCVCpu.h"




RISCVCpu::RISCVCpu(Memory& mem)
:mem(mem)
{
	wbs = new WBStage(memwbr.instructionOut, memwbr.readDataOut, memwbr.aluResOut,
			dataWritebackWBID, regWritebackWBID, regWriteWBID);
	mems = new MEMStage(mem, exmemr.instructionOut, exmemr.zeroSignalOut, exmemr.aluResOut,
			exmemr.writeDataOut,
			memwbr.instructionIn, memwbr.aluResIn, memwbr.readDataIn, pcSRCMEMIF);
	exs = new EXStage(idexr.pcvalOut, idexr.readData1Out, idexr.readData2Out, idexr.immediateOut,
			idexr.instructionOut, exmemr.instructionIn,
			exmemr.pcvalIn, exmemr.zeroSignalIn, exmemr.aluResIn, exmemr.writeDataIn);
	ids = new IDStage(ifidr.pcvalOut, ifidr.instructionOut,
			regWritebackWBID, dataWritebackWBID, regWriteWBID,
			idexr.instructionIn, idexr.pcvalIn, idexr.readData1In, idexr.readData2In, idexr.immediateIn);
	ifs = new IFStage(mem, pcMEMIF, pcSRCMEMIF, ifidr.pcvalIn, ifidr.instructionIn);

	c1 = new Coupler<pcval_t>(exmemr.pcvalOut, pcMEMIF);
}

RISCVCpu::~RISCVCpu(){
	delete ifs;
	delete ids;
	delete exs;
	delete mems;
	delete wbs;
	delete c1;
}


void RISCVCpu::cycleSystem(){
	ifs->clock(RISING);
	ifidr.clock(RISING);
	ids->clock(RISING);
	idexr.clock(RISING);
	exs->clock(RISING);
	exmemr.clock(RISING);
	mems->clock(RISING);
	memwbr.clock(RISING);
	wbs->clock(RISING);

	ifs->clock(FALLING);
	ifidr.clock(FALLING);
	ids->clock(FALLING);
	idexr.clock(FALLING);
	exs->clock(FALLING);
	exmemr.clock(FALLING);
	mems->clock(FALLING);
	memwbr.clock(FALLING);
	//wbs->clock(FALLING);
}
