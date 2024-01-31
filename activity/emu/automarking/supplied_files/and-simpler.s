main:                       # x in $t0, message in $t1
    la $a0, prompt          # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5               # scanf("%d", x);
    syscall
    move $t0, $v0

    la $t1, small_big_str   # message = "small/big\n";
    ble $t0, 100, end       # if (x <= 100) goto small_big;
    bge $t0, 1000, end      # if (x >= 1000) goto small_big;

    la $t1, medium_str      # printf("medium\n");

end:
    move $a0, $t1           # printf("%s", message);
    li   $v0, 4
    syscall

    jr   $ra                # return

    .data
prompt:
    .asciiz "Enter a number: "
medium_str:
    .asciiz "medium\n"
small_big_str:
    .asciiz "small/big\n"
