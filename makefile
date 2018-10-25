exe: main.o
	gcc main.o -o exe -lSDLmain -lSDL -Wall
main.o: main.c
	gcc -c main.c -Wall
