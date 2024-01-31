main:
    la $t0, dynamic_code # t0 contains the address we store the next instruction

    la $a0, prompt      # printf("Enter mips instructions as integers, -1 to finish");
    li $v0, 4
    syscall

loop:
    li $v0, 5            # scanf("%d", &numbers[i]);
    syscall              #
    beq $v0, -1, end     #
    sw $v0, ($t0)        # store entered number in  extra_code
    add $t0, $t0, 4      # next location to store an instruction
    b loop

end:
    li $v0, 65011720     # store jr $ra at finish of extra_code
    sw $v0, ($t0)        # in case execution reaches there

    la $a0, start        # printf("Starting executing instructions\n");
    li $v0, 4
    syscall

    move $s0, $ra        # save our return address in s0

    la $t0, dynamic_code # jump to the code we've read in
    jal $t0

    la $a0, finish       # printf("Finished executing instructions\n");
    li $v0, 4
    syscall

    jr $s0               # return using saved return address in $s0

dynamic_code:            # the code segment in SPIM is write-able allowing
.space 4096              # us to write instruction here to be executed
                         # often code segments are configured to be read-only
                         #
                         # we can't put the code in the data segment
                         # because that is configured to be not executable on SPIM
                         # and this is typical to avoid security exploits & weird bugs
.data

prompt:
    .asciiz "Enter mips instructions as integers, -1 to finish:\n"
start:
    .asciiz "Starting executing instructions\n"
finish:
    .asciiz "Finished executing instructions\n"
