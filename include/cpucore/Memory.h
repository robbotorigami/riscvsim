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
#include <vector>
#include <string>

typedef uint32_t memaddress;

/*!
 * \brief Class to represent main memory
 */
class Memory{
public:
	Memory();

	void buildFromImage(std::string filename);

	/*!
	 * \brief Template function to read from memory
	 * \tparam T the type to be read from memory
	 * \param addr the address to be read from
	 * \return the value at addr in memory
	 */
	template <typename T>
	T read(memaddress addr){
		assert(addr < data.size() - sizeof(T));
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
		assert(addr < data.size() - sizeof(T));
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



#endif /* INCLUDE_CPUCORE_MEMORY_H_ */
