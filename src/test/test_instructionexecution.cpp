/*
 * test_instructions.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: cyborg9
 */
#include "test/catch.hpp"
#include "cpucore/InstructionExecute.h"
#include "instruction/InstructionSignals.h"
#include "instruction/BInstructions.h"
#include "instruction/IInstructions.h"
#include "instruction/JInstructions.h"
#include "instruction/RInstructions.h"
#include "instruction/SInstructions.h"
#include "instruction/UInstructions.h"

#define INSTRUCTIONTESTS(NAME) \
	SECTION("TEST " #NAME){ \
		Instruction##NAME instance ##NAME; \
		ins = & instance##NAME;

TEST_CASE("Test execute stage functions correctly", "[signals][alu]"){
	Signal<regdata> data1, data2, immed;
	Signal<Instruction*> ins;
	Signal<bool> zeroSignal;
	Signal<regdata> aluResOut, writeData;
	Signal<pcval_t> pcIn, pcOut;

	pcIn = 0;
	immed = 0;

	EXStage ex(pcIn, data1, data2, immed, ins, pcOut, zeroSignal, aluResOut, writeData);


	INSTRUCTIONTESTS(BEQ)
		data1 = 10;
		data2 = 10;
		immed = 10;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == immed);
		data1 = 10;
		data2 = 20;
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(BNE)
		data1 = 10;
		data2 = 10;
		immed = 10;
		REQUIRE(zeroSignal == false);
		data1 = 10;
		data2 = 20;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == immed);
	}
	INSTRUCTIONTESTS(BLT)
		data1 = 10;
		data2 = 10;
		immed = 10;
		REQUIRE(zeroSignal == false);
		data1 = 10;
		data2 = 20;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == immed);
		data1 = 20;
		data2 = 10;
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(BGE)
		data1 = 10;
		data2 = 10;
		immed = 10;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == immed);
		data1 = 10;
		data2 = 20;
		REQUIRE(zeroSignal == false);
		data1 = 20;
		data2 = 10;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == immed);
	}
	INSTRUCTIONTESTS(BLTU)
		data1 = 10;
		data2 = 10;
		immed = 10;
		REQUIRE(zeroSignal == false);
		data1 = 10;
		data2 = 20;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == immed);
		data1 = 20;
		data2 = 10;
		REQUIRE(zeroSignal == false);
		data1 = -1;
		data2 = 10;
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(BGEU)
		data1 = 10;
		data2 = 10;
		immed = 10;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == immed);
		data1 = 10;
		data2 = 20;
		REQUIRE(zeroSignal == false);
		data1 = 20;
		data2 = 10;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == immed);
		data1 = -1;
		data2 = 10;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == immed);
	}
	INSTRUCTIONTESTS(JALR)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == data1 + immed);
		REQUIRE(aluResOut == pcIn);
	}
	INSTRUCTIONTESTS(LB)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == false);
		REQUIRE(aluResOut == data1 + immed);
	}
	INSTRUCTIONTESTS(LH)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == false);
		REQUIRE(aluResOut == data1 + immed);
	}
	INSTRUCTIONTESTS(LW)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == false);
		REQUIRE(aluResOut == data1 + immed);
	}
	INSTRUCTIONTESTS(LBU)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == false);
		REQUIRE(aluResOut == data1 + immed);
	}
	INSTRUCTIONTESTS(LHU)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == false);
		REQUIRE(aluResOut == data1 + immed);
	}
	INSTRUCTIONTESTS(LWU)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == false);
		REQUIRE(aluResOut == data1 + immed);
	}
	INSTRUCTIONTESTS(LD)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == false);
		REQUIRE(aluResOut == data1 + immed);
	}
	INSTRUCTIONTESTS(ADDI)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == false);
		REQUIRE(aluResOut == data1 + immed);
	}
	INSTRUCTIONTESTS(SLTI)
		data1 = 10;
		data2 = 10;
		immed = 10;
		REQUIRE(aluResOut == 0);
		data1 = 10;
		data2 = 10;
		immed = 20;
		REQUIRE(aluResOut == 1);
		data1 = -10;
		data2 = 10;
		immed = 20;
		REQUIRE(aluResOut == 1);
	}
	INSTRUCTIONTESTS(SLTIU)
		data1 = 10;
		data2 = 10;
		immed = 10;
		REQUIRE(aluResOut == 0);
		data1 = 10;
		data2 = 10;
		immed = 20;
		REQUIRE(aluResOut == 1);
		data1 = -10;
		data2 = 10;
		immed = 20;
		REQUIRE(aluResOut == 0);
	}
	INSTRUCTIONTESTS(XORI)
		data1 = 1;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == 0);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(ORI)
		data1 = 1;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
		data1 = 0;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(ANDI)
		data1 = 1;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 0);
		REQUIRE(zeroSignal == false);
		data1 = 0;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SLLI)
		data1 = 3;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == 6);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SRLI)
		data1 = 3;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SRAI)
		data1 = 3;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(JAL)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == true);
		REQUIRE(pcOut == pcIn + immed);
		REQUIRE(aluResOut == pcIn);
	}
	INSTRUCTIONTESTS(ADD)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == false);
		REQUIRE(aluResOut == data1 + data2);
	}
	INSTRUCTIONTESTS(SUB)
		data1 = 10;
		data2 = 20;
		immed = 5;
		REQUIRE(zeroSignal == false);
		REQUIRE(aluResOut == data1 - data2);
	}
	INSTRUCTIONTESTS(SLT)
		data1 = 10;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 0);
		data1 = 10;
		data2 = 20;
		immed = 0;
		REQUIRE(aluResOut == 1);
		data1 = -10;
		data2 = 20;
		immed = 0;
		REQUIRE(aluResOut == 1);
	}
	INSTRUCTIONTESTS(SLTU)
		data1 = 10;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 0);
		data1 = 10;
		data2 = 20;
		immed = 0;
		REQUIRE(aluResOut == 1);
		data1 = -10;
		data2 = 20;
		immed = 0;
		REQUIRE(aluResOut == 0);
	}
	INSTRUCTIONTESTS(XOR)
		data1 = 1;
		data2 = 1;
		immed = 10;
		REQUIRE(aluResOut == 0);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 0;
		immed = 10;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(OR)
		data1 = 1;
		data2 = 1;
		immed = 10;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 0;
		immed = 10;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
		data1 = 0;
		data2 = 0;
		immed = 10;
		REQUIRE(aluResOut == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(AND)
		data1 = 1;
		data2 = 1;
		immed = 10;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 0;
		immed = 10;
		REQUIRE(aluResOut == 0);
		REQUIRE(zeroSignal == false);
		data1 = 0;
		data2 = 0;
		immed = 10;
		REQUIRE(aluResOut == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SLL)
		data1 = 3;
		data2 = 1;
		immed = 10;
		REQUIRE(aluResOut == 6);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 0;
		immed = 10;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SRL)
		data1 = 3;
		data2 = 1;
		immed = 10;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 0;
		immed = 10;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SRA)
		data1 = 3;
		data2 = 1;
		immed = 10;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 0;
		immed = 10;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SB)
		data1 = 3;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == 4);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SH)
		data1 = 3;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == 4);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SW)
		data1 = 3;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == 4);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SD)
		data1 = 3;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == 4);
		REQUIRE(zeroSignal == false);
		data1 = 1;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(LUI)
		data1 = 10;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == immed<<12);
		REQUIRE(zeroSignal == false);
		data1 = 10;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == immed<<12);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(AUIPC)
		pcIn = 20;
		data1 = 10;
		data2 = 10;
		immed = 1;
		REQUIRE(aluResOut == pcIn + (immed<<12));
		REQUIRE(zeroSignal == false);
		data1 = 10;
		data2 = 10;
		immed = 0;
		REQUIRE(aluResOut == pcIn + (immed<<12));
		REQUIRE(zeroSignal == false);
	}
}


