main:
    move $a0, $sp
    li   $v0, 1
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

    move $a0, $fp
    li   $v0, 1
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

    move $a0, $gp
    li   $v0, 1
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

    move $a0, $ra
    li   $v0, 1
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

    jr $ra
