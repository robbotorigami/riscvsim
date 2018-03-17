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
	textAddr = 0x400000; //Offset for Reserved section
	dataAddr = textAddr + text;
	stackAddr = dataAddr + stack;
	this->data.resize(stackAddr); //Allocate enough memory
}

/*!
 * \brief Constructs a memory object from the provided filename
 */
void Memory::fromFile(std::string filename)
{
	std::ifstream fs(filename);
	textAddr = 0x400000; //Offset for Reserved section
	dataAddr = textAddr + text;
	stackAddr = dataAddr + stack;
	this->data.resize(stackAddr); //Allocate enough memory

}




