/*
 * RegisterFile.cpp
 *
 *  Created on: Mar 5, 2018
 *      Author: cyborg9
 */

#include "cpucore/RegisterFile.h"
#include <sstream>
#include "config.h"

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
	//writeRegister.registerDriven(this);
	//writeData.registerDriven(this);
	//regWrite.registerDriven(this);

	registers.resize(32, 0);
	printInfo();
}

RegisterFile::~RegisterFile(){
	readRegister1.unregisterDriven(this);
	readRegister2.unregisterDriven(this);
}

void RegisterFile::computeSignals(){
	readData1 = registers[static_cast<regaddress>(readRegister1)];
	readData2 = registers[static_cast<regaddress>(readRegister2)];
}

void RegisterFile::clock(ClockEdge edge){
	if(edge == RISING){
		if(regWrite && writeRegister != 0){
			registers[static_cast<regaddress>(writeRegister)] = writeData;
		}
		computeSignals();
		printInfo();
	}
	if(edge == FALLING){
		computeSignals();
	}
}

void RegisterFile::printInfo(){
	std::stringstream ss;
	ss << "Register:   ";
	for(int i = 0; i < 32; i++){
		ss << "x" << i << ", " << registers[i] << "     ";
	}
	INFORMATION(ss.str());
}


