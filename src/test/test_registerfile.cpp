/*
 * test_registerfile.cpp
 *
 *  Created on: Mar 5, 2018
 *      Author: cyborg9
 */


#include "test/catch.hpp"
#include "cpucore/RegisterFile.h"


TEST_CASE("Test That RegisterFile works correctly", "[registerfile][signals]"){
	Signal<regaddress>  readRegister1;
	Signal<regaddress>  readRegister2;
	Signal<regaddress>	writeRegister;
	Signal<regdata>	    writeData;
	Signal<regdata>		readData1;
	Signal<regdata>		readData2;
	Signal<bool>		regWrite;

	RegisterFile rf(readRegister1, readRegister2, writeRegister, writeData,
			readData1, readData2, regWrite);

	SECTION("Test simple write and read"){
		writeRegister = 2;
		writeData = 0xAA;
		regWrite = true;
		rf.clock(RISING);
		readRegister1 = 2;
		readRegister2 = 4;
		REQUIRE(readData1 == 0xAA);
		writeRegister = 4;
		writeData = 0xBB;
		rf.clock(RISING);
		REQUIRE(readData1 == 0xAA);
		REQUIRE(readData2 == 0xBB);
	}

	SECTION("Test that reg zero always returns 0"){
		readRegister1 = 0;
		REQUIRE(readData1 == 0x00);
		writeRegister = 0;
		writeData = 0xAA;
		regWrite = true;
		rf.clock(RISING);
		REQUIRE(readData1 == 0x00);
	}
}

