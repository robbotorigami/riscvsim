/*
 * riscvcpu.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_RISCVCPU_H_
#define INCLUDE_CPUCORE_RISCVCPU_H_
#include <cstdint>

/*!
 * \brief Main container for the CPU
 */
class RISCVCpu{
public:
	RISCVCpu();
private:
	//! The program counter for the processor
	uint64_t pc;
};



#endif /* INCLUDE_CPUCORE_RISCVCPU_H_ */
