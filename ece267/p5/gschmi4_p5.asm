.data

Array_X:        .word 1, 2, 4, 8, 16, 32, 64, 128, 256, 512
Array_Y:        .word 2, 3, 5, 7, 11, 13, 17, 19, 23, 29

len:            .word 40

sol1:           .word 0
sol2:           .word 0
bsol:           .word 0

s_input:        .asciiz "Input w: "
s_solx:         .asciiz "2-item solution in Array_X: "
s_soly:         .asciiz "\n2-item solution in Array_Y: "
s_none:         .asciiz "none"

.text
main:

while_main:
        li $v0, 4
        la $a0, s_input
        syscall
        li $v0, 5
        syscall
        move $t0, $v0
        
        # Array_X:
        li $t1, 0
        lw $t2, len($zero)
        for_lenx_outer:
                bge $t1, $t2, for_lenx_outer_exit
                addi $t3, $t1, 4
                for_lenx_inner:
                        bge $t3, $t2, for_lenx_inner_exit
                        lw $t4, Array_X($t1)
                        lw $t5, Array_X($t3)
                        add $t6, $t4, $t5
                        beq $t6, $t0, found_xpair
                        addi $t3, $t3, 4
                        j for_lenx_inner
                for_lenx_inner_exit:
                addi $t1, $t1, 4
                j for_lenx_outer
        for_lenx_outer_exit:
        j notfound_xpair
        found_xpair:
                sw $t4, sol1($zero)
                sw $t5, sol2($zero)
                li $t1, 1
                sw $t1, bsol($zero)
        notfound_xpair:        
        # print output
        li $v0, 4
        la $a0, s_solx
        syscall
        lw $t1, bsol($zero)
        beq $t1, $zero, if_xnone
        if_xnone_not:
                li $v0, 1
                move $a0, $t0
                syscall
                li $v0, 11
                li $a0, '='
                syscall
                li $v0, 1
                move $a0, $t4
                syscall
                li $v0, 11
                li $a0, '+'
                syscall
                li $v0, 1
                move $a0, $t5
                syscall
                j if_xnone_exit
        if_xnone:
                li $v0, 4
                la $a0, s_none
                syscall
        if_xnone_exit:
        sw $zero, bsol($zero)



        # Array_Y:
        li $t1, 0
        lw $t2, len($zero)
        for_leny_outer:
                bge $t1, $t2, for_leny_outer_exit
                addi $t3, $t1, 4
                for_leny_inner:
                        bge $t3, $t2, for_leny_inner_exit
                        lw $t4, Array_Y($t1)
                        lw $t5, Array_Y($t3)
                        add $t6, $t4, $t5
                        beq $t6, $t0, found_ypair
                        addi $t3, $t3, 4
                        j for_leny_inner
                for_leny_inner_exit:
                addi $t1, $t1, 4
                j for_leny_outer
        for_leny_outer_exit:
        j notfound_ypair
        found_ypair:
                sw $t4, sol1($zero)
                sw $t5, sol2($zero)
                li $t1, 1
                sw $t1, bsol($zero)
        notfound_ypair:
        # print output
        li $v0, 4
        la $a0, s_soly
        syscall
        lw $t1, bsol($zero)
        beq $t1, $zero, if_ynone
        if_ynone_not:
                li $v0, 1
                move $a0, $t0
                syscall
                li $v0, 11
                li $a0, '='
                syscall
                li $v0, 1
                move $a0, $t4
                syscall
                li $v0, 11
                li $a0, '+'
                syscall
                li $v0, 1
                move $a0, $t5
                syscall
                li $v0, 11
                li $a0, 10
                syscall
                j if_ynone_exit
        if_ynone:
                li $v0, 4
                la $a0, s_none
                syscall
                li $v0, 11
                li $a0, 10
                syscall
        if_ynone_exit:
        sw $zero, bsol($zero)
        
        j while_main
while_main_exit:

end:
li $v0, 10
syscall
