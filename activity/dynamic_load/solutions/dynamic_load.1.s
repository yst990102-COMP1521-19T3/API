.data
    GREET: .asciiz "Enter mips instructions as integers, -1 to finish:\n"
    START: .asciiz "Starting executing instructions\n"
    STOP:  .asciiz "Finished executing instructions\n"
.text
.globl main
main:
    sw $fp, -4($sp)
    la $fp, -4($sp)
    sw $ra, -4($fp) # $ra is the only register that we need after dynamic code
    la $sp, unsafe  # requisition $sp to point into the .text area

    li $v0, 4     # puts()
    la $a0, GREET
    syscall

next_input:
    li $v0, 5     # scanf("%d")
    syscall

    beq $v0, -1, end_input

    sw  $v0, 0($sp) # save the dynamic instruction into memory at the location pointed to by $sp
    la  $sp, 4($sp) # $sp ins't in the stack, it's in the text, so grow up not down

    j next_input
end_input:

    li $v0, 4     # puts()
    la $a0, START
    syscall

    jal unsafe # goto dynamic code, and allow dynamic code to return to here

    li $v0, 4    # puts()
    la $a0, STOP
    syscall

    lw  $ra, -4($fp) # $fp is assumed to be in the same place after dynamic code as it was before
    la  $sp,  4($fp)
    lw  $fp,   ($fp)
    jr  $ra
unsafe:
