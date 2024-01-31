.data
    GREET: .asciiz "Enter a number: "
.text
.globl main
main:
    la $a0, GREET
    li $v0, 4
    syscall

    li $v0, 5
    syscall
    move $s0, $v0

    mul $s1, $s0, $s0

    move $a0, $s1
    li   $v0, 1
    syscall

    li $a0, '\n'
    li $v0, 11
    syscall

    jr $ra
