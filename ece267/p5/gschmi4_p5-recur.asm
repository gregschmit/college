.data

Array_X:        .word 1, 2, 4, 8, 16, 32, 64, 128, 256, 512
Array_Y:        .word 2, 3, 5, 7, 11, 13, 17, 19, 23, 29

rtstack:        .word 0
                .space 3996     # space for 200 $ra, a0-3
rtstack_len:    .word 0
rtstack_head:   .word 0
rtstack_max:    .word 200
rtstack_ofmsg:  .asciiz "\n\nRuntime Stack Overflow!\n"
rtstack_ufmsg:  .asciiz "\n\nRuntime Stack Underflow!\n"

.text
main:







rts_push:
        # $fp: address to push to the stack
        lw $t0, rtstack_len($zero)
        lw $t1, rtstack_max($zero)
        ble $t0, $zero, rtspush_if_rts_init
                bge $t0, $t1, rtspush_if_rts_full
                        # Push to runtime stack (update head, len)
                        addi $t0, $t0, 1
                        sw $t0, rtstack_len($zero)
                        lw $t2, rtstack_head($zero)
                        addi $t2, $t2, 4
                        sw $fp, ($t2)
                        addi $t2, $t2, 4
                        sw $a0, ($t2)
                        addi $t2, $t2, 4
                        sw $a1, ($t2)
                        addi $t2, $t2, 4
                        sw $a2, ($t2)
                        addi $t2, $t2, 4
                        sw $a3, ($t2)
                        sw $t2, rtstack_head($zero)
                        j rtspush_if_rts_exit
                rtspush_if_rts_full:
                        # Runtime stack overflow
                        j rts_overflow
                        #j rtspush_if_rts_exit
        rtspush_if_rts_init:
                # Initialize runtime stack
                la $t2, rtstack
                sw $fp, ($t2)
                addi $t2, $t2, 4
                sw $a0, ($t2)
                addi $t2, $t2, 4
                sw $a1, ($t2)
                addi $t2, $t2, 4
                sw $a2, ($t2)
                addi $t2, $t2, 4
                sw $a3, ($t2)
                li $t0, 1
                sw $t0, rtstack_len($zero)
                sw $t2, rtstack_head($zero)
        rtspush_if_rts_exit:
jr $ra

rts_pop
        # fp: address popped from the stack
        # a0-3 set to stack popped values
        lw $t0, rtstack_len($zero)
        lw $t1, rtstack_max($zero)
        ble $t0, $zero, rtspop_if_rts_empty
                # Pop from runtime stack
                lw $t2, rtstack_head($zero)
                lw $a3, ($t2)
                addi $t2, $t2, -4
                lw $a2, ($t2)
                addi $t2, $t2, -4
                lw $a1, ($t2)
                addi $t2, $t2, -4
                lw $a0, ($t2)
                addi $t2, $t2, -4
                lw $fp, ($t2)
                addi $t2, $t2, -4
                sw $t2, rtstack_head($zero)
                addi $t0, $t0, -1
                sw $t0, rtstack_len($zero)
                j rtspop_if_rts_exit
        rtspop_if_rts_empty:
                # Runtime stack underflow
                j rts_underflow
        rtspop_if_rts_exit:
jr $ra

--- end of program ---

j end

rts_overflow:
li $v0, 4
la $a0, rtstack_ofmsg
syscall
j end

rts_underflow:
li $v0, 4
la $a0, rtstack_ufmsg
syscall
j end

end:
li $v0, 10
syscall
