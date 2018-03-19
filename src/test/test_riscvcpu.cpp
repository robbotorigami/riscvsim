/*
 * test_riscvcpu.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: cyborg9
 */

#include "test/catch.hpp"
#include "cpucore/RISCVCpu.h"

TEST_CASE("Test Simple Load", "[.][riscv]"){
	Memory mem;
	mem.buildFromImage("resource/ins_assembly_test.img");
	RISCVCpu cpu(mem);
}


