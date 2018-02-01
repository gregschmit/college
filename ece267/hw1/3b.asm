.text

l1:

li $v0, 5
syscall

move $a0, $v0

li $v0, 11
syscall
li $a0, 10
syscall

j l1
