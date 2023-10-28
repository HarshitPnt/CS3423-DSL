# Running Tests

- The tests for the lexical analyzer are placed in `/tests/lexer_tests/` directory.
- There are four types of tests `complex_tests`, `easy_tests`, `medium_tests` and `error_tests`.
- Inorder to execute the tests run the following command from `/lexer/` directory.

```bash
make run FILE=../tests/lexer_tests/<test_type>/test_files/<test_name>.fsm
```

- The token files will be generated in `/test/lexer_tests/<test_type>/tokens/seq_tokens_<test_name>.tok`

- Inorder to run the tests on entire folder run the following command from `/lexer/` directory.

```bash
make test FOLDER=../test/lexer_tests/<test_type>/test_files
# example currently on easy_tests

make test FOLDER=../test/lexer_tests/easy_tests/test_files
```
