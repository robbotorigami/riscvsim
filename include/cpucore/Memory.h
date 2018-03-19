/*
 * Memory.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_CPUCORE_MEMORY_H_
#define INCLUDE_CPUCORE_MEMORY_H_
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <cstring>
#include <vector>
#include <string>
#include "cpucore/Signals.h"
#include "cpucore/cputypes.h"


/*!
 * \brief Class to represent main memory
 */
class Memory{
public:
	Memory();

	void buildFromImage(std::string filename);

	/*!
	 * \brief Template function to build memory from a vector
	 * \tparam T the type to be used as initializers
	 * \param data the data to build memory from
	 */
	template <typename T>
	void buildFromVector(std::vector<T> data){
		for(T i : data){
			uint8_t* start = reinterpret_cast<uint8_t*>(&i);
			for(size_t j = 0; j < sizeof(T); j++){
				this->data.push_back(*(start+j));
			}
		}
	}

	/*!
	 * \brief Template function to read from memory
	 * \tparam T the type to be read from memory
	 * \param addr the address to be read from
	 * \return the value at addr in memory
	 */
	template <typename T>
	T read(memaddress addr){
		assert(addr <= data.size() - sizeof(T));
		T t;
		memcpy(&t, &data[addr], sizeof(t));
		return t;
	}

	/*!
	 * \brief Template function to write to memory
	 * \tparam T the type of the value to be written
	 * \param addr the address to write to
	 * \param t the value to be written
	 */
	template <typename T>
	void write(memaddress addr, T t){
		assert(addr <= data.size() - sizeof(T));
		memcpy(&data[addr], &t, sizeof(t));
	}

private:
	//! The data in the memory object
	std::vector<uint8_t> data;
	//! The address of the start of text
	memaddress textAddr;
	//! The address of the start of data
	memaddress dataAddr;
	//! The address of the top of the stack
	memaddress stackAddr;
};

/*!
 * \brief class to implement the instruction path to memory
 */
class InstructionMemory: public DrivenObject{
public:
	InstructionMemory(Memory& mem, Signal<pcval_t>& address, Signal<inscode>& instruction);
	~InstructionMemory();

	void computeSignals();

private:
	//! Reference to the memory
	Memory& mem;
	//! The address to read from
	Signal<pcval_t>& address;
	//! The instruction at the address
	Signal<inscode>& instruction;
};

class DataMemory: public ClockableObject{
public:
	DataMemory(Memory& mem, Signal<regdata>& address, Signal<regdata>&writeData,
			Signal<BitCount_t>& bitcount,
			Signal<bool>& memWrite, Signal<bool>& memRead, Signal<regdata>&readData);
	~DataMemory();

	void clock(ClockEdge edge);
private:
	Memory& mem;
	Signal<regdata>& address;
	Signal<regdata>& writeData;
	Signal<BitCount_t>& bitcount;
	Signal<bool>& memWrite;
	Signal<bool>& memRead;
	Signal<regdata>&readData;
};

#endif /* INCLUDE_CPUCORE_MEMORY_H_ */
