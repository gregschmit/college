.data

s_prompt:       .asciiz "Please enter a number: "
s_x:            .asciiz "x="
s_y:            .asciiz "y="
s_z:            .asciiz "z="
s_has:          .asciiz " has "
s_digits:       .asciiz " digits\n"
s_backwards:    .asciiz " is x backwards\n"
s_compliment:   .asciiz " is -x in ten's compliment\n"
s_plus:         .asciiz " +"
s_minus:        .asciiz " -"
s_equal:        .asciiz " ="
s_p:            .asciiz " p"
s_n:            .asciiz " n"
s_correct:      .asciiz " correct\n"
s_wrong:        .asciiz " wrong\n"

x:              .word 1
d:              .word 1
y:              .word 1
z:              .word 1

xy:             .word 1
yz:             .word 1
 
dpo:            .word 1

.text

# Prompt user and get input string
li $v0, 4
la $a0, s_prompt
syscall
li $v0, 5
syscall
sw $v0, x

# Get digits
lw $t0, x
li $t1, 0
li $t2, 10
while_digits:
        beq $t0, 0, while_digits_exit
        divu $t0, $t2
        mflo $t0
        addi $t1, $t1, 1
        j while_digits
while_digits_exit:
sw $t1, d

# Print d
li $v0, 4
la $a0, s_x
syscall
li $v0, 1
lw $a0, x
syscall
li $v0, 4
la $a0, s_has
syscall
li $v0, 1
lw $a0, d
syscall
li $v0, 4
la $a0, s_digits
syscall

# build y
lw $t0, x       # number
lw $t1, d       # counter initialized to digits
li $t2, 10      # const 10
li $t3, 0       # modulo
li $t4, 0       # y
for_buildy:
        beq $t1, 0, for_buildy_exit
        divu $t0, $t2
        mflo $t0
        mfhi $t3
        li $t5, 1
        for_digitweight:
                bge $t5, $t1, for_digitweight_exit
                multu $t3, $t2
                mflo $t3
                addi $t5, $t5, 1
                j for_digitweight
        for_digitweight_exit:
        add $t4, $t4, $t3
        subi $t1, $t1, 1
        j for_buildy
for_buildy_exit:
sw $t4, y

# Print y
li $v0, 4
la $a0, s_y
syscall
li $v0, 1
lw $a0, y
syscall
li $v0, 4
la $a0, s_backwards
syscall

# Build z
# But before that, build the first number with d+1 digits (dpo)
li $t0, 1       # counter
lw $t1, d       # const digit
li $t2, 1       # dpo
li $t3, 10      # const 10
lw $t4, x       # x
for_dpo:
        bgt $t0, $t1, for_dpo_exit
        mult $t2, $t3
        mflo $t2
        addi $t0, $t0, 1
        j for_dpo
for_dpo_exit:
sw $t2, dpo
sub $t5, $t2, $t4
sw $t5, z

# Print z
li $v0, 4
la $a0, s_z
syscall
li $v0, 1
lw $a0, z
syscall
li $v0, 4
la $a0, s_compliment
syscall

# Do x+y and cut off potential factor of dpo, print
lw $t0, x
lw $t1, y
lw $t3, dpo
add $t2, $t0, $t1
if_overdpo:
        blt $t2, $t3, if_overdpo_exit
        sub $t2, $t3, $t2
        sw $t2, xy
if_overdpo_exit:

# Spent too much time on building the entire project with extra credit in 
# mind... oh well... that will be my pet project.

# Do y_z and cut off potential factor of dpo, print

end:
li $v0, 10
syscall
