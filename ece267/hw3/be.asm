.data

buffer:         .space 20
byte_array_X:   .byte -1, -2, -3, -4, -5
byte_array_Y:   .byte 0, 0, 0, 0, 0, 0, 0
int_array_A:    .word 2, -4, 7, 7, 97, -53, 0, 1
int_array_B:    .word -1, -1, -1, -1, -1, -1, -1, -1

.text

# Part e)
li $t0, 0
la $t1, int_array_A
la $t2, int_array_B
li $t4, -1      # const -1
for_8copy:
        lb $t3, ($t1)
        bge $t0, 8, for_8copy_exit
        bge $t3, 0, if_neg_exit
                mult $t3, $t4
                mflo $t3
        if_neg_exit:
        sb $t3, ($t2)
        addi $t0, $t0, 1
        addi $t1, $t1, 4
        addi $t2, $t2, 4
        j for_8copy
for_8copy_exit:
