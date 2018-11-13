exe: main.o Player.o console.o gui.o Vector.o Pion.o consoleBoard.o sdlBoard.o Menu.o
	gcc main.o Player.o console.o gui.o Vector.o Pion.o consoleBoard.o sdlBoard.o Menu.o -o exe `sdl2-config --cflags --libs` -lSDL2_ttf -Wall

main.o: main.c
	gcc -c main.c -Wall

Menu.o: interfaces/sdl/Menu.h interfaces/sdl/Menu.c
	gcc -c interfaces/sdl/Menu.c -Wall

gui.o: interfaces/sdl/gui.h interfaces/sdl/gui.c
	gcc -c interfaces/sdl/gui.c -Wall

console.o: interfaces/console/console.h interfaces/console/console.c
	gcc -c interfaces/console/console.c -Wall

consoleBoard.o: interfaces/console/consoleBoard.h interfaces/console/consoleBoard.c
	gcc -c interfaces/console/consoleBoard.c -Wall

sdlBoard.o: interfaces/sdl/sdlBoard.h interfaces/sdl/sdlBoard.c
	gcc -c interfaces/sdl/sdlBoard.c -Wall

Vector.o: mods/Vector.h mods/Vector.c
	gcc -c mods/Vector.c -Wall 

Pion.o: mods/Pion.h mods/Pion.c
	gcc -c mods/Pion.c -Wall

Player.o: mods/Player.h mods/Player.c
	gcc -c mods/Player.c -Wall