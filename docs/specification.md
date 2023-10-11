- [Introduction](#introduction)
  - [What is XYZ?](#what-is-xyz)
  - [Why XYZ?](#why-xyz)
- [Language Specifications](#language-specifications)
  - [Data Types](#data-types)
    - [Primitive Data Types](#primitive-data-types)
      - [Integer:](#integer)
      - [Character:](#character)
      - [Float:](#float)
      - [Boolean:](#boolean)
    - [Comments](#comments)
  - [Operators](#operators)
    - [Arithmetic Operators](#arithmetic-operators)
    - [Logical Operators](#logical-operators)
    - [Comparison Operators](#comparison-operators)
    - [Assignment Operators](#assignment-operators)
    - [Operator Precedence](#operator-precedence)
  - [Control Flow](#control-flow)
    - [If-Else](#if-else)
    - [Loops](#loops)
  - [Constants](#constants)
  - [Keywords](#keywords)
  - [Identifiers](#identifiers)
- [References](#references)

# Introduction

## What is XYZ?

## Why XYZ?

# Language Specifications

XYZ follows, making it easier for programmers to pick up the language easily and keep their focus on the logic rather than the language.

- XYZ is a **statically typed** language
- XYZ is a **strongly typed** language
- XYZ is a **procedural** language

XYZ does not support Object Oriented Programming(**OOPs**).

## Data Types

The language uses common data types found in most programming languages.

### Primitive Data Types

#### Integer: 
Integers are represented by the `int_x` keyword, where `x` is the number of bits used to represent the integer. The language supports 8, 16, 32 and 64 bit integers.

#### Character:
Characters are represented by the `char` keyword. The language supports 8 bit characters.

#### Float: 
Floats are represented by the `float_x` keyword, where `x` is the number of bits used to represent the float. The language supports 32 and 64 bit floats.

#### Boolean:
Booleans are represented by the `bool` keyword, which is similar to the `bool` keyword in C, C++, Java and Python.

### Comments

XYZ has only one type of comment, that can act as both single line and multi line comments. The comment starts with `<!--` and ends with `--!>`. Below is an example of a comment:

```
<!-- This is a comment --!>

<!-- This is a
multi line comment --!>
```


## Operators
Operators supports by the language are similar to the operators supported by C.

### Arithmetic Operators

| Operator | Description | Associativity |
| :---: | :---: | :---: |
| `+` | Addition | Left to Right |
| `-` | Subtraction | Left to Right |
| `*` | Multiplication | Left to Right |
| `/` | Division | Left to Right |
| `%` | Modulo | Left to Right |

### Logical Operators

| Operator | Description | Associativity |
| :---: | :---: | :---: |
| `&&` | Logical AND | Left to Right |
| `||` | Logical OR | Left to Right |
| `!` | Logical NOT | Right to Left |

### Comparison Operators

| Operator | Description | Associativity |
| :---: | :---: | :---: |
| `==` | Equal to | Left to Right |
| `!=` | Not equal to | Left to Right |
| `>` | Greater than | Left to Right |
| `<` | Less than | Left to Right |
| `>=` | Greater than or equal to | Left to Right |
| `<=` | Less than or equal to | Left to Right |

### Assignment Operators

| Operator | Description | Associativity |
| :---: | :---: | :---: |
| `=` | Assignment | Right to Left |
| `+=` | Addition Assignment | Right to Left |
| `-=` | Subtraction Assignment | Right to Left |
| `*=` | Multiplication Assignment | Right to Left |
| `/=` | Division Assignment | Right to Left |
| `%=` | Modulo Assignment | Right to Left |
| `&=` | Logical AND Assignment | Right to Left |
| `|=` | Logical OR Assignment | Right to Left |

### Operator Precedence

| Operator | Description |
| :---: | :---: |
| `()` | Parentheses |
| `!` | Logical NOT |
| `*`, `/`, `%` | Multiplication, Division, Modulo |
| `+`, `-` | Addition, Subtraction |
| `>`, `<`, `>=`, `<=` | Comparison |
| `==`, `!=` | Equality |
| `&&` | Logical AND |
| `||` | Logical OR |
| `=` | Assignment |
| `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=` | Assignment |

## Control Flow

XYZ enforce the use of curly braces for all control flow statements. The language does not support the use of indentation for control flow statements. The language supports the following control flow statements:

### If-Else

Below is the syntax for the if-else statement:

```
if (condition) {
    statement;
} elif {
    statement;
} else {
    statement;
}
```

### Loops

XYZ only supports the `while` loop. Below is the syntax for the `while` loop:

```
while (condition) {
    statements;
}
```

## Constants

## Keywords

## Identifiers

# References

