.data

s_rprompt:      .asciiz "Enter the number system radix (1<r<16): "
s_prompt:       .asciiz "Please enter a number: "
s_x:            .asciiz "x="
s_y:            .asciiz "y="
s_z:            .asciiz "z="
s_has:          .asciiz " has "
s_digits:       .asciiz " digits\n"
s_backwards:    .asciiz " is x backwards\n"
s_compliment:   .asciiz " is -x in r's compliment\n"
s_plus:         .asciiz " +"
s_minus:        .asciiz " -"
s_equal:        .asciiz " ="
s_p:            .asciiz " p"
s_n:            .asciiz " n"
s_correct:      .asciiz " correct\n"
s_wrong:        .asciiz " wrong\n"

r:              .space 4
max_digvalue:   .space 4
x:              .space 4
d:              .space 4
y:              .space 4
z:              .space 4
 
radix:          .space 1
number:         .space 11
numberback:     .space 11

.text

# Prompt user and get input string
li $v0, 4
la $a0, rprompt
syscall
li $v0, 5
syscall
sw $v0, r
li $v0, 4
la $a0, prompt
syscall
li $v0, 8
la $a0, number
li $a1, 11
syscall

# Set max_digvalue based on radix
lw $t0, r
ble $t0, 10, if_less10_true
        j if_less10_else
        if_less10_true:
                addi $t0, $t0, 47
                j if_less10_exit
        if_less10_else:
                addi $t0, $t0, 86
if_less10_exit:
sw $t0, max_digvalue

# Sanity check on string (numbers, letters, ending NULL)
li $t0, 0
while_sanity:
        # $t0:  counter for string position
        # $t1:  value holder for current character
        # $t2:  boolean to set if we need to numberfy

        # Set char holder
        lb $t1, number($t0)

        # Test for end of string
        beq $t1, 0, while_sanity_exit
        beq $t1, 10, while_sanity_exit  # string smaller than buffer, so add LF

        # upper to lower conversion (0x41-5A, add 0x20)
        bge $t1, 0x41, if_lowerify_true
                j if_lowerify_exit
                if_lowerify_true:
                        ble $t1, 0x5A, if_lowerify_and_true
                        j if_lowerify_exit
                if_lowerify_and_true:
                        addi $t1, $t1, 0x20
                        sb $t1, number($t0)
        if_lowerify_exit:

        # set boolean flag if char 0x30-39 or 0x61-7a, and less than max digit
        # $t3: tmp for max digit
        lw $t3, max_digvalue
        bge $t1, 0x30, if_bnumberfy_first_true
                j if_bnumberfy_false
                if_bnumberfy_first_true:
                        ble $t1, 0x7a, if_bnumberfy_and_true
                        j if_bnumberfy_false
                if_bnumberfy_and_true:
                        ble $t1, 0x39, if_bnumberfy_and2_true
                        bge $t1, 0x61, if_bnumberfy_and2_true
                        j if_bnumberfy_false
                if_bnumberfy_and2_true:
                        ble $t1, $t3, if_bnumberfy_true
                        j if_bnumberfy_false
                if_bnumberfy_true:
                        li $t2, 1
                        j if_bnumberfy_exit
                if_bnumberfy_false:
                        li $t2, 0
        if_bnumberfy_exit:
        li $t3, 0


        # $t3:  counter for string shift position lo
        # $t4:  counter for string shift position hi
        # $t5:  value holder for string shift position hi
        beq $t2, 1, if_numberfy_exit
                move $t3, $t0
                move $t4, $t0
                addi $t4, $t4, 1
                li $t5, 0
                lb $t5, number($t3)
                while_shift:
                        beq $t5, 0, while_shift_exit
                        beq $t5, 10, while_shift_exit
                        lb $t5, number($t4)
                        sb $t5, number($t3)
                        addi $t3, $t3, 1
                        addi $t4, $t4, 1
                        j while_shift
                while_shift_exit:
                subi $t0, $t0, 1
        if_numberfy_exit:
        addi $t0, $t0, 1
        j while_sanity
while_sanity_exit:
sb $zero, number($t0)   # ensure ending NULL

### TEST ONLY - print string
#li $v0, 11
#li $a0, 10
#syscall

#li $v0, 4
#la $a0, number
#syscall
### TEST END

# count digits (2, use 5 and up for tmp)
li $t0, 0
li $t1, 0
li $t2, 0
while_count:
        lb $t1, number($t0)
        beq $t1, 0, while_count_end
        addi $t2, $t2, 1
        addi $t0, $t0, 1
        j while_count
while_count_end:
sw $t2, d

# Print d
li $v0, 4
la $a0, x
syscall
la $a0, number
syscall
la $a0, has
syscall
li $v0, 1
move $a0, $t2
syscall
li $v0, 4
la $a0, digits
syscall

# build numberback
move $t5, $t2
li $t6, 0
sb $zero, numberback($t5)
subi $t5, $t5, 1
li $t7, 0
while_reversify:
        blt $t5, 0, while_reversify_exit
        lb $t7, number($t6)
        sb $t7, numberback($t5)
        subi $t5, $t5, 1
        addi $t6, $t6, 1
        j while_reversify
while_reversify_exit:
li $v0, 11
li $a0, 10
syscall
li $v0, 4
la $a0, number
syscall
li $v0, 11
li $a0, 10
syscall
li $v0, 4
la $a0, numberback
syscall

# Parse number and numberback as integer (x) and (y)

# Print y

# Model the 10's compliment of x, in d-digits (z)

# Print z

end:
li $v0, 10
syscall
