
# some test code which calls max
main:
    addi $sp, $sp, -4  # create stack frame
    sw   $ra, 0($sp)   # save return address

    la   $a0, array
    li   $a1, 10
    jal   max    #

    move  $a0, $v0     # printf ("%d")
    li    $v0, 1
    syscall

    li   $a0, '\n'     # printf("%c", '\n');
    li   $v0, 11
    syscall

                       # clean up stack frame
    lw   $ra, 0($sp)   # restore $ra
    addi $sp, $sp, 4   # restore sp

    li  $v0, 0         # return 0
    jr  $ra

# Recursive maximum of array function

# Register usage:
#   - `a' is in $a0
#   - `length' is in $a1
#   - `first_element' is in $s0
#   - `max_so_far' is in $t0

# s0 & s1 used for a and first_element because they need
# to keep their value across recursive call

max:
    # prologue
    addi  $sp, $sp, -8
    sw    $ra, 0($sp)
    sw    $s0, 4($sp)

    lw    $s0, ($a0)     # first_element = a[0]

    bne   $a1, 1, end1   # if (length == 1)
    move  $v0, $s0       #   return first_element;
    j     max_return
end1:                    # }

    addi  $a0, $a0, 4    # calculate &a[1]
    addi  $a1, $a1, -1   # length - 1
    jal   max            #
    move  $t0, $v0       # max_so_far = max(&a[1], length - 1);

    ble   $s0, $t0, end2 # if (first_element > max_so_far) {
    move  $t0, $s0
end2:

    move  $v0, $t0       # return max_so_far

max_return:
    # epilogue
    lw    $ra, 0($sp)
    lw    $s0, 4($sp)
    addi  $sp, $sp, 8
    jr    $ra



.data
array:
    .word 1 2 3 4 5 6 4 3 2 1
