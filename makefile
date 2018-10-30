exe: console.o gui.o Vector.o main.o Pion.o Player.o consoleBoard.o sdlBoard.o
	gcc console.o gui.o Vector.o main.o Pion.o Player.o consoleBoard.o sdlBoard.o -o exe `sdl2-config --cflags --libs` -lm -Wall

main.o: interfaces/console/console.c interfaces/sdl/gui.c main.c
	gcc -c main.c -Wall

gui.o: interfaces/sdl/gui.h interfaces/sdl/gui.c
	gcc -c interfaces/sdl/gui.c -Wall

console.o: interfaces/console/console.h interfaces/console/console.c interfaces/console/consoleBoard.h
	gcc -c interfaces/console/console.c -Wall

consoleBoard.o: interfaces/console/consoleBoard.h interfaces/console/consoleBoard.c define.h
	gcc -c interfaces/console/consoleBoard.c -Wall

sdlBoard.o: interfaces/sdl/sdlBoard.h interfaces/sdl/sdlBoard.c define.h
	gcc -c interfaces/sdl/sdlBoard.c -Wall

Vector.o: mods/Vector.h mods/Vector.c
	gcc -c mods/Vector.c -Wall 

Pion.o: mods/Pion.h mods/Pion.c define.h
	gcc -c mods/Pion.c -Wall

Player.o: mods/Player.h mods/Player.c
	gcc -c mods/Player.c -Wall
