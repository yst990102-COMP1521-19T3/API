# print the square of a number
main:                       # x,y in $t0, $t1
    la $a0, prompt          # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5               # scanf("%d", x);
    syscall
    move $t0, $v0

    ble $t0, 46340, square  # if (x <= 46340) goto square;

    la $a0, too_big         # printf("square too big for 32 bits\n");
    li $v0, 4
    syscall

    b end                   # goto end;

square:
    mul $t1, $t0, $t0       # y = x * x

    move $a0, $t1           # printf("%d", y);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
end:
    jr   $ra                # return

    .data
prompt:
    .asciiz "Enter a number: "
too_big:
    .asciiz "square too big for 32 bits\n"
