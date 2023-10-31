cd ../tests/lexer
rm -rf tokens
mkdir tokens

cd ../../lexer
make compile
make test FOLDER=../tests/lexer/test_files