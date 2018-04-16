/*
 * main.cpp
 *
 *  Created on: Mar 2, 2018
 *      Author: cyborg9
 */
#include <iostream>
#include "cpucore/RISCVCpu.h"
#include "cpucore/Analytics.h"

#include "config.h"


std::ofstream fs("output.txt");

using namespace std;
int main(){
	Memory mem;
	mem.buildFromImage("resource/ins_assembly_test.img");
	INFORMATION("\n\n\n\n############################## CYCLE #" << 0 << " ############################################");
	RISCVCpu cpu(mem);

	for (int cycle = 1; cycle < 1000; cycle++){
		INFORMATION("\n\n\n\n############################## CYCLE #" << cycle << " ############################################");
		cpu.cycleSystem();
		Analytics::processInformation();
	}
	Analytics::printSummary();

	return 0;
}


