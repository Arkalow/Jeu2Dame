exe: main.o
	gcc main.o -o exe `sdl2-config --cflags --libs` -Wall
main.o: main.c
	gcc -c main.c -Wall
