	.file	"main.c"
	.globl	N
	.section	.rodata
	.align 4
	.type	N, @object
	.size	N, 4
N:
	.long	5
	.globl	signalCaught
	.bss
	.align 4
	.type	signalCaught, @object
	.size	signalCaught, 4
signalCaught:
	.zero	4
	.text
	.globl	int_handler
	.type	int_handler, @function
int_handler:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, signalCaught(%rip)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	int_handler, .-int_handler
	.section	.rodata
	.align 8
.LC0:
	.string	"Process %d received signal %d\n"
.LC1:
	.string	"Created process %d\n"
.LC2:
	.string	"Killing process %d\n"
	.align 8
.LC3:
	.string	"Child %d terminated with exit status %d\n"
	.align 8
.LC4:
	.string	"Child %d terminated abnormally\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$104, %rsp
	.cfi_offset 3, -24
	movl	%edi, -100(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	$5, %eax
	cltq
	subq	$1, %rax
	movq	%rax, -32(%rbp)
	movl	$5, %eax
	cltq
	movq	%rax, %r8
	movl	$0, %r9d
	movl	$5, %eax
	cltq
	movq	%rax, %rdx
	movl	$0, %ecx
	movl	$5, %eax
	cltq
	salq	$2, %rax
	leaq	3(%rax), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %ecx
	movl	$0, %edx
	divq	%rcx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -40(%rbp)
	movl	$int_handler, %esi
	movl	$2, %edi
	call	signal
	movl	$0, -20(%rbp)
	jmp	.L4
.L8:
	call	fork
	movl	%eax, %ecx
	movq	-40(%rbp), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	movq	-40(%rbp), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	testl	%eax, %eax
	jne	.L5
.L7:
	movl	signalCaught(%rip), %eax
	testl	%eax, %eax
	je	.L6
	movl	signalCaught(%rip), %ebx
	movl	$0, %eax
	call	getpid
	movl	%ebx, %edx
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	signalCaught(%rip), %eax
	movl	%eax, %edi
	call	exit
.L6:
	jmp	.L7
.L5:
	movq	-40(%rbp), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -20(%rbp)
.L4:
	movl	$5, %eax
	cmpl	%eax, -20(%rbp)
	jl	.L8
	cmpl	$1, -100(%rbp)
	jle	.L9
	movq	-112(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, -44(%rbp)
	cmpl	$0, -44(%rbp)
	jle	.L9
	movl	-44(%rbp), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	sleep
.L9:
	movl	$0, -20(%rbp)
	jmp	.L10
.L11:
	movq	-40(%rbp), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movq	-40(%rbp), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	$2, %esi
	movl	%eax, %edi
	call	kill
	addl	$1, -20(%rbp)
.L10:
	movl	$5, %eax
	cmpl	%eax, -20(%rbp)
	jl	.L11
	movl	$0, -20(%rbp)
	jmp	.L12
.L15:
	leaq	-84(%rbp), %rax
	movq	%rax, %rdi
	call	wait
	movl	%eax, -48(%rbp)
	movl	-84(%rbp), %eax
	movl	%eax, -80(%rbp)
	movl	-80(%rbp), %eax
	andl	$127, %eax
	testl	%eax, %eax
	jne	.L13
	movl	-84(%rbp), %eax
	movl	%eax, -64(%rbp)
	movl	-64(%rbp), %eax
	andl	$65280, %eax
	sarl	$8, %eax
	movl	%eax, %edx
	movl	-48(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L14
.L13:
	movl	-48(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
.L14:
	addl	$1, -20(%rbp)
.L12:
	movl	$5, %eax
	cmpl	%eax, -20(%rbp)
	jl	.L15
	movl	$0, %eax
	movq	%rbx, %rsp
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Debian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
