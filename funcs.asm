section .text
global f1
global f2
global f3

f1:
	push ebp
	mov ebp, esp
	finit

	fld qword[ebp+8]

	push dword -1
	fild dword[esp]
	add esp, 4

	fmulp ST1, ST0

	fldl2e
	fmulp
	fld1
	fld st1
	fprem
	f2xm1
	faddp
	fscale
	fstp st1

	push dword 3
	fild dword[esp]
	add esp, 4

	faddp ST1, ST0

	xor eax, eax
	mov esp, ebp
	pop ebp
	ret

f2:
	push ebp
	mov ebp, esp
	finit

	push dword 2
	fild dword[esp]
	add esp, 4

	fld qword[ebp+8]

	push dword 2
	fild dword[esp]
	add esp, 4

	fmulp ST1, ST0

	fsubrp ST1, ST0

	xor eax, eax
	mov esp, ebp
	pop ebp
	ret

f3:
	push ebp
	mov ebp, esp
	finit

	fld1
	fld qword[ebp+8]

	fdivp ST1, ST0

	xor eax, eax
	mov esp, ebp
	pop ebp
	ret