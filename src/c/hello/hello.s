	.file	"hello.c"
	.intel_syntax noprefix
	.globl	string
	.section	.rodata
.LC0:
	.string	"hello sabir"
	.data
	.align 8
	.type	string, @object
	.size	string, 8
string:
	.quad	.LC0
	.section	.rodata
.LC1:
	.string	"%s\r\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	rax, QWORD PTR string[rip]
	mov	rsi, rax
	mov	edi, OFFSET FLAT:.LC1
	mov	eax, 0
	call	printf
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
