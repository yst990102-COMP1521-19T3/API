# row in $t0, col in $t1
main:
    li   $t0, 0         # for (int row = 0; row < 6; row++) {

loop1:
    bge  $t0, 6, end1
    li   $t1, 0         # for (int col = 0; col < 12; col++) {

loop2:
   beq  $t1, 12, end2   # printf("%c", flag[row][col])
   mul  $t2, $t0, 12    # convert [row][col] to byte offset
   add  $t3, $t2, $t1
   la   $t4, flag
   add  $t5, $t3, $t4
   lb   $a0, ($t5)
   li   $v0, 11
   syscall

   addi $t1, $t1, 1    # col++
   j    loop2

end2:
   li   $a0, '\n'      # printf("%c", '\n')
   li   $v0, 11
   syscall
   addi $t0, $t0, 1    # row++
   j    loop1
end1:

    li  $v0, 0         # return 0
    jr  $ra

.data
flag:
    .byte '#' '#' '#' '#' '#' '.' '.' '#' '#' '#' '#' '#'
    .byte '#' '#' '#' '#' '#' '.' '.' '#' '#' '#' '#' '#'
    .byte '.' '.' '.' '.' '.' '.' '.' '.' '.' '.' '.' '.'
    .byte '.' '.' '.' '.' '.' '.' '.' '.' '.' '.' '.' '.'
    .byte '#' '#' '#' '#' '#' '.' '.' '#' '#' '#' '#' '#'
    .byte '#' '#' '#' '#' '#' '.' '.' '#' '#' '#' '#' '#'
