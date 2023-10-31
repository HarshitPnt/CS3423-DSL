FILES := $(wildcard ${FOLDER}/*)
RED := \033[0;31m
GREEN := \033[0;32m
RESET := \033[0m

run: compile
	./lexer ${FILE}

test: compile ${FILES}
	@for file in $(FILES); do \
		echo "Processing $$file" && ./lexer $$file; \
		if [ $$? = 0 ]; then \
            echo "${GREEN}LEXER Test Passed${RESET}"; \
			echo "-----------------------------------"; \
        else \
            echo "${RED}LEXER Test Failed${RESET}"; \
			echo "-----------------------------------"; \
        fi \
	done

compile:
	lex lex.l
	gcc lex.yy.c -o lexer

