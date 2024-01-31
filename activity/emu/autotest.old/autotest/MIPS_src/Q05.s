.text
.globl main
main:
    li $s0, 24

    loop_start:
    li  $t0, 42
    bge $s0, $t0, loop_end

    move $a0, $s0
    li   $v0, 1
    syscall
    addi $s0, $s0, 3
    j loop_start

    loop_end:

    jr $ra