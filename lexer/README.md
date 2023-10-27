# Running Tests

- The tests for the lexical analyzer are placed in `/tests/lexer_tests/` directory.
- There are four types of tests `complex_tests`, `easy_tests`, `medium_tests` and `error_tests`.
- Inorder to execute the tests run the following command from `/lexer/` directory.

```bash
make run FILE=../tests/lexer_tests/<test_type>/test_files/<test_name>.fsm
```

- The token files will be generated in `/tests/lexer_tests/<test_type>/tokens/seq_tokens_<test_name>.tok`
