all: main.o integral.o root.o functions.o funcs.o derivs.o test.o
	gcc -m32 main.o integral.o root.o functions.o funcs.o derivs.o test.o -o out -lm
main.o: main.c
	gcc -m32 -c -o main.o main.c
funcs.o: funcs.asm
	nasm -f elf funcs.asm -o funcs.o
derivs.o: derivs.asm
	nasm -f elf derivs.asm -o derivs.o
integral.o: integral.c
	gcc -m32 -c -o integral.o integral.c
root.o: root.c
	gcc -m32 -c -o root.o root.c
functions.o: functions.c
	gcc -m32 -c -o functions.o functions.c
test.o:
	gcc -m32 -c -o test.o test.c
clean:
	rm *.o