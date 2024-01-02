all: test

test: functions.c main.c
	gcc -Wall -Wextra -g functions.c main.c -o test

val: test
	valgrind --leak-check=full --track-origins=yes -s ./test