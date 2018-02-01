# find the third largest number in an array

.data
third_largest_value: .word 0x80000000
third_largest_index: .word -1
large_index: .word -1 -1 -1
#              10010008 0c 10
Array1ByteCount: .word 40
Array1: .word 200, -3, 15, 9, -1200, 45, 0, 6, 12, -2
#        10010018 1c   20    ...   ..2c    ...     3c

.text
f_thirdlarge:
  lui $t0, 0x1001   # start of .data
  addi $t1, $t0, 24 # address of array
  and $t2, $t2, $0       # do_three loop counter
  addi $t2, $t2, 8
  addi $t4, $t0, 8   # array of largest indices
  # do this process three times
  do_three:
    lw $t5, 20($t0) # set array count
    add $t5, $t5, $t1 # offset t5 to one past array
    lui $t3, 0x8000    # value of largest so far known (init smallest possible)
    do_arrcount:
      addi $t5, $t5, -4
      # pull value and see if it is larger than the last largest
      lw $t6, 0($t5)
      if_large:
      slt $t7, $t6, $t3 # (t7 = 1 iff t6 < t3)
      bne $t7, $0, skip_if_large
        # check to see if this index is already logged
        lw $t7, 0($t4)
        beq $t7, $t5, skip_if_indexed
        lw $t7, 4($t4)
        beq $t7, $t5, skip_if_indexed
        lw $t7, 8($t4)
        beq $t7, $t5, skip_if_indexed
          # this item is large and not indexed, record it!
          addi $t3, $t6, 0 # recording value
          add $t6, $t4, $t2 # getting spot in large_index array
          sw $t5, 0($t6) # storing pointer to large item in large_index position
        skip_if_indexed:
      skip_if_large:
      bne $t5, $t1, do_arrcount # (if data array pointer is not at beginning)
    addi $t2, $t2, -4 # (t2 goes 8 4 0 -4)
    slt $t3, $t2, $0
    beq $t3, $0, do_three
end_f_thirdlarge:
lw $t2, 0($t4) # t4 is address of third largest
lw $t3, 0($t2) # deref t4
sw $t3, 0($t0) # push value to memory
sub $t2, $t2, $t1
and $t3, $t3, $0
while_not_zero:
  addi $t2, $t2, -4
  addi $t3, $t3, 1
  bne $t2, $0, while_not_zero
sw $t3, 4($t0)
