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
		writeRegister.setData(2);
		writeData.setData(0xAA);
		regWrite.setData(true);
		readRegister1.setData(2);
		readRegister2.setData(4);
		REQUIRE(readData1.getData() == 0xAA);
		writeRegister.setData(4);
		writeData.setData(0xBB);
		REQUIRE(readData1.getData() == 0xAA);
		REQUIRE(readData2.getData() == 0xBB);
	}
}

