exe: Vector.o main.o
	gcc Vector.o main.o -o exe -lm -Wall

main.o: Vector.h main.c
	gcc -c main.c -Wall

Vector.o: Vector.h Vector.c
	gcc -c Vector.c -Wall 