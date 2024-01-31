# Read a number and print positive multiples of  7 or 11 < n

main:                   # int main(void) {
                        # int number, i;  number in $t0, i in $t1

    la $a0, prompt      # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", number);
    syscall
    move $t0, $v0

    li    $t1, 1        # i = 1;

loop:                   # loop:
    bge  $t1, $t0 end   # if (i >= number) goto end;

    rem $v0, $t1, 7     # if (i % 7 == 0) goto print
    beq $v0, 0, print

    rem $v0, $t1, 11    # if (i % 11 != 0) goto next
    bne $v0, 0, next

print:
    move $a0, $t1       # printf("%d" i);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

next:
    add  $t1, $t1, 1    # i = i + 1;

    b    loop           # goto loop;

end:
    jr   $ra            # return

    .data
prompt:
    .asciiz "Enter a number: "
