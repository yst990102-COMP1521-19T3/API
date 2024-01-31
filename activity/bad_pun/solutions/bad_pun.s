#
# COMP1521 lab exercise sample solution
#
# A simple MIPS program that attempts to be punny
# Written 2/10/2019
# by Andrew Taylor (andrewt@unsw.edu.au)

main:
    la   $a0, string  # get address of string
    li   $v0, 4       # 4 is print string syscall
    syscall

    jr   $ra          # return

    .data
string:
    .asciiz "I MIPS you!\n"
