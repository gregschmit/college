.data

buffer:         .space 20
byte_array_X:   .byte -1, -2, -3, -4, -5
byte_array_Y:   .byte 0, 0, 0, 0, 0, 0, 0
int_array_A:    .word 2, -4, 7, 7, 97, -53, 0, 1
int_array_B:    .word -1, -1, -1, -1, -1, -1, -1, -1

prompt:         .asciiz "Enter a character and press enter: "
list_upper:     .asciiz "Here are the uppercase letters in that array: "

.text

# Part a)
li $t0, 0
la $t1, byte_array_X
for_input5:
        bge $t0, 5, for_input5_exit
        li $v0, 4
        la $a0, prompt
        syscall
        li $v0, 12
        syscall
        sb $v0, ($t1)
        addi $t0, $t0, 1
        addi $t1, $t1, 1
        j for_input5
for_input5_exit:
li $v0, 4
la $a0, list_upper
syscall
li $t0, 0
la $t1, byte_array_X
for_print5:
        bge $t0, 5, for_print5_exit
        lb $t2, ($t1)
        blt $t2, 65, if_upperprint_exit
        bgt $t2, 90, if_upperprint_exit
        li $v0, 11
        move $a0, $t2
        syscall
        if_upperprint_exit:
        addi $t0, $t0, 1
        addi $t1, $t1, 1
        j for_print5
for_print5_exit:
