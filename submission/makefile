RED := \033[01;31m
GREEN := \033[01;32m
RESET := \033[01;0m
YACCDEFINE := --defines
YACCFLAGS := -v -t -o
SRC := ./code/src
BUILD := ./code/build
TESTS2 := testcases/phase2/testfiles
TESTS3 := testcases/phase3/testfiles
TESTS4 := testcases/phase4/testfiles
FILES2 := $(wildcard ${TESTS2}/*)
FILES3 := $(wildcard ${TESTS3}/*)
FILES4 := $(wildcard ${TESTS4}/*)
TESTS_TOKS2 := ./testcases/phase2/logs
TESTS_TOKS3 := ./testcases/phase3/logs
TESTS_TOKS4 := ./testcases/phase4/logs
_CSRC := lexer.l parser.y semantic.c
OBJS := lexer.o parser.o semantic.o
CSRC := $(pathsubst %,${SRC}/%,$(_CSRC))
LIBFOLDER := lib
COMPILER := g++
VERSION := -std=c++17

compile:
	 ${MAKE} -C ${BUILD} compile

run: compile
	rm -rf ${TESTS_TOKS2}
	mkdir ${TESTS_TOKS2}
	rm -rf ${TESTS_TOKS3}
	mkdir ${TESTS_TOKS3}
	rm -rf ${TESTS_TOKS4}
	mkdir ${TESTS_TOKS4}
	${BUILD}/prog ${FILE} ${LOGS}

test_code_gen : library
	${COMPILER} ${VERSION} -c ${FILE}.cc -o ${FILE}.o
	${COMPILER} -o ${FILE} ${FILE}.o -L./${LIBFOLDER} -lfsm
	./${FILE}
	

library: 
	${MAKE} -C ${BUILD} library
	
test: compile
	rm -rf ${TESTS_TOKS2}
	mkdir ${TESTS_TOKS2}
	rm -rf ${TESTS_TOKS3}
	mkdir ${TESTS_TOKS3}
	rm -rf ${TESTS_TOKS4}
	mkdir ${TESTS_TOKS4}
	@echo "-----------------------------------"
	@echo "Testing Phase 2"
	@for file in $(FILES2); do \
		echo "Processing $$file" && ${BUILD}/prog $$file; \
		if [ $$? = 0 ]; then \
			echo "${GREEN}Test Passed${RESET}"; \
			echo "-----------------------------------"; \
		else \
			echo "${RED}Test Failed${RESET}"; \
			echo "-----------------------------------"; \
		fi \
	done
	@echo "-----------------------------------"
	@echo "Testing Phase 3"
	@for file in $(FILES3); do \
		echo "Processing $$file" && ${BUILD}/prog $$file; \
		if [ $$? = 0 ]; then \
			echo "${GREEN}Test Passed${RESET}"; \
			echo "-----------------------------------"; \
		else \
			echo "${RED}Test Failed${RESET}"; \
			echo "-----------------------------------"; \
		fi \
	done
	@echo "-----------------------------------"
	@echo "Testing Phase 4"
	@for file in $(FILES4); do \
		echo "Processing $$file" && ${BUILD}/prog $$file; \
		if [ $$? = 0 ]; then \
			echo "${GREEN}Test Passed${RESET}"; \
			echo "-----------------------------------"; \
		else \
			echo "${RED}Test Failed${RESET}"; \
			echo "-----------------------------------"; \
		fi \
	done

clean:
	${MAKE} -C ${BUILD} clean
	rm -rf ${TESTS_TOKS2}
	rm -rf ${TESTS_TOKS3}
	rm -rf ${TESTS_TOKS4}
	echo "${GREEN}Clean Successful${RESET}"