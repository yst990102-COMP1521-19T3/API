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

    la $s1,MEDIUM
    
    j if_end

    small:
    big:

    la $s1, OTHER

    if_end:

    move $a0, $s1
    li   $v0, 4
    syscall