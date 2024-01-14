all: 
	gcc -Wall  -g functions.c bmp.c main.c -o  test

val: test
	valgrind --leak-check=full --track-origins=yes -s ./test