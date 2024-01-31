#  print the integers between x and y except 13
# x in $t0, y in $t1, i in $t2
main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    add $t2, $t0, 1     # i = x + 1;

loop:
    bge $t2, $t1, end   # while (i < y) {
    beq $t2, 13, skip   #   if (i != 13) {
    move $a0, $t2       #     printf("%d\n", i);
    li $v0, 1
    syscall
    li   $a0, '\n'      #     printf("%c", '\n');
    li   $v0, 11
    syscall
skip:                   #   }
    add $t2, $t2, 1     #   i = i + 1;
    b loop              # }

end:

    li $v0, 0           # return 0
    jr $31
