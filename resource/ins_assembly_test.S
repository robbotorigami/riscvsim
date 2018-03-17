

#This code is used to test RISC V Instruction set. The register x10 value is incremented with
#every instruction. If an instruction fails it jumps to FAIL sub routine and the value of x20
# is set to 1. The instruction number which failed can be seen in value of register x10. If all
# instructions worked correctly, it jumps to PASS sub routine and the value of x25 register is
# is set to 1 //


# Section .crt0 is always placed from address 0
    .section .crt0, "x"


#Symbol start is used to obtain entry point information
_start:
    .global _start

    #Testing alu instruction addi: case 1//
    li x10,1
    li x2,10
    addi x1,x1,10
    bne x1,x2,FAIL

    #Testing add: case 2//
    addi x10,x10,1
    li x3,20
    add x1,x1,x2
    bne x1,x3,FAIL

    #Test and: case 3//
    addi x10,x10,1
    and x3,x3,x0
    bnez x3,FAIL

    #Test or: case 4//
    addi x10,x10,1
    li x3,10
    or x2,x2,x0
    bne x2,x3,FAIL

    #Test xor: case 5//
    addi x10,x10,1
    xor x2,x2,x3
    bnez x2,FAIL

    #Test sub: case 6//
    addi x10,x10,1
    li x2,10
    sub x2,x2,x3
    bnez x2,FAIL

    #Test sll: case 7//
    addi x10,x10,1
    li x2,170
    mv x5,x2
    li x3,2
    li x4,680
    sll x2,x2,x3
    bne x2,x4,FAIL

    #Test srl: case 8//
    addi x10,x10,1
    srl x2,x2,x3
    bne x2,x5,FAIL

    #Test slt: case 9//
    addi x10,x10,1
    li x2,1
    slt x6,x3,x5
    bne x6,x2,FAIL
    slt x6,x4,x5
    bnez x6,FAIL
    li x3,-1
    slt x6,x3,x0
    bne x6, x2,FAIL

    #Test sltu: case 10//
    addi x10,x10,1
    sltu x6,x3,x0
    bnez x6,FAIL

    #Test andi: case 11//
    addi x10,x10,1
    andi x4,x4,0
    bnez x4,FAIL

    #Test ori: case 12//
    addi x10,x10,1
    li x3,0x55
    li x2,0x50
    mv x4,x2
    ori x2,x2,0x05
    bne x2,x3,FAIL

    #Test xori: case 13//
    addi x10,x10,1
    xori x3,x3,5
    bne x3,x4,FAIL

    #Test slti: case 14//
    addi x10,x10,1
    li x4,1
    slti x7,x3,0x60
    bne x7,x4,FAIL
    slti x7,x3,0x45
    bnez x7,FAIL
    slti x7,x3,-1
    bnez x7,FAIL

    #Test sltiu: case 15//
    addi x10,x10,1
    sltiu x7,x3,-1
    bne x7,x4,FAIL

    #Test beq: case 16//
    addi x10,x10,1
    li x3,5
    mv x5,x3
    beq x5,x3,BEQ1
    bne x5,x3,FAIL


BEQ1:
    #Test bne: case 17//
    addi x10,x10,1
    bne x5,x4,BNE1
    beq x5,x4,FAIL


BNE1:
    #Test blt: case 18//
    addi x10,x10,1
    blt x4,x3,BLT1
    bgt x4,x3,FAIL
    beq x4,x3,FAIL


BLT1:
    #Test bgt: case 19//
    addi x10,x10,1
    bgt x3,x4,BGT1
    blt x3,x4,FAIL
    beq x3,x4,FAIL


BGT1:
    #Test bltu:case 20//
    addi x10,x10,1
    li x1,-1
    bltu x5,x1,BLTU1
    bgt x5,x1,FAIL
    beq x5,x1,FAIL


BLTU1:
    #Test bge: case 21//
    addi x10,x10,1
    bge x5,x1,BGE1
    blt x5,x1,FAIL


BGE1:
    #Test bgeu: case 22//
    addi x10,x10,1
    bgeu x1,x5,BGEU1
    blt x1,x5,FAIL


BGEU1:
    #Test slli: case 23//
    addi x10,x10,1
    li x3,0xAA
    mv x5,x3
    li x4,0x2A8
    slli x3,x3,2
    bne x3,x4,FAIL

    #Test srli: case 24//
    addi x10,x10,1
    srli x3,x3,2
    bne x3,x5,FAIL

    #Test jal: case 25//
    addi x10,x10,1
    jal x3,SUB_ROUTINE
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


#Set x20 to 1 if an instruction fails, instruction no. which failed is in x10//
FAIL:
    li x20,1
    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE:
    #Test jr: case 26//
    addi x10,x10,1
    jal x3,SUB_ROUTINE2

    #Test lw and sw: case 27//
    addi x10,x10,1
    sw x10, 1600(x0)
    lw x11, 1600(x0)
    bne x11,x10,FAIL


    #Test lbu and sb: case 28//
    addi x10,x10,1
    li x13,0xFF
    sb x13,1600(x0)
    lbu x14,1600(x0)
    bne x14,x13,FAIL

    #Test lhu and sh:case 29//
    addi x10,x10,1
    li x13,0x3FF
    sh x13,1600(x0)
    lhu x14,1600(x0)
    bne x14,x13,FAIL

    #Test lb: case 30//
    addi x10,x10,1
    li x13,0xFA
    sb x13,1600(x0)
    lb x15,1600(x0)
    andi x15,x15,0xFF
    bne x15,x13,FAIL

    #Test lh: case 31//
    addi x10,x10,1
    lui x14,0x0000F
    addi x14,x14,0x73A
    sh x14,1600(x0)
    lh x15,1600(x0)
    lui x16,0x0000F
    addi x16,x16,0x7FF
    addi x16,x16,0x7FF
    addi x16,x16,1
    and x15,x15,x16
    bne x15,x14,FAIL

    #Test li: case 32//
    addi x10,x10,1
    li x13,0xAB
    and x19,x19,x0
    addi x19,x19,0xAB
    bne x19,x13,FAIL

    #Test mv: case 33//
    addi x10,x10,1
    mv x14,x13
    bne x13,x14,FAIL

    #Test not: case 34//
    addi x10,x10,1
    lui x13,0xAAAAA
    addi x13,x13,0xAA
    lui x14,0x55555
    addi x14,x14,0x755
    addi x14,x14,0x7FF
    addi x14,x14,1
    not x14,x14
    bne x13,x14,FAIL

    #Test neg: case 35//
    addi x10,x10,1
    addi x13,x13,1
    not x14,x14
    neg x14,x14
    bne x13,x14,FAIL

    #Test seqz: case 36//
    addi x10,x10,1
    li x1,1
    seqz x5,x0
    bne x5,x1, FAIL

    #Test snez: case 37//
    addi x10,x10,1
    snez x6,x5
    bne x6,x1,FAIL
    snez x6,x0
    bnez x6,FAIL

    #Test sltz: case 38//
    addi x10,x10,1
    mv x2,x1
    neg x2,x2
    sltz x6,x2
    bne x6,x1,FAIL
    sltz x6,x1
    bnez x6,FAIL

    #Test sgtz: case 39//
    addi x10,x10,1
    sgtz x6,x1
    bne x6,x1,FAIL
    sgtz x6,x2
    bnez x6,FAIL

    #Test beqz: case 40//
    addi x10,x10,1
    beqz x0,SUB_ROUTINE3
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE3:
    #Test bnez: case 41//
    addi x10,x10,1
    bnez x1, SUB_ROUTINE4
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE4:
    #Test blez: case 42//
    addi x10,x10,1
    blez x2,SUB_ROUTINE5
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE5:
    blez x0,SUB_ROUTINE6
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE6:
    #Test bgez: case 43//
    addi x10,x10,1
    bgez x1, SUB_ROUTINE7
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE7:
    bgez x0,SUB_ROUTINE8
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE8:
    #Test bltz: case 44//
    addi x10,x10,1
    bltz x2,SUB_ROUTINE9
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE9:
    #Test bgtz: case 45//
    addi x10,x10,1
    bgtz x1,SUB_ROUTINE10
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE10:
    #Test ble: case 46//
    addi x10,x10,1
    ble x2,x1,SUB_ROUTINE11
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE11:
    #Test bgtu: case 47//
    addi x10,x10,1
    bgtu x2,x1,SUB_ROUTINE12
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE12:
    #Test bleu: case 48//
    addi x10,x10,1
    bleu x1,x2,SUB_ROUTINE13
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE13:
    #Test call: case 49//
    addi x10,x10,1
    call SUB_ROUTINE14
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE14:
    #Test ret: case 50//
    addi x10,x10,1
    call SUB_ROUTINE15
    j PASS
    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE15:
    ret
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


SUB_ROUTINE2:
    jr x3
    j FAIL

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop


PASS:
    addi x25,x25,1 #set x25 to 1 is all intsructions are working correctly

    nop
    nop
    nop
    add x0, x0, x0
    nop
    nop
    nop
