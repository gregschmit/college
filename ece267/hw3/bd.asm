.data

buffer:         .space 20
byte_array_X:   .byte -1, -2, -3, -4, -5
byte_array_Y:   .byte 0, 0, 0, 0, 0, 0, 0
int_array_A:    .word 2, -4, 7, 7, 97, -53, 0, 1
int_array_B:    .word -1, -1, -1, -1, -1, -1, -1, -1

large:          .asciiz "largest: A["
close:          .asciiz "]="
small:          .asciiz " smallest: A["
close2:         .asciiz "]\n"

.text

# Part d)
li $t0, 0
la $t1, int_array_A
lw $t3, int_array_A     # max val
li $t4, 0               # max index
lw $t5, int_array_A     # min val
li $t6, 0               # min index
for_8extrema:
        lw $t2, ($t1)
        bge $t0, 8, for_8extrema_exit
        ble $t2, $t3, if_max_exit
                move $t3, $t2
                move $t4, $t0
        if_max_exit:
        bge $t2, $t5, if_min_exit
                move $t5, $t2
                move $t6, $t0
        if_min_exit:
        addi $t0, $t0, 1
        addi $t1, $t1, 4
        j for_8extrema
for_8extrema_exit:
li $v0, 4
la $a0, large
syscall
li $v0, 1
move $a0, $t3
syscall
li $v0, 4
la $a0, close
syscall
la $a0, small
syscall
li $v0, 1
move $a0, $t5
syscall
li $v0, 4
la $a0, close2
syscall
