CC 				= gcc
#DEBUG 			= -DDEBUG_ENABLED
CFLAGS 			= -Wall -Wextra -Wpedantic -g --std=c11 -fPIC ${DEBUG}
CFLAGS_COMPILE 	= -c
LDFLAGS			= 

BUILD 			= build
TXTS			= txts
HTMLS			= html

PROGRAM 		= patient-generator 
OBJS 			= ${BUILD}/dll.o \
				  ${BUILD}/db.o \
				  ${BUILD}/utils.o \
				  ${BUILD}/timelib.o \
				  ${BUILD}/files.o \
				  ${BUILD}/html.o \
				  ${BUILD}/randomize.o

all: clean ${TXTS} ${HTMLS} ${BUILD} ${PROGRAM} 

${TXTS}:
	test -d ${TXTS} || mkdir ${TXTS} 

${BUILD}:
	test -d ${BUILD} || mkdir ${BUILD} 

${HTMLS}:
	test -d ${HTMLS} || mkdir ${HTMLS}

${PROGRAM}: ${OBJS} 
	${CC} ${CFLAGS} $^ ${LDFLAGS} -o ${BUILD}/$@
	rm -f ${PROGRAM}
	ln -s ${BUILD}/$@ ${PROGRAM}

${BUILD}/dll.o: dll.c dll.h
	${CC} ${CFLAGS} ${CFLAGS_COMPILE} $< -o $@

${BUILD}/db.o: db.c db.h
	${CC} ${CFLAGS} ${CFLAGS_COMPILE} $< -o $@

${BUILD}/utils.o: utils.c utils.h
	${CC} ${CFLAGS} ${CFLAGS_COMPILE} $< -o $@

${BUILD}/files.o: files.c files.h
	${CC} ${CFLAGS} ${CFLAGS_COMPILE} $< -o $@

${BUILD}/timelib.o: timelib.c timelib.h
	${CC} ${CFLAGS} ${CFLAGS_COMPILE} $< -o $@

${BUILD}/html.o: html.c html.h
	${CC} ${CFLAGS} ${CFLAGS_COMPILE} $< -o $@

${BUILD}/randomize.o: randomize.c dll.c dll.h db.c db.h
	${CC} ${CFLAGS} ${CFLAGS_COMPILE} $< -o $@
	
new: clean ${TXTS} ${BUILD} ${PROGRAM} run
int: clean ${TXTS} ${BUILD} ${PROGRAM} with-db 

run:
	clear
	./${PROGRAM}

with-db:
	clear
	./${PROGRAM} -i

clean:
	rm -rf *~ ${PROGRAM} ${BUILD} ${TXTS} ${HTMLS}

