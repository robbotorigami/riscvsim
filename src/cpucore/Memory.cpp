/*
 * Memory.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#include "cpucore/Memory.h"

/*!
 * \brief Constructs memory object with the specified sizes for
 * the different sections
 * \param text the size of the text section
 * \param data the size of the data section
 * \param stack the size of the stack
 */
Memory::Memory(size_t text, size_t data, size_t stack)
:data()
{
	textAddr = 0x400000; //Offset for Reserved section
	dataAddr = textAddr + text;
	stackAddr = dataAddr + stack;
	this->data.resize(stackAddr); //Allocate enough memory
}




