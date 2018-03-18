/*
 * cputypes.h
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_CPUTYPES_H_
#define INCLUDE_CPUCORE_CPUTYPES_H_

typedef uint32_t memaddress;
typedef memaddress pcval_t;

typedef uint32_t inscode;

typedef size_t regaddress;
typedef int64_t regdata;

typedef enum{
	IMMEDIATE,
	REGISTER,
}ALUSrc_t;




#endif /* INCLUDE_CPUCORE_CPUTYPES_H_ */
