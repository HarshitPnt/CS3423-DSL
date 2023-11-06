RED := \033[01;31m
GREEN := \033[01;32m
RESET := \033[01;0m
YACCDEFINE := --defines
YACCFLAGS := -v -t -o
SRC := src
BUILD := build
TESTS := tests/test_files
FILES := $(wildcard ${TESTS}/*)
TESTS_TOKS := tests/logs
_CSRC := lexer.l parser.y semantic.c
OBJS := lexer.o parser.o semantic.o
CSRC := $(pathsubst %,${SRC}/%,$(_CSRC))

run: build
	./prog ${FILE} ${LOGS}

build: ${CSRC}
	echo "${CSRC}"
	 ${MAKE} -C ./build compile
	
test: build
	rm -rf ${TESTS_TOKS}
	mkdir ${TESTS_TOKS}
	@for file in $(FILES); do \
		echo "Processing $$file" && ./build/prog $$file; \
		if [ $$? = 0 ]; then \
			echo "${GREEN}Test Passed${RESET}"; \
			echo "-----------------------------------"; \
		else \
			echo "${RED}Test Failed${RESET}"; \
			echo "-----------------------------------"; \
		fi \
	done

clean:
	${MAKE} -C ./build clean
	echo "${GREEN}Clean Successful${RESET}"