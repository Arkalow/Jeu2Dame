exe: gui.o Vector.o main.o Pion.o Player.o
	gcc Vector.o main.o Pion.o Player.o gui.o -o exe `sdl2-config --cflags --libs` -lm -Wall

gui.o: gui.c
	gcc -c gui.c -Wall

main.o: Pion.h Vector.h main.c
	gcc -c main.c -Wall

Vector.o: Vector.h Vector.c
	gcc -c Vector.c -Wall 

Pion.o: Pion.h Pion.c
	gcc -c Pion.c -Wall

Player.o: Player.h Player.c
	gcc -c Player.c -Wall
