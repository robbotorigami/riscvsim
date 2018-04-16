/*
 * Analytics.cpp
 *
 *  Created on: Apr 16, 2018
 *      Author: cyborg9
 */
#include "cpucore/Analytics.h"
#include <sstream>

Signal<bool> Analytics::stall;
Signal<bool> Analytics::flush;
Signal<uint8_t> Analytics::forwarded1;
Signal<uint8_t> Analytics::forwarded2;

size_t Analytics::cycles_stalled = 0;
size_t Analytics::times_flushed = 0;
size_t Analytics::cycles_forwarded = 0;

void Analytics::processInformation(){
	std::stringstream ss;
	ss << "Stall: " << stall << ", Flush: " << flush << ", arg1 is ";
	switch(forwarded1){
	case 1:
		ss << "Forwarded from EXMEM";
		break;
	case 2:
		ss << "Forwarded from MEMWB";
		break;
	default:
		ss << "Not forwarded";
	}
	ss << ", arg2 is ";
	switch(forwarded2){
	case 1:
		ss << "Forwarded from EXMEM";
		break;
	case 2:
		ss << "Forwarded from MEMWB";
		break;
	default:
		ss << "Not forwarded";
	}
	INFORMATION(ss.str());
	if(stall){
		cycles_stalled++;
	}

	if(flush){
		times_flushed++;
	}

	if(forwarded1){
		cycles_forwarded += forwarded1;
	}

	if(forwarded2){
		cycles_forwarded += forwarded2;
	}
}

void Analytics::printSummary(){
	std::cout << "Cycles stalled for Load: " << cycles_stalled << std::endl;
	std::cout << "Times pipline flushed (failed branch predict): " << times_flushed << std::endl;
	std::cout << "Cycles saved by forwarding ~ " << cycles_forwarded << std::endl;
}
