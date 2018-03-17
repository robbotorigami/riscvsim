#ifndef GENERATED_TESTCODES_H
#define GENERATED_TESTCODES_H

inscode icodes[] = {0x00ee8ce7,0x03c18203,0x060f1a03,0x00b9a183,0x0231c683,0x023b5403,0x04f0e803,0x02c23183,0x00f70413,0x012a2a13,0x00363093,0x00fac893,0x0124eb93,0x004f7e93,0x011a1c93,0x00fcd393,0x40795493};
string iinstructions[] ={"JALR x25, x29, 14","LB x4, 60(x3)","LH x20, 96(x30)","LW x3, 11(x19)","LBU x13, 35(x3)","LHU x8, 35(x22)","LWU x16, 79(x1)","LD x3, 44(x4)","ADDI x8, x14, 15","SLTI x20, x20, 18","SLTIU x1, x12, 3","XORI x17, x21, 15","ORI x23, x9, 18","ANDI x29, x30, 4","SLLI x25, x20, 17","SRLI x7, x25, 15","SRAI x9, x18, 7"};
inscode rcodes[] = {0x01f681b3,0x40dc0a33,0x010b1033,0x01e92cb3,0x01bc3c33,0x013ac633,0x00d15c33,0x4199dd33,0x009d66b3,0x0017f133,0x01c608bb,0x41410cbb,0x00209b3b,0x01e7dcbb,0x412d5b3b};
string rinstructions[] ={"ADD x3, x13, x31","SUB x20, x24, x13","SLL x0, x22, x16","SLT x25, x18, x30","SLTU x24, x24, x27","XOR x12, x21, x19","SRL x24, x2, x13","SRA x26, x19, x25","OR x13, x26, x9","AND x2, x15, x1","ADDW x17, x12, x28","SUBW x25, x2, x20","SLLW x22, x1, x2","SRLW x25, x15, x30","SRAW x22, x26, x18"};
inscode bcodes[] = {0x00938063,0xfe279ee3,0xff50cce3,0xff01dae3,0xfffe68e3,0xff44f6e3};
string binstructions[] ={"BEQ x7, x9, 0","BNE x15, x2, -4","BLT x1, x21, -8","BGE x3, x16, -12","BLTU x28, x31, -16","BGEU x9, x20, -20"};
inscode jcodes[] = {0x30f0136f};
string jinstructions[] ={"JAL x6, 6926"};
inscode scodes[] = {0x019585a3,0x04fc16a3,0x02d126a3,0x062b3023};
string sinstructions[] ={"SB x25, 11(x11)","SH x15, 77(x24)","SW x13, 45(x2)","SD x2, 96(x22)"};
inscode ucodes[] = {0x01dead37,0x01ec6c17};
string uinstructions[] ={"LUI x26, 7658","AUIPC x24, 7878"};
#endif