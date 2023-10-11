---
title: XYZ Language Specification
author: Compilers Project
geometry: margin=2cm
documentclass: extarticle
fontsize: 12pt
header-includes:
    - \usepackage{setspace}
    - \onehalfspacing
---

$$ \large{\text{Authors}} $$
$$ \text{Vishal Vijay Devadiga (CS21BTECH11061)} $$
$$ \text{Satpute Aniket Tukaram (CS21BTECH11056)} $$
$$ \text{Mahin Bansal (CS21BTECH11034)} $$
$$ \text{Harshit Pant (CS21BTECH11021)} $$

\pagebreak
# Table of Contents
- [Table of Contents](#table-of-contents)
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
    - [Composite Data Types](#composite-data-types)
      - [Sets:](#sets)
      - [Structs:](#structs)
    - [Comments](#comments)
  - [Operators](#operators)
    - [Arithmetic Operators](#arithmetic-operators)
    - [Logical Operators](#logical-operators)
    - [Comparison Operators](#comparison-operators)
    - [Assignment Operators](#assignment-operators)
    - [Misc Operators](#misc-operators)
    - [Operator Precedence](#operator-precedence)
  - [Control Flow](#control-flow)
    - [If-Else](#if-else)
    - [Loops](#loops)
  - [Constants](#constants)
  - [Keywords](#keywords)
  - [Identifiers](#identifiers)
  - [Statements](#statements)
- [References](#references)

\pagebreak
# Introduction

## What is XYZ?

## Why XYZ?

\pagebreak
# Language Specifications

XYZ follows, making it easier for programmers to pick up XYZ easily and keep their focus on the logic rather than XYZ.

- XYZ is a **statically typed** language
- XYZ is a **strongly typed** language
- XYZ is a **procedural** language
- XYZ is case sensitive.

XYZ does not support Object Oriented Programming(**OOPs**).

## Data Types

XYZ uses common data types found in most programming languages.

### Primitive Data Types

#### Integer: 
Signed Integers are represented by the `int_x` keyword, where `x` is the number of bits used to represent the integer. XYZ supports 8, 16, 32 and 64 bit integers.

Unsigned Integers are represented by the `uint_x` keyword, where `x` is the number of bits used to represent the integer. XYZ supports 8, 16, 32 and 64 bit integers.

#### Character:
Characters are represented by the `char` keyword. XYZ supports 8 bit characters.

#### Float: 
Floats are represented by the `float_x` keyword, where `x` is the number of bits used to represent the float. XYZ supports 32 and 64 bit floats.

#### Boolean:
Booleans are represented by the `bool` keyword, which is similar to the `bool` keyword in C, C++, Java and Python.

### Composite Data Types

#### Sets:
Sets are collections of elements of the same data type. XYZ supports two types of sets: Ordered Sets and Unordered Sets.

- Ordered Sets are represented by the `o_set` keyword. 
- Unordered Sets are represented by the `u_set` keyword. 

#### Structs:
Structs are represented by the `struct` keyword. Structs can contain any data type supported by XYZ.

### Comments

XYZ has only one type of comment, that can act as both single line and multi line comments. The comment starts with `<!--` and ends with `--!>`. Below is an example of a comment:

```markdown
<!-- This is a comment --!>

<!-- This is a
multi line comment --!>
```

## Operators
Operators supports by XYZ are similar to the operators supported by C.

### Arithmetic Operators

| Operator |  Description   | Associativity |
| :------: | :------------: | :-----------: |
|   `+`    |    Addition    | Left to Right |
|   `-`    |  Subtraction   | Left to Right |
|   `*`    | Multiplication | Left to Right |
|   `/`    |    Division    | Left to Right |
|   `%`    |     Modulo     | Left to Right |

### Logical Operators

| Operator | Description | Associativity |
| :------: | :---------: | :-----------: |
|   `&&`   | Logical AND | Left to Right |
|  `\|\|`  | Logical OR  | Left to Right |
|   `!`    | Logical NOT | Right to Left |

### Comparison Operators

| Operator |       Description        | Associativity |
| :------: | :----------------------: | :-----------: |
|   `==`   |         Equal to         | Left to Right |
|   `!=`   |       Not equal to       | Left to Right |
|   `>`    |       Greater than       | Left to Right |
|   `<`    |        Less than         | Left to Right |
|   `>=`   | Greater than or equal to | Left to Right |
|   `<=`   |  Less than or equal to   | Left to Right |

### Assignment Operators

| Operator |        Description        | Associativity |
| :------: | :-----------------------: | :-----------: |
|   `=`    |        Assignment         | Right to Left |
|   `+=`   |    Addition Assignment    | Right to Left |
|   `-=`   |  Subtraction Assignment   | Right to Left |
|   `*=`   | Multiplication Assignment | Right to Left |
|   `/=`   |    Division Assignment    | Right to Left |
|   `%=`   |     Modulo Assignment     | Right to Left |
|   `&=`   |  Logical AND Assignment   | Right to Left |
|  `\|=`   |   Logical OR Assignment   | Right to Left |

### Misc Operators

| Operator |     Description      | Associativity |
| :------: | :------------------: | :-----------: |
|   `.`    | Access Struct Member | Left to Right |
|   `[]`   |  Access Set Element  | Left to Right |


### Operator Precedence

|                 Operator                  |           Description            |
| :---------------------------------------: | :------------------------------: |
|                   `()`                    |           Parentheses            |
|                    `!`                    |           Logical NOT            |
|               `*`, `/`, `%`               | Multiplication, Division, Modulo |
|                 `+`, `-`                  |      Addition, Subtraction       |
|           `>`, `<`, `>=`, `<=`            |            Comparison            |
|                `==`, `!=`                 |             Equality             |
|                   `&&`                    |           Logical AND            |
|                  `\|\|`                   |            Logical OR            |
|                    `=`                    |            Assignment            |
| `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `\|=` |            Assignment            |

## Control Flow

XYZ enforce the use of curly braces for all control flow statements. XYZ does not support the use of indentation for control flow statements. XYZ supports the following control flow statements:

### If-Else

Below is the syntax for the if-else statement:

```python
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

```c
while (condition) {
    statements;
}
```

## Constants

Constants are represented by the `const` keyword. Constants can be of any data type supported by XYZ.

## Keywords

|  Keyword   |   Description    |
| :--------: | :--------------: |
|  `int_x`   |     Integer      |
|  `uint_x`  | Unsigned Integer |
|   `char`   |    Character     |
| `float_x`  |      Float       |
|   `bool`   |     Boolean      |
|  `const`   |     Constant     |
|  `struct`  |      Struct      |
|  `o_set`   |   Ordered Set    |
|  `u_set`   |  Unordered Set   |
|    `if`    |        If        |
|   `elif`   |     Else If      |
|   `else`   |       Else       |
|  `while`   |      While       |
|  `break`   |      Break       |
| `continue` |     Continue     |
|  `return`  |      Return      |
|   `true`   |       True       |
|  `false`   |      False       |
|   `<!--`   | Start of comment |
|   `--!>`   |  End of comment  |

## Identifiers

XYZ uses the following rules for identifiers:

- Identifiers can only contain alphanumeric characters and underscores.
- Identifiers cannot start with a number.
- Identifiers cannot be a keyword.
- Identifiers cannot contain spaces.
- Identifiers cannot contain special characters.

Regular Expressions for Identifiers:

```re
[a-zA-Z_][a-zA-Z0-9_]*
```

## Statements

\pagebreak
# References

