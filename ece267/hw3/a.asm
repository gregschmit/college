.data

V1: .asciiz "ABCDE"
V2: .byte 5, -5, 0xAB
V3: .space 2
V4: .word -5, 0x10010004, 0x80000002

.text

la $t0, V1
addi $t0, $t0, 3
lb $t1, ($t0)
subi $t0, $t0, 1
lb $t1, ($t0)
addi $t0, $t0, 2
lb $t1, ($t0)
addi $t2, $t1, 2
sb $t2, ($t0)
lb $t1, ($t0) 
la $t0, V2
subi $t0, $t0, 2
lb $t1, ($t0)
addi $t0, $t0, 2
lb $t1, ($t0)
addi $t0, $t0, 1
lb $t2, ($t0)
addi $t0, $t0, 1
lb $t3, ($t0) 
la $t0, V4
lw $t4, 4($t0)
lw $t5, ($t4)
lw $t6, 8($t0)
lb $t7, 8($t0)
lw $t8, ($t0)

# add $t6, $t6, $t8
add $t7, $t7, $t8