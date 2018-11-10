exe: police.o
	gcc police.o -o exe `sdl2-config --cflags --libs` -lSDL_ttf -Wall

main.o: police.c
	gcc -c police.c -Wall