#include <stdint.h>

#include "instructions.h"

#ifndef ASS1__IMPLEMENTATIONS_H
#define ASS1__IMPLEMENTATIONS_H

int implementation_ADD(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_ADDI(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_SUB(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_MUL(uint32_t op, instruction_info i, uint32_t *pc);

/*
int implementation_ADDU(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_ADDIU(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_SUBU(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_MULT(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_MULTU(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_DIV(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_DIVU(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_MFHI(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_MTHI(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_MFLO(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_MTLO(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_SLTU(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_SLTIU(uint32_t op, instruction_info i, uint32_t *pc);
*/

int implementation_AND(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_ANDI(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_OR(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_ORI(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_XOR(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_XORI(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_SLL(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_SLLV(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_SRL(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_SRLV(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_SLT(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_SLTI(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_LUI(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_LB(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_LH(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_LW(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_SB(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_SH(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_SW(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_BEQ(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_BNE(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_BLEZ(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_BGTZ(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_BLTZ(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_BGEZ(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_J(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_JAL(uint32_t op, instruction_info i, uint32_t *pc);
int implementation_JR(uint32_t op, instruction_info i, uint32_t *pc);

int implementation_SYSCALL(uint32_t op, instruction_info i, uint32_t *pc);

#endif //ASS1__IMPLEMENTATIONS_H
