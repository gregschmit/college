.text

L1:

li $v0, 12
syscall

move $a0, $v0
li $v0, 1
syscall

li $a0, 10
li $v0, 11
syscall

j L1
