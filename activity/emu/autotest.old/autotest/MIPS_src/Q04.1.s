.data
    GREET:  .asciiz "Enter a number: "
    MEDIUM: .asciiz "medium\n"
    OTHER:  .asciiz "small/big\n"
.text
.globl main
main:
    la $a0, GREET
    li $v0, 4
    syscall

    li $v0, 5
    syscall
    move $s0, $v0

    li  $t0, 100
    ble $s0, $t0, small

    li  $t0, 1000
    bge $s0, $t0, big

    la $a0, MEDIUM
    li $v0, 4
    syscall
    
    j if_end

    small:;
    big:;

    la $a0, OTHER
    li $v0, 4
    syscall

    if_end:;

    jr $ra