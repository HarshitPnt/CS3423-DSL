RED := \033[01;31m
GREEN := \033[01;32m
RESET := \033[01;0m
SRC := src
TESTS := tests/test_files
FILES := $(wildcard ${TESTS}/*)
TESTS_TOKS := tests/logs

run: compile
	./prog ${FILE} ${LOGS}

compile:
	$(MAKE) -C ${SRC} compile
	rm -rf ./build
	mkdir ./build
	cp ${SRC}/prog ./build/prog

test: compile
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
	rm -rf ./build
	$(MAKE) -C ${SRC} clean
	rm -rf ${TESTS_TOKS}
	echo "${GREEN}Clean Successful${RESET}"