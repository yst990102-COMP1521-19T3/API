# i in register $t1
# j in register $t2
main:
    li $t1, 1           # i = 1
loop0:
    bgt $t1, 10, end0   # if (i > 10) goto end0;

    li $t2, 0           # j = 0
loop1:
    bge $t2, $t1, end1  # if (j >= i) goto end1;

    li   $a0, '*'       # printf("%c", '*');
    li   $v0, 11
    syscall

    add $t2, $t2, 1     # j++

    b loop1
end1:

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t1, $t1, 1     # i++

    b loop0

end0:
    jr $31
