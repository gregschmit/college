.data

buffer:         .space 20
byte_array_X:   .byte -1, -2, -3, -4, -5
byte_array_Y:   .byte 0, 0, 0, 0, 0, 0, 0
int_array_A:    .word 2, -4, 7, 7, 97, -53, 0, 1
int_array_B:    .word -1, -1, -1, -1, -1, -1, -1, -1

prompt:         .asciiz "Enter a string and press enter: "
list_upper:     .asciiz "Here is the string, in uppercase: "

.text

# Part c)
li $v0, 4
la $a0, prompt
syscall
li $v0, 8
la $a0, buffer
li $a1, 20
syscall
la $t0, buffer
while_upperfy:
        lb $t1, ($t0)
        beq $t1, 10, while_upperfy_exit_n
        beq $t1, 0, while_upperfy_exit
        blt $t1, 97, if_upper_exit
        bgt $t1, 123, if_upper_exit
        subi $t1, $t1, 0x20
        sb $t1, ($t0)
        if_upper_exit:
        addi $t0, $t0, 1
        j while_upperfy
while_upperfy_exit_n:
li $t1, 0
sb $t1, ($t0)   # Replace /n with /0
while_upperfy_exit:
li $v0, 4
la $a0, list_upper
syscall
la $a0, buffer
syscall
