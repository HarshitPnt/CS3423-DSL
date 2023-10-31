#!/bin/bash

comp=$1

if [ $comp == "lexer" ]
then
    cd ../tests/lexer
    rm -rf tokens
    mkdir tokens

    cd ../../lexer
    make compile
    make test FOLDER=../tests/lexer/test_files
elif [ $comp == "parser" ]
then
    cd ../tests/parser
    rm -rf logs
    mkdir logs

    cd ../../parser
    make compile
    make test FOLDER=../tests/parser/test_files
# elif [ $comp == "semantic" ]
# then
#     cd ../tests/semantic
#     rm -rf ast
#     mkdir ast

#     cd ../../semantic
#     make compile
#     make test FOLDER=../tests/semantic/test_files
# elif [ $comp == "codegen" ]
# then
#     cd ../tests/codegen
#     rm -rf ast
#     mkdir ast

#     cd ../../codegen
#     make compile
#     make test FOLDER=../tests/codegen/test_files
elif [ $comp == "all" ]
then
    cd ../tests/lexer
    rm -rf tokens
    mkdir tokens

    cd ../../lexer
    make compile
    make test FOLDER=../tests/lexer/test_files

    cd ../tests/parser
    rm -rf logs
    mkdir logs

    cd ../../parser
    make compile
    make test FOLDER=../tests/parser/test_files

    # cd ../tests/semantic
    # rm -rf ast
    # mkdir ast

    # cd ../../semantic
    # make compile
    # make test FOLDER=../tests/semantic/test_files

    # cd ../tests/codegen
    # rm -rf ast
    # mkdir ast

    # cd ../../codegen
    # make compile
    # make test FOLDER=../tests/codegen/test_files
else
    echo "Invalid input"
fi