/*
 * registerFile.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_REGISTERFILE_H_
#define INCLUDE_CPUCORE_REGISTERFILE_H_
#include <vector>
#include <cstdint>
#include <cstdlib>
#include "cpucore/Signals.h"
#include "cpucore/cputypes.h"


class RegisterFile: public DrivenObject, public ClockableObject{
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
	RegisterFile(
	Signal<regaddress>& readRegister1,
	Signal<regaddress>& readRegister2,
	Signal<regaddress>& writeRegister,
	Signal<regdata>&    writeData,
	Signal<regdata>&	readData1,
	Signal<regdata>&	readData2,
	Signal<bool>&		regWrite
	);

	~RegisterFile();

	/*!
	 * \brief Computes the output signal from the given inputs
	 */
	void computeSignals();

	/*!
	 * \brief Handles clock signals
	 */
	void clock(ClockEdge edge);

private:
	void printInfo();
	//! Read Register 1 input
	Signal<regaddress>& readRegister1;
	//! Read register 2 input
	Signal<regaddress>& readRegister2;
	//! Write register input
	Signal<regaddress>& writeRegister;
	//! Write data input
	Signal<regdata>&    writeData;
	//! Read data output
	Signal<regdata>&	readData1;
	//! Read data output
	Signal<regdata>&	readData2;
	//! Register write control
	Signal<bool>&		regWrite;

	//! Vector containing the values of the registers
	std::vector<regdata> registers;
};



#endif /* INCLUDE_CPUCORE_REGISTERFILE_H_ */
