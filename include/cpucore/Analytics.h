/*
 * Analytics.h
 *
 *  Created on: Apr 16, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_ANALYTICS_H_
#define INCLUDE_CPUCORE_ANALYTICS_H_
#include "cpucore/cputypes.h"
#include "cpucore/Signals.h"
#include "config.h"

struct Analytics{
	static Signal<bool> stall;
	static Signal<bool> flush;
	static Signal<uint8_t> forwarded1;
	static Signal<uint8_t> forwarded2;

	static size_t cycles_stalled;
	static size_t times_flushed;
	static size_t cycles_forwarded;

	static void processInformation();

	static void printSummary();
};



#endif /* INCLUDE_CPUCORE_ANALYTICS_H_ */
