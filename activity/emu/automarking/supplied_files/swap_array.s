# i in register $t0, x in $t4, y in $t8
main:

    # assume there is code here to assign values to the array

    li $t0, 0            # i = 0
loop2:
    bge $t0, 5, end2     # while (i < 5) {

    mul $t1, $t0, 4      #
    la $t2, numbers      #
    add $t3, $t1, $t2    #   $t3 = &numbers[i]
    lw $t4, ($t3)        #   x = numbers[i]

    li $t5, 9            #   $t5 = 9 - i
    sub $t5, $t5, $t0    #
    mul $t6, $t5, 4      #
    add $t7, $t6, $t2    #   $t7 = &numbers[9 - i]
    lw $t8, ($t7)        #   y = numbers[9 - i]


    sw $t8, ($t3)        #   numbers[i] = y
    sw $t4, ($t7)        #   numbers[9 - i] = x

    add $t0, $t0, 1      #   i++;
    b loop2              # }
end2:


    jr $31              # return

.data

numbers:
     .word 0 1 2 3 4 5 6 7 8 9  # int numbers[10] = {0,1,2,3,4,5,6,7,8,9};

