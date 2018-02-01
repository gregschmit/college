.text

L_1:

li $v0, 5
syscall

addi $a0, $v0, -3

li $v0, 1
syscall

# add a newline to make this better, and preserve all memory states (assuming s0 is null)
move $s0, $a0
li $a0, 10
li $v0, 11
syscall
move $a0, $s0
li $s0, 0

j L_1
