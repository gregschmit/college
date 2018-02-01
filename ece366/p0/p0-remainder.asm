# compute the remainder of a division operation

.data
A: .word 5250
B: .word 5235
R: .word -1

.text
f_rem:
  lui $t0, 0x1001
  lw $t1, 0($t0)
  lw $t2, 4($t0)
  # check if B is 0, if so, return -1
  beq $t2, $0, divzero
  # normal subtraction loop
  loop_sub:
    # check if A is less than B, if so, a is returned
    slt $t3, $t1, $t2
    bne $t3, $0, end_loop_sub
    # otherwise, subtract B from A -> A
    sub $t1, $t1, $t2
    j loop_sub
  end_loop_sub:
  sw $t1, 8($t0)
  j end_f_rem
  divzero:
  addi $t1, $0, -1
  sw $t1, 8($t0)
  j end_f_rem
end_f_rem:
