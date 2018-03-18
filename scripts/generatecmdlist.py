import random
from compiletools import codeobject

def format_and_split(cmds):
    cmds = cmds.split('\n')
    cmds = [c.split('(')[1] for c in cmds]
    cmds = [c.split(')')[0] for c in cmds]
    return cmds

def create_line(optype, cmds, comp, immeds, rs1s, rs2s, rds):
    string =  "static inscode {}codes[] = {{{}}};\n"
    string += "static string {}instructions[] ={{{}}};\n"
    string += "static regdata {}immeds[] = {{{}}};\n"
    string += "static regaddress {}rs1s[] = {{{}}};\n"
    string += "static regaddress {}rs2s[] = {{{}}};\n"
    string += "static regaddress {}rds[] = {{{}}};\n"
    string = string.format(optype, ','.join(['0x{:08x}'.format(c) for c in comp]),
                           optype, ','.join(['"{}"'.format(c) for c in cmds]),
                           optype, ','.join(["{}".format(i) for i in immeds]),
                           optype, ','.join(["{}".format(i) for i in rs1s]),
                           optype, ','.join(["{}".format(i) for i in rs2s]),
                           optype, ','.join(["{}".format(i) for i in rds]))
    return string

def create_header():
    string =  '.section .crt0, "x"\n'
    string += '_start:\n'
    string += '.global _start\n'
    return string

filetext = ""

############################ I Instructions #############################


icmds = '''INSTRUCTION_BOILERPLATE(JALR);
INSTRUCTION_BOILERPLATE(LB);
INSTRUCTION_BOILERPLATE(LH);
INSTRUCTION_BOILERPLATE(LW);
INSTRUCTION_BOILERPLATE(LBU);
INSTRUCTION_BOILERPLATE(LHU);
INSTRUCTION_BOILERPLATE(LWU);
INSTRUCTION_BOILERPLATE(LD);
INSTRUCTION_BOILERPLATE(ADDI);
INSTRUCTION_BOILERPLATE(SLTI);
INSTRUCTION_BOILERPLATE(SLTIU);
INSTRUCTION_BOILERPLATE(XORI);
INSTRUCTION_BOILERPLATE(ORI);
INSTRUCTION_BOILERPLATE(ANDI);
INSTRUCTION_BOILERPLATE(SLLI);
INSTRUCTION_BOILERPLATE(SRLI);
INSTRUCTION_BOILERPLATE(SRAI);'''
icmds = format_and_split(icmds)

loads = icmds[1:8]
others = [icmds[0]] + icmds[8:]

immedlo = [random.randint(0, 100) for c in loads]
immedot = [random.randint(0, 20) for c in others]

rs1lo = [random.randint(0, 31) for c in loads]
rs2lo = [0 for c in loads]
rdlo  = [random.randint(0, 31) for c in loads]

rs1ot = [random.randint(0, 31) for c in others]
rs2ot = [0 for c in others]
rdot  = [random.randint(0, 31) for c in others]

loads = ['{} x{}, {}(x{})'.format(c, rd, i, rs1) for i,rs1,rs2,rd,c in zip(immedlo,rs1lo,rs2lo,rdlo,loads)]
others = ['{} x{}, x{}, {}'.format(c, rd, rs1, i) for i,rs1,rs2,rd,c in zip(immedot,rs1ot,rs2ot,rdot,others)]

icmds = [others[0]] + loads + others[1:]
immeds = [immedot[0]] + immedlo + immedot[1:]
rs1s = [rs1ot[0]] + rs1lo + rs1ot[1:]
rs2s = [rs2ot[0]] + rs2lo + rs2ot[1:]
rds  = [rdot[0]]  + rdlo  + rdot[1:]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

print(create_line('i', icmds, icomp, immeds, rs1s, rs2s, rds))
filetext += create_line('i', icmds, icomp, immeds, rs1s, rs2s, rds)




############################ R Instructions #############################

icmds = '''INSTRUCTION_BOILERPLATE(ADD)
INSTRUCTION_BOILERPLATE(SUB)
INSTRUCTION_BOILERPLATE(SLL)
INSTRUCTION_BOILERPLATE(SLT)
INSTRUCTION_BOILERPLATE(SLTU)
INSTRUCTION_BOILERPLATE(XOR)
INSTRUCTION_BOILERPLATE(SRL)
INSTRUCTION_BOILERPLATE(SRA)
INSTRUCTION_BOILERPLATE(OR)
INSTRUCTION_BOILERPLATE(AND)
INSTRUCTION_BOILERPLATE(ADDW)
INSTRUCTION_BOILERPLATE(SUBW)
INSTRUCTION_BOILERPLATE(SLLW)
INSTRUCTION_BOILERPLATE(SRLW)
INSTRUCTION_BOILERPLATE(SRAW)'''
icmds = format_and_split(icmds)

immeds = [0 for c in icmds]
rs1s = [random.randint(0, 31) for c in loads]
rs2s = [random.randint(0, 31) for c in loads]
rds  = [random.randint(0, 31) for c in loads]

icmds = ['{} x{}, x{}, x{}'.format(c, rd, rs1, rs2) for i,rs1,rs2,rd,c in zip(immeds,rs1s,rs2s,rds,icmds)]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

print(create_line('r', icmds, icomp, immeds, rs1s, rs2s, rds))
filetext += create_line('r', icmds, icomp, immeds, rs1s, rs2s, rds)




############################ B Instructions #############################

icmds = '''INSTRUCTION_BOILERPLATE(BEQ)
INSTRUCTION_BOILERPLATE(BNE)
INSTRUCTION_BOILERPLATE(BLT)
INSTRUCTION_BOILERPLATE(BGE)
INSTRUCTION_BOILERPLATE(BLTU)
INSTRUCTION_BOILERPLATE(BGEU)'''
icmds = format_and_split(icmds)

rs1s = [random.randint(0, 31) for c in loads]
rs2s = [random.randint(0, 31) for c in loads]
rds  = [0 for c in loads]

icmds = ['{} x{}, x{}, {}'.format(c, rs1, rs2, '_start') for i,rs1,rs2,rd,c in zip(immeds,rs1s,rs2s,rds,icmds)]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

#replace label with correct jumps
icmds = ['{}, {}'.format(','.join(c.split(',')[:-1]), -i*4) for i,c in enumerate(icmds)]

immeds = [-i*4 for i,c in enumerate(icmds)]

print(create_line('b', icmds, icomp, immeds, rs1s, rs2s, rds))
filetext += create_line('b', icmds, icomp, immeds, rs1s, rs2s, rds)




############################ J Instructions #############################

icmds = '''INSTRUCTION_BOILERPLATE(JAL)'''

icmds = format_and_split(icmds)

immeds = [random.randint(0,4000)*2 for c in icmds]
rs1s = [0 for c in loads]
rs2s = [0 for c in loads]
rds  = [random.randint(0, 31) for c in loads]

icmds = ['{} x{}, {}'.format(c, rd, i) for i,rs1,rs2,rd,c in zip(immeds,rs1s,rs2s,rds,icmds)]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

print(create_line('j', icmds, icomp, immeds, rs1s, rs2s, rds))
filetext += create_line('j', icmds, icomp, immeds, rs1s, rs2s, rds)




############################ S Instructions #############################

icmds = '''INSTRUCTION_BOILERPLATE(SB)
INSTRUCTION_BOILERPLATE(SH)
INSTRUCTION_BOILERPLATE(SW)
INSTRUCTION_BOILERPLATE(SD)'''

icmds = format_and_split(icmds)

immeds = [random.randint(0, 100) for c in icmds]
rs1s = [random.randint(0, 31) for c in loads]
rs2s = [random.randint(0, 31) for c in loads]
rds  = [0 for c in loads]

icmds = ['{} x{}, {}(x{})'.format(c, rs2, i, rs1) for i,rs1,rs2,rd,c in zip(immeds,rs1s,rs2s,rds,icmds)]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

print(create_line('s', icmds, icomp, immeds, rs1s, rs2s, rds))
filetext += create_line('s', icmds, icomp, immeds, rs1s, rs2s, rds)



############################ U Instructions #############################

icmds = '''INSTRUCTION_BOILERPLATE(LUI)
INSTRUCTION_BOILERPLATE(AUIPC)'''

icmds = format_and_split(icmds)

immeds = [random.randint(0,4000)*2 for c in icmds]
rs1s = [0 for c in loads]
rs2s = [0 for c in loads]
rds  = [random.randint(0, 31) for c in loads]

icmds = ['{} x{}, {}'.format(c, rd, i) for i,rs1,rs2,rd,c in zip(immeds,rs1s,rs2s,rds,icmds)]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

print(create_line('u', icmds, icomp, immeds, rs1s, rs2s, rds))
filetext += create_line('u', icmds, icomp, immeds, rs1s, rs2s, rds)

with open('../include/test/gen_testcodes.h', 'w+') as f:
    f.write("#ifndef GENERATED_TESTCODES_H\n#define GENERATED_TESTCODES_H\n\n")
    f.write('#include "cpucore/cputypes.h"\n#include <string>\n\nusing namespace std;\n')
    f.write(filetext)
    f.write("#endif")
