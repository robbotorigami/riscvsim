/*
 * cputypes.h
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_CPUTYPES_H_
#define INCLUDE_CPUCORE_CPUTYPES_H_

#include <cstdint>
#include <cstdlib>

typedef uint32_t memaddress;
typedef memaddress pcval_t;

typedef uint32_t inscode;

typedef size_t regaddress;
typedef int64_t regdata;

typedef enum: bool{
	IMMEDIATE = true,
	PROGRAMCOUNTER = true,
	REGISTER = false,
}ALUSrc_t;

typedef enum: uint8_t {
	BIT8 = 8,
	BIT16 = 16,
	BIT32 = 32,
	BIT64 = 64,
}BitCountEnum_t;

typedef uint8_t BitCount_t;


#define EXTEND8(val) \
	(uint64_t)(val & 0xFF) 			| ((val & 0x80) ? 		0xFFFFFFFFFFFFFF00ull : 0x00ull)
#define EXTEND16(val) \
	(uint64_t)(val & 0xFFFF) 		| ((val & 0x8000) ? 	0xFFFFFFFFFFFF0000ull : 0x00ull)
#define EXTEND32(val) \
	(uint64_t)(val & 0xFFFFFFFF) 	| ((val & 0x80000000) ? 0xFFFFFFFF00000000ull : 0x00ull)


#endif /* INCLUDE_CPUCORE_CPUTYPES_H_ */
