YACCDEFINE = --defines
YACCFLAGS = -v -t -o

compile: parser lexer
	gcc -c ./lexer.c ./parser.c
	gcc -o ./prog ./lexer.o ./parser.o
	echo "Compilation Successful"

parser: parser.y
	bison $(YACCDEFINE)=./tokens.h parser.y ${YACCFLAGS} ./parser.c -Wcounterexamples

lexer: lexer.l ./tokens.h
	flex -o ./lexer.c lexer.l

clean:
	rm -rf ./lexer.c ./parser.c ./parser ./lexer.o ./parser.o ./tokens.h ./parser.output ./prog
