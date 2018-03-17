import random
from compiletools import codeobject

def format_and_split(cmds):
    cmds = cmds.split('\n')
    cmds = [c.split('(')[1] for c in cmds]
    cmds = [c.split(')')[0] for c in cmds]
    return cmds

def create_line(optype, cmds, comp):
    string = "inscode {}codes[] = {{{}}};\n"
    string += "string {}instructions[] ={{{}}};\n"
    string = string.format(optype, ','.join(['0x{:08x}'.format(c) for c in comp]), optype, ','.join(['"{}"'.format(c) for c in cmds]))
    return string

def create_header():
    string =  '.section .crt0, "x"\n'
    string += '_start:\n'
    string += '.global _start\n'
    return string

filetext = ""


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

loads = ['{} x{}, {}(x{})'.format(c, random.randint(0, 31), random.randint(0, 100), random.randint(0, 31)) for c in loads]
others = ['{} x{}, x{}, {}'.format(c, random.randint(0, 31), random.randint(0,31), random.randint(0,20)) for c in others]

icmds = [others[0]] + loads + others[1:]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

print(create_line('i', icmds, icomp))
filetext += create_line('i', icmds, icomp)

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

icmds = ['{} x{}, x{}, x{}'.format(c, random.randint(0, 31), random.randint(0,31), random.randint(0,31)) for c in icmds]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

print(create_line('r', icmds, icomp))
filetext += create_line('r', icmds, icomp)


icmds = '''INSTRUCTION_BOILERPLATE(BEQ)
INSTRUCTION_BOILERPLATE(BNE)
INSTRUCTION_BOILERPLATE(BLT)
INSTRUCTION_BOILERPLATE(BGE)
INSTRUCTION_BOILERPLATE(BLTU)
INSTRUCTION_BOILERPLATE(BGEU)'''
icmds = format_and_split(icmds)

icmds = ['{} x{}, x{}, {}'.format(c, random.randint(0, 31), random.randint(0,31), '_start') for c in icmds]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

#replace label with correct jumps
icmds = ['{}, {}'.format(','.join(c.split(',')[:-1]), -i*4) for i,c in enumerate(icmds)]

print(create_line('b', icmds, icomp))
filetext += create_line('b', icmds, icomp)


icmds = '''INSTRUCTION_BOILERPLATE(JAL)'''

icmds = format_and_split(icmds)
icmds = icmds

icmds = ['{} x{}, {}'.format(c, random.randint(0, 31), random.randint(0,4000)*2) for c in icmds]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

print(create_line('j', icmds, icomp))
filetext += create_line('j', icmds, icomp)

icmds = '''INSTRUCTION_BOILERPLATE(SB)
INSTRUCTION_BOILERPLATE(SH)
INSTRUCTION_BOILERPLATE(SW)
INSTRUCTION_BOILERPLATE(SD)'''


icmds = format_and_split(icmds)
icmds = icmds

icmds = ['{} x{}, {}(x{})'.format(c, random.randint(0, 31), random.randint(0, 100), random.randint(0, 31)) for c in icmds]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

print(create_line('s', icmds, icomp))
filetext += create_line('s', icmds, icomp)

icmds = '''INSTRUCTION_BOILERPLATE(LUI)
INSTRUCTION_BOILERPLATE(AUIPC)'''

icmds = format_and_split(icmds)
icmds = icmds

icmds = ['{} x{}, {}'.format(c, random.randint(0, 31), random.randint(0,4000)*2) for c in icmds]

co = codeobject()
co.addstring(create_header())
co.addstring('\n'.join(icmds) + '\n')
icomp = co.compile()

print(create_line('u', icmds, icomp))
filetext += create_line('u', icmds, icomp)

with open('../include/test/gen_testcodes.h', 'w+') as f:
    f.write("#ifndef GENERATED_TESTCODES_H\n#define GENERATED_TESTCODES_H\n\n")
    f.write(filetext)
    f.write("#endif")
