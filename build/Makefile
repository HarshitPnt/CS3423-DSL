SRC := ../src
_CSRC := semantic.c
YACCDEFINE := --defines
YACCFLAGS := -v -t -o
OBJS := lexer.o parser.o semantic.o
CSRC := $(pathsubst %,${SRC}/%,$(_CSRC))

parser: ${SRC}/parser.y
	bison ${YACCDEFINE}=tokens.h ${YACCFLAGS} parser.c ${SRC}/parser.y

lexer: ${SRC}/lexer.l
	flex -o lexer.c ${SRC}/lexer.l

semantic: ${SRC}/semantic.c
	gcc -c ${SRC}/semantic.c

compile:clean parser lexer semantic
	gcc -lfl -o prog parser.c lexer.c semantic.o

clean:
	rm -rf *.o parser.c lexer.c tokens.h parser.output prog