main:                       # x in $t0
    la $a0, prompt          # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5               # scanf("%d", x);
    syscall
    move $t0, $v0

    ble $t0, 100, small_big  # if (x <= 100) goto small_big;
    bge $t0, 1000, small_big # if (x >= 1000) goto small_big;

    la $a0, medium_str       # printf("medium\n");

    li $v0, 4
    syscall

    b end                   # goto end;

small_big:
    la   $a0, small_big_str #printf("small/big\n");
    li   $v0, 4
    syscall
end:
    jr   $ra                # return

    .data
prompt:
    .asciiz "Enter a number: "
medium_str:
    .asciiz "medium\n"
small_big_str:
    .asciiz "small/big\n"
