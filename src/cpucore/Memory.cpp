/*
 * Memory.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#include "cpucore/Memory.h"
#include <fstream>
#include <cassert>

/*!
 * \brief Constructs memory object with the specified sizes for
 * the different sections
 * \param text the size of the text section
 * \param data the size of the data section
 * \param stack the size of the stack
 */
Memory::Memory()
:data()
{
	dataAddr = 0;
	textAddr = 0;
	stackAddr = 0;
}

/*!
 * \brief Constructs a memory object from the provided filename
 */
void Memory::buildFromImage(std::string filename)
{
	std::ifstream fs(filename, std::ios::binary);
	if(!fs){
		return;
	}
	uint32_t text, data, stack;
	fs.read(reinterpret_cast<char *>(&text), sizeof(text));
	fs.read(reinterpret_cast<char *>(&data), sizeof(data));
	fs.read(reinterpret_cast<char *>(&stack), sizeof(stack));
	textAddr = 0x00000000;
	dataAddr = textAddr + text;
	stackAddr = dataAddr + data + stack;
	this->data.resize(stackAddr+1); //Allocate enough memory
	fs.read(reinterpret_cast<char *>(&this->data[textAddr]), text+data+stack);
}

InstructionMemory::InstructionMemory(Memory& mem, Signal<pcval_t>& address, Signal<inscode>& instruction)
:mem(mem), address(address), instruction(instruction)
{
	address.registerDriven(this);
}

InstructionMemory::~InstructionMemory(){
	address.unregisterDriven(this);
}

//! Reads the value from memory and return the value at the address
void InstructionMemory::computeSignals(){
	instruction = mem.read<inscode>(address);
}


DataMemory::DataMemory(Memory& mem, Signal<regdata>& address, Signal<regdata>&writeData,
			Signal<BitCount_t>& bitcount,
			Signal<bool>& memWrite, Signal<bool>& memRead, Signal<regdata>&readData)
:mem(mem), address(address), writeData(writeData), bitcount(bitcount),
 memWrite(memWrite), memRead(memRead), readData(readData)
{

}

DataMemory::~DataMemory(){

}

void DataMemory::clock(ClockEdge edge){
	if(memRead){
		if(bitcount == BIT8){
			readData = mem.read<uint8_t>(address);
		}else if(bitcount == BIT16){
			readData = mem.read<uint16_t>(address);
		}else if(bitcount == BIT32){
			readData = mem.read<uint32_t>(address);
		}else if(bitcount == BIT64){
			readData = mem.read<uint64_t>(address);
		}
	}
	if(memWrite){
		if(bitcount == BIT8){
			mem.write<uint8_t>(address, writeData);
		}else if(bitcount == BIT16){
			mem.write<uint16_t>(address, writeData);
		}else if(bitcount == BIT32){
			mem.write<uint32_t>(address, writeData);
		}else if(bitcount == BIT64){
			mem.write<uint64_t>(address, writeData);
		}
	}
}


