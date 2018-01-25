CC 				= gcc
DEBUG 			= -DDEBUG_ENABLED
CFLAGS 			= -Wall -Wextra -Wpedantic -g --std=c11 -fPIC ${DEBUG}
CFLAGS_COMPILE 	= -c
LDFLAGS			= 

BUILD 			= build
TXTS			= txts

PROGRAM 		= test
OBJS 			= ${BUILD}/dll.o \
				  ${BUILD}/db.o \
				  ${BUILD}/randomize.o

all: clean ${TXTS} ${BUILD} ${PROGRAM} 

${TXTS}:
	test -d ${TXTS} || mkdir ${TXTS} 

${BUILD}:
	test -d ${BUILD} || mkdir ${BUILD} 

test: ${OBJS} 
	${CC} ${CFLAGS} $^ ${LDFLAGS} -o ${BUILD}/$@
	rm -f ${PROGRAM}
	ln -s ${BUILD}/$@ ${PROGRAM}

${BUILD}/dll.o: dll.c dll.h
	${CC} ${CFLAGS} ${CFLAGS_COMPILE} $< -o $@

${BUILD}/db.o: db.c db.h
	${CC} ${CFLAGS} ${CFLAGS_COMPILE} $< -o $@

${BUILD}/randomize.o: randomize.c dll.c dll.h db.c db.h
	${CC} ${CFLAGS} ${CFLAGS_COMPILE} $< -o $@
	
clean:
	rm -rf *~ ${PROGRAM} ${BUILD} ${TXTS}

