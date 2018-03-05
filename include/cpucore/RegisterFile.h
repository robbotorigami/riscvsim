/*
 * registerFile.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_REGISTERFILE_H_
#define INCLUDE_CPUCORE_REGISTERFILE_H_
#include "cpucore/Signals.h"
#include <vector>
#include <cstdlib>

typedef size_t regaddress;
typedef uint64_t regdata;

class registerFile{
public:
	/*!
	 * \brief Initializes register file
	 * \param readRegister1 the first register address to be read from
	 * \param readRegister2 the second register address to be read from
	 * \param writeRegister the register to be written to
	 * \param writeData the data to be written
	 * \param readData1 the data in the first read register
	 * \param readData2 the data in the second read register
	 * \param regWrite control signal for whether or not to write to the register
	 */
	registerFile(
	Signal<regaddress>& readRegister1,
	Signal<regaddress>& readRegister2,
	Signal<regaddress>& writeRegister,
	Signal<regdata>&    writeData,
	Signal<regdata>&	readData1,
	Signal<regdata>&	readData2,
	Signal<bool>&		regWrite,
	);

private:
	//! Vector containing the values of the registers
	std::vector<regdata> registers;
};



#endif /* INCLUDE_CPUCORE_REGISTERFILE_H_ */
