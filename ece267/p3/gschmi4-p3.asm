.data

prompt:         .asciiz "Enter a string of characters, then press 'enter': "

f_profile:      .asciiz "Frequency profile:\n"
ranked:         .asciiz "Ranked:\n"
wl_report:      .asciiz "Word-length report:\n"

input:          .space 141
v_index:        .word 'a' ,'e' ,'i' ,'o' ,'u'
v_indexU:       .word 'A', 'E', 'I', 'O', 'U'
v_freq:         .word 0, 0, 0, 0, 0

w_freq:         .word 0
                .space 560

loweraddr:      .word 0
upperaddr:      .word 0

.text

# Print prompt
li $v0, 4
la $a0, prompt
syscall

# Get input string
li $v0, 8
la $a0, input
li $a1, 141
syscall
li $v0, 11
li $a0, 10
syscall

# Go through string and for each character if it matches aeiou, then add one to
#  the frequency. Also, remove possible \n (replace with \0).
li $t0, 0
lb $t1, input($t0)
while_inputfreq:
        beq $t1, 10, while_inputfreq_exit
        beq $t1, 0, while_inputfreq_exit

        li $t2, 0
        for_vowelsadd:
        bge $t2, 20, for_vowelsadd_exit
                lw $t3, v_index($t2)
                beq $t1, $t3, if_add
                lw $t3, v_indexU($t2)
                beq $t1, $t3, if_add
                j if_add_exit
                if_add:
                        lw $t4, v_freq($t2)
                        addi $t4, $t4, 1
                        sw $t4, v_freq($t2)
                if_add_exit:
        addi $t2, $t2, 4
        j for_vowelsadd
        for_vowelsadd_exit:

        addi $t0, $t0, 1
        lb $t1, input($t0)
        j while_inputfreq
while_inputfreq_exit:
li $t1, 0
sb $t1, input($t0)

# Print report with for loop for stars
li $v0, 4
la $a0, f_profile
syscall
li $t0, 0
for_vprintstar:
        bge $t0, 20, for_vprintstar_exit
        li $v0, 11
        lw $a0, v_indexU($t0)
        syscall
        li $a0, '/'
        syscall
        lw $a0, v_index($t0)
        syscall
        li $a0, ':'
        syscall
        li $a0, ' '
        syscall

        li $t1, 0
        lw $t2, v_freq($t0)
        li $a0, '*'
        for_vfreqprint:
                bge $t1, $t2, for_vfreqprint_exit
                syscall
                addi $t1, $t1, 1
                j for_vfreqprint
        for_vfreqprint_exit:

        li $a0, 10
        syscall

        addi $t0, $t0, 4
        j for_vprintstar
for_vprintstar_exit:
li $v0, 11
li $a0, 10
syscall

# Sort v array (keep vowel with freq value, selection sort)

li $t0, 0
## Go through array from base to end
while_basenotend:
        bge $t0, 20, while_basenotend_exit

        # t0: base index
        # t1: temp counter up to max
        # t2: temp holder of freq up to max
        # t3: max index this round
        # t4: max value this round

        move $t1, $t0
        addi $t1, $t1, 4
        move $t3, $t0
        lw $t4, v_freq($t0)
        # search from base to end, find max
        for_basetoend:
                bge $t1, 20, for_basetoend_exit
                lw $t2, v_freq($t1)
                ble $t2, $t4, if_greater_exit
                        # higher than current, update max
                        move $t3, $t1
                        lw $t4, v_freq($t1)
                if_greater_exit:
                addi $t1, $t1, 4
                j for_basetoend
        for_basetoend_exit:

        # swap max with base (overwrite t2 and t2, since they are tmps)
        beq $t0, $t3, if_swapneeded_exit
                lw $t1, v_freq($t0)
                lw $t2, v_freq($t3)
                sw $t2, v_freq($t0)
                sw $t1, v_freq($t3)
                lw $t1, v_index($t0)
                lw $t2, v_index($t3)
                sw $t2, v_index($t0)
                sw $t1, v_index($t3)
                lw $t1, v_indexU($t0)
                lw $t2, v_indexU($t3)
                sw $t2, v_indexU($t0)
                sw $t1, v_indexU($t3)
        if_swapneeded_exit:

        addi $t0, $t0, 4
        j while_basenotend
while_basenotend_exit:

# Print report with numbers for freq
li $v0, 4
la $a0, ranked
syscall
li $t0, 0
for_vprintfreq:
        bge $t0, 20, for_vprintfreq_exit
        li $v0, 11
        lw $a0, v_indexU($t0)
        syscall
        li $a0, '/'
        syscall
        lw $a0, v_index($t0)
        syscall
        li $a0, ':'
        syscall
        li $a0, ' '
        syscall

        li $v0, 1
        lw $a0, v_freq($t0)
        syscall

        li $v0, 11
        li $a0, 10
        syscall

        addi $t0, $t0, 4
        j for_vprintfreq
for_vprintfreq_exit:
li $v0, 11
li $a0, 10
syscall

# init w_freq array to zero
li $t0, 0
li $t1, 0
for_wfinit:
        bgt $t0, 560, for_wfinit_exit
        sw $t1, w_freq($t0)
        addi $t0, $t0, 4
        j for_wfinit
for_wfinit_exit:

li $v0, 4
la $a0, wl_report
syscall

li $t0, 0
lb $t1, input($t0)
li $t2, 0
li $s0, 0
while_runstring:
        beq $s0, 1, while_runstring_exit
        beq $t1, 0, set_exitbit
        j skip_exitbit
        set_exitbit:
                li $s0, 1
        skip_exitbit:
        
        bge $t1, 65, if_first
        j if_else
        if_first:
        ble $t1, 122, if_second
        j if_else
        if_second:
        ble $t1, 90, if_third
        bge $t1, 97, if_third
        j if_else
        if_third:
                # just add 1 to word counter:
                addi $t2, $t2, 1
        j if_exit
        if_else:
                # print counter if t2 > 0:
                ble $t2, $zero, if_over0_exit
                        li $v0, 11
                        li $a0, '('
                        syscall
                        li $v0, 1
                        move $a0, $t2
                        syscall
                        li $v0, 11
                        li $a0, ')'
                        syscall
                        li $t4, 4
                        mult $t2, $t4
                        mflo $t4
                        lw $t3, w_freq($t4)
                        addi $t3, $t3, 1
                        sw $t3, w_freq($t4)
                if_over0_exit:
                li $t2, 0
        if_exit:

        li $v0, 11
        move $a0, $t1
        syscall

        beq $s0, 1, if_exitbit_exit
                addi $t0, $t0, 1
                lb $t1, input($t0)
        if_exitbit_exit:
        j while_runstring
while_runstring_exit:
li $v0, 11
li $a0, 10
syscall

# determine lower bound
la $t0, w_freq
lw $t1, ($t0)
addi $t2, $t0, 560
while_zerolower:
        bne $t1, $zero, while_zerolower_exit
        bge $t0, $t2, while_zerolower_exit
        addi $t0, $t0, 4
        lw $t1, ($t0)
        j while_zerolower
while_zerolower_exit:
sw $t0, loweraddr

# determine upper bound
la $t0, w_freq
move $t2, $t0
addi $t0, $t0, 560
lw $t1, ($t0)
while_zeroupper:
        bne $t1, $zero, while_zeroupper_exit
        ble $t0, $t2, while_zeroupper_exit
        addi $t0, $t0, -4
        lw $t1, ($t0)
        j while_zeroupper
while_zeroupper_exit:
sw $t0, upperaddr

# Print from lower to upper values stored in array
li $v0, 11
li $a0, 10
syscall
li $v0, 4
la $a0, f_profile
syscall

la $t0, loweraddr
lw $t0, ($t0)
la $t1, upperaddr
lw $t1, ($t1)
la $t2, w_freq

sub $t2, $t0, $t2
li $t3, 4
div $t2, $t3
mflo $t2
while_printwpro:
        bgt $t0, $t1, while_printwpro_exit

        li $v0, 1
        move $a0, $t2
        syscall

        li $v0, 11
        li $a0, ':'
        syscall
        li $a0, ' '
        syscall

        li $t3, 0
        lw $t4, ($t0)
        li $a0, '*'

        while_pstar:
                bge $t3, $t4, while_pstar_exit
                syscall
                addi $t3, $t3, 1
                j while_pstar
        while_pstar_exit:

        li $v0, 11
        li $a0, 10
        syscall

        addi $t0, $t0, 4
        addi $t2, $t2, 1
        j while_printwpro
while_printwpro_exit:

end:
li $v0, 10
syscall
