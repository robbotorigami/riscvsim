/*
 * test_memory.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: cyborg9
 */

#include "test/catch.hpp"
#include "cpucore/Memory.h"
#include <cstdio>
#include <fstream>

TEST_CASE("Test that memory can load images correctly", "[memory][load]"){
	Memory mem;
	uint32_t tsize = 10, dsize = 10, ssize = 10;
	std::ofstream fs("test.img", std::ios::binary);
	fs.write(reinterpret_cast<char*>(&tsize), sizeof(tsize));
	fs.write(reinterpret_cast<char*>(&dsize), sizeof(dsize));
	fs.write(reinterpret_cast<char*>(&ssize), sizeof(ssize));
	std::vector<uint8_t> text = {0,1,2,3,4,5,6,7,8,9};
	std::vector<uint8_t> data = {1,2,3,4,5,6,7,8,9,10};
	std::vector<uint8_t> stack = {2,3,4,5,6,7,8,9,10,11};
	fs.write(reinterpret_cast<char*>(&text[0]), text.size());
	fs.write(reinterpret_cast<char*>(&data[0]), data.size());
	fs.write(reinterpret_cast<char*>(&stack[0]), stack.size());
	fs.close();

	mem.buildFromImage("test.img");

	std::vector<uint8_t> check = {0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,10,2,3,4,5,6,7,8,9,10,11};
	size_t addr = 0;
	for(auto i : check){
		CAPTURE(addr);
		REQUIRE(mem.read<uint8_t>(addr) == i);
		addr++;
	}

	remove("test.img");
}

TEST_CASE("Test that memory can be loaded from vector", "[memory][load]"){
	Memory mem;
	std::vector<uint8_t> data = {1,2,3,4,5,6,7,8,9};
	mem.buildFromVector(data);
	memaddress addr = 0;
	for(auto i : data){
		CAPTURE(addr);
		REQUIRE(mem.read<uint8_t>(addr) == i);
		addr++;
	}
}

TEST_CASE("Test that instruction memory works properly", "[memory][instructionmem]"){
	Memory mem;
	std::vector<uint8_t> data = {1,0,0,0, 2,0,0,0, 3,0,0,0, 4,0,0,0};
	mem.buildFromVector(data);
	Signal<pcval_t> pc;
	Signal<inscode> instruction;
	InstructionMemory im(mem, pc, instruction);
	pc = 0;
	REQUIRE(instruction == 1);
	pc = pc + 4;
	REQUIRE(instruction == 2);
	pc = pc + 4;
	REQUIRE(instruction == 3);
	pc = pc + 4;
	REQUIRE(instruction == 4);
}


