	.file	"hello.c"
	.text
	.section	.rodata
.LC0:
	.string	"hello %d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movb	$1, -1(%rbp)
	movzbl	-1(%rbp), %eax
	movl	%eax, %esi
	movl	$4, %edi
	call	add@PLT
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-11ubuntu0~18.04.1) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
