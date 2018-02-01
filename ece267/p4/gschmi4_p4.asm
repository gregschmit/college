.data

s_initprompt:   .asciiz "Initial Ticket #: "
s_nextprompt:   .asciiz "\nnext ticket # ("
s_nextprompt2:  .asciiz "), input x: "
s_qprompt:      .asciiz "Q: <- "
s_qprompt2:     .asciiz "<-\n"
s_sprompt:      .asciiz "S:  | "
s_sprompt2:     .asciiz "<->\n"

s_overflow:     .asciiz "overflow rejected:"
s_underflow:    .asciiz "underflow after "

q:              .word 0
                .space 20

q_head:         .word 0
q_tail:         .word 0
q_len:          .word 0

s:              .word 0
                .space 20

s_head:         .word 0
s_len:          .word 0

.text
# .global main
main:
        # s0: next ticket
        # s1: number of tickets (counter)
        # s2: over/underflow end num
        # s3: over/underflow qty
        # s4: number of tickets
        li $s2, 0
        li $s3, 0
        li $v0, 4
        la $a0, s_initprompt
        syscall
        li $v0, 5
        syscall
        move $s0, $v0
        while_main:
                li $v0, 4
                la $a0, s_nextprompt
                syscall
                li $v0, 1
                move $a0, $s0
                syscall
                li $v0, 4
                la $a0, s_nextprompt2
                syscall
                li $v0, 5
                syscall
                move $s1, $v0
                move $s4, $v0
                
                ble $s1, $zero, if_main_ticketpop
                if_main_ticketpush:
                        while_ticket_push:
                                ble $s1, $zero, while_ticket_push_exit
                                move $a0, $s0
                                jal q_enqueue
                                beq $v0, $zero, if_overflow_exit
                                        addi $s3, $s3, 1
                                        move $s2, $s0
                                if_overflow_exit:
                                jal s_push
                                addi $s0, $s0, 1
                                addi $s1, $s1, -1
                                j while_ticket_push
                        while_ticket_push_exit:
                        j if_main_ticketexit
                if_main_ticketpop:
                        while_ticket_pop:
                                bge $s1, $zero, while_ticket_pop_exit
                                jal q_dequeue
                                bge $v0, $zero, if_underflow_exit
                                        addi $s3, $s3, -1
                                if_underflow_exit:
                                jal s_pop
                                addi $s1, $s1, 1
                                j while_ticket_pop
                        while_ticket_pop_exit:
                if_main_ticketexit:
                jal print_qs_status
                
                # print overflow/underflow
                ble $s3, $zero, if_overflowp_exit
                        li $v0, 4
                        la $a0, s_overflow
                        syscall
                        while_overflowp:
                                ble $s3, $zero, while_overflowp_exit
                                li $v0, 11
                                li $a0, ' '
                                syscall
                                addi $s3, $s3, -1
                                sub $a0, $s2, $s3
                                li $v0, 1
                                syscall
                                j while_overflowp
                        while_overflowp_exit:
                        li $v0, 11
                        li $a0, 10
                        syscall
                if_overflowp_exit:
                bge $s3, $zero, if_underflowp_exit
                        li $v0, 4
                        la $a0, s_underflow
                        syscall
                        li $v0, 1
                        sub $a0, $s4, $s3
                        syscall
                        li $v0, 11
                        li $a0, 10
                        syscall
                if_underflowp_exit:
                
                li $s2, 0
                li $s3, 0
                j while_main
        while_main_exit:
j end

# procedures:

q_enqueue:
# PRE:
#       a0: Item to enqueue
#       If q_len > 0 then head/tail is assumed to point to real head/tail of 
#               queue
# POST:
#       If q_len <= 0 then queue is initialized and head/tail is set to first 
#               element
#       If q_len >= 6 then item is not enqueued and 1 is returned in v0
#       If q_len < 6 then item is enqueued and 0 is returned in v0
        lw $t0, q_head
        lw $t1, q_len
        la $t2, q
        addi $t2, $t2, 20
        bge $t1, 6, if_qenqueue_full
                ble $t1, $zero, if_qenqueue_init
                        addi $t0, $t0, 4
                        addi $t1, $t1, 1
                        ble $t0, $t2, if_qenqueue_qwrap_exit
                                la $t0, q
                        if_qenqueue_qwrap_exit:
                        sw $a0, ($t0)
                        sw $t1, q_len($zero)
                        sw $t0, q_head($zero)
                        j if_qenqueue_init_exit
                if_qenqueue_init:
                        sw $a0, q($zero)
                        li $t1, 1
                        sw $t1, q_len($zero)
                        la $t2, q
                        sw $t2, q_head($zero)
                        sw $t2, q_tail($zero)
                if_qenqueue_init_exit:
                li $v0, 0
                j if_qenqueue_full_exit
        if_qenqueue_full:
                li $v0, 1
        if_qenqueue_full_exit:
jr $ra

q_dequeue:
# PRE:  none
# POST:
#       v0: Value dequeued
#       If q_len <= 0 then -1 is returned in v0
        lw $t0, q_tail
        lw $t1, q_len
        la $t2, q
        addi $t2, $t2, 20
        ble $t1, $zero, if_qdequeue_void
                lw $v0, q_tail($zero)
                addi $t0, $t0, 4
                addi $t1, $t1, -1
                ble $t0, $t2, if_qdequeue_qwrap_exit
                        la $t0, q
                if_qdequeue_qwrap_exit:
                sw $t0, q_tail($zero)
                sw $t1, q_len($zero)
                j if_qdequeue_exit
        if_qdequeue_void:
                li $v0, -1
        if_qdequeue_exit:
jr $ra

s_push:
# PRE:
#       a0: Item to push to the stack
#       If s_len > 0 then head is assumed to point to real head of stack
# POST:
#       v0: Return value (see below)
#       If s_len <= 0 then stack is initialized and head is set to first element
#       If s_len >= 6 then item is not pushed and 1 is returned in v0
#       If s_len < 6 then item is pushed and 0 is returned in v0
        lw $t0, s_head
        lw $t1, s_len
        bge $t1, 6, if_spush_full
                ble $t1, $zero, if_spush_init
                        addi $t0, $t0, 4
                        addi $t1, $t1, 1
                        sw $a0, ($t0)
                        sw $t1, s_len($zero)
                        sw $t0, s_head($zero)
                        j if_spush_init_exit
                if_spush_init:
                        sw $a0, s($zero)
                        li $t1, 1
                        sw $t1, s_len($zero)
                        la $t0, s
                        sw $t0, s_head($zero)
                if_spush_init_exit:
                li $v0, 0
                j if_spush_full_exit
        if_spush_full:
                li $v0, 1
        if_spush_full_exit:
jr $ra

s_pop:
# PRE:  none
# POST:
#       v0: Value popped from stack
#       If s_len <= 0 then -1 is returned in v0
        lw $t0, s_head($zero)
        lw $t1, s_len($zero)
        ble $t1, $zero, if_spop_void
                lw $v0, ($t0)
                addi $t0, $t0, -4
                addi $t1, $t1, -1
                sw $t0, s_head($zero)
                sw $t1, s_len($zero)
                j if_spop_exit
        if_spop_void:
                li $v0, -1
        if_spop_exit:
jr $ra

print_qs_status:
# No pre or post conditions
        li $v0, 4
        la $a0, s_qprompt
        syscall
        lw $t0, q_tail
        lw $t1, q_len
        la $t2, q
        addi $t2, $t2, 20
        li $t3, 0
        while_printq:
                bge $t3, $t1, while_printq_exit
                li $v0, 1
                lw $a0, ($t0)
                syscall
                li $v0, 11
                li $a0, ' '
                syscall
                addi $t0, $t0, 4
                ble $t0, $t2, if_qwrap_exit
                        la $t0, q
                if_qwrap_exit:
                addi $t3, $t3, 1
                j while_printq
        while_printq_exit:
        li $v0, 4
        la $a0, s_qprompt2
        syscall

        la $a0, s_sprompt
        syscall
        la $t0, s
        lw $t1, s_len
        li $t2, 0
        while_prints:
                bge $t2, $t1, while_prints_exit
                li $v0, 1
                lw $a0, ($t0)
                syscall
                li $v0, 11
                li $a0, ' '
                syscall
                addi $t0, $t0, 4
                addi $t2, $t2, 1
                j while_prints
        while_prints_exit:
        li $v0, 4
        la $a0, s_sprompt2
        syscall
jr $ra

end:
li $v0, 10
syscall
