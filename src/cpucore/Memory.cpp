/*
 * Memory.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#include "cpucore/Memory.h"
#include <fstream>

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
	uint32_t text, data, stack;
	fs.read(reinterpret_cast<char *>(&text), sizeof(text));
	fs.read(reinterpret_cast<char *>(&data), sizeof(data));
	fs.read(reinterpret_cast<char *>(&stack), sizeof(stack));
	textAddr = 0x00000000;
	dataAddr = textAddr + text;
	stackAddr = dataAddr + data + stack;
	this->data.resize(stackAddr); //Allocate enough memory
	fs.read(reinterpret_cast<char *>(&this->data[textAddr]), text+data+stack);
}




