/*
 * test_instructionfetch.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: cyborg9
 */

#include "cpucore/InstructionFetch.h"
#include "test/catch.hpp"

TEST_CASE("Test Instruction Fetch", "[cpucore][IF]"){
	Memory mem;
	std::vector<inscode> data = {1,2,3,4,5,6,7,8,9,0};
	mem.buildFromVector(data);
	Signal<pcval_t> pcALU;
	Signal<bool> PCSrc;
	Signal<pcval_t> pcOut;
	Signal<inscode> instructionOut;

	IFStage ifs(mem, pcALU, PCSrc, pcOut, instructionOut);

	SECTION("No branches"){
		pcALU = 0;
		PCSrc = false;

		size_t j = 0;
		std::vector<inscode> check = {1,2,3,4,5,6,7,8,9};
		for(auto i : check){
			CAPTURE(j);
			REQUIRE(pcOut == j);
			REQUIRE(instructionOut == i);
			ifs.clock(RISING);
			j+=4;
		}
	}

	SECTION("Revert to zero"){
		for(size_t i = 0; i < 10; i++){
			pcALU = 0;
			PCSrc = false;

			size_t j = 0;
			std::vector<inscode> check = {1,2,3,4};
			for(auto i : check){
				CAPTURE(j);
				REQUIRE(pcOut == j);
				REQUIRE(instructionOut == i);
				ifs.clock(RISING);
				j+=4;
			}
			pcALU = 0;
			PCSrc = true;
			ifs.clock(RISING);
		}
	}

}
