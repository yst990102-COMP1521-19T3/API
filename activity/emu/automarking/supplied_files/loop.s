main:                 # int main(void) {
                      # int i;  // in register $t0

    li    $t0, 24     # i = 24;

loop:                 # loop:
    bge  $t0, 42 end  # if (i > 10) goto end;

    move $a0, $t0     #   printf("%d" i);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    add  $t0, $t0 3   #   i += 3;

    b    loop         # goto loop;

end:
    jr   $ra          # return
