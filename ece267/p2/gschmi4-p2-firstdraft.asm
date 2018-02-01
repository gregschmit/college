.data

rprompt:        .asciiz "Enter the number system radix (1<r<16): "
prompt:         .asciiz "Please enter a number: "
x:              .asciiz "x="
y:              .asciiz "y="
z:              .asciiz "z="
has:            .asciiz " has "
digits:         .asciiz " digits\n"
backwards:      .asciiz " is x backwards\n"
compliment:     .asciiz " is -x in r's compliment\n"
plus:           .asciiz " +"
minus:          .asciiz " -"
equal:          .asciiz " ="
p:              .asciiz " p"
n:              .asciiz " n"
correct:        .asciiz " correct\n"
wrong:          .asciiz " wrong\n"

radix:          .space 2
number:         .space 11
numberback:     .space 11
.text

# Definitions
# $t0:          r
# $s1:          max_number
# $t1:          x
# $t2:          d
# $t3:          y
# $t4:          z
# $t5-9:        transient
# $s0:          transient

# Prompt user and get input string
li $v0, 4
la $a0, rprompt
syscall
li $v0, 5
syscall
move $t0, $v0
li $v0, 4
la $a0, prompt
syscall
li $v0, 8
la $a0, number
li $a1, 11
syscall

# Set max_number based on radix
move $s1, $t0
ble $t0, 10, if_less10_true
        j if_less10_else
        if_less10_true:
                addi $s1, $s1, 47
                j if_less10_exit
        if_less10_else:
                addi $s1, $s1, 86
if_less10_exit:

# Sanity check on string (numbers, letters, ending NULL)
li $t5, 0
while_sanity:
        # $t5:  counter for string position
        # $t6:  value holder for current character
        # $t7:  boolean to set if we need to numberfy
        # $t8:  counter for string shift position lo
        # $t9:  counter for string shift position hi
        # $s0: value holder for string shift position hi

        lb $t6, number($t5)
        beq $t6, 0, while_sanity_exit
        beq $t6, 10, while_sanity_exit  # string smaller than buffer, so add LF
        # upper to lower conversion (0x41-5A, add 0x20)
        bge $t6, 0x41, if_lowerify_true
                j if_lowerify_exit
                if_lowerify_true:
                        ble $t6, 0x5A, if_lowerify_and_true
                        j if_lowerify_exit
                if_lowerify_and_true:
                        addi $t6, $t6, 0x20
                        sb $t6, number($t5)
        if_lowerify_exit:
        # set boolean if char 0x30-39 or 0x61-7a, and less than radix-1
        bge $t6, 0x30, if_bnumberfy_first_true
                j if_bnumberfy_false
                if_bnumberfy_first_true:
                        ble $t6, 0x7a, if_bnumberfy_and_true
                        j if_bnumberfy_false
                if_bnumberfy_and_true:
                        ble $t6, 0x39, if_bnumberfy_and2_true
                        bge $t6, 0x61, if_bnumberfy_and2_true
                        j if_bnumberfy_false
                if_bnumberfy_and2_true:
                        ble $t6, $s1, if_bnumberfy_true
                        j if_bnumberfy_false
                if_bnumberfy_true:
                        li $t7, 1
                        j if_bnumberfy_exit
                if_bnumberfy_false:
                        li $t7, 0
        if_bnumberfy_exit:
        
        ### TEST
        #li $v0, 1
        #move $a0, $t7
        #syscall
        ### TEST END

        beq $t7, 1, if_numberfy_exit
                move $t8, $t5
                move $t9, $t5
                addi $t9, $t9, 1
                li $s0, 0
                lb $s0, number($t8)
                while_shift:
                        ### TEST
                        #li $v0, 11
                        #li $a0, 10
                        #syscall
                        #li $v0, 1
                        #move $a0, $t8
                        #syscall
                        #move $a0, $t9
                        #syscall
                        #li $v0, 11
                        #li $a0, 10
                        #syscall
                        ### TEST END
                        beq $s0, 0, while_shift_exit
                        beq $s0, 10, while_shift_exit
                        lb $s0, number($t9)
                        sb $s0, number($t8)
                        addi $t8, $t8, 1
                        addi $t9, $t9, 1
                        j while_shift
                while_shift_exit:
                subi $t5, $t5, 1
        if_numberfy_exit:
        addi $t5, $t5, 1
        j while_sanity
while_sanity_exit:
sb $zero, number($t5)   # ensure ending NULL

### TEST ONLY - print string
#li $v0, 11
#li $a0, 10
#syscall

#li $v0, 4
#la $a0, number
#syscall
### TEST END

# count digits (2, use 5 and up for tmp)
li $t5, 0
li $t6, 0
while_count:
        lb $t6, number($t5)
        beq $t6, 0, while_count_end
        addi $t2, $t2, 1
        addi $t5, $t5, 1
        j while_count
while_count_end:

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
