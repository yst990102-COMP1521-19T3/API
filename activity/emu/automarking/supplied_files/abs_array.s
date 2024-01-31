# i in register $t0
main:

    li $t0, 1            # i = 1
loop2:
    bge $t0, 10, end2    # while (i < 10) {

    mul $t1, $t0, 4      #
    la $t2, numbers      #
    add $t3, $t1, $t2    #   $t3 = &numbers[i]
    lw $t5, ($t3)        #   $t5 = numbers[i]


    bge $t5, 0, skip2    #   if (numbers([i]) < 0) {
    add $t5, $t5, 42     #     numbers[i] += 42
    sw $t5, ($t3)        #
                         #   }
skip2:
    add $t0, $t0, 1      #   i++;
    b loop2              # }
end2:


    jr $31              # return

.data

numbers:
    .word 0 1 2 -3 4 -5 6 -7 8 9  # int numbers[10] = {0,1,2,-3,4,-5,6,-7,8,9};

