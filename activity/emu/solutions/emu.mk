include ../files.cp/emu.mk

SRCS.emu	+= instructions.c implementations.c syscalls.c meta_mips_defs.c
emu:			${SRCS.emu}
instructions.o:		instructions.c instructions.h implementations.h registers.h
implementations.o:	implementations.c registers.h instructions.h implementations.h syscalls.h
syscalls.o:		syscalls.c syscalls.h registers.h ram.h
meta_mips_defs.o:	meta_mips_defs.c instructions.h implementations.h

