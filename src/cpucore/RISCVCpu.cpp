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
	wbs = new WBStage(instructionMEMWB, readDataMEMWB, aluResultMEMWB,
			dataWritebackWBID, regWritebackWBID, regWriteWBID);
	mems = new MEMStage(mem, instructionIDEX, zeroSignalEXMEM, aluResultEXMEM, writeDataEXMEM,
			instructionMEMWB, aluResultMEMWB, readDataMEMWB, pcSRCMEMIF);
	exs = new EXStage(pcIDEX, readData1IDEX, readData2IDEX, immediateIDEX, instructionIDEX,
			pcEXMEM, zeroSignalEXMEM, aluResultEXMEM, writeDataEXMEM);
	ids = new IDStage(pcIFID, instructioncodeIFID,
			regWritebackWBID, dataWritebackWBID, regWriteWBID,
			instructionIDEX, pcIDEX, readData1IDEX, readData2IDEX, immediateIDEX);
	ifs = new IFStage(mem, pcMEMIF, pcSRCMEMIF, pcIFID, instructioncodeIFID);

	c1 = new Coupler<pcval_t>(pcEXMEM, pcMEMIF);
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
	ifs->clock(FALLING);
	mems->clock(RISING);
	ids->clock(RISING);
	ifs->clock(RISING);
}
