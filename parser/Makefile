YACCDEFINE = --defines
YACCFLAGS =  -t -v -o

run: parser
	flex -o ./build/lexer.c lex.l
	rm ./parser
	gcc -c ./build/lexer.c -o ./build/lexer.o
	gcc -c ./build/parser.c -o ./build/parser.o
	gcc -lfl ./build/lexer.o ./build/parser.o -o parser
	./parser ${FILE}

parser: parser.y
	rm -rf ./build
	mkdir ./build
	bison $(YACCDEFINE)=./build/tokens.h parser.y ${YACCFLAGS} ./build/parser.c