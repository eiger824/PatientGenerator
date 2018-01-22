CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g --std=c11

all: txts clean test

txts:
	test -d txts || mkdir txts
test: randomize.c
	${CC} ${CFLAGS} $^ -o $@
	
clean:
	rm -rf *~ test txts
