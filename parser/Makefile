YACCDEFINE = --defines
YACCFLAGS =  -t -v -o
FILES := $(wildcard ${FOLDER}/*)
RED := \033[0;31m
GREEN := \033[0;32m
RESET := \033[0m

run: compile
	./parser ${FILE}

parser: parser.y
	rm -rf ./build
	mkdir ./build
	bison $(YACCDEFINE)=./build/tokens.h parser.y ${YACCFLAGS} ./build/parser.c -Wcounterexamples

test: compile ${FILES}
	@for file in $(FILES); do \
		echo "Processing $$file" && ./parser $$file; \
		if [ $$? = 0 ]; then \
            echo "${GREEN}LEXER Test Passed${RESET}"; \
			echo "-----------------------------------"; \
        else \
            echo "${RED}LEXER Test Failed${RESET}"; \
			echo "-----------------------------------"; \
        fi \
	done

compile: parser
	flex -o ./build/lexer.c lex.l
	rm -f ./parser
	gcc -c ./build/lexer.c -o ./build/lexer.o
	gcc -c ./build/parser.c -o ./build/parser.o
	gcc -lfl ./build/lexer.o ./build/parser.o -o parser