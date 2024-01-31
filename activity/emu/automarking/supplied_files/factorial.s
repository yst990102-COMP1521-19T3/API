### COMP1521 19t2 ... week 04 lab
### Compute factorials -- no functions (except main)


main:

    # code for main()
    li  $s0, 0      # n = 0

    la  $a0, msg1
    li  $v0, 4
    syscall         # printf("n  = ")

    li  $v0, 5
    syscall         # scanf("%d", into $v0)

    ### >>>>>
    move    $s0, $v0

    li  $s2, 1          # fac = 1

main_fac_init:
    li  $s1, 1          # i = 1
main_fac_cond:
    bgt $s1, $s0, main_fac_f    # i <= n  -->  if (i > n) break
    mul $s2, $s2, $s1       # fac = fac * i
main_fac_step:
    addi    $s1, $s1, 1     # i++
    j   main_fac_cond
main_fac_f:

    ### <<<<<

    la  $a0, msg2
    li  $v0, 4
    syscall         # printf("n! = ")

    move    $a0, $s2    # assume $s2 holds n!
    li  $v0, 1
    syscall         # printf("%d", fac)

    la  $a0, eol
    li  $v0, 4
    syscall         # printf("\n")

    jr  $ra     # return 0

    .data
msg1:   .asciiz "n  = "
msg2:   .asciiz "n! = "
eol:    .asciiz "\n"

