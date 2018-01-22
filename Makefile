CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g --std=c11

test: randomize.c
	${CC} ${CFLAGS} $^ -o $@
	
clean:
	rm -f *~ test