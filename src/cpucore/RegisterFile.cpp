/*
 * RegisterFile.cpp
 *
 *  Created on: Mar 5, 2018
 *      Author: cyborg9
 */

#include "cpucore/RegisterFile.h"

RegisterFile::RegisterFile(
	Signal<regaddress>& readRegister1,
	Signal<regaddress>& readRegister2,
	Signal<regaddress>& writeRegister,
	Signal<regdata>&    writeData,
	Signal<regdata>&	readData1,
	Signal<regdata>&	readData2,
	Signal<bool>&		regWrite
	)
:readRegister1(readRegister1),
 readRegister2(readRegister2),
 writeRegister(writeRegister),
 writeData(writeData),
 readData1(readData1),
 readData2(readData2),
 regWrite(regWrite)
{
	readRegister1.registerDriven(this);
	readRegister2.registerDriven(this);
	writeRegister.registerDriven(this);
	writeData.registerDriven(this);
	regWrite.registerDriven(this);

	registers.resize(32, 0);
}

void RegisterFile::computeSignals(){
	if(regWrite.getData()){
		registers[writeRegister.getData()] = writeData.getData();
	}
	readData1.setData(registers[readRegister1.getData()]);
	readData2.setData(registers[readRegister2.getData()]);
}



