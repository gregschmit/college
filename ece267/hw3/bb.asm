.data

buffer:         .space 20
byte_array_X:   .byte -1, -2, -3, -4, -5
byte_array_Y:   .byte 0, 0, 0, 0, 0, 0, 0
int_array_A:    .word 2, -4, 7, 7, 97, -53, 0, 1
int_array_B:    .word -1, -1, -1, -1, -1, -1, -1, -1

prompt:         .asciiz "Enter a number and press enter: "
list_neg:       .asciiz "Here are the negative values printed backwards: "

.text

# Part b)
li $t0, 0
la $t1, byte_array_Y
for_input7:
        bge $t0, 7, for_input7_exit
        li $v0, 4
        la $a0, prompt
        syscall
        li $v0, 5
        syscall
        sb $v0, ($t1)
        addi $t0, $t0, 1
        addi $t1, $t1, 1
        j for_input7
for_input7_exit:
li $v0, 4
la $a0, list_neg
syscall
li $t0, 0
la $t1, byte_array_Y
addi $t1, $t1, 7
for_print7:
        bge $t0, 7, for_print7_exit
        lb $t2, ($t1)
        bge $t2, 0, if_negprint_exit
        li $v0, 1
        move $a0, $t2
        syscall
        if_negprint_exit:
        addi $t0, $t0, 1
        subi $t1, $t1, 1
        j for_print7
for_print7_exit:
