/*
 * RISCVCpu.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: cyborg9
 */
#include "cpucore/RISCVCpu.h"
#include "cpucore/Analytics.h"




RISCVCpu::RISCVCpu(Memory& mem)
:mem(mem)
{
	wbs = new WBStage(memwbr.instructionOut, memwbr.readDataOut, memwbr.aluResOut,
			dataWritebackWBID, regWritebackWBID, regWriteWBID);
	mems = new MEMStage(mem, exmemr.instructionOut, exmemr.zeroSignalOut, exmemr.aluResOut,
			exmemr.writeDataOut,
			memwbr.instructionIn, memwbr.aluResIn, memwbr.readDataIn, pcSRCMEMIF, stall);
	exs = new EXStage(idexr.pcvalOut, idexr.readData1Out, idexr.readData2Out, idexr.immediateOut,
			idexr.instructionOut, exmemr.instructionOut, memwbr.instructionOut, exmemr.aluResOut,
			dataWritebackWBID, exmemr.instructionIn,
			exmemr.pcvalIn, exmemr.zeroSignalIn, exmemr.aluResIn, exmemr.writeDataIn);
	ids = new IDStage(ifidr.pcvalOut, ifidr.instructionOut,
			regWritebackWBID, dataWritebackWBID, regWriteWBID,
			idexr.instructionIn, idexr.pcvalIn, idexr.readData1In, idexr.readData2In, idexr.immediateIn);
	ifs = new IFStage(mem, pcMEMIF, pcSRCMEMIF, ifidr.pcvalIn, ifidr.instructionIn, stall);

	c1 = new Coupler<pcval_t>(exmemr.pcvalOut, pcMEMIF);

	cu1 = new Coupler<bool>(exmemr.zeroSignalOut, ifidr.flush);
	cu2 = new Coupler<bool>(exmemr.zeroSignalOut, idexr.flush);

	cu3 = new Coupler<bool>(stall, ifidr.stall);
	cu4 = new Coupler<bool>(stall, idexr.stall);
	cu5 = new Coupler<bool>(stall, exmemr.stall);

	cu6 = new Coupler<bool>(stall, Analytics::stall);
	cu7 = new Coupler<bool>(exmemr.zeroSignalOut, Analytics::flush);
}

RISCVCpu::~RISCVCpu(){
	delete ifs;
	delete ids;
	delete exs;
	delete mems;
	delete wbs;
	delete c1;
	delete cu1;
	delete cu2;
	delete cu3;
	delete cu4;
	delete cu5;
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
