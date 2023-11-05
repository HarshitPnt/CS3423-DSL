YACCDEFINE = --defines
YACCFLAGS = -v -t -o

compile: parser lexer semantic
	gcc -c ./lexer.c ./parser.c ./semantic.c
	gcc -o ./prog ./lexer.o ./parser.o ./semantic.o
	echo "Compilation Successful"

semantic: semantic.c
	gcc -c ./semantic.c

parser: parser.y
	bison $(YACCDEFINE)=./tokens.h parser.y ${YACCFLAGS} ./parser.c -Wcounterexamples

lexer: lexer.l ./tokens.h
	flex -o ./lexer.c lexer.l

clean:
	rm -f ./prog
	rm -f ./lexer.c ./lexer.o
	rm -f ./parser.c ./parser.output ./parser.o
	rm -f ./semantic.o
	rm -f ./tokens.h
