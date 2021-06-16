CC = gcc
EXEC = MorseCode

MorseCode:main.o Morse.o Graphic.o
	$(CC) -o $(EXEC) main.o Morse.o Graphic.o -lSDL2 -lSDL2_image -lSDL2_ttf -std=c99
	./$(EXEC) --help

main.o:main.c ../headers/Morse.h ../headers/Graphic.h
	$(CC) -o main.o -c main.c -std=c99

Morse.o:Morse.c ../headers/Morse.h
	$(CC) -o Morse.o -c Morse.c -std=c99

Graphic.o:Graphic.c ../headers/Graphic.h
	$(CC) -o Graphic.o -c Graphic.c

clean:
	rm -rf *.o

mrproper:clean
	rm -rf $(EXEC)
