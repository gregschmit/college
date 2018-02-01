.data

instruc: .asciiz "Please enter an integer and press 'enter' twice, for rows and cols.\n"
r: .asciiz "r="
c: .asciiz "c="

.text

# t0, t1 are rows and cols
# t2, t3 are rows and cols loop counters
# t4 is char counter
# t5, t6 are asterisk counters

# print instruction line
li $v0, 4
la $a0, instruc
syscall

# get r
li $v0, 4
la $a0, r
syscall
li $v0, 5
syscall
move $t0, $v0

# get c
li $v0, 4
la $a0, c
syscall
li $v0, 5
syscall
move $t1, $v0

# set asterisk counters
li $t6, 0
move $t5, $t0
ble $t5, $t1, if_asterisk_exit
        move $t5, $t1
if_asterisk_exit:

# zero check
ble $t0, 0, end
ble $t1, 0, end

li $t2, 0
li $t4, 65
dowhile_rows:
        li $t3, 0
        move $t6, $t2
        while_offset:
                blt $t6, $t5, while_offset_exit
                sub $t6, $t6, $t5
                j while_offset
        while_offset_exit:
        dowhile_cols:
                li $v0, 11
                move $a0, $t4
                bge $t6, 1, if_asteriskify_exit
                        li, $a0, 42
                        add, $t6, $t6, $t5
                if_asteriskify_exit:
                syscall
                li $v0, 11
                li $a0, 32
                syscall
                addi $t3, $t3, 1
                addi $t4, $t4, 1
                addi $t6, $t6, -1
                blt $t4, 91, if_alphabet_wrap_back_exit
                        li $t4, 65
                if_alphabet_wrap_back_exit:
        blt $t3, $t1, dowhile_cols
        li $v0, 11
        li $a0, 10
        syscall
        addi $t2, $t2, 1
blt $t2, $t0, dowhile_rows

end:

li $v0, 10
syscall
