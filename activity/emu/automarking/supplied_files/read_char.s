# read a char and print it

main:
    li   $v0, 12
    syscall
    move $a0, $v0
    li   $v0, 11
    syscall
    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall
    jr   $ra          # return
