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

#ifndef YY_YY_TOKENS_HH_INCLUDED
# define YY_YY_TOKENS_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 61 "../src/parser.y"

    #include "../includes/semantic.hh"
    #include "../includes/attr.hh"
    #include "../includes/helper.hh"

#line 55 "tokens.hh"

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
    TYPE_PRIMITIVE = 259,          /* TYPE_PRIMITIVE  */
    TYPE_STRING = 260,             /* TYPE_STRING  */
    TYPE_REG = 261,                /* TYPE_REG  */
    TYPE_SET = 262,                /* TYPE_SET  */
    TYPE_AUTOMATA = 263,           /* TYPE_AUTOMATA  */
    INT_CONST = 264,               /* INT_CONST  */
    FLOAT_CONST = 265,             /* FLOAT_CONST  */
    STRING_CONST = 266,            /* STRING_CONST  */
    CHAR_CONST = 267,              /* CHAR_CONST  */
    BOOL_CONST = 268,              /* BOOL_CONST  */
    REGEX_R = 269,                 /* REGEX_R  */
    ID = 270,                      /* ID  */
    REGEX_LIT = 271,               /* REGEX_LIT  */
    IF_KW = 272,                   /* IF_KW  */
    ELIF_KW = 273,                 /* ELIF_KW  */
    ELSE_KW = 274,                 /* ELSE_KW  */
    WHILE_KW = 275,                /* WHILE_KW  */
    BREAK_KW = 276,                /* BREAK_KW  */
    STRUCT_KW = 277,               /* STRUCT_KW  */
    RETURN_KW = 278,               /* RETURN_KW  */
    CONTINUE_KW = 279,             /* CONTINUE_KW  */
    TEMP_FN_KW = 280,              /* TEMP_FN_KW  */
    ARROW = 281,                   /* ARROW  */
    COLON = 282,                   /* COLON  */
    COMMA = 283,                   /* COMMA  */
    DOT = 284,                     /* DOT  */
    SEMICOLON = 285,               /* SEMICOLON  */
    DOLLAR = 286,                  /* DOLLAR  */
    OPER_AND = 287,                /* OPER_AND  */
    OPER_OR = 288,                 /* OPER_OR  */
    OPER_COMP = 289,               /* OPER_COMP  */
    COMP_GT = 290,                 /* COMP_GT  */
    COMP_LT = 291,                 /* COMP_LT  */
    TEMP_LEFT = 292,               /* TEMP_LEFT  */
    TEMP_RIGHT = 293,              /* TEMP_RIGHT  */
    OPER_PLUS = 294,               /* OPER_PLUS  */
    OPER_MINUS = 295,              /* OPER_MINUS  */
    OPER_MUL = 296,                /* OPER_MUL  */
    OPER_DIV = 297,                /* OPER_DIV  */
    OPER_MOD = 298,                /* OPER_MOD  */
    AT_THE_RATE = 299,             /* AT_THE_RATE  */
    OPER_POWER = 300,              /* OPER_POWER  */
    OPER_NOT = 301,                /* OPER_NOT  */
    OPER_HASH = 302,               /* OPER_HASH  */
    OPER_ASN = 303,                /* OPER_ASN  */
    OPER_ASN_SIMPLE = 304,         /* OPER_ASN_SIMPLE  */
    LPAREN = 305,                  /* LPAREN  */
    RPAREN = 306,                  /* RPAREN  */
    LBRACK = 307,                  /* LBRACK  */
    RBRACK = 308,                  /* RBRACK  */
    LBRACE = 309,                  /* LBRACE  */
    RBRACE = 310,                  /* RBRACE  */
    EPSILON = 311                  /* EPSILON  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 66 "../src/parser.y"

    // Constants
    int cint;
    float cfloat;
    char cchar;
    char* cstring;
    bool cbool;

    // Data types
    expr_attr *expr;
    id_attr *id;
    type_attr *type;
    arg_list_attr *arg;
    func_attr *func;
    id_list_attr *id_lst;
    expr_list_attr *expr_lst;
    param_list_attr *para;
    state_list_attr *state_lst;
    rules_attr *rules;
    rhs_automata_attr *rhs_automata;
    lhs_arrow_attr *lhs_arrow;
    cfg_rule_attr *cfg_rule;
    element_PDA_attr *ele_pda;
    elements_PDA_attr *eles_pda;
    cc_code *c;

    VTYPE_PRIMITIVE dtype_primitive;
    VTYPE_AUTOMATA dtype_automata;
    VTYPE_SET dtype_set;
    VTYPE_SR dtype_SR;

    // Variables
    char* identifier;
    char* comp;

#line 164 "tokens.hh"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_TOKENS_HH_INCLUDED  */
