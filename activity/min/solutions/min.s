#  print the minimum of two integers
# x in $t0, y in $t1
main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    bge $t0, $t1 else   # if (x < y) {
    move $a0, $t0       #   printf("%d\n", x);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    b end

else:

    move $a0, $t1       #   printf("%d\n", y);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

end:

    li $v0, 0           # return 0
    jr $31
