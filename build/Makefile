SRC := ../src
_CSRC := semantic.c
YACCDEFINE := --defines
YACCFLAGS := -v -t -o
OBJS := lexer.o parser.o semantic.o
CSRC := $(pathsubst %,${SRC}/%,$(_CSRC))
COMPILER := g++

parser: ${SRC}/parser.y
	bison ${YACCDEFINE}=tokens.hh ${YACCFLAGS} parser.cc ${SRC}/parser.y
	${COMPILER} -c parser.cc

lexer: ${SRC}/lexer.l
	flex -o lexer.cc ${SRC}/lexer.l
	${COMPILER} -c lexer.cc

semantic: ${SRC}/semantic.cc
	${COMPILER} -c ${SRC}/semantic.cc

compile:clean parser lexer semantic
	${COMPILER} -o prog parser.o lexer.o semantic.o

clean:
	rm -f *.o parser.o lexer.o semantic.o
	rm -f parser.cc lexer.cc
	rm -f tokens.hh parser.output prog