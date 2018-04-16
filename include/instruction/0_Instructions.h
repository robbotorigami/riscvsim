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

#define NOP_CODE (19ul)

#define NOP (InstructionFactory::parseInstruction(NOP_CODE))

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
	virtual regaddress getRD() = 0;
	virtual bool getRegWriteSignal() = 0;
	virtual bool getMemtoRegSignal() = 0;

	virtual regdata getALUResult(regdata arg1, regdata arg2) = 0;
	virtual bool getZeroSignal(regdata arg1, regdata arg2) = 0;
	virtual ALUSrc_t getALUSrc1() = 0;
	virtual ALUSrc_t getALUSrc2() = 0;

	virtual regdata preProcessStore(regdata val) {return val;}
	virtual regdata postProcessLoad(regdata val) {return val;}
	virtual BitCount_t getMemoryType() {return BIT8;}
	virtual bool getMemWriteSignal() {return false;}
	virtual bool getMemReadSignal() {return false;}

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

#define STD_INSTRUCTION_METHODS(NAME, TYPE) \
	public: \
		Instruction* clone(inscode code); \
		bool getZeroSignal(regdata arg1, regdata arg2); \
		regdata getALUResult(regdata arg1, regdata arg2); \
		ALUSrc_t getALUSrc1(); \
		ALUSrc_t getALUSrc2(); \
		bool matches(inscode code); \
		regaddress getRD(); \
		bool getRegWriteSignal(); \
		bool getMemtoRegSignal(); \
	protected: \
		std::string getName(); \

#define INSTRUCTION(NAME, TYPE) \
	class Instruction ## NAME: public TYPE ## Instruction{ \
		STD_INSTRUCTION_METHODS(NAME, TYPE) \
	}

#define STORE_INSTRUCTION(NAME, TYPE) \
	class Instruction ## NAME: public TYPE ## Instruction{ \
		STD_INSTRUCTION_METHODS(NAME, TYPE) \
	public: \
		regdata preProcessStore(regdata val); \
		BitCount_t getMemoryType(); \
		bool getMemWriteSignal(); \
	}

#define LOAD_INSTRUCTION(NAME, TYPE) \
	class Instruction ## NAME: public TYPE ## Instruction{ \
		STD_INSTRUCTION_METHODS(NAME, TYPE) \
	public: \
		regdata postProcessLoad(regdata val); \
		BitCount_t getMemoryType(); \
		bool getMemReadSignal(); \
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

#define ALU_SOURCE(NAME, SRC1, SRC2) \
	ALUSrc_t Instruction ##NAME::getALUSrc1(){ \
		return (SRC1); \
	} \
	ALUSrc_t Instruction ##NAME::getALUSrc2(){ \
		return (SRC2); \
	}

#define WRITEBACK(NAME, RD, REGWRITE, MEMREG) \
	regaddress Instruction ##NAME::getRD(){ \
		return (RD); \
	} \
	bool Instruction ##NAME::getRegWriteSignal(){ \
		return (REGWRITE); \
	} \
	bool Instruction ##NAME::getMemtoRegSignal(){ \
		return (MEMREG); \
	}

#define STORE_OPERATION(NAME, PP, TYPE) \
	regdata Instruction ##NAME::preProcessStore(regdata val){ \
		return (PP); \
	} \
	BitCount_t Instruction ##NAME::getMemoryType() { \
		return (TYPE); \
	} \
	bool Instruction ## NAME::getMemWriteSignal() { \
		return true; \
	}

#define LOAD_OPERATION(NAME, PP, TYPE) \
	regdata Instruction ##NAME::postProcessLoad(regdata val){ \
		return (PP); \
	} \
	BitCount_t Instruction ##NAME::getMemoryType() { \
		return (TYPE); \
	} \
	bool Instruction ## NAME::getMemReadSignal() { \
		return true; \
	}

#endif /* INCLUDE_INSTRUCTION_0_INSTRUCTIONS_H_ */
