/*
 * Signals.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: cyborg9
 */

#include "cpucore/Signals.h"



//TODO: This is a horrific quick hack
static Instruction* nop = new InstructionADDI();
template <>
Instruction* Signal<Instruction*>::getData() const{
	if(data == nullptr){
		return nop;
	}
	return data;
}
