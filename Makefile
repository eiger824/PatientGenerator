CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g --std=c11

all: clean txts test

txts:
	test -d txts || mkdir txts

test: randomize.c
	${CC} ${CFLAGS} $^ -o $@
	
clean:
	rm -rf *~ test txts
