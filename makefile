exe: Vector.o main.o Pion.o board.o
	gcc Vector.o main.o Pion.o board.o -o exe -lm -Wall

main.o: Pion.h Vector.h main.c
	gcc -c main.c -Wall

Vector.o: Vector.h Vector.c
	gcc -c Vector.c -Wall 

Pion.o: Pion.h Pion.c
	gcc -c Pion.c -Wall

board.o: board.h board.c
	gcc -c board.c -Wall