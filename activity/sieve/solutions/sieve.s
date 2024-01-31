# i in register $t0
# j in register $t1
# registers $t2, $t3, $t4 used to hold temporary results

main:
    li $t0, 0            # i = 0;
loop0:
    bge  $t0, 1000, end0 # while (i < 1000) {
    la   $t2, prime      #   calculate &prime[i]
    add  $t3, $t2, $t0   #
    li   $t4, 1
    sb   $t4, ($t3)      #   prime[i] = 1

    add $t0, $t0, 1      #   i++;
    b loop0              # }
end0:

    li $t0, 2            # i = 2;
loop1:
    bge $t0, 1000, done  # while (i < 1000) {

    la $t2, prime        #   calculate &prime[i]
    add $t3, $t2, $t0    #
    lb $t4, ($t3)        #   load prime[i] into $t3
    bne $t4, 1, end2     #   if (prime[i]) {

    move $a0, $t0        #     printf("%d", i);
    li $v0, 1
    syscall

    li   $a0, '\n'       #     printf("%c", '\n');
    li   $v0, 11
    syscall

    mul $t1, $t0, 2      #     j = 2 * i;
loop2:
    bge $t1, 1000, end2  #     while (j < 1000) {
    la $t2, prime        #       calculate &prime[j]
    add $t3, $t2, $t1    #
    sb $0, ($t3)         #        prime[j] = 0

    add $t1, $t1, $t0    #       j = j + i;
    b loop2              #     }
end2:                    #   }
    add $t0, $t0, 1      #   i++;
    b loop1              # }

done:
    li $v0, 0            # return 0
    jr $31

    .data
prime:
    .space 1000
