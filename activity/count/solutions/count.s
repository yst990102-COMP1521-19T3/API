# COMP1521 lab sample solution
# read a number n and print the integers 1..n one per line

main:                           # int main(void) {
    # number in $t0; i in $t1

    la  $a0, prompt             # printf("Enter a number: ");
    li  $v0, 4
    syscall

    li  $v0, 5                  # scanf("%d", number);
    syscall
    move    $t0, $v0

    li  $t1, 1

loop:                           # loop:
    bgt $t1, $t0, end           # if ($t1 > $t0) goto end;

    move $a0, $t1               # printf("%d", i);
    li  $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $t1, $t1, 1            # i = i + 1
    b   loop                    # goto loop;

end:
    jr  $ra                     # return

    .data
prompt:
    .asciiz "Enter a number: "
