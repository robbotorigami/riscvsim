/*
 * test_instructions.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: cyborg9
 */
#include "test/catch.hpp"
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

TEST_CASE("Test ALU functions correctly", "[signals][alu]"){
	Signal<regdata> arg1, arg2, output;
	Signal<Instruction*> ins;
	Signal<bool> zeroSignal;

	ALU alu(ins, arg1, arg2, output, zeroSignal);

	INSTRUCTIONTESTS(BEQ)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(zeroSignal == true);
		arg1 = 10;
		arg2 = 20;
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(BNE)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(zeroSignal == false);
		arg1 = 10;
		arg2 = 20;
		REQUIRE(zeroSignal == true);
	}
	INSTRUCTIONTESTS(BLT)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(zeroSignal == false);
		arg1 = 10;
		arg2 = 20;
		REQUIRE(zeroSignal == true);
		arg1 = 20;
		arg2 = 10;
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(BGE)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(zeroSignal == true);
		arg1 = 10;
		arg2 = 20;
		REQUIRE(zeroSignal == false);
		arg1 = 20;
		arg2 = 10;
		REQUIRE(zeroSignal == true);
	}
	INSTRUCTIONTESTS(BLTU)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(zeroSignal == false);
		arg1 = 10;
		arg2 = 20;
		REQUIRE(zeroSignal == true);
		arg1 = 20;
		arg2 = 10;
		REQUIRE(zeroSignal == false);
		arg1 = -1;
		arg2 = 10;
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(BGEU)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(zeroSignal == true);
		arg1 = 10;
		arg2 = 20;
		REQUIRE(zeroSignal == false);
		arg1 = 20;
		arg2 = 10;
		REQUIRE(zeroSignal == true);
		arg1 = -1;
		arg2 = 10;
		REQUIRE(zeroSignal == true);
	}
	INSTRUCTIONTESTS(JALR)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 10);
		REQUIRE(zeroSignal == true);
	}
	INSTRUCTIONTESTS(LB)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 20);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(LH)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 20);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(LW)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 20);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(LBU)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 20);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(LHU)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 20);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(LWU)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 20);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(LD)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 20);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(ADDI)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 20);
		REQUIRE(zeroSignal == false);
		arg1 = 10;
		arg2 = -10;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SLTI)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
		arg1 = 10;
		arg2 = 20;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = -10;
		arg2 = 20;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SLTIU)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
		arg1 = 10;
		arg2 = 20;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = -10;
		arg2 = 20;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(XORI)
		arg1 = 1;
		arg2 = 1;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(ORI)
		arg1 = 1;
		arg2 = 1;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 0;
		arg2 = 0;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(ANDI)
		arg1 = 1;
		arg2 = 1;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
		arg1 = 0;
		arg2 = 0;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SLLI)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 6);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SRLI)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SRAI)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(JAL)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 3);
		REQUIRE(zeroSignal == true);
	}
	INSTRUCTIONTESTS(ADD)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 20);
		REQUIRE(zeroSignal == false);
		arg1 = 10;
		arg2 = -10;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SUB)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
		arg1 = 10;
		arg2 = -10;
		REQUIRE(output == 20);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SLT)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
		arg1 = 10;
		arg2 = 20;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = -10;
		arg2 = 20;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SLTU)
		arg1 = 10;
		arg2 = 10;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
		arg1 = 10;
		arg2 = 20;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = -10;
		arg2 = 20;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(XOR)
		arg1 = 1;
		arg2 = 1;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(OR)
		arg1 = 1;
		arg2 = 1;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 0;
		arg2 = 0;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(AND)
		arg1 = 1;
		arg2 = 1;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
		arg1 = 0;
		arg2 = 0;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SLL)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 6);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SRL)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 680;
		arg2 = 2;
		REQUIRE(output == 170);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SRA)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SB)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 4);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SH)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 4);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SW)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 4);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(SD)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 4);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(LUI)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == 1<<12);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 0);
		REQUIRE(zeroSignal == false);
	}
	INSTRUCTIONTESTS(AUIPC)
		arg1 = 3;
		arg2 = 1;
		REQUIRE(output == (1<<12) + 3);
		REQUIRE(zeroSignal == false);
		arg1 = 1;
		arg2 = 0;
		REQUIRE(output == 1);
		REQUIRE(zeroSignal == false);
	}
}


