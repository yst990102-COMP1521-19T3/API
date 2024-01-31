.data
    STRING: .space 50
.text
main:
    la $a0, STRING
    li $a1, 50
    li $v0, 8
    syscall

    move $t0, $a0
loop:
    lb $a0, ($t0)
    beqz $a0, end_loop
    li $v0, 11
    syscall
    addi $t0, $t0, 1
    b loop
end_loop:

    la $a0, STRING
    li $v0, 4
    syscall

    jr $ra
