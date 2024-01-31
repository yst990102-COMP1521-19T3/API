.data
.align 2
    SPACE: .space 100
.text
main:
    la $t0, SPACE

    li $t1, '8'
    sb $t1, 9($t0)
    lb $t2, 9($t0)
    bne $t1, $t2 panic

    li $t1, 180
    sh $t1, 32($t0)
    lh $t2, 32($t0)
    bne $t1, $t2 panic

    li $t1, 9999999
    sw $t1, 80($t0)
    lw $t2, 80($t0)
    bne $t1, $t2 panic

    li $a0, 0
    li $v0, 1
    syscall
end:

    li $a0, 10
    li $v0, 11
    syscall

    jr $ra

panic:
    li $a0, 1
    li $v0, 1
    syscall
    j end