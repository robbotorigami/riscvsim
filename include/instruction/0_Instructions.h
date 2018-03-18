/*
 * Instruction.h
 *
 *  Created on: Mar 3, 2018
 *      Author: cyborg9
 */

#ifndef INCLUDE_INSTRUCTION_0_INSTRUCTIONS_H_
#define INCLUDE_INSTRUCTION_0_INSTRUCTIONS_H_
#include <cstdint>
#include <iostream>
#include <vector>
#include "cpucore/cputypes.h"

/*!
 * \brief Base class for all Instructions, inheirets common functionality
 */
class Instruction{
public:
	virtual ~Instruction() = 0;
	virtual bool matches(inscode code) = 0;
	virtual std::string asString() = 0;

	virtual regdata getImmediate() = 0;
	virtual regaddress getRS1() = 0;
	virtual regaddress getRS2() = 0;

	virtual regdata getALUResult(regdata arg1, regdata arg2) = 0;
	virtual bool getZeroSignal(regdata arg1, regdata arg2) = 0;
	virtual ALUSrc_t getALUSrc() = 0;

	virtual Instruction* clone(inscode code) = 0;
	virtual std::string getName() = 0;
};

/*!
 * \brief Static class to handle instruction parsing and creation
 */
class InstructionFactory{
public:
	static Instruction* parseInstruction(inscode code);
	static Instruction* registerInstruction(Instruction*);
private:
	//! Registry of all instruction types
	static std::vector<Instruction*> instructionRegistry;
};

#define INSTRUCTION(NAME, TYPE) \
	class Instruction ## NAME: public TYPE ## Instruction{ \
	public: \
		Instruction* clone(inscode code); \
		bool getZeroSignal(regdata arg1, regdata arg2); \
		regdata getALUResult(regdata arg1, regdata arg2); \
		bool matches(inscode code); \
	protected: \
		std::string getName(); \
	}

#define INSTRUCTION_BOILERPLATE(NAME) \
	Instruction* NAME ## _prototype = InstructionFactory::registerInstruction(new Instruction ## NAME()); \
	\
	std::string Instruction ## NAME::getName(){ \
		return #NAME; \
	} \
	\
	Instruction* Instruction ## NAME::clone(inscode code){ \
		Instruction ## NAME* instance = new Instruction ## NAME(); \
		instance->parseFields(code); \
		return instance; \
	}

#define MATCHES_ON(NAME, COMPARISON) \
	bool Instruction ## NAME::matches(inscode code){ \
		parseFields(code); \
		return (COMPARISON); \
	}

#define ALU_OPERATION(NAME, OPERATION, ZERO) \
	regdata Instruction ## NAME::getALUResult(regdata arg1, regdata arg2){ \
		return (OPERATION); \
	} \
	bool Instruction ## NAME::getZeroSignal(regdata arg1, regdata arg2){ \
		return (ZERO); \
	}

#endif /* INCLUDE_INSTRUCTION_0_INSTRUCTIONS_H_ */
