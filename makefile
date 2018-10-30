exe: console.o gui.o Vector.o main.o Pion.o Player.o
	gcc console.o gui.o Vector.o main.o Pion.o Player.o -o exe `sdl2-config --cflags --libs` -lm -Wall

main.o: interface/console.c interface/gui.c main.c
	gcc -c main.c -Wall

gui.o: interface/gui.h interface/gui.c
	gcc -c interface/gui.c -Wall

console.o: interface/console.h interface/console.c
	gcc -c interface/console.c -Wall

Vector.o: mods/Vector.h mods/Vector.c
	gcc -c mods/Vector.c -Wall 

Pion.o: mods/Pion.h mods/Pion.c define.h
	gcc -c mods/Pion.c -Wall

Player.o: mods/Player.h mods/Player.c
	gcc -c mods/Player.c -Wall
