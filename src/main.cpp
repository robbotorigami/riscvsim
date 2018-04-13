/*
 * main.cpp
 *
 *  Created on: Mar 2, 2018
 *      Author: cyborg9
 */
#include <iostream>
#include "cpucore/RISCVCpu.h"

using namespace std;
int main(){
	Memory mem;
	mem.buildFromImage("resource/ins_assembly_test.img");
	cout << "\n\n\n\n############################## CYCLE #" << 0 << " ############################################" << endl;
	RISCVCpu cpu(mem);

	for (int cycle = 1; cycle < 100000; cycle++){
		cout << "\n\n\n\n############################## CYCLE #" << cycle << " ############################################" << endl;
		cpu.cycleSystem();
	}

	return 0;
}


