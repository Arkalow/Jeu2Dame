exe: gui.o
	gcc gui.o -o exe `sdl2-config --cflags --libs` -Wall
gui.o: gui.c
	gcc -c gui.c -Wall
