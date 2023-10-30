/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_TOKENS_H_INCLUDED
# define YY_YY_TOKENS_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PSEUDO_LOW = 258,              /* PSEUDO_LOW  */
    STRING = 259,                  /* STRING  */
    BOOL = 260,                    /* BOOL  */
    CHAR = 261,                    /* CHAR  */
    INT_8 = 262,                   /* INT_8  */
    INT_16 = 263,                  /* INT_16  */
    INT_32 = 264,                  /* INT_32  */
    INT_64 = 265,                  /* INT_64  */
    UINT_8 = 266,                  /* UINT_8  */
    UINT_16 = 267,                 /* UINT_16  */
    UINT_32 = 268,                 /* UINT_32  */
    UINT_64 = 269,                 /* UINT_64  */
    FLOAT_32 = 270,                /* FLOAT_32  */
    FLOAT_64 = 271,                /* FLOAT_64  */
    REGEX = 272,                   /* REGEX  */
    O_SET = 273,                   /* O_SET  */
    U_SET = 274,                   /* U_SET  */
    CFG = 275,                     /* CFG  */
    DFA = 276,                     /* DFA  */
    NFA = 277,                     /* NFA  */
    PDA = 278,                     /* PDA  */
    ID = 279,                      /* ID  */
    IF_KW = 280,                   /* IF_KW  */
    ELIF_KW = 281,                 /* ELIF_KW  */
    ELSE_KW = 282,                 /* ELSE_KW  */
    WHILE_KW = 283,                /* WHILE_KW  */
    BREAK_KW = 284,                /* BREAK_KW  */
    STRUCT_KW = 285,               /* STRUCT_KW  */
    RETURN_KW = 286,               /* RETURN_KW  */
    ARROW = 287,                   /* ARROW  */
    COLON = 288,                   /* COLON  */
    OPER_AND = 289,                /* OPER_AND  */
    OPER_OR = 290,                 /* OPER_OR  */
    OPER_COMP = 291,               /* OPER_COMP  */
    COMP_GT = 292,                 /* COMP_GT  */
    COMP_LT = 293,                 /* COMP_LT  */
    OPER_PLUS = 294,               /* OPER_PLUS  */
    OPER_MINUS = 295,              /* OPER_MINUS  */
    OPER_MUL = 296,                /* OPER_MUL  */
    OPER_DIV = 297,                /* OPER_DIV  */
    OPER_MOD = 298,                /* OPER_MOD  */
    AT_THE_RATE = 299,             /* AT_THE_RATE  */
    OPER_POWER = 300,              /* OPER_POWER  */
    OPER_NOT = 301,                /* OPER_NOT  */
    OPER_ASN = 302,                /* OPER_ASN  */
    OPER_ASN_SIMPLE = 303,         /* OPER_ASN_SIMPLE  */
    LPAREN = 304,                  /* LPAREN  */
    RPAREN = 305,                  /* RPAREN  */
    LBRACK = 306,                  /* LBRACK  */
    RBRACK = 307,                  /* RBRACK  */
    LBRACE = 308,                  /* LBRACE  */
    RBRACE = 309,                  /* RBRACE  */
    COMMA = 310,                   /* COMMA  */
    DOT = 311,                     /* DOT  */
    SEMICOLON = 312,               /* SEMICOLON  */
    SIN_QUOTE = 313,               /* SIN_QUOTE  */
    INT_CONST = 314,               /* INT_CONST  */
    FLOAT_CONST = 315,             /* FLOAT_CONST  */
    STRING_CONST = 316,            /* STRING_CONST  */
    CHAR_CONST = 317,              /* CHAR_CONST  */
    BOOL_CONST = 318,              /* BOOL_CONST  */
    REGEX_R = 319,                 /* REGEX_R  */
    REGEX_LIT = 320,               /* REGEX_LIT  */
    REGEX_NUM = 321,               /* REGEX_NUM  */
    REGEX_OR = 322,                /* REGEX_OR  */
    REGEX_STAR = 323,              /* REGEX_STAR  */
    REGEX_PLUS = 324,              /* REGEX_PLUS  */
    REGEX_QUE = 325,               /* REGEX_QUE  */
    REGEX_CARET = 326,             /* REGEX_CARET  */
    REGEX_LRANGE = 327,            /* REGEX_LRANGE  */
    REGEX_HYPHEN = 328,            /* REGEX_HYPHEN  */
    REGEX_RRANGE = 329,            /* REGEX_RRANGE  */
    REGEX_DOLLAR = 330,            /* REGEX_DOLLAR  */
    EPSILON = 331,                 /* EPSILON  */
    PSEUDO_TOKEN = 332             /* PSEUDO_TOKEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_TOKENS_H_INCLUDED  */
