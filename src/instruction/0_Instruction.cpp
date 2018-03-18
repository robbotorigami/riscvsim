/*
 * This file has a 0 at the start because I am doing
 * some stupid stuff with global constructor order
 */

#include <instruction/0_Instructions.h>
#include "util/easylogging++.h"
#include <iostream>
#include <algorithm>

std::vector<Instruction*> InstructionFactory::instructionRegistry;

//! Default destructor
Instruction::~Instruction(){}

/*!
 * \brief Factory method to build a instruction object from bytes
 * \param code The raw instruction
 * \return the processed instruction object
 */
Instruction* InstructionFactory::parseInstruction(inscode code){
	for(auto ins : instructionRegistry){
		//Use the matches operator to see if the code matches
		if(ins->matches(code)){
			Instruction* instruction = ins->clone(code);
			return instruction;
		}
	}
	//Unable to find the instruction, bad code
	return nullptr;
}

/*!
 * \brief Adds the provided object to the registry
 * \param ins Instruction to be added
 * \return a copy of the instruction
 */
Instruction* InstructionFactory::registerInstruction(Instruction* ins){
	instructionRegistry.push_back(ins);
	return ins;
}
