.data
    GREET: .asciiz "Enter a number: "
    ERROR: .asciiz "square too big for 32 bits\n"
.text
.globl main
main:
    la $a0, GREET
    li $v0, 4
    syscall
    
    li $v0, 5
    syscall
    move $s0, $v0

    li  $t0, 46340
    ble $s0, $t0, if_else

    la $a0, ERROR
    li $v0, 4
    syscall
    j if_end 

    if_else:

    mul  $s1, $s0, $s0
    move $a0, $s1
    li   $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall

    if_end:

    jr $ra