.data

prompt: .asciiz "please input a char and press 'enter':"
asc: .asciiz "ASCII="
upper: .asciiz " uppercase\n\n"
lower: .asciiz " lowercase\n\n"
not: .asciiz " not an alphabet\n\n"

.text

# t0 stores the input char

start:

# display prompt
li $v0, 4
la $a0, prompt
syscall

# get input char
li $v0, 12
syscall
move $t0, $v0

li $v0, 4
la $a0, asc
syscall
li $v0, 1
move $a0, $t0
syscall
li $v0, 11
li $a0, 32
syscall

bge $t0, 65, if_test_true
elseif_test:
bge $t0, 97, elseif_test_true
j else_test
        if_test_true:
                ble $t0, 90, if_test_and_true
                j elseif_test
                if_test_and_true:
                        la $a0, upper
                        j if_test_exit
        elseif_test_true:
                ble $t0, 122, elseif_test_and_true
                j else_test
                elseif_test_and_true:
                        la $a0, lower
                        j if_test_exit
        else_test:
                la $a0, not
if_test_exit:

li $v0, 4
syscall

j start

end:
li $v0, 10
syscall
