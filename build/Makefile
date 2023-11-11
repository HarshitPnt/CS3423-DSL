SRC := ../src
_CSRC := semantic.c
YACCDEFINE := --defines
YACCFLAGS := -v --debug -o
OBJS := lexer.o parser.o semantic.o
CSRC := $(patsubst %,${SRC}/%,$(_CSRC))
COMPILER := g++
VERSION := -std=c++17

parser: ${SRC}/parser.y
	bison ${YACCDEFINE}=tokens.hh ${YACCFLAGS} parser.cc ${SRC}/parser.y
	${COMPILER} ${VERSION} -c parser.cc

lexer: ${SRC}/lexer.l
	flex -o lexer.cc ${SRC}/lexer.l
	${COMPILER} ${VERSION} -c lexer.cc

semantic: ${SRC}/semantic.cc
	${COMPILER} ${VERSION} -c ${SRC}/semantic.cc

compile:clean parser lexer semantic
	${COMPILER} -o prog parser.o lexer.o semantic.o

clean:
	rm -f *.o parser.o lexer.o semantic.o
	rm -f parser.cc lexer.cc
	rm -f tokens.hh parser.output prog
