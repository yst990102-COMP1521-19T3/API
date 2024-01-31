# read a line and print the first character of the line

main:
    la $a0, str0         # printf("Enter a line of input: ");
    li $v0, 4
    syscall

    la $a0, line
    la $a1, 256
    li $v0, 8            # fgets(buffer, 256, stdin)
    syscall              #

    la $a0, str1         # printf("First character was: ");
    li $v0, 4
    syscall

    la   $t0, line       # printf("%c", buffer[0]);
    lb   $a0, ($t0)
    li   $v0, 11
    syscall


    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    li $v0, 0            # return 0
    jr $31

.data
str0:
    .asciiz "Enter a line of input: "
str1:
    .asciiz "First character was: "


# line of input stored here
line:
    .space 256

