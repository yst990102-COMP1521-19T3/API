# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

# i in register $t0
# j in register $t1
# n in register $t2
# total in register $t3
# how_many in register $t4

main:

    la $a0, prompt      # printf("Enter how many: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", number);
    syscall
    move $t4, $v0

    li $t2, 1           # n = 1;

loop0:
    bgt $t2, $t4, end0  # while (n <= how_many) {
    li $t3, 0           # total = 0
    li $t1, 0           # j = 1
loop1:
    bgt $t1, $t2, print # while (j <= n) {
    li $t0, 1           # i = 1

loop2:
    bgt $t0, $t1, next  # while (i <= j) {
    add $t3, $t3, $t0   # total = total + i
    add $t0, $t0, 1     # i = i + 1
    b loop2

next:
    add $t1, $t1, 1     # j = j + 1
    b loop1

print:
    move $a0, $t3       # printf("%d", total);
    li $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t2, $t2, 1     # n = n + 1
    b loop0
end0:

    jr   $ra            # return

    .data
prompt:
    .asciiz "Enter how many: "
