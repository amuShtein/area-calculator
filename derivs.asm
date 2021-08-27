section .text

global df1dx
global df2dx
global df3dx

df1dx:
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

	push dword -1
	fild dword[esp]
	add esp, 4

	fmulp ST1, ST0

	xor eax, eax
	mov esp, ebp
	pop ebp
	ret

df2dx:
	push ebp
	mov ebp, esp
	finit

	push dword 2
	fild dword[esp]
	add esp, 4

	xor eax, eax
	mov esp, ebp
	pop ebp
	ret

df3dx:
	push ebp
	mov ebp, esp
	finit

	fld1
	fld qword[ebp+8]
	fld qword[ebp+8]
	fmulp ST1, ST0

	fdivp ST1, ST0

	push dword -1
	fild dword[esp]
	add esp, 4

	fmulp ST1, ST0

	xor eax, eax
	mov esp, ebp
	pop ebp
	ret
