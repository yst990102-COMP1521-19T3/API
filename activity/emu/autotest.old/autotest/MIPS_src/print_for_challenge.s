# print a string without using pre-initialized data
# for the dynamic load challenge exercise

main:
    li $a0, 0x10000000    # printf("hi\n"); without using pre-initialized data
    li $v0, 0x000a6948    # 0x000a6948 = ascii codes for '\0' '\n' 'i' 'H'
    sw $v0, ($a0)         # assuming little-endian word layout
    li $v0, 4             # also assumes address  0x10000000 is available to use
    syscall
    jr $ra
.data
    .space 40
    .asciiz "Hi\n"