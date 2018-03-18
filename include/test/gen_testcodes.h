#ifndef GENERATED_TESTCODES_H
#define GENERATED_TESTCODES_H

#include "cpucore/cputypes.h"
#include <string>

using namespace std;
static inscode icodes[] = {0x00e00167,0x00e98f03,0x02009a03,0x044aa683,0x04efc583,0x0056d783,0x05656183,0x034dbd03,0x00580513,0x003e2713,0x000d3813,0x003f4993,0x00f96f93,0x0116fb13,0x011f9593,0x0076d993,0x414ad113};
static string iinstructions[] ={"JALR x2, x0, 14","LB x30, 14(x19)","LH x20, 32(x1)","LW x13, 68(x21)","LBU x11, 78(x31)","LHU x15, 5(x13)","LWU x3, 86(x10)","LD x26, 52(x27)","ADDI x10, x16, 5","SLTI x14, x28, 3","SLTIU x16, x26, 0","XORI x19, x30, 3","ORI x31, x18, 15","ANDI x22, x13, 17","SLLI x11, x31, 17","SRLI x19, x13, 7","SRAI x2, x21, 20"};
static regdata iimmeds[] = {14,14,32,68,78,5,86,52,5,3,0,3,15,17,17,7,20};
static regaddress irs1s[] = {0,19,1,21,31,13,10,27,16,28,26,30,18,13,31,13,21};
static regaddress irs2s[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static regaddress irds[] = {2,30,20,13,11,15,3,26,10,14,16,19,31,22,11,19,2};
static inscode rcodes[] = {0x00368eb3,0x40060933,0x01881eb3,0x0053a133,0x00afbb33,0x01c6ccb3,0x00a555b3};
static string rinstructions[] ={"ADD x29, x13, x3","SUB x18, x12, x0","SLL x29, x16, x24","SLT x2, x7, x5","SLTU x22, x31, x10","XOR x25, x13, x28","SRL x11, x10, x10"};
static regdata rimmeds[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static regaddress rrs1s[] = {13,12,16,7,31,13,10};
static regaddress rrs2s[] = {3,0,24,5,10,28,10};
static regaddress rrds[] = {29,18,29,2,22,25,11};
static inscode bcodes[] = {0x009d8063,0xff309ee3,0xfe734ce3,0xffd3dae3,0xfeeee8e3,0xff51f6e3};
static string binstructions[] ={"BEQ x27, x9, 0","BNE x1, x19, -4","BLT x6, x7, -8","BGE x7, x29, -12","BLTU x29, x14, -16","BGEU x3, x21, -20"};
static regdata bimmeds[] = {0,-4,-8,-12,-16,-20};
static regaddress brs1s[] = {27,1,6,7,29,3,30};
static regaddress brs2s[] = {9,19,7,29,14,21,24};
static regaddress brds[] = {0,0,0,0,0,0,0};
static inscode jcodes[] = {0x57e0056f};
static string jinstructions[] ={"JAL x10, 1406"};
static regdata jimmeds[] = {1406};
static regaddress jrs1s[] = {0,0,0,0,0,0,0};
static regaddress jrs2s[] = {0,0,0,0,0,0,0};
static regaddress jrds[] = {10,29,15,22,25,0,9};
static inscode scodes[] = {0x075c00a3,0x019919a3,0x020baba3,0x047eb623};
static string sinstructions[] ={"SB x21, 97(x24)","SH x25, 19(x18)","SW x0, 55(x23)","SD x7, 76(x29)"};
static regdata simmeds[] = {97,19,55,76};
static regaddress srs1s[] = {24,18,23,29,21,17,2};
static regaddress srs2s[] = {21,25,0,7,8,2,5};
static regaddress srds[] = {0,0,0,0,0,0,0};
static inscode ucodes[] = {0x0173abb7,0x0113cc17};
static string uinstructions[] ={"LUI x23, 5946","AUIPC x24, 4412"};
static regdata uimmeds[] = {5946,4412};
static regaddress urs1s[] = {0,0,0,0,0,0,0};
static regaddress urs2s[] = {0,0,0,0,0,0,0};
static regaddress urds[] = {23,24,14,29,27,5,29};
#endif