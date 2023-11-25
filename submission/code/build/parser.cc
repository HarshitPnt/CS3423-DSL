/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "../src/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fstream>
#include <list>
#include <iostream>
#include <set>
#include <queue>
#include <typeinfo>
#include "../includes/st.hh"


#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

extern int yylex();
void yyerror(char const* str);
extern FILE* yyin;
extern std::fstream seq_token;
extern std::set<std::string> *set_funcs;
FILE* parse_log;
std::fstream cc_file;
std::queue<std::queue<std::string>> st;
std::queue<std::string> *current_queue = NULL;
std::vector<std::string> *current_states = NULL;
std::vector<std::pair<std::string,std::string>> *current_alphabets = NULL;
std::vector<std::string> *cfg_rhs_current = NULL;
std::vector<std::vector<std::string>> *cfg_prods = NULL;
std::vector<std::vector<std::string>> *transition = NULL;
std::vector<std::pair<std::string,std::string>> *pda_lhs = NULL;
std::vector<std::pair<std::string,std::string>> *pda_rhs = NULL;
std::vector<std::string> *nfa_dfa_rhs = NULL;
std::vector<std::string> *nfa_dfa_lhs = NULL;
int current_automata = 0;
extern int yylineno;
void terminate()
{
    fclose(yyin);
    cc_file.close();
    exit(1);
}

int in_function = 0;
int in_loop = 0;
int num_params = 0;
int isTemplateFn = 0;
FunctionSymbolTableEntry *current_function;

#define printlog(a) fprintf(parse_log,"%s declaration at line no: %d\n",a,yylineno)
#define getVTA(a) (a==TYPE_NFA?"nfa":(a==TYPE_DFA?"dfa":(a==TYPE_PDA?"pda":(a==TYPE_CFG?"cfg":""))))
#define getConst(a) (a->val->type==CINT?a->val->ccint:(a->val->type==CFLOAT?a->val->ccfloat:(a->val->type==CBOOL?a->val->ccbool:a->val->ccchar)))
#define getCTYPE(a) ((a->vtp==TYPE_INT_64 || a->vtp==TYPE_INT_32 || a->vtp==TYPE_INT_16 || a->vtp==TYPE_INT_8)?CINT:((a->vtp==TYPE_FLOAT_64 || a->vtp==TYPE_FLOAT_32)?CFLOAT:((a->vtp==TYPE_BOOL)?CBOOL:CCHAR)))
#define getVTP(a) (a==TYPE_INT_64?"int_64":(a==TYPE_INT_32?"int_32":(a==TYPE_INT_16?"int_16":(a==TYPE_INT_8?"int_8":(a==TYPE_FLOAT_64?"float_64":(a==TYPE_FLOAT_32?"float_32":(a==TYPE_BOOL?"bool":"char")))))))
#define getVTS(a) (a==TYPE_OSET?"o_set":"u_set")
#define getVTSR(a) (a==TYPE_STR?"string":(a==TYPE_REGEX?"regex":"struct"))
#define getFSM(a) (a==TYPE_DFA?"dfa":(a==TYPE_NFA?"nfa":(a==TYPE_PDA?"pda":"cfg")))

#line 132 "parser.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "tokens.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PSEUDO_LOW = 3,                 /* PSEUDO_LOW  */
  YYSYMBOL_TYPE_PRIMITIVE = 4,             /* TYPE_PRIMITIVE  */
  YYSYMBOL_TYPE_STRING = 5,                /* TYPE_STRING  */
  YYSYMBOL_TYPE_REG = 6,                   /* TYPE_REG  */
  YYSYMBOL_TYPE_SET = 7,                   /* TYPE_SET  */
  YYSYMBOL_TYPE_AUTOMATA = 8,              /* TYPE_AUTOMATA  */
  YYSYMBOL_INT_CONST = 9,                  /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 10,               /* FLOAT_CONST  */
  YYSYMBOL_STRING_CONST = 11,              /* STRING_CONST  */
  YYSYMBOL_CHAR_CONST = 12,                /* CHAR_CONST  */
  YYSYMBOL_BOOL_CONST = 13,                /* BOOL_CONST  */
  YYSYMBOL_REGEX_R = 14,                   /* REGEX_R  */
  YYSYMBOL_ID = 15,                        /* ID  */
  YYSYMBOL_REGEX_LIT = 16,                 /* REGEX_LIT  */
  YYSYMBOL_IF_KW = 17,                     /* IF_KW  */
  YYSYMBOL_ELIF_KW = 18,                   /* ELIF_KW  */
  YYSYMBOL_ELSE_KW = 19,                   /* ELSE_KW  */
  YYSYMBOL_WHILE_KW = 20,                  /* WHILE_KW  */
  YYSYMBOL_BREAK_KW = 21,                  /* BREAK_KW  */
  YYSYMBOL_STRUCT_KW = 22,                 /* STRUCT_KW  */
  YYSYMBOL_RETURN_KW = 23,                 /* RETURN_KW  */
  YYSYMBOL_CONTINUE_KW = 24,               /* CONTINUE_KW  */
  YYSYMBOL_TEMP_FN_KW = 25,                /* TEMP_FN_KW  */
  YYSYMBOL_ARROW = 26,                     /* ARROW  */
  YYSYMBOL_COLON = 27,                     /* COLON  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_SEMICOLON = 30,                 /* SEMICOLON  */
  YYSYMBOL_DOLLAR = 31,                    /* DOLLAR  */
  YYSYMBOL_OPER_AND = 32,                  /* OPER_AND  */
  YYSYMBOL_OPER_OR = 33,                   /* OPER_OR  */
  YYSYMBOL_OPER_COMP = 34,                 /* OPER_COMP  */
  YYSYMBOL_COMP_GT = 35,                   /* COMP_GT  */
  YYSYMBOL_COMP_LT = 36,                   /* COMP_LT  */
  YYSYMBOL_TEMP_LEFT = 37,                 /* TEMP_LEFT  */
  YYSYMBOL_TEMP_RIGHT = 38,                /* TEMP_RIGHT  */
  YYSYMBOL_OPER_PLUS = 39,                 /* OPER_PLUS  */
  YYSYMBOL_OPER_MINUS = 40,                /* OPER_MINUS  */
  YYSYMBOL_OPER_MUL = 41,                  /* OPER_MUL  */
  YYSYMBOL_OPER_DIV = 42,                  /* OPER_DIV  */
  YYSYMBOL_OPER_MOD = 43,                  /* OPER_MOD  */
  YYSYMBOL_AT_THE_RATE = 44,               /* AT_THE_RATE  */
  YYSYMBOL_OPER_POWER = 45,                /* OPER_POWER  */
  YYSYMBOL_OPER_NOT = 46,                  /* OPER_NOT  */
  YYSYMBOL_OPER_HASH = 47,                 /* OPER_HASH  */
  YYSYMBOL_OPER_ASN = 48,                  /* OPER_ASN  */
  YYSYMBOL_OPER_ASN_SIMPLE = 49,           /* OPER_ASN_SIMPLE  */
  YYSYMBOL_LPAREN = 50,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 51,                    /* RPAREN  */
  YYSYMBOL_LBRACK = 52,                    /* LBRACK  */
  YYSYMBOL_RBRACK = 53,                    /* RBRACK  */
  YYSYMBOL_LBRACE = 54,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 55,                    /* RBRACE  */
  YYSYMBOL_EPSILON = 56,                   /* EPSILON  */
  YYSYMBOL_YYACCEPT = 57,                  /* $accept  */
  YYSYMBOL_program = 58,                   /* program  */
  YYSYMBOL_instruction_list = 59,          /* instruction_list  */
  YYSYMBOL_struct_declaration = 60,        /* struct_declaration  */
  YYSYMBOL_61_1 = 61,                      /* $@1  */
  YYSYMBOL_62_2 = 62,                      /* $@2  */
  YYSYMBOL_struct_body = 63,               /* struct_body  */
  YYSYMBOL_struct_member = 64,             /* struct_member  */
  YYSYMBOL_id_list_decl = 65,              /* id_list_decl  */
  YYSYMBOL_expression_list = 66,           /* expression_list  */
  YYSYMBOL_function_declaration = 67,      /* function_declaration  */
  YYSYMBOL_68_3 = 68,                      /* $@3  */
  YYSYMBOL_function_header = 69,           /* function_header  */
  YYSYMBOL_type_list = 70,                 /* type_list  */
  YYSYMBOL_param_list = 71,                /* param_list  */
  YYSYMBOL_param = 72,                     /* param  */
  YYSYMBOL_next_param = 73,                /* next_param  */
  YYSYMBOL_function_body = 74,             /* function_body  */
  YYSYMBOL_statements = 75,                /* statements  */
  YYSYMBOL_76_4 = 76,                      /* $@4  */
  YYSYMBOL_variable_declaration = 77,      /* variable_declaration  */
  YYSYMBOL_id_list = 78,                   /* id_list  */
  YYSYMBOL_pseudo_ID = 79,                 /* pseudo_ID  */
  YYSYMBOL_assignment = 80,                /* assignment  */
  YYSYMBOL_states_list = 81,               /* states_list  */
  YYSYMBOL_cfg_rules = 82,                 /* cfg_rules  */
  YYSYMBOL_cfg_rule_list = 83,             /* cfg_rule_list  */
  YYSYMBOL_cfg_rule = 84,                  /* cfg_rule  */
  YYSYMBOL_rhs = 85,                       /* rhs  */
  YYSYMBOL_expression = 86,                /* expression  */
  YYSYMBOL_call = 87,                      /* call  */
  YYSYMBOL_type_list_call = 88,            /* type_list_call  */
  YYSYMBOL_type_call = 89,                 /* type_call  */
  YYSYMBOL_argument_list = 90,             /* argument_list  */
  YYSYMBOL_arg_list_next = 91,             /* arg_list_next  */
  YYSYMBOL_rhs_automata = 92,              /* rhs_automata  */
  YYSYMBOL_alphabet_list = 93,             /* alphabet_list  */
  YYSYMBOL_alphabet = 94,                  /* alphabet  */
  YYSYMBOL_rules_list = 95,                /* rules_list  */
  YYSYMBOL_rule = 96,                      /* rule  */
  YYSYMBOL_lhs_arrow = 97,                 /* lhs_arrow  */
  YYSYMBOL_elements_PDA = 98,              /* elements_PDA  */
  YYSYMBOL_element_PDA = 99,               /* element_PDA  */
  YYSYMBOL_elements_others = 100,          /* elements_others  */
  YYSYMBOL_rhs_arrow = 101,                /* rhs_arrow  */
  YYSYMBOL_cfg_rhs = 102,                  /* cfg_rhs  */
  YYSYMBOL_cfg_rhs_ele = 103,              /* cfg_rhs_ele  */
  YYSYMBOL_cfg_rhs_list = 104,             /* cfg_rhs_list  */
  YYSYMBOL_cfg_rhs_ele_list = 105,         /* cfg_rhs_ele_list  */
  YYSYMBOL_control_body = 106,             /* control_body  */
  YYSYMBOL_if_statement = 107,             /* if_statement  */
  YYSYMBOL_108_5 = 108,                    /* $@5  */
  YYSYMBOL_109_6 = 109,                    /* $@6  */
  YYSYMBOL_ifexp = 110,                    /* ifexp  */
  YYSYMBOL_elif_statement = 111,           /* elif_statement  */
  YYSYMBOL_112_7 = 112,                    /* $@7  */
  YYSYMBOL_elif = 113,                     /* elif  */
  YYSYMBOL_else_statement = 114,           /* else_statement  */
  YYSYMBOL_115_8 = 115,                    /* $@8  */
  YYSYMBOL_while_statement = 116,          /* while_statement  */
  YYSYMBOL_117_9 = 117,                    /* $@9  */
  YYSYMBOL_whileexp = 118,                 /* whileexp  */
  YYSYMBOL_call_statement = 119,           /* call_statement  */
  YYSYMBOL_return_statement = 120,         /* return_statement  */
  YYSYMBOL_break_statement = 121,          /* break_statement  */
  YYSYMBOL_continue_statement = 122,       /* continue_statement  */
  YYSYMBOL_dtype = 123,                    /* dtype  */
  YYSYMBOL_set_type = 124                  /* set_type  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   569

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  340

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   311


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   139,   139,   145,   146,   147,   148,   152,   166,   151,
     186,   187,   190,   221,   245,   262,   282,   296,   310,   309,
     342,   386,   427,   527,   620,   642,   667,   676,   717,   732,
     749,   758,   797,   798,   799,   802,   805,   811,   816,   821,
     822,   823,   824,   825,   825,   840,   948,   971,   995,  1027,
    1045,  1070,  1085,  1092,  1100,  1131,  1175,  1205,  1276,  1301,
    1317,  1351,  1361,  1372,  1375,  1376,  1379,  1397,  1421,  1439,
    1445,  1454,  1468,  1558,  1615,  1671,  1703,  1723,  1774,  1790,
    1810,  1849,  1886,  1906,  1926,  1959,  1968,  1996,  2006,  2016,
    2026,  2036,  2046,  2149,  2175,  2272,  2365,  2371,  2380,  2385,
    2399,  2404,  2427,  2437,  2441,  2464,  2473,  2479,  2487,  2488,
    2491,  2499,  2504,  2516,  2641,  2648,  2657,  2664,  2676,  2688,
    2694,  2701,  2707,  2715,  2722,  2729,  2740,  2749,  2756,  2766,
    2775,  2789,  2794,  2797,  2802,  2807,  2812,  2817,  2822,  2828,
    2831,  2840,  2851,  2852,  2853,  2857,  2865,  2856,  2874,  2883,
    2882,  2897,  2900,  2910,  2909,  2924,  2928,  2927,  2943,  2951,
    2957,  2988,  3004,  3011,  3018,  3024,  3032,  3038,  3044,  3052,
    3058
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PSEUDO_LOW",
  "TYPE_PRIMITIVE", "TYPE_STRING", "TYPE_REG", "TYPE_SET", "TYPE_AUTOMATA",
  "INT_CONST", "FLOAT_CONST", "STRING_CONST", "CHAR_CONST", "BOOL_CONST",
  "REGEX_R", "ID", "REGEX_LIT", "IF_KW", "ELIF_KW", "ELSE_KW", "WHILE_KW",
  "BREAK_KW", "STRUCT_KW", "RETURN_KW", "CONTINUE_KW", "TEMP_FN_KW",
  "ARROW", "COLON", "COMMA", "DOT", "SEMICOLON", "DOLLAR", "OPER_AND",
  "OPER_OR", "OPER_COMP", "COMP_GT", "COMP_LT", "TEMP_LEFT", "TEMP_RIGHT",
  "OPER_PLUS", "OPER_MINUS", "OPER_MUL", "OPER_DIV", "OPER_MOD",
  "AT_THE_RATE", "OPER_POWER", "OPER_NOT", "OPER_HASH", "OPER_ASN",
  "OPER_ASN_SIMPLE", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "LBRACE",
  "RBRACE", "EPSILON", "$accept", "program", "instruction_list",
  "struct_declaration", "$@1", "$@2", "struct_body", "struct_member",
  "id_list_decl", "expression_list", "function_declaration", "$@3",
  "function_header", "type_list", "param_list", "param", "next_param",
  "function_body", "statements", "$@4", "variable_declaration", "id_list",
  "pseudo_ID", "assignment", "states_list", "cfg_rules", "cfg_rule_list",
  "cfg_rule", "rhs", "expression", "call", "type_list_call", "type_call",
  "argument_list", "arg_list_next", "rhs_automata", "alphabet_list",
  "alphabet", "rules_list", "rule", "lhs_arrow", "elements_PDA",
  "element_PDA", "elements_others", "rhs_arrow", "cfg_rhs", "cfg_rhs_ele",
  "cfg_rhs_list", "cfg_rhs_ele_list", "control_body", "if_statement",
  "$@5", "$@6", "ifexp", "elif_statement", "$@7", "elif", "else_statement",
  "$@8", "while_statement", "$@9", "whileexp", "call_statement",
  "return_statement", "break_statement", "continue_statement", "dtype",
  "set_type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-245)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-62)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -245,    25,   176,  -245,  -245,  -245,  -245,    -9,  -245,    61,
     -17,    -8,    73,    65,   236,    74,    81,  -245,  -245,  -245,
      86,  -245,  -245,   140,  -245,    91,  -245,   102,  -245,   108,
    -245,  -245,  -245,  -245,   144,   511,     5,   516,   245,   147,
     300,   300,  -245,  -245,  -245,  -245,  -245,  -245,    -7,  -245,
     300,   300,   300,   300,    67,   437,  -245,  -245,   163,   199,
    -245,   141,   179,    55,   223,   300,  -245,  -245,  -245,    50,
     180,  -245,  -245,   106,    55,   528,  -245,   130,  -245,  -245,
     184,   341,   170,   210,  -245,   357,   377,   172,   126,   126,
    -245,   397,  -245,   300,   300,   300,   300,   300,   300,   300,
     300,   300,   300,   300,  -245,  -245,  -245,   136,    95,  -245,
     199,   169,   213,   201,    48,  -245,   187,  -245,   225,   300,
     212,   453,   231,   220,   319,   199,   199,   528,  -245,  -245,
    -245,   244,   216,   233,   249,   516,   224,   288,  -245,  -245,
    -245,   221,  -245,  -245,  -245,  -245,   467,   467,   522,   522,
     522,   126,   126,   126,   126,   126,   232,   263,   533,   238,
    -245,  -245,  -245,   131,   251,    -3,   258,   259,  -245,   -11,
     453,  -245,   260,  -245,  -245,   247,   250,   241,  -245,  -245,
     528,  -245,  -245,  -245,   245,   184,   341,    55,   545,  -245,
     289,   291,  -245,  -245,  -245,    51,   293,   124,     7,    20,
    -245,    22,  -245,    87,  -245,  -245,  -245,   300,  -245,  -245,
    -245,  -245,  -245,   233,   265,  -245,  -245,  -245,   299,    16,
    -245,   299,   267,   268,   308,   292,   240,   306,   294,   179,
    -245,   310,  -245,   273,  -245,   453,   311,  -245,  -245,  -245,
     181,   301,  -245,   185,   528,   528,  -245,    -5,   304,   278,
     279,   209,  -245,  -245,   237,  -245,  -245,  -245,  -245,   309,
    -245,  -245,   285,   318,   287,   327,  -245,  -245,  -245,   296,
     297,  -245,   328,    -4,  -245,  -245,    43,   329,   330,   237,
      88,   295,   302,  -245,   300,   303,  -245,  -245,  -245,  -245,
    -245,   337,  -245,  -245,    89,  -245,    92,  -245,    -4,  -245,
     316,   313,   315,   209,  -245,   356,   363,   417,  -245,   199,
       0,   344,  -245,    17,  -245,    94,   105,  -245,  -245,  -245,
     237,   324,   332,  -245,   199,   340,   352,   354,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,   351,  -245,  -245,  -245,  -245
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     2,     1,   164,   167,   168,     0,   166,    53,
       0,     0,     0,     0,     0,     0,     0,    43,     3,     4,
       0,     5,    35,     0,    36,     0,    37,     0,    38,     0,
      42,    39,    40,    41,     0,     0,    47,     0,   100,     0,
       0,     0,   162,     7,    88,    89,    91,    90,    53,   161,
       0,     0,     0,     0,    92,     0,    93,   163,     0,     0,
      18,     0,     0,     0,     0,     0,   159,   145,   156,    47,
       0,   170,   169,     0,     0,    26,    99,     0,    96,    98,
     103,   103,     0,     0,    46,     0,     0,     0,    87,    86,
      84,     0,   160,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    78,    85,    24,     0,    53,   143,
     142,     0,     0,    34,     0,    53,    52,    70,     0,     0,
       0,    67,     0,     0,     0,     0,     0,    26,    45,   165,
      48,     0,     0,    30,     0,     0,     0,     0,   102,   101,
      94,    49,   148,   158,     8,    71,    81,    80,    77,    82,
      83,    72,    73,    74,    75,    76,    79,     0,     0,    47,
     144,    44,    33,     0,     0,     0,     0,     0,    69,     0,
      16,    54,     0,    55,    51,     0,     0,     0,    29,    21,
       0,    27,    28,    97,   100,   103,   103,     0,     0,    25,
       0,     0,    19,    32,    59,    53,     0,     0,     0,     0,
      64,     0,   108,     0,   111,    58,    57,     0,    68,    56,
     146,   157,    20,    30,     0,   105,   104,    50,     0,     0,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      63,     0,   106,     0,   107,    17,   151,    31,    95,    14,
       0,     0,    10,     0,    26,    26,   110,     0,     0,     0,
       0,     0,   137,    66,   131,   132,    62,    60,    65,     0,
     109,   112,     0,   155,     0,     0,    13,     9,    12,     0,
       0,   114,     0,     0,   116,   115,     0,     0,     0,   140,
       0,     0,     0,   135,     0,     0,   147,   149,    15,    22,
      23,     0,   123,   124,     0,   119,     0,   127,     0,   129,
       0,     0,     0,     0,   139,     0,     0,     0,   153,     0,
       0,     0,   117,     0,   118,     0,     0,   113,   138,   136,
     141,     0,     0,   152,     0,     0,     0,     0,   120,   125,
     126,   130,   128,   134,   133,     0,   150,   121,   122,   154
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -245,  -245,  -245,  -245,  -245,  -245,  -245,   188,   193,  -245,
    -245,  -245,  -245,  -245,  -114,   235,   214,  -245,     3,  -245,
    -245,   -20,    -2,  -245,  -245,  -245,  -245,   194,   -58,   -12,
       2,  -245,   290,   242,   -72,  -245,  -245,   203,  -245,   202,
    -245,   145,  -239,   148,  -245,  -245,  -244,  -245,  -245,  -107,
    -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,  -245,    -1,  -245
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    18,    87,   188,   219,   220,   240,   169,
      19,   113,    20,   107,   132,   133,   181,   163,   110,    59,
      22,    39,    54,    24,   198,   166,   199,   200,   120,   121,
      56,    77,    78,    82,   138,   167,   201,   202,   203,   204,
     248,   294,   295,   296,   300,   253,   254,   255,   280,   111,
      26,   125,   236,    27,   263,   309,   264,   286,   324,    28,
     126,    29,    30,    31,    32,    33,   112,    73
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    34,    55,   160,    25,    21,   123,   279,   275,   139,
     271,   292,   195,   177,    70,   326,   130,   207,   175,   176,
       4,     5,     6,     7,     8,     3,    81,    35,    85,    86,
      37,   218,   329,    40,    72,   227,    79,   299,    88,    89,
      90,    91,    41,    38,   208,   272,   272,   196,   229,   273,
     231,   274,   293,   124,    74,    75,   327,    23,   297,   320,
     116,    25,   228,   164,    44,    45,   117,    46,    47,   118,
      48,   241,   328,   330,   134,   230,    36,   232,   224,   -61,
      43,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,    70,   272,    50,    51,    62,   298,    37,    74,
     127,    52,   165,    42,    57,    53,   -61,   170,    23,   119,
     159,    38,    25,   215,   216,   233,   303,   311,    58,    65,
     313,    66,   311,    23,    23,   186,   134,    25,    25,   217,
     269,   270,    37,   313,    79,     4,     5,     6,     7,     8,
      60,   129,   234,   304,   312,    38,   108,   314,    10,   331,
     226,    11,    12,    62,    14,    15,    67,   191,   135,    69,
     332,    23,    68,   197,   157,    25,   193,    61,   136,    62,
     103,   104,    81,   105,   158,    83,    65,    84,   106,   134,
       4,     5,     6,     7,     8,    17,   192,   221,    63,    64,
     114,     9,    65,    10,   115,   235,    11,    12,    13,    14,
      15,    16,   325,     4,     5,     6,     7,     8,    83,   265,
     128,   266,   137,   265,   108,   268,    10,   335,   221,    11,
      12,   140,    14,    15,   161,   141,   144,   197,   159,   109,
      17,   162,    44,    45,   117,    46,    47,   122,    48,    65,
     249,   168,   171,   134,   134,    44,    45,   172,    46,    47,
     173,    48,   250,    17,    44,    45,    80,    46,    47,   178,
      48,   180,    50,    51,   182,   252,    49,   179,   281,    52,
     187,   249,   307,    53,   184,    50,    51,   119,   189,   105,
     282,   194,    52,   250,    50,    51,    53,    74,   205,   206,
     209,    52,   212,   283,   251,    53,   252,    44,    45,   185,
      46,    47,   210,    48,   222,   211,   223,    23,   225,    44,
      45,    25,    46,    47,   239,    48,   238,   244,   245,   246,
     247,   256,    23,   196,   257,   259,    25,    50,    51,   262,
     276,   267,   277,   278,    52,   284,   224,   285,    53,    50,
      51,   287,   288,   291,   301,   302,    52,   289,   290,   305,
      53,    93,    94,    95,    96,    97,   306,   308,    98,    99,
     100,   101,   102,   103,   104,   310,   105,   317,   318,   137,
     319,   321,   174,    93,    94,    95,    96,    97,   322,   333,
      98,    99,   100,   101,   102,   103,   104,   334,   105,    93,
      94,    95,    96,    97,   272,   336,    98,    99,   100,   101,
     102,   103,   104,   337,   105,   338,   339,   242,   142,    93,
      94,    95,    96,    97,   243,   213,    98,    99,   100,   101,
     102,   103,   104,   258,   105,   183,   214,   237,   143,    93,
      94,    95,    96,    97,   260,   261,    98,    99,   100,   101,
     102,   103,   104,   315,   105,     0,   316,     0,   145,    93,
      94,    95,    96,    97,     0,     0,    98,    99,   100,   101,
     102,   103,   104,     0,   105,     0,     0,    92,   323,    93,
      94,    95,    96,    97,     0,     0,    98,    99,   100,   101,
     102,   103,   104,     0,   105,    93,    94,    95,    96,    97,
       0,     0,    98,    99,   100,   101,   102,   103,   104,     0,
     105,    95,    96,    97,     0,     0,    98,    99,   100,   101,
     102,   103,   104,     0,   105,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,     0,    71,     0,     0,     0,
       0,    76,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     0,   131,     0,     0,     0,     0,   190,     4,
       5,     6,     7,     8,     0,     0,     0,     0,     0,     0,
     218,    98,    99,   100,   101,   102,   103,   104,     0,   105
};

static const yytype_int16 yycheck[] =
{
       2,     2,    14,   110,     2,     2,    64,   251,   247,    81,
      15,    15,    15,   127,    34,    15,    74,    28,   125,   126,
       4,     5,     6,     7,     8,     0,    38,    36,    40,    41,
      37,    15,    15,    50,    35,    28,    37,   276,    50,    51,
      52,    53,    50,    50,    55,    50,    50,    50,    28,    54,
      28,    56,    56,    65,    49,    50,    56,    59,    15,   303,
      62,    59,    55,    15,     9,    10,    11,    12,    13,    14,
      15,    55,   311,    56,    75,    55,    15,    55,    27,    28,
      15,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   112,    50,    39,    40,    29,    54,    37,    49,
      50,    46,    54,    30,    30,    50,    55,   119,   110,    54,
      15,    50,   110,   185,   186,    28,    28,    28,    37,    52,
      28,    30,    28,   125,   126,   137,   127,   125,   126,   187,
     244,   245,    37,    28,   135,     4,     5,     6,     7,     8,
      54,    35,    55,    55,    55,    50,    15,    55,    17,    55,
      26,    20,    21,    29,    23,    24,    54,   158,    28,    15,
      55,   163,    54,   165,    28,   163,   163,    27,    38,    29,
      44,    45,   184,    47,    38,    28,    52,    30,    15,   180,
       4,     5,     6,     7,     8,    54,    55,   188,    48,    49,
      49,    15,    52,    17,    15,   207,    20,    21,    22,    23,
      24,    25,   309,     4,     5,     6,     7,     8,    28,    28,
      30,    30,    28,    28,    15,    30,    17,   324,   219,    20,
      21,    51,    23,    24,    55,    15,    54,   229,    15,    30,
      54,    30,     9,    10,    11,    12,    13,    14,    15,    52,
      31,    16,    30,   244,   245,     9,    10,    16,    12,    13,
      30,    15,    43,    54,     9,    10,    11,    12,    13,    15,
      15,    28,    39,    40,    15,    56,    30,    51,    31,    46,
      49,    31,   284,    50,    50,    39,    40,    54,    15,    47,
      43,    30,    46,    43,    39,    40,    50,    49,    30,    30,
      30,    46,    51,    56,    54,    50,    56,     9,    10,    11,
      12,    13,    55,    15,    15,    55,    15,   309,    15,     9,
      10,   309,    12,    13,    15,    15,    51,    50,    50,    11,
      28,    15,   324,    50,    30,    15,   324,    39,    40,    18,
      26,    30,    54,    54,    46,    50,    27,    19,    50,    39,
      40,    54,    15,    15,    15,    15,    46,    51,    51,    54,
      50,    32,    33,    34,    35,    36,    54,    54,    39,    40,
      41,    42,    43,    44,    45,    28,    47,    51,    55,    28,
      55,    15,    53,    32,    33,    34,    35,    36,    15,    55,
      39,    40,    41,    42,    43,    44,    45,    55,    47,    32,
      33,    34,    35,    36,    50,    55,    39,    40,    41,    42,
      43,    44,    45,    51,    47,    51,    55,   219,    51,    32,
      33,    34,    35,    36,   221,   180,    39,    40,    41,    42,
      43,    44,    45,   229,    47,   135,   184,   213,    51,    32,
      33,    34,    35,    36,   231,   233,    39,    40,    41,    42,
      43,    44,    45,   298,    47,    -1,   298,    -1,    51,    32,
      33,    34,    35,    36,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    -1,    -1,    30,    51,    32,
      33,    34,    35,    36,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    32,    33,    34,    35,    36,
      -1,    -1,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    34,    35,    36,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,    -1,    15,    -1,    -1,    -1,
      -1,    15,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,    -1,    15,    -1,    -1,    -1,    -1,    15,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    39,    40,    41,    42,    43,    44,    45,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    58,    59,     0,     4,     5,     6,     7,     8,    15,
      17,    20,    21,    22,    23,    24,    25,    54,    60,    67,
      69,    75,    77,    79,    80,    87,   107,   110,   116,   118,
     119,   120,   121,   122,   123,    36,    15,    37,    50,    78,
      50,    50,    30,    15,     9,    10,    12,    13,    15,    30,
      39,    40,    46,    50,    79,    86,    87,    30,    37,    76,
      54,    27,    29,    48,    49,    52,    30,    54,    54,    15,
      78,    15,   123,   124,    49,    50,    15,    88,    89,   123,
      11,    86,    90,    28,    30,    86,    86,    61,    86,    86,
      86,    86,    30,    32,    33,    34,    35,    36,    39,    40,
      41,    42,    43,    44,    45,    47,    15,    70,    15,    30,
      75,   106,   123,    68,    49,    15,    79,    11,    14,    54,
      85,    86,    14,    85,    86,   108,   117,    50,    30,    35,
      85,    15,    71,    72,   123,    28,    38,    28,    91,    91,
      51,    15,    51,    51,    54,    51,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    28,    38,    15,
     106,    55,    30,    74,    15,    54,    82,    92,    16,    66,
      86,    30,    16,    30,    53,   106,   106,    71,    15,    51,
      28,    73,    15,    89,    50,    11,    86,    49,    62,    15,
      15,   123,    55,    75,    30,    15,    50,    79,    81,    83,
      84,    93,    94,    95,    96,    30,    30,    28,    55,    30,
      55,    55,    51,    72,    90,    91,    91,    85,    15,    63,
      64,   123,    15,    15,    27,    15,    26,    28,    55,    28,
      55,    28,    55,    28,    55,    86,   109,    73,    51,    15,
      65,    55,    64,    65,    50,    50,    11,    28,    97,    31,
      43,    54,    56,   102,   103,   104,    15,    30,    84,    15,
      94,    96,    18,   111,   113,    28,    30,    30,    30,    71,
      71,    15,    50,    54,    56,    99,    26,    54,    54,   103,
     105,    31,    43,    56,    50,    19,   114,    54,    15,    51,
      51,    15,    15,    56,    98,    99,   100,    15,    54,    99,
     101,    15,    15,    28,    55,    54,    54,    86,    54,   112,
      28,    28,    55,    28,    55,    98,   100,    51,    55,    55,
     103,    15,    15,    51,   115,   106,    15,    56,    99,    15,
      56,    55,    55,    55,    55,   106,    55,    51,    51,    55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    59,    59,    59,    59,    61,    62,    60,
      63,    63,    64,    64,    65,    65,    66,    66,    68,    67,
      69,    69,    69,    69,    70,    70,    71,    71,    72,    72,
      73,    73,    74,    74,    74,    75,    75,    75,    75,    75,
      75,    75,    75,    76,    75,    77,    77,    78,    78,    78,
      78,    79,    79,    79,    80,    80,    80,    80,    80,    80,
      80,    81,    81,    82,    83,    83,    84,    85,    85,    85,
      85,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    87,    87,    88,    88,    89,    89,
      90,    90,    90,    91,    91,    91,    92,    92,    93,    93,
      94,    95,    95,    96,    97,    97,    97,    97,    97,    98,
      98,    99,    99,   100,   100,   100,   100,   101,   101,   101,
     101,   102,   102,   103,   103,   103,   103,   103,   103,   104,
     105,   105,   106,   106,   106,   108,   109,   107,   110,   112,
     111,   111,   113,   115,   114,   114,   117,   116,   118,   119,
     120,   120,   121,   122,   123,   123,   123,   123,   123,   124,
     124
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     0,     0,     0,     8,
       2,     1,     3,     3,     1,     3,     1,     3,     0,     5,
       5,     5,     9,     9,     1,     3,     0,     2,     2,     2,
       0,     3,     2,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     1,     3,     3,
       5,     4,     3,     1,     4,     4,     5,     5,     5,     5,
       7,     1,     3,     3,     1,     3,     3,     1,     3,     2,
       1,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     4,     7,     1,     3,     1,     1,
       0,     2,     2,     0,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     6,     2,     2,     2,     4,     4,     1,
       3,     5,     5,     1,     1,     3,     3,     1,     3,     1,
       3,     1,     1,     5,     5,     2,     4,     1,     4,     3,
       1,     3,     1,     1,     2,     0,     0,     8,     4,     0,
       5,     0,     4,     0,     5,     0,     0,     5,     4,     2,
       3,     2,     2,     2,     1,     4,     1,     1,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: instruction_list  */
#line 140 "../src/parser.y"
        {
            if(!fst->lookup("main"))
                yyerror("No main function found");
        }
#line 1535 "parser.cc"
    break;

  case 7: /* $@1: %empty  */
#line 152 "../src/parser.y"
                                {
                                    //check if struct already exists
                                    if(sst->lookup(std::string((yyvsp[0].identifier))))
                                    {
                                        if(sst->lookup(std::string((yyvsp[0].identifier)))->isTemplate)
                                        {
                                            std::string error = "typename in use: "+std::string((yyvsp[0].identifier));
                                            yyerror(error.c_str());
                                        }
                                        std::string error = "Struct redeclaration: "+std::string((yyvsp[0].identifier));
                                        yyerror(error.c_str());
                                    }
                                    cc_file<<"struct "<<std::string((yyvsp[0].identifier))<<std::string(" ")<<std::string("{\n\tpublic:")<<std::endl;
                                }
#line 1554 "parser.cc"
    break;

  case 8: /* $@2: %empty  */
#line 166 "../src/parser.y"
                           {
                                //create a new symbol table
                                VarSymbolTable *new_st = new VarSymbolTable();
                                current_vst = new_st;
                                vstl->insert(new_st);
                            }
#line 1565 "parser.cc"
    break;

  case 9: /* struct_declaration: STRUCT_KW ID $@1 LBRACE $@2 struct_body RBRACE SEMICOLON  */
#line 173 "../src/parser.y"
                    {
                        //first get the symbol table for this struct and put it into the members column of the struct symbol table
                        StructSymbolTableEntry *entry = new StructSymbolTableEntry(std::string((yyvsp[-6].identifier)),current_vst);
                        sst->insert(entry);
                        printlog("Struct");
                        //remove struct scope from the varSymbolTableList
                        if(vstl->remove())
                            yyerror("Internal Error");
                        current_vst = vstl->getTop();
                        cc_file<<std::string("};")<<std::endl;
                    }
#line 1581 "parser.cc"
    break;

  case 12: /* struct_member: dtype id_list_decl SEMICOLON  */
#line 191 "../src/parser.y"
            {
                //backpatching here
                
                if((yyvsp[-2].type)->indicator!=3)
                {
                    for(auto it = (yyvsp[-1].id_lst)->lst.begin();it!=(yyvsp[-1].id_lst)->lst.end();it++)
                    {
                        if(current_vst->backpatch(it->first,getType((yyvsp[-2].type)),(yyvsp[-2].type)->inner,NULL))
                        {
                            yyerror("Internal Error");
                        }
                        if((yyvsp[-2].type)->indicator==2)//sets (set inner type)
                        {
                            it->first->inner = (yyvsp[-2].type)->inner;
                        }
                    }
                }
                else
                {
                    for(auto it = (yyvsp[-1].id_lst)->lst.begin();it!=(yyvsp[-1].id_lst)->lst.end();it++)
                    {
                        VarSymbolTable *struct_vst = sst->lookup(std::string(getFSM((yyvsp[-2].type)->vta)))->fields;
                        if(current_vst->backpatch(it->first,getType((yyvsp[-2].type)),NULL,struct_vst))
                        {
                            yyerror("Internal Error");
                        }
                    }
                }
                cc_file<<(yyvsp[-2].type)->cc<<(yyvsp[-1].id_lst)->cc<<";"<<std::endl;
            }
#line 1616 "parser.cc"
    break;

  case 13: /* struct_member: ID id_list_decl SEMICOLON  */
#line 222 "../src/parser.y"
            {
                //check if struct exists
                if(!sst->lookup(std::string((yyvsp[-2].identifier))))
                {
                    std::string str = std::string("Error: Struct ")+std::string((yyvsp[-2].identifier))+std::string(" not defined");
                    yyerror(str.c_str());
                }
                //backpatching here
                //create an empty vector
                std::list<int> *temp;
                temp = new std::list<int>();
                VarSymbolTable *struct_vst = sst->lookup(std::string((yyvsp[-2].identifier)))->fields;
                for(auto it = (yyvsp[-1].id_lst)->lst.begin();it!=(yyvsp[-1].id_lst)->lst.end();it++)
                {
                    if(current_vst->backpatch(it->first,std::string((yyvsp[-2].identifier)),NULL,struct_vst))
                    {
                        yyerror("Internal Error");
                    }
                }
                cc_file<<std::string((yyvsp[-2].identifier))<<(yyvsp[-1].id_lst)->cc<<";"<<std::endl;
            }
#line 1642 "parser.cc"
    break;

  case 14: /* id_list_decl: ID  */
#line 246 "../src/parser.y"
            {
                //create a new symbol table entry
                (yyval.id_lst) = new id_list_attr();
                //insert this ID in the symbol table (backpatch later)
                if(current_vst->lookup(std::string((yyvsp[0].identifier))))
                {
                    std::string error = "Variable redeclaration in struct: "+std::string((yyvsp[0].identifier));
                    yyerror(error.c_str());
                }
                VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string((yyvsp[0].identifier)));
                current_vst->insert(entry);
                type_attr *type = new type_attr();
                type->indicator = 0;
                (yyval.id_lst)->lst.push_back(std::make_pair(entry,type));
                (yyval.id_lst)->cc = std::string(" ")+std::string((yyvsp[0].identifier));
            }
#line 1663 "parser.cc"
    break;

  case 15: /* id_list_decl: id_list_decl COMMA ID  */
#line 263 "../src/parser.y"
            {
                //create a new symbol table entry
                (yyval.id_lst) = new id_list_attr();
                //insert this ID in the symbol table (backpatch later)
                if(current_vst->lookup(std::string((yyvsp[0].identifier))))
                {
                    std::string error = "Variable redeclaration in struct: "+std::string((yyvsp[0].identifier));
                    yyerror(error.c_str());
                }
                VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string((yyvsp[0].identifier)));
                current_vst->insert(entry);
                type_attr *type = new type_attr();
                type->indicator = 0;
                (yyval.id_lst)->lst = (yyvsp[-2].id_lst)->lst;
                (yyval.id_lst)->lst.push_back(std::make_pair(entry,type));
                (yyval.id_lst)->cc = (yyvsp[-2].id_lst)->cc + std::string(", ") + std::string((yyvsp[0].identifier));
            }
#line 1685 "parser.cc"
    break;

  case 16: /* expression_list: expression  */
#line 283 "../src/parser.y"
                {
                    (yyval.expr_lst) = new expr_list_attr();
                    (yyval.expr_lst)->inner = getType((yyvsp[0].expr));
                    if(current_queue==NULL)
                    {
                        current_queue = new std::queue<std::string>();
                        current_queue->push((yyvsp[0].expr)->cc);
                    }
                    else
                    {
                        current_queue->push((yyvsp[0].expr)->cc);
                    }
                }
#line 1703 "parser.cc"
    break;

  case 17: /* expression_list: expression_list COMMA expression  */
#line 297 "../src/parser.y"
               {
                 if(!isCoherent(getType((yyvsp[0].expr)),(yyvsp[-2].expr_lst)->inner))
                 {
                    std::string error = std::string("Error: Invalid type conversion from ")+getType((yyvsp[0].expr))+std::string(" to ")+(yyvsp[-2].expr_lst)->inner;
                    yyerror(error.c_str());
                 }
                (yyval.expr_lst) = new expr_list_attr();
                (yyval.expr_lst)->inner = (yyvsp[-2].expr_lst)->inner;
                current_queue->push((yyvsp[0].expr)->cc);
               }
#line 1718 "parser.cc"
    break;

  case 18: /* $@3: %empty  */
#line 310 "../src/parser.y"
                    {
                        //create a function scope
                        VarSymbolTable *new_st = new VarSymbolTable();
                        vstl->insert(new_st);
                        current_vst = new_st;
                        cc_file<<(yyvsp[-1].c)->cc<<std::string("\t")<<std::string("{")<<std::endl;
                    }
#line 1730 "parser.cc"
    break;

  case 19: /* function_declaration: function_header LBRACE $@3 function_body RBRACE  */
#line 318 "../src/parser.y"
                    {
                        in_function = 0;
                        //remove function scope
                        if(vstl->remove())
                            yyerror("Internal Error");
                        if(vstl->remove())
                            yyerror("Internal Error");
                        current_vst = vstl->getTop();
                        // if(isTemplateFn)
                        // {
                        //     //remove struct entries
                        //     std::vector<std::string> type_list = current_function->template_params;
                        //     for(auto it = type_list.begin();it!=type_list.end();it++)
                        //     {
                        //         if(sst->remove(*it))
                        //             yyerror("Internal Error");
                        //     }
                        // }
                        isTemplateFn = 0;
                        current_function = NULL;
                        cc_file<<std::string("}")<<std::endl;
                    }
#line 1757 "parser.cc"
    break;

  case 20: /* function_header: dtype ID LPAREN param_list RPAREN  */
#line 342 "../src/parser.y"
                                                   {
                        //check if function exists
                        if(fst->lookup(std::string((yyvsp[-3].identifier))))
                        {
                            std::string error = "Function redeclaration: "+std::string((yyvsp[-3].identifier));
                            yyerror(error.c_str());
                        }
                        printlog("Function");
                        if(in_function)
                            yyerror("Nested function declaration");
                        in_function = 1;
                        //handling param_list
                        //push new function to function table
                        FunctionSymbolTableEntry *entry = new FunctionSymbolTableEntry(std::string((yyvsp[-3].identifier)),num_params,current_vst,getType((yyvsp[-4].type)));
                        vstl->insert(entry->params);
                        current_vst = entry->params;
                        //handling return type
                        std::string outer;
                        if((yyvsp[-4].type)->indicator==2)//set
                        {
                            outer = getType((yyvsp[-4].type));
                            outer= outer + std::string(" ") + (yyvsp[-4].type)->inner->print();
                            entry->return_type = outer;
                        }
                        else
                        {
                            outer = getType((yyvsp[-4].type));
                            entry->return_type = outer;
                        }
                        current_function = entry;
                        //insert function into function table
                        for(auto it = (yyvsp[-1].para)->lst.begin();it!=(yyvsp[-1].para)->lst.end();it++)
                        {
                            entry->id_list.push_back(*it);
                            if(entry->params->lookup(*it)->type=="template")
                            {
                                std::string error = "Invalid type for argument: "+std::string(*it);
                                yyerror(error.c_str());
                            }
                        }
                        fst->insert(entry);
                        (yyval.c) = new cc_code();
                        (yyval.c)->cc = (yyvsp[-4].type)->cc + std::string(" ") + std::string((yyvsp[-3].identifier)) + std::string("(") + (yyvsp[-1].para)->cc + std::string(")");
                    }
#line 1806 "parser.cc"
    break;

  case 21: /* function_header: ID ID LPAREN param_list RPAREN  */
#line 386 "../src/parser.y"
                                                 {
                        //check if function exists

                        if(fst->lookup(std::string((yyvsp[-3].identifier))))
                        {
                            std::string error = "Function redeclaration: "+std::string((yyvsp[-3].identifier));
                            yyerror(error.c_str());
                        }
                        printlog("Function");
                        if(in_function)
                            yyerror("Nested function declaration");
                        in_function = 1;
                        //check if struct exists
                        if(std::string((yyvsp[-4].identifier))!=std::string("void"))
                        {
                            if(!sst->lookup(std::string((yyvsp[-4].identifier))))
                            {
                                std::string str = std::string("Error: Struct ")+std::string((yyvsp[-4].identifier))+std::string(" not defined");
                                yyerror(str.c_str());
                            }
                        }
                        //push new function to function table
                        FunctionSymbolTableEntry *entry = new FunctionSymbolTableEntry(std::string((yyvsp[-3].identifier)),num_params,current_vst,std::string((yyvsp[-4].identifier)));
                        vstl->insert(entry->params);
                        current_vst = entry->params;
                        current_function = entry;
                        //insert function into function table
                        for(auto it = (yyvsp[-1].para)->lst.begin();it!=(yyvsp[-1].para)->lst.end();it++)
                        {
                            entry->id_list.push_back(*it);
                            if(entry->params->lookup(*it)->type=="template")
                            {
                                std::string error = "Invalid type for argument: "+std::string(*it);
                                yyerror(error.c_str());
                            }
                        }
                        fst->insert(entry);
                        std::string str = std::string((yyvsp[-4].identifier)) + std::string(" ") + std::string((yyvsp[-3].identifier)) + std::string("(") + (yyvsp[-1].para)->cc + std::string(")");
                        // $$->cc = str;
                        cc_file<<str;
                    }
#line 1852 "parser.cc"
    break;

  case 22: /* function_header: TEMP_FN_KW TEMP_LEFT type_list TEMP_RIGHT ID ID LPAREN param_list RPAREN  */
#line 427 "../src/parser.y"
                                                                                           {
                        // struct return type
                        // need to insert the typenames into the struct symbol table and after the function need to remove them
                        if(in_function)
                            yyerror("Nested function declaration");
                        in_function = 1;
                        isTemplateFn = 1;
                        //check for function
                        if(fst->lookup(std::string((yyvsp[-3].identifier))))
                        {
                            std::string error = "Function redeclaration: "+std::string((yyvsp[-3].identifier));
                            yyerror(error.c_str());
                        }
                        //check if struct exists
                        FunctionSymbolTableEntry *entry;
                        std::vector<std::string> type_list;
                        for(auto it = (yyvsp[-6].state_lst)->lst.begin();it!=(yyvsp[-6].state_lst)->lst.end();it++)
                        {
                            type_list.push_back(*it);
                        }
                        if(std::string((yyvsp[-4].identifier))!=std::string("void"))
                        {
                            if(sst->lookup(std::string((yyvsp[-4].identifier))))
                            {
                                //return type is struct
                                entry = new FunctionSymbolTableEntry(std::string((yyvsp[-3].identifier)),num_params,current_vst,std::string((yyvsp[-4].identifier)),true,type_list);
                                vstl->insert(entry->params);
                                current_vst = entry->params;
                            }
                            else
                            {
                                std::string str = std::string("Error: struct ")+std::string((yyvsp[-4].identifier))+std::string(" not defined");
                                yyerror(str.c_str());
                            }
                        }
                        else
                        {
                            //return type is void
                            entry = new FunctionSymbolTableEntry(std::string((yyvsp[-3].identifier)),num_params,current_vst,std::string((yyvsp[-4].identifier)),true,type_list);
                            vstl->insert(entry->params);
                            current_vst = entry->params;
                        }
                        //type checking for arguments
                        current_function = entry;
                        for(auto it = (yyvsp[-1].para)->lst.begin();it!=(yyvsp[-1].para)->lst.end();it++)
                        {
                            std::string type = entry->params->lookup(*it)->type;
                            if(isPrimitive(type) || isAutomata(type))
                                ;
                            else if(isSet(type))
                            {
                                //recurisvely find the inner template/struct
                                std::string inner = entry->params->lookup(*it)->inner->print();
                                inner = trim(inner);
                                if(inner.find(" ")==std::string::npos)
                                {
                                    //check structs
                                    if(sst->lookup(inner) || isAutomata(inner) || isPrimitive(inner))
                                        ;
                                    else
                                    {
                                        std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                                        yyerror(error.c_str());
                                    }
                                }
                                else
                                {
                                    std::string inner_next = inner.substr(0,inner.find(" "));
                                    while(isSet(inner_next))
                                    {
                                        inner = inner.substr(inner.find(" ")+1);
                                        inner_next = inner.substr(0,inner.find(" "));
                                    }
                                    if(sst->lookup(inner_next) || isPrimitive(inner_next) || isAutomata(inner_next))
                                        ;
                                    else
                                    {
                                        std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                                        yyerror(error.c_str());
                                    }
                                }
                            }
                            else if(sst->lookup(type))
                                ;
                            else if(std::find(type_list.begin(),type_list.end(),type)!=type_list.end())
                                ;
                            else
                            {
                                std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                                yyerror(error.c_str());
                            }
                            entry->id_list.push_back(*it);
                        }
                        fst->insert(entry);
                        
                        (yyval.c) = new cc_code();
                        (yyval.c)->cc = "template <" + (yyvsp[-6].state_lst)->cc + std::string("> ") + std::string((yyvsp[-4].identifier)) + std::string(" ") + std::string((yyvsp[-3].identifier)) + std::string("(") + (yyvsp[-1].para)->cc + std::string(")");
                        cc_file<<(yyval.c)->cc;
                        (yyval.c)->cc = "";
                    }
#line 1957 "parser.cc"
    break;

  case 23: /* function_header: TEMP_FN_KW TEMP_LEFT type_list TEMP_RIGHT dtype ID LPAREN param_list RPAREN  */
#line 527 "../src/parser.y"
                                                                                              {
                    if(in_function)
                            yyerror("Nested function declaration");
                    in_function = 1;
                    isTemplateFn = 1;
                    //check for function
                    if(fst->lookup(std::string((yyvsp[-3].identifier))))
                    {
                        std::string error = "Function redeclaration: "+std::string((yyvsp[-3].identifier));
                        yyerror(error.c_str());
                    }
                    //make a functionsymboltable entry
                    std::vector<std::string> type_list;
                    for(auto it = (yyvsp[-6].state_lst)->lst.begin();it!=(yyvsp[-6].state_lst)->lst.end();it++)
                    {
                        type_list.push_back(*it);
                    }
                    FunctionSymbolTableEntry *entry = new FunctionSymbolTableEntry(std::string((yyvsp[-3].identifier)),num_params,current_vst,getType((yyvsp[-4].type)),true,type_list);
                    vstl->insert(entry->params);
                    current_vst = entry->params;
                    std::string outer;
                    if((yyvsp[-4].type)->indicator==2)//set
                    {
                        outer = getType((yyvsp[-4].type));
                        outer= outer + std::string(" ") + (yyvsp[-4].type)->inner->print();
                        entry->return_type = outer;
                    }
                    else
                    {
                        outer = getType((yyvsp[-4].type));
                        entry->return_type = outer;
                    }
                    outer = trim(outer);
                    current_function = entry;
                    fst->insert(entry);
                    //type checking of arguments
                    for(auto it = (yyvsp[-1].para)->lst.begin();it!=(yyvsp[-1].para)->lst.end();it++)
                    {
                        std::string type = entry->params->lookup(*it)->type;
                        if(isSet(type))
                        {
                                std::string inner = entry->params->lookup(*it)->inner->print();
                                inner = trim(inner);
                                if(inner.find(" ")==std::string::npos)
                                {
                                    //check structs
                                    if(sst->lookup(inner) || isPrimitive(inner) || isAutomata(inner))
                                        ;
                                    else
                                    {
                                        std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                                        yyerror(error.c_str());
                                    }
                                }
                                else
                                {
                                    std::string inner_next = inner.substr(0,inner.find(" "));
                                    while(isSet(inner_next))
                                    {
                                        inner = inner.substr(inner.find(" ")+1);
                                        inner_next = inner.substr(0,inner.find(" "));
                                    }
                                    if(sst->lookup(inner_next) || isPrimitive(inner_next) || isAutomata(inner_next))
                                        ;
                                    else
                                    {
                                        std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                                        yyerror(error.c_str());
                                    }
                                }
                        }
                        else if(isPrimitive(type) || isAutomata(type))
                            ;
                        else if(sst->lookup(type))
                            ;
                        else if(std::find(type_list.begin(),type_list.end(),type)!=type_list.end())
                            ;
                        else
                        {
                            std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                            yyerror(error.c_str());
                        }
                        //insert into param list
                        entry->id_list.push_back(*it);

                    }
                        (yyval.c) = new cc_code();
                        (yyval.c)->cc = "template <" + (yyvsp[-6].state_lst)->cc + std::string("> ") + (yyvsp[-4].type)->cc + std::string(" ") + std::string((yyvsp[-3].identifier)) + std::string("(") + (yyvsp[-1].para)->cc + std::string(")");
                        cc_file<<(yyval.c)->cc;
                        (yyval.c)->cc = "";
                }
#line 2053 "parser.cc"
    break;

  case 24: /* type_list: ID  */
#line 621 "../src/parser.y"
          {
            
            //check if ID exists as a struct
            if(sst->lookup(std::string((yyvsp[0].identifier))))
            {
                std::string error = "Cannot be used as typename as Struct with same name exists: "+std::string((yyvsp[0].identifier));
                yyerror(error.c_str());
            }
            if(std::string((yyvsp[0].identifier))=="void")
            {
                yyerror("Cannot use void as typename");
            }
            (yyval.state_lst) = new state_list_attr();
            (yyval.state_lst)->lst.push_back(std::string((yyvsp[0].identifier)));
            //insert this ID in the struct symbol table
            VarSymbolTable *table = new VarSymbolTable();
            StructSymbolTableEntry *entry_struct = new StructSymbolTableEntry(std::string((yyvsp[0].identifier)),table);
            entry_struct->isTemplate = true;
            sst->insert(entry_struct);
            (yyval.state_lst)->cc = "typename " + std::string((yyvsp[0].identifier));
          }
#line 2079 "parser.cc"
    break;

  case 25: /* type_list: type_list COMMA ID  */
#line 643 "../src/parser.y"
          {
            //check if ID exists as a struct
            if(sst->lookup(std::string((yyvsp[0].identifier))))
            {
                std::string error = "Cannot be used as typename as Struct with same name exists: "+std::string((yyvsp[0].identifier));
                yyerror(error.c_str());
            }
            if(std::string((yyvsp[0].identifier))=="void")
            {
                yyerror("Cannot use void as typename");
            }
            (yyval.state_lst) = new state_list_attr();
            (yyval.state_lst)->lst = (yyvsp[-2].state_lst)->lst;
            (yyval.state_lst)->lst.push_back(std::string((yyvsp[0].identifier)));
            //insert this ID in the struct symbol table
            VarSymbolTable *table = new VarSymbolTable();
            StructSymbolTableEntry *entry_struct = new StructSymbolTableEntry(std::string((yyvsp[0].identifier)),table);
            entry_struct->isTemplate = true;
            sst->insert(entry_struct);
            (yyval.state_lst)->cc = (yyvsp[-2].state_lst)->cc + std::string(", typename ") + std::string((yyvsp[0].identifier));
          }
#line 2105 "parser.cc"
    break;

  case 26: /* param_list: %empty  */
#line 667 "../src/parser.y"
            {
                //no params
                (yyval.para) = new param_list_attr();
                (yyval.para)->num = 0;
                VarSymbolTable *new_st = new VarSymbolTable();
                current_vst = new_st;
                vstl->insert(new_st);
                (yyval.para)->cc = std::string("");
            }
#line 2119 "parser.cc"
    break;

  case 27: /* param_list: param next_param  */
#line 677 "../src/parser.y"
          {
            if(vstl->lookup((yyvsp[-1].id)->name))
            {
                std::string error = "Variable redeclaration: "+(yyvsp[-1].id)->name;
                yyerror(error.c_str());
            }
            if((yyvsp[-1].id)->indicator==7)
            {
                //check if struct exists
                if(!sst->lookup((yyvsp[-1].id)->ifStruct))
                {
                    std::string str = std::string("Error: Struct ")+(yyvsp[-1].id)->ifStruct+std::string(" not defined");
                    yyerror(str.c_str());
                }
                VarSymbolTableEntry *entry = new VarSymbolTableEntry((yyvsp[-1].id)->name);
                entry->type = (yyvsp[-1].id)->ifStruct;
                entry->struct_vst = sst->lookup((yyvsp[-1].id)->ifStruct)->fields;
                current_vst->insert(entry);
            }
            else
            {
                VarSymbolTableEntry *entry = new VarSymbolTableEntry((yyvsp[-1].id)->name);
                if((yyvsp[-1].id)->indicator!=8)
                    entry->type = getType((yyvsp[-1].id));
                else
                    entry->type = std::string("template");
                if((yyvsp[-1].id)->indicator==2)
                {
                    entry->inner = genInnerType((yyvsp[-1].id)->inner);
                }
                current_vst->insert(entry);
            }
            (yyval.para) = new param_list_attr();
            (yyval.para)->num = num_params;
            (yyval.para)->lst = (yyvsp[0].para)->lst;
            (yyval.para)->lst.push_back((yyvsp[-1].id)->name);
            (yyval.para)->cc = (yyvsp[-1].id)->cc + std::string(" ") + (yyvsp[0].para)->cc;
          }
#line 2162 "parser.cc"
    break;

  case 28: /* param: dtype ID  */
#line 718 "../src/parser.y"
     {
        (yyval.id) = new id_attr();
        (yyval.id)->name = std::string((yyvsp[0].identifier));
        (yyval.id)->indicator = (yyvsp[-1].type)->indicator;
        (yyval.id)->vtp = (yyvsp[-1].type)->vtp;
        (yyval.id)->vta = (yyvsp[-1].type)->vta;
        (yyval.id)->vts = (yyvsp[-1].type)->vts;
        std::string inner = (yyvsp[-1].type)->inner->print();
        if(inner[inner.length()-1]==' ')
            inner = inner.substr(0,inner.length()-1);
        (yyval.id)->inner = inner;
        ++num_params;
        (yyval.id)->cc = (yyvsp[-1].type)->cc + std::string(" ") + std::string((yyvsp[0].identifier));
     }
#line 2181 "parser.cc"
    break;

  case 29: /* param: ID ID  */
#line 733 "../src/parser.y"
     {
        (yyval.id) = new id_attr();
        (yyval.id)->name = std::string((yyvsp[0].identifier));
        (yyval.id)->indicator = 7;
        if(!sst->lookup(std::string((yyvsp[-1].identifier))))
        {
            (yyval.id)->indicator = 8;
        }
        (yyval.id)->vtsr = TYPE_STRU;
        (yyval.id)->ifStruct = std::string((yyvsp[-1].identifier));
        ++num_params;
        (yyval.id)->cc = std::string((yyvsp[-1].identifier)) + std::string(" ") + std::string((yyvsp[0].identifier));
     }
#line 2199 "parser.cc"
    break;

  case 30: /* next_param: %empty  */
#line 749 "../src/parser.y"
            {
                //end of params
                (yyval.para) = new param_list_attr();
                (yyval.para)->num = num_params;

                VarSymbolTable *new_st = new VarSymbolTable();
                current_vst = new_st;
                (yyval.para)->cc = std::string("");
            }
#line 2213 "parser.cc"
    break;

  case 31: /* next_param: COMMA param next_param  */
#line 759 "../src/parser.y"
           {
                (yyval.para) = new param_list_attr();
                (yyval.para)->num = num_params;
                (yyval.para)->lst = (yyvsp[0].para)->lst;
                (yyval.para)->lst.push_back((yyvsp[-1].id)->name);
                //check if variable redeclaration
                if(vstl->lookup((yyvsp[-1].id)->name))
                {
                    std::string error = "Variable redeclaration: "+(yyvsp[-1].id)->name;
                    yyerror(error.c_str());
                }
                if((yyvsp[-1].id)->indicator ==7)
                {
                    //check if struct exists
                    if(!sst->lookup((yyvsp[-1].id)->ifStruct))
                    {
                        std::string str = std::string("Error: Struct ")+(yyvsp[-1].id)->ifStruct+std::string(" not defined");
                        yyerror(str.c_str());
                    }
                    VarSymbolTableEntry *entry = new VarSymbolTableEntry((yyvsp[-1].id)->name);
                    entry->type = (yyvsp[-1].id)->ifStruct;
                    entry->struct_vst = sst->lookup((yyvsp[-1].id)->ifStruct)->fields;
                    current_vst->insert(entry);
                }
                else
                {
                    VarSymbolTableEntry *entry = new VarSymbolTableEntry((yyvsp[-1].id)->name);
                    entry->type = getType((yyvsp[-1].id));
                    if((yyvsp[-1].id)->indicator==2)
                    {
                        entry->inner = genInnerType((yyvsp[-1].id)->inner);
                    }
                    current_vst->insert(entry);
                }
                (yyval.para)->cc = std::string(", ")+(yyvsp[-1].id)->cc + std::string(" ") + (yyvsp[0].para)->cc;
           }
#line 2254 "parser.cc"
    break;

  case 35: /* statements: variable_declaration  */
#line 802 "../src/parser.y"
                                 {
            printlog("Variable declaration");
            }
#line 2262 "parser.cc"
    break;

  case 36: /* statements: assignment  */
#line 805 "../src/parser.y"
                       {
            printlog("Assignment");
            (yyval.c) = new cc_code();
            (yyval.c)->cc = (yyvsp[0].c)->cc;
            cc_file<<(yyval.c)->cc<<std::endl;
            }
#line 2273 "parser.cc"
    break;

  case 37: /* statements: if_statement  */
#line 812 "../src/parser.y"
          {
            (yyval.c) = new cc_code();
            (yyval.c)->cc = std::string("");
          }
#line 2282 "parser.cc"
    break;

  case 38: /* statements: while_statement  */
#line 817 "../src/parser.y"
          {
            (yyval.c) = new cc_code();
            (yyval.c)->cc = std::string("");
          }
#line 2291 "parser.cc"
    break;

  case 39: /* statements: return_statement  */
#line 821 "../src/parser.y"
                             {printlog("Return");}
#line 2297 "parser.cc"
    break;

  case 40: /* statements: break_statement  */
#line 822 "../src/parser.y"
                            {printlog("Break");}
#line 2303 "parser.cc"
    break;

  case 41: /* statements: continue_statement  */
#line 823 "../src/parser.y"
                               {printlog("Continue");}
#line 2309 "parser.cc"
    break;

  case 42: /* statements: call_statement  */
#line 824 "../src/parser.y"
                           {printlog("Function call");}
#line 2315 "parser.cc"
    break;

  case 43: /* $@4: %empty  */
#line 825 "../src/parser.y"
                   {
                        //create a new symbol table
                        VarSymbolTable *new_st = new VarSymbolTable();
                        current_vst = new_st;
                        vstl->insert(new_st);
                    }
#line 2326 "parser.cc"
    break;

  case 44: /* statements: LBRACE $@4 control_body RBRACE  */
#line 831 "../src/parser.y"
                              {
            //remove symbol table
            if(vstl->remove())
                yyerror("Internal Error");
            current_vst = vstl->getTop();
            printlog("Block");
            }
#line 2338 "parser.cc"
    break;

  case 45: /* variable_declaration: dtype id_list SEMICOLON  */
#line 841 "../src/parser.y"
                    {
                        // backpatch id_list with dtype
                        for(auto it = (yyvsp[-1].id_lst)->lst.begin();it!=(yyvsp[-1].id_lst)->lst.end();it++)
                        {
                            if(it->second->indicator)
                            {
                                if(it->second->indicator!=1 && (yyvsp[-2].type)->indicator==1) //Primitive DTYPE
                                {
                                    std::string str = std::string("Error: Invalid type conversion from ")+getType(it->second)+std::string(" to ")+getType((yyvsp[-2].type));
                                    yyerror(str.c_str());
                                }
                                // for dynamic set initialization also need to check inner type (to be done)
                                if((yyvsp[-2].type)->indicator==2 && (it->second->indicator!=2 && it->second->indicator!=6)) //Set DTYPE
                                {
                                    std::string str = std::string("Error: Invalid type conversion from ")+getType(it->second)+std::string(" to ")+getType((yyvsp[-2].type));
                                    yyerror(str.c_str());
                                    // *** sets
                                }
                                if((yyvsp[-2].type)->indicator==3 && it->second->indicator!=3 || ((yyvsp[-2].type)->indicator==3 && (yyvsp[-2].type)->vta != it->second->vta))
                                {
                                    std::string str = std::string("Error: Invalid type conversion from ")+getType(it->second)+std::string(" to ")+getType((yyvsp[-2].type));
                                    yyerror(str.c_str());
                                }
                                if((yyvsp[-2].type)->indicator==4 && it->second->indicator!=4)
                                {
                                    std::string str = std::string("Error: Invalid type conversion from ")+getType(it->second)+std::string(" to ")+getType((yyvsp[-2].type));
                                    yyerror(str.c_str());
                                }
                                if((yyvsp[-2].type)->indicator==5 && it->second->indicator!=5)
                                {
                                    std::string str = std::string("Error: Invalid type conversion from ")+getType(it->second)+std::string(" to ")+getType((yyvsp[-2].type));
                                    yyerror(str.c_str());
                                }
                            }
                        }
                        // safe to backpatch
                        if((yyvsp[-2].type)->indicator!=3)
                        {
                            for(auto it = (yyvsp[-1].id_lst)->lst.begin();it!=(yyvsp[-1].id_lst)->lst.end();it++)
                            {
                                if(current_vst->backpatch(it->first,getType((yyvsp[-2].type)),(yyvsp[-2].type)->inner,NULL))
                                {
                                    yyerror("Internal Error");
                                }

                            }
                            if((yyvsp[-2].type)->indicator!=2)
                            {
                                cc_file<<(yyvsp[-2].type)->cc + std::string(" ") + (yyvsp[-1].id_lst)->cc +std::string(";")<<std::endl;
                            }  
                            else
                            {
                                int i = 0;
                                bool flag = false;
                                for(auto it=(yyvsp[-1].id_lst)->lst.begin();it!=(yyvsp[-1].id_lst)->lst.end();it++)
                                {
                                   if(it->second->indicator!=6 && i)
                                   {
                                     cc_file<<std::string(" ,")<<it->first->name;
                                     if(it->second->indicator)
                                        cc_file<<std::string(" = ")<<it->second->cc;
                                     ++i;
                                     flag = false;
                                   }
                                   else if(it->second->indicator!=6)
                                   {
                                     cc_file<<(yyvsp[-2].type)->cc+ std::string(" ");
                                     cc_file<<std::string(" ")<<it->first->name;
                                        if(it->second->indicator)
                                            cc_file<<std::string(" = ")<<it->second->cc;
                                     ++i;
                                     flag = false;
                                   }
                                   else
                                   {
                                    std::queue<std::string> stk;
                                    stk = st.front();
                                    cc_file<<";\n"<<(yyvsp[-2].type)->cc + std::string(" ")<<it->first->name<<";"<<std::endl;
                                    st.pop();
                                    i=0;
                                    while(!stk.empty())
                                    {
                                        // add inserts
                                        std::string str = stk.front();
                                        stk.pop();
                                        cc_file<<it->first->name<<".insert("<<str<<");"<<std::endl;
                                    }
                                    flag = true;    
                                   }
                                } 
                                if(!flag)
                                    cc_file<<";"<<std::endl;
                            }    
                        }
                        else
                        {
                            for(auto it=(yyvsp[-1].id_lst)->lst.begin();it!=(yyvsp[-1].id_lst)->lst.end();it++)
                            {
                                VarSymbolTable *struct_vst = sst->lookup(std::string(getFSM((yyvsp[-2].type)->vta)))->fields;
                                if(current_vst->backpatch(it->first,getType((yyvsp[-2].type)),NULL,struct_vst))
                                {
                                    yyerror("Internal Error");
                                }
                            }
                            cc_file<<(yyvsp[-2].type)->cc + std::string(" ") + (yyvsp[-1].id_lst)->cc +std::string(";")<<std::endl;
                        }
                    }
#line 2450 "parser.cc"
    break;

  case 46: /* variable_declaration: ID id_list SEMICOLON  */
#line 949 "../src/parser.y"
                    {
                        //check if struct exists
                        if(!sst->lookup(std::string((yyvsp[-2].identifier))))
                        {
                            std::string str = std::string("Error: Struct ")+std::string((yyvsp[-2].identifier))+std::string(" not defined");
                            yyerror(str.c_str());
                        }
                        std::list<int> *temp;
                        temp = new std::list<int>();
                        VarSymbolTable *struct_fields = sst->lookup(std::string((yyvsp[-2].identifier)))->fields;
                        for(auto it = (yyvsp[-1].id_lst)->lst.begin();it!=(yyvsp[-1].id_lst)->lst.end();it++)
                        {
                            if(current_vst->backpatch(it->first,std::string((yyvsp[-2].identifier)),NULL,struct_fields))
                            {
                                yyerror("Internal Error");
                            }
                        }
                        // before backpatching check if rhs are variables of same struct type (to be done)
                        cc_file<<"struct "<<std::string((yyvsp[-2].identifier))<<" "<<(yyvsp[-1].id_lst)->cc<<";"<<std::endl;
                    }
#line 2475 "parser.cc"
    break;

  case 47: /* id_list: ID  */
#line 971 "../src/parser.y"
            {
                (yyval.id_lst) = new id_list_attr();
                //insert this ID in the symbol table (backpatch later)
                if(current_vst->lookup(std::string((yyvsp[0].identifier))))
                {
                    std::string error = "Variable redeclaration: "+std::string((yyvsp[0].identifier));
                    yyerror(error.c_str());
                }
                //check in function params also
                if(current_function)
                {
                    if(current_function->params->lookup(std::string((yyvsp[0].identifier))))
                    {
                        std::string error = "Variable redeclaration: "+std::string((yyvsp[0].identifier));
                        yyerror(error.c_str());
                    }
                }
                VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string((yyvsp[0].identifier)));
                current_vst->insert(entry);
                type_attr *type = new type_attr();
                type->indicator = 0;
                (yyval.id_lst)->lst.push_back(std::make_pair(entry,type));
                (yyval.id_lst)->cc = std::string((yyvsp[0].identifier));
            }
#line 2504 "parser.cc"
    break;

  case 48: /* id_list: ID OPER_ASN_SIMPLE rhs  */
#line 996 "../src/parser.y"
       {
            (yyval.id_lst) = new id_list_attr();
            //insert this ID in the symbol table (backpatch later)
            if(current_vst->lookup(std::string((yyvsp[-2].identifier))))
            {
                std::string error = "Variable redeclaration: "+std::string((yyvsp[-2].identifier));
                yyerror(error.c_str());
            }
            //check if function params also
            if(current_function)
            {
                if(current_function->params->lookup(std::string((yyvsp[-2].identifier))))
                {
                    std::string error = "Variable redeclaration: "+std::string((yyvsp[-2].identifier));
                    yyerror(error.c_str());
                }
            }
            VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string((yyvsp[-2].identifier)));
            current_vst->insert(entry);
            type_attr *type = new type_attr();
            type->indicator = (yyvsp[0].type)->indicator;
            type->vtp = (yyvsp[0].type)->vtp;
            type->vta = (yyvsp[0].type)->vta;
            type->vts = (yyvsp[0].type)->vts;
            type->inner = (yyvsp[0].type)->inner;
            type->cc = (yyvsp[0].type)->cc;
            if(!current_function && !(yyvsp[0].type)->isConst)
                yyerror("Cannot initialize global variable with a non-constant value");
            (yyval.id_lst)->lst.push_back(std::make_pair(entry,type));
            (yyval.id_lst)->cc = std::string((yyvsp[-2].identifier)) + std::string(" = ") + std::string((yyvsp[0].type)->cc);
       }
#line 2540 "parser.cc"
    break;

  case 49: /* id_list: id_list COMMA ID  */
#line 1028 "../src/parser.y"
       {
            (yyval.id_lst) = new id_list_attr();
            //insert this ID in the symbol table (backpatch later)
            if(current_vst->lookup(std::string((yyvsp[0].identifier))))
            {
                std::string error = "Variable redeclaration: "+std::string((yyvsp[0].identifier));
                yyerror(error.c_str());
            }
            VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string((yyvsp[0].identifier)));
            current_vst->insert(entry);
            type_attr *type = new type_attr();
            type->indicator = 0;
            //append to list
            (yyval.id_lst)->lst = (yyvsp[-2].id_lst)->lst;
            (yyval.id_lst)->lst.push_back(std::make_pair(entry,type));
            (yyval.id_lst)->cc = (yyvsp[-2].id_lst)->cc + std::string(", ") + std::string((yyvsp[0].identifier));
       }
#line 2562 "parser.cc"
    break;

  case 50: /* id_list: id_list COMMA ID OPER_ASN_SIMPLE rhs  */
#line 1046 "../src/parser.y"
       {
            (yyval.id_lst) = new id_list_attr();
            //insert this ID in the symbol table (backpatch later)
            if(current_vst->lookup(std::string((yyvsp[-2].identifier))))
            {
                std::string error = "Variable redeclaration: "+std::string((yyvsp[-2].identifier));
                yyerror(error.c_str());
            }
            VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string((yyvsp[-2].identifier)));
            current_vst->insert(entry);
            type_attr *type = new type_attr();
            type->indicator = (yyvsp[0].type)->indicator;
            type->vtp = (yyvsp[0].type)->vtp;
            type->vta = (yyvsp[0].type)->vta;
            type->vts = (yyvsp[0].type)->vts;
            type->inner = (yyvsp[0].type)->inner;
            type->cc = (yyvsp[0].type)->cc;
            //append to list
            (yyval.id_lst)->lst = (yyvsp[-4].id_lst)->lst;
            (yyval.id_lst)->lst.push_back(std::make_pair(entry,type));
            (yyval.id_lst)->cc = (yyvsp[-4].id_lst)->cc + std::string(", ") + std::string((yyvsp[-2].identifier)) + std::string(" = ") + (yyvsp[0].type)->cc;
       }
#line 2589 "parser.cc"
    break;

  case 51: /* pseudo_ID: pseudo_ID LBRACK expression RBRACK  */
#line 1071 "../src/parser.y"
         {
            //accessing the set member
            if((yyvsp[-1].expr)->indicator != 1)
                yyerror("Invalid operation: Set can only be accessed using integer index");
            if(!isInteger((yyvsp[-1].expr)->vtp))
                yyerror("Invalid operation: Set can only be accessed using integer/unsigned integer index");
            //idea is to build the entire pseudo_ID and check whenever it is used somewhere
            (yyval.id) = new id_attr();
            if((yyvsp[-1].expr)->isConst)
                (yyval.id)->name = std::string((yyvsp[-3].id)->name)+std::string("[")+std::to_string((yyvsp[-1].expr)->val->ccint)+std::string("]");
            else //first need to build expression
                (yyval.id)->name = std::string((yyvsp[-3].id)->name)+std::string("[")+std::string("_expr_")+std::string("]");
            (yyval.id)->cc = (yyvsp[-3].id)->cc + "[" + (yyvsp[-1].expr)->cc + "]";
         }
#line 2608 "parser.cc"
    break;

  case 52: /* pseudo_ID: pseudo_ID DOT pseudo_ID  */
#line 1086 "../src/parser.y"
         {
            //accessing the inner member
            (yyval.id) = new id_attr();
            (yyval.id)->name = std::string((yyvsp[-2].id)->name)+std::string(".")+std::string((yyvsp[0].id)->name);
            (yyval.id)->cc = (yyvsp[-2].id)->cc + "." + (yyvsp[0].id)->cc;
         }
#line 2619 "parser.cc"
    break;

  case 53: /* pseudo_ID: ID  */
#line 1092 "../src/parser.y"
              {
                //check if ID exists
                (yyval.id) = new id_attr();
                (yyval.id)->name = (yyvsp[0].identifier);
                (yyval.id)->cc = std::string((yyvsp[0].identifier));
              }
#line 2630 "parser.cc"
    break;

  case 54: /* assignment: pseudo_ID OPER_ASN rhs SEMICOLON  */
#line 1101 "../src/parser.y"
            {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,(yyvsp[-3].id)->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            //we need to match rhs type with type of pseudo_ID
            std::string type_lhs = ret.second.substr(ret.second.find(" ")+1);
            std::string type_rhs = getType((yyvsp[-1].type));
            if(type_rhs[type_rhs.length()-1]==' ')
                    type_rhs=type_rhs.substr(0,type_rhs.length()-1);
            if(type_rhs=="string" || type_rhs=="regex" || type_lhs=="" || type_lhs=="regex")
            {
                //error
                std::string error = std::string("Invalid operation: Cannot use operator +=/-=/*=//=/%= on ")+type_lhs+std::string(" and ")+type_rhs;
                yyerror(error.c_str());
            }
            if(!isPrimitive(type_rhs) || !isPrimitive(type_lhs))
            {   
                //error
                std::string outer_lhs = type_lhs.find(" ")!=std::string::npos?type_lhs.substr(0,type_lhs.find(" ")):type_lhs;
                std::string error = std::string("Invalid operation: Cannot use operator ") + std::string((yyvsp[-2].identifier)) + std::string(" on ") +outer_lhs +std::string(" and ")+type_rhs;
                yyerror(error.c_str());
            }
            if(!isCoherent(type_lhs,type_rhs))
            {
                std::string error = std::string("Error: Invalid type conversion from ")+type_rhs+std::string(" to ")+type_lhs;
                yyerror(error.c_str());
            }
            // need to be done
            (yyval.c)->cc = std::string((yyvsp[-3].id)->cc) + " " +std::string((yyvsp[-2].identifier)) + std::string((yyvsp[-1].type)->cc)+std::string(" ;");
            }
#line 2665 "parser.cc"
    break;

  case 55: /* assignment: pseudo_ID OPER_ASN_SIMPLE rhs SEMICOLON  */
#line 1131 "../src/parser.y"
                                                    {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,(yyvsp[-3].id)->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type_lhs = ret.second.substr(ret.second.find(" ")+1);
            std::string type_rhs = getType((yyvsp[-1].type));
            if(type_rhs[type_rhs.length()-1]==' ')
                    type_rhs=type_rhs.substr(0,type_rhs.length()-1);
            if(type_rhs=="o_set"||type_rhs=="u_set"||type_rhs=="sets")
            {   
                type_rhs+=std::string(" ")+(yyvsp[-1].type)->inner->print();
                if(type_rhs[type_rhs.length()-1]==' ')
                    type_rhs=type_rhs.substr(0,type_rhs.length()-1);
            }
            if(type_rhs=="string" && type_lhs=="string"){
                (yyval.c)->cc = std::string((yyvsp[-3].id)->cc) + " = " + std::string((yyvsp[-1].type)->cc)+std::string(" ;");
            }
            else
            {
                if(!isCoherent(type_lhs,type_rhs))
                {
                    std::string error = std::string("Error: Invalid type conversion from ")+type_rhs+std::string(" to ")+type_lhs;
                    yyerror(error.c_str());
                }
                // need to be done
                if((yyvsp[-1].type)->indicator==6)
                {
                    //set initialization
                    std::queue<std::string> stk;
                    stk = st.front();
                    st.pop();
                    (yyval.c)->cc = "";
                    while(!stk.empty())
                    {
                        // add inserts
                        std::string str = stk.front();
                        stk.pop();
                        cc_file<<(yyvsp[-3].id)->cc<<".insert("<<str<<");"<<std::endl;
                    }
                }
                else
                    (yyval.c)->cc = std::string((yyvsp[-3].id)->cc)+" = "+std::string((yyvsp[-1].type)->cc) + std::string(" ;");
            }
        }
#line 2714 "parser.cc"
    break;

  case 56: /* assignment: pseudo_ID OPER_ASN_SIMPLE REGEX_R REGEX_LIT SEMICOLON  */
#line 1176 "../src/parser.y"
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,(yyvsp[-4].id)->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type_lhs = ret.second.substr(ret.second.find(" ")+1);
            std::string type_rhs("regex");
            if(!isCoherent(type_lhs,type_rhs))
            {
                std::string error = std::string("Error: Invalid type conversion from ")+type_rhs+std::string(" to ")+type_lhs;
                yyerror(error.c_str());
            }
            std::string lit((yyvsp[-1].identifier));
            lit = lit.substr(1,lit.length()-2);
            (yyval.c)->cc = std::string((yyvsp[-4].id)->cc)+" = " + "*(new fsm::regex(\""+lit+"\"));\n";
          }
#line 2734 "parser.cc"
    break;

  case 57: /* assignment: pseudo_ID COLON OPER_ASN_SIMPLE rhs_automata SEMICOLON  */
#line 1206 "../src/parser.y"
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,(yyvsp[-4].id)->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type = stripFound(ret.second);
            if(type!="alphabets" && type!="transitions_nfa" && type!="transitions_dfa" && type!="transitions_pda")
            {
                std::string error = std::string("Error: Invalid type conversion from transition function to ")+type;
                yyerror(error.c_str());
            }
            if(type=="alphabets" && (yyvsp[-1].rhs_automata)->type!="alphabets")
            {
                std::string error = std::string("Error: Invalid type conversion from ")+(yyvsp[-1].rhs_automata)->type+std::string(" to ")+type;
                yyerror(error.c_str());
            }
            if(type=="transitions_dfa" && ((yyvsp[-1].rhs_automata)->type!="transitions" || (yyvsp[-1].rhs_automata)->automata_type!="dfa"))
            {
                std::string error = std::string("Error: Invalid type conversion from ")+((yyvsp[-1].rhs_automata)->type=="transitions"?(std::string("transitions_")+(yyvsp[-1].rhs_automata)->automata_type):"alphabets")+std::string(" to ")+type;
                yyerror(error.c_str());
            }
            if(type=="transitions_pda" && ((yyvsp[-1].rhs_automata)->type!="transitions" || (yyvsp[-1].rhs_automata)->automata_type!="pda"))
            {
                std::string error = std::string("Error: Invalid type conversion from")+((yyvsp[-1].rhs_automata)->type=="transitions"?(std::string("transitions_")+(yyvsp[-1].rhs_automata)->automata_type):"alphabets")+std::string(" to ")+type;
                yyerror(error.c_str());
            }
            if(type=="transitions_nfa" && ((yyvsp[-1].rhs_automata)->type!="transitions" || ((yyvsp[-1].rhs_automata)->automata_type!="nfa" && (yyvsp[-1].rhs_automata)->automata_type!="dfa")))
            {
                std::string error = std::string("Error: Invalid type conversion from")+((yyvsp[-1].rhs_automata)->type=="transitions"?(std::string("transitions_")+(yyvsp[-1].rhs_automata)->automata_type):"alphabets")+std::string(" to ")+type;
                yyerror(error.c_str());
            }
            //codegen
            if(type=="alphabets")
            {
                std::string str = (yyvsp[-4].id)->cc.substr(0,(yyvsp[-4].id)->cc.find_last_of("."));
                for(auto it = current_alphabets->begin(); it!=current_alphabets->end();it++)
                {
                    cc_file<<str<<".insert_alphabet("<<(*it).first<<", "<<(*it).second<<");"<<std::endl;
                }
                current_alphabets = NULL;
            }
            if(type=="transitions_nfa")
            {
                std::string str = (yyvsp[-4].id)->cc.substr(0,(yyvsp[-4].id)->cc.find_last_of("."));
                for(auto it = transition->begin(); it!=transition->end();it++)
                {
                    cc_file<<str<<".insert_transition(\""<<(*it)[0]<<"\", \""<<(*it)[1]<<"\", \""<<(*it)[2]<<"\");"<<std::endl;
                }
                transition = NULL;
            }
            if(type=="transitions_dfa")
            {
                std::string str = (yyvsp[-4].id)->cc.substr(0,(yyvsp[-4].id)->cc.find_last_of("."));
                for(auto it = transition->begin(); it!=transition->end();it++)
                {
                    cc_file<<str<<".insert_transition(\""<<(*it)[0]<<"\", \""<<(*it)[1]<<"\", \""<<(*it)[2]<<"\");"<<std::endl;
                }
                transition = NULL;
            }
            if(type=="transitions_pda")
            {
                std::string str = (yyvsp[-4].id)->cc.substr(0,(yyvsp[-4].id)->cc.find_last_of("."));
                for(auto it = transition->begin(); it!=transition->end();it++)
                {
                    cc_file<<str<<".insert_transition(\""<<(*it)[0]<<"\", \""<<(*it)[1]<<"\", \""<<(*it)[2]<<"\", \""<<(*it)[3]<<"\", \""<<(*it)[4]<<"\");"<<std::endl;
                }
                transition = NULL;
            }
          (yyval.c)->cc = std::string("");
          current_automata = 0;
          }
#line 2809 "parser.cc"
    break;

  case 58: /* assignment: pseudo_ID COLON OPER_ASN_SIMPLE cfg_rules SEMICOLON  */
#line 1277 "../src/parser.y"
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,(yyvsp[-4].id)->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type = stripFound(ret.second);
            if(type!="productions")
            {
                std::string error = std::string("Error: Invalid type conversion from productions to ")+type;
                yyerror(error.c_str());
            }
            //codegen
            std::string str = (yyvsp[-4].id)->cc.substr(0,(yyvsp[-4].id)->cc.find_last_of("."));
            (yyval.c)->cc = std::string("");
            for(auto &it: *cfg_prods)
            {
                if(it[0].find(".")!=std::string::npos || it[0].find("[")!=std::string::npos)   
                    yyerror("Incorrect format of cfg non-terminal in lhs of rule");
                std::string init = it[0];
                std::string prod = it[1];
                cc_file<<str<<".add_P(\""<<init<<" -> "<<prod<<"\");"<<std::endl;
                
            }
            cfg_prods = NULL;
          }
#line 2838 "parser.cc"
    break;

  case 59: /* assignment: pseudo_ID COLON OPER_ASN_SIMPLE ID SEMICOLON  */
#line 1302 "../src/parser.y"
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,(yyvsp[-4].id)->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type = stripFound(ret.second);
            if(type!="start")
            {
                std::string error = std::string("Error: Invalid type conversion from start state to")+type;
                yyerror(error.c_str());
            }
            (yyval.c)->cc = std::string("");
            //codegen
            std::string str = (yyvsp[-4].id)->cc.substr(0,(yyvsp[-4].id)->cc.find_last_of("."));
            cc_file<<str<<".change_start(\""<<std::string((yyvsp[-1].identifier))<<"\");"<<std::endl;
          }
#line 2858 "parser.cc"
    break;

  case 60: /* assignment: pseudo_ID COLON OPER_ASN_SIMPLE LBRACE states_list RBRACE SEMICOLON  */
#line 1318 "../src/parser.y"
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,(yyvsp[-6].id)->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            // stateslist and accept states list
            std::string type = stripFound(ret.second);
            if(type!="states" && type!="accept")
            {
                std::string error = std::string("Error: Invalid type conversion from list of states to ")+type;
                yyerror(error.c_str());
            }
            if(type=="states")
            {
                std::string str = (yyvsp[-6].id)->cc.substr(0,(yyvsp[-6].id)->cc.find_last_of("."));
                for(auto &it: *current_states)
                {
                    cc_file<<str<<".insert_state("<<it<<");"<<std::endl;
                }
                current_states = NULL;
            }
            if(type=="accept")
            {
                std::string str = (yyvsp[-6].id)->cc.substr(0,(yyvsp[-6].id)->cc.find_last_of("."));
                for(auto &it: *current_states)
                {
                    cc_file<<str<<".insert_final("<<it<<");"<<std::endl;
                }
                current_states = NULL;
            }
            (yyval.c)->cc = std::string("");
          }
#line 2894 "parser.cc"
    break;

  case 61: /* states_list: ID  */
#line 1352 "../src/parser.y"
           {
                //need to accumulate IDs which will be used as states and non-terminals
                (yyval.state_lst) = new state_list_attr();
                (yyval.state_lst)->lst.push_back(std::string((yyvsp[0].identifier)));
                if(current_states==NULL)
                    current_states = new std::vector<std::string>();
                current_states->push_back("\""+std::string((yyvsp[0].identifier))+"\"");

           }
#line 2908 "parser.cc"
    break;

  case 62: /* states_list: states_list COMMA ID  */
#line 1362 "../src/parser.y"
           {
                (yyval.state_lst) = new state_list_attr();
                (yyval.state_lst)->lst = (yyvsp[-2].state_lst)->lst;
                (yyval.state_lst)->lst.push_back(std::string((yyvsp[0].identifier)));
                if(current_states==NULL)
                    current_states = new std::vector<std::string>();
                current_states->push_back("\""+std::string((yyvsp[0].identifier))+"\"");
           }
#line 2921 "parser.cc"
    break;

  case 66: /* cfg_rule: pseudo_ID ARROW cfg_rhs  */
#line 1380 "../src/parser.y"
            {
                //codegen
                std::string str = (yyvsp[-2].id)->cc.substr(0,(yyvsp[-2].id)->cc.find_last_of("."));
                for(auto &it: *cfg_rhs_current)
                {
                    std::vector<std::string> *temp = new std::vector<std::string>();
                    temp->push_back((yyvsp[-2].id)->cc);
                    temp->push_back(it);
                    if(cfg_prods==NULL)
                        cfg_prods = new std::vector<std::vector<std::string>>();
                    cfg_prods->push_back(*temp);
                }
                cfg_rhs_current = NULL;
                
            }
#line 2941 "parser.cc"
    break;

  case 67: /* rhs: expression  */
#line 1398 "../src/parser.y"
    {
        (yyval.type) = new type_attr();
        (yyval.type)->vtp = (yyvsp[0].expr)->vtp;
        (yyval.type)->vta = (yyvsp[0].expr)->vta;
        (yyval.type)->vts = (yyvsp[0].expr)->vts;
        (yyval.type)->inner = (yyvsp[0].expr)->inner;
        (yyval.type)->isConst = (yyvsp[0].expr)->isConst;
        (yyval.type)->indicator = (yyvsp[0].expr)->indicator;
        if((yyval.type)->isConst)
        {
            (yyval.type)->val = new constant();
            (yyval.type)->val->type = getCTYPE((yyval.type));
            if((yyval.type)->val->type==CINT)
                (yyval.type)->val->ccint = getConst((yyvsp[0].expr));
            else if((yyval.type)->val->type==CFLOAT)
                (yyval.type)->val->ccfloat = getConst((yyvsp[0].expr));
            else if((yyval.type)->val->type==CBOOL)
                (yyval.type)->val->ccbool = getConst((yyvsp[0].expr));
            else if((yyval.type)->val->type==CCHAR)
                (yyval.type)->val->ccchar = getConst((yyvsp[0].expr));
        }
        (yyval.type)->cc = std::string((yyvsp[0].expr)->cc);
    }
#line 2969 "parser.cc"
    break;

  case 68: /* rhs: LBRACE expression_list RBRACE  */
#line 1422 "../src/parser.y"
   {
     /*
        indicator = 1 arithmetic expressions
        indicator = 2 set expressions
        indicator = 3 automata expressions
        indicator = 4 string initialization
        indicator = 5 regex initialization
        indicator = 6 dynamic set initialization
        indicator = 7 struct
     */
     (yyval.type) = new type_attr();
     (yyval.type)->indicator = 6;
     //based on the type of the element set inner type
     (yyval.type)->inner = genInnerType((yyvsp[-1].expr_lst)->inner);
     st.push(*current_queue);
     current_queue = NULL;
   }
#line 2991 "parser.cc"
    break;

  case 69: /* rhs: REGEX_R REGEX_LIT  */
#line 1440 "../src/parser.y"
   {
    (yyval.type) = new type_attr();
    (yyval.type)->indicator = 5;
    (yyval.type)->vtsr = TYPE_REGEX;
   }
#line 3001 "parser.cc"
    break;

  case 70: /* rhs: STRING_CONST  */
#line 1446 "../src/parser.y"
   {
    (yyval.type) = new type_attr();
    (yyval.type)->indicator = 4;
    (yyval.type)->vtsr = TYPE_STR;
    (yyval.type)->cc = std::string((yyvsp[0].cstring));
   }
#line 3012 "parser.cc"
    break;

  case 71: /* expression: LPAREN expression RPAREN  */
#line 1454 "../src/parser.y"
                                     {
                                      (yyval.expr) = new expr_attr();
                                      (yyval.expr)->indicator = (yyvsp[-1].expr)->indicator;
                                      (yyval.expr)->vtp = (yyvsp[-1].expr)->vtp;
                                      (yyval.expr)->vta = (yyvsp[-1].expr)->vta;
                                      (yyval.expr)->vts = (yyvsp[-1].expr)->vts;
                                      (yyval.expr)->isConst = false;
                                      if((yyvsp[-1].expr)->isConst)
                                      {
                                        (yyval.expr)->isConst = true;
                                        (yyval.expr)->val = (yyvsp[-1].expr)->val;
                                      }
                                      (yyval.expr)->cc = std::string("(")+(yyvsp[-1].expr)->cc+std::string(")");
                                     }
#line 3031 "parser.cc"
    break;

  case 72: /* expression: expression OPER_PLUS expression  */
#line 1469 "../src/parser.y"
          {
                (yyval.expr) = new expr_attr();
                if((yyvsp[-2].expr)->indicator ==1 && (yyvsp[0].expr)->indicator==1)
                {
                    (yyval.expr)->indicator = 1;
                    if((yyvsp[-2].expr)->vtp==TYPE_FLOAT_64 || (yyvsp[0].expr)->vtp==TYPE_FLOAT_64)
                    (yyval.expr)->vtp = TYPE_FLOAT_64;
                    else if((yyvsp[-2].expr)->vtp==TYPE_FLOAT_32 || (yyvsp[0].expr)->vtp==TYPE_FLOAT_32)
                        (yyval.expr)->vtp = TYPE_FLOAT_32;
                    else
                        (yyval.expr)->vtp = TYPE_INT_64;
                    (yyval.expr)->isConst = false;
                    if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
                    {
                        (yyval.expr)->isConst = true;
                        (yyval.expr)->val = new constant();
                        (yyval.expr)->val->type = getCTYPE((yyval.expr));
                        if((yyval.expr)->val->type==CINT)
                            (yyval.expr)->val->ccint = getConst((yyvsp[-2].expr))+getConst((yyvsp[0].expr));
                        else if((yyval.expr)->val->type==CFLOAT)
                            (yyval.expr)->val->ccfloat = getConst((yyvsp[-2].expr))+getConst((yyvsp[0].expr));
                        else if((yyval.expr)->val->type==CBOOL)
                            (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr))+getConst((yyvsp[0].expr));
                        else if((yyval.expr)->val->type==CCHAR)
                            (yyval.expr)->val->ccchar = getConst((yyvsp[-2].expr))+getConst((yyvsp[0].expr));
                    }
                    (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" + ") + (yyvsp[0].expr)->cc;
                }
                else if((yyvsp[-2].expr)->indicator ==2 && (yyvsp[0].expr)->indicator==2)
                {
                    (yyval.expr)->indicator = 2;
                    if((yyvsp[-2].expr)->vts==TYPE_OSET || (yyvsp[0].expr)->vts==TYPE_OSET)
                    {
                        (yyval.expr)->vts = TYPE_OSET;
                    }
                    else if((yyvsp[-2].expr)->vts==TYPE_USET || (yyvsp[0].expr)->vts==TYPE_USET)
                    {
                        (yyval.expr)->vts = TYPE_USET;
                    }
                    else
                    {
                        (yyval.expr)->vts = TYPE_OSET;
                    }
                    if(trim((yyvsp[-2].expr)->inner->print())!=trim((yyvsp[0].expr)->inner->print()))
                    {
                        std::string error = std::string("Invalid operation: Cannot add sets of different types: ")+(yyvsp[-2].expr)->inner->print()+std::string(" and ")+(yyvsp[0].expr)->inner->print();
                        yyerror(error.c_str());
                    }
                    else
                        (yyval.expr)->inner = (yyvsp[-2].expr)->inner;
                    (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" + ") + (yyvsp[0].expr)->cc;
                }
                else if((yyvsp[-2].expr)->indicator==3 && (yyvsp[0].expr)->indicator==3)
                {
                    if(((yyvsp[-2].expr)->vta == TYPE_NFA && (yyvsp[0].expr)->vta == TYPE_DFA) || ((yyvsp[0].expr)->vta == TYPE_NFA && (yyvsp[-2].expr)->vta == TYPE_DFA) || ((yyvsp[-2].expr)->vta == TYPE_NFA && (yyvsp[0].expr)->vta == TYPE_NFA))
                    {
                        (yyval.expr)->vta = TYPE_DFA;
                        if((yyvsp[-2].expr)->vta==TYPE_NFA && (yyvsp[0].expr)->vta ==TYPE_NFA)
                            (yyval.expr)->cc = std::string("(*fsm::union_nfa(")+(yyvsp[-2].expr)->cc+std::string(", ")+(yyvsp[0].expr)->cc+std::string("))");
                        else
                        {
                            (yyval.expr)->vta = TYPE_NFA;
                            (yyval.expr)->cc = std::string("(*fsm::union_nfa_dfa(")+(yyvsp[-2].expr)->cc+std::string(", ")+(yyvsp[0].expr)->cc+std::string("))");
                        }
                    }
                    else if((yyvsp[-2].expr)->vta == TYPE_DFA && (yyvsp[0].expr)->vta == TYPE_DFA)
                    {
                        (yyval.expr)->vta = TYPE_DFA;
                        (yyval.expr)->cc = std::string("(*fsm::union_dfa(")+(yyvsp[-2].expr)->cc+std::string(", ")+(yyvsp[0].expr)->cc+std::string("))");
                    }
                    else if((yyvsp[-2].expr)->vta == TYPE_PDA && (yyvsp[0].expr)->vta == TYPE_PDA)
                    {
                        (yyval.expr)->vta = TYPE_PDA;
                        (yyval.expr)->cc = std::string("(*fsm::union_pda(")+(yyvsp[-2].expr)->cc+std::string(", ")+(yyvsp[0].expr)->cc+std::string("))");
                    }
                    else if((yyvsp[-2].expr)->vta == TYPE_CFG && (yyvsp[0].expr)->vta == TYPE_CFG)
                    {
                        (yyval.expr)->vta = TYPE_CFG;
                        (yyval.expr)->cc = std::string("(*fsm::union_cfg(")+(yyvsp[-2].expr)->cc+std::string(", ")+(yyvsp[0].expr)->cc+std::string("))");
                    }
                    else 
                    {
                        std::string error = std::string("Invalid operation:")+std::string(getVTA((yyvsp[-2].expr)->vta))+std::string(", ")+std::string(getVTA((yyvsp[0].expr)->vta))+std::string(" union  not defined");
                        yyerror(error.c_str());
                    }
                }
                else
                    yyerror("Invalid operation: Addition can only be done between 'primitive' types");
          }
#line 3125 "parser.cc"
    break;

  case 73: /* expression: expression OPER_MINUS expression  */
#line 1559 "../src/parser.y"
          {
                // Set difference
                (yyval.expr) = new expr_attr();
                if((yyvsp[-2].expr)->indicator==1 && (yyvsp[0].expr)->indicator==1)
                {
                    (yyval.expr)->indicator = 1;
                    (yyval.expr)->isConst = false;
                    if((yyvsp[-2].expr)->vtp==TYPE_FLOAT_64 || (yyvsp[0].expr)->vtp==TYPE_FLOAT_64)
                        (yyval.expr)->vtp = TYPE_FLOAT_64;
                    else if((yyvsp[-2].expr)->vtp==TYPE_FLOAT_32 || (yyvsp[0].expr)->vtp==TYPE_FLOAT_32)
                        (yyval.expr)->vtp = TYPE_FLOAT_32;
                    else
                        (yyval.expr)->vtp = TYPE_INT_64;
                    if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
                    {
                        (yyval.expr)->isConst = true;
                        (yyval.expr)->val = new constant();
                        (yyval.expr)->val->type = getCTYPE((yyval.expr));
                        if((yyval.expr)->val->type==CINT)
                            (yyval.expr)->val->ccint = getConst((yyvsp[-2].expr))-getConst((yyvsp[0].expr));
                        else if((yyval.expr)->val->type==CFLOAT)
                            (yyval.expr)->val->ccfloat = getConst((yyvsp[-2].expr))-getConst((yyvsp[0].expr));
                        else if((yyval.expr)->val->type==CBOOL)
                            (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr))-getConst((yyvsp[0].expr));
                        else if((yyval.expr)->val->type==CCHAR)
                            (yyval.expr)->val->ccchar = getConst((yyvsp[-2].expr))-getConst((yyvsp[0].expr));
                    }
                (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" - ") + (yyvsp[0].expr)->cc;
                }
                else if((yyvsp[-2].expr)->indicator==2 && (yyvsp[0].expr)->indicator==2)
                {
                    (yyval.expr)->indicator = 2;
                    if((yyvsp[-2].expr)->vts==TYPE_OSET || (yyvsp[0].expr)->vts==TYPE_OSET)
                    {
                        (yyval.expr)->vts = TYPE_OSET;
                    }
                    else if((yyvsp[-2].expr)->vts==TYPE_USET || (yyvsp[0].expr)->vts==TYPE_USET)
                    {
                        (yyval.expr)->vts = TYPE_USET;
                    }
                    else
                    {
                        (yyval.expr)->vts = TYPE_OSET;
                    }
                    if(trim((yyvsp[-2].expr)->inner->print())!=trim((yyvsp[0].expr)->inner->print()))
                    {
                        std::string error = std::string("Invalid operation: Cannot subtract sets of different types: ")+(yyvsp[-2].expr)->inner->print()+std::string(" and ")+(yyvsp[0].expr)->inner->print();
                        yyerror(error.c_str());
                    }
                    else
                        (yyval.expr)->inner = (yyvsp[-2].expr)->inner;
                    (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" - ") + (yyvsp[0].expr)->cc;
                }
                else
                    yyerror("Invalid operation: Subtrction can only be done between 'primitive' and 'set' types");
          }
#line 3186 "parser.cc"
    break;

  case 74: /* expression: expression OPER_MUL expression  */
#line 1616 "../src/parser.y"
          {
                (yyval.expr) = new expr_attr();
                //intersection
                (yyval.expr)->isConst = false;
                if((yyvsp[-2].expr)->indicator ==1 && (yyvsp[0].expr)->indicator ==1)
                {
                    (yyval.expr)->indicator = 1;
                    if((yyvsp[-2].expr)->vtp==TYPE_FLOAT_64 || (yyvsp[0].expr)->vtp==TYPE_FLOAT_64)
                        (yyval.expr)->vtp = TYPE_FLOAT_64;
                    else if((yyvsp[-2].expr)->vtp==TYPE_FLOAT_32 || (yyvsp[0].expr)->vtp==TYPE_FLOAT_32)
                        (yyval.expr)->vtp = TYPE_FLOAT_32;
                    else
                        (yyval.expr)->vtp = TYPE_INT_64;
                    if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
                    {
                        (yyval.expr)->isConst = true;
                        (yyval.expr)->val = new constant();
                        (yyval.expr)->val->type = getCTYPE((yyval.expr));
                        if((yyval.expr)->val->type==CINT)
                            (yyval.expr)->val->ccint = getConst((yyvsp[-2].expr))*getConst((yyvsp[0].expr));
                        else if((yyval.expr)->val->type==CFLOAT)
                            (yyval.expr)->val->ccfloat = getConst((yyvsp[-2].expr))*getConst((yyvsp[0].expr));
                        else if((yyval.expr)->val->type==CBOOL)
                            (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr))*getConst((yyvsp[0].expr));
                        else if((yyval.expr)->val->type==CCHAR)
                            (yyval.expr)->val->ccchar = getConst((yyvsp[-2].expr))*getConst((yyvsp[0].expr));
                    }
                }
                else if((yyvsp[-2].expr)->indicator ==2 && (yyvsp[0].expr)->indicator ==2)
                {
                    (yyval.expr)->indicator = 2;
                    if((yyvsp[-2].expr)->vts==TYPE_OSET || (yyvsp[0].expr)->vts==TYPE_OSET)
                    {
                        (yyval.expr)->vts = TYPE_OSET;
                    }
                    else if((yyvsp[-2].expr)->vts==TYPE_USET || (yyvsp[0].expr)->vts==TYPE_USET)
                    {
                        (yyval.expr)->vts = TYPE_USET;
                    }
                    else
                    {
                        (yyval.expr)->vts = TYPE_OSET;
                    }
                    if(trim((yyvsp[-2].expr)->inner->print())!=trim((yyvsp[0].expr)->inner->print()))
                    {
                        std::string error = std::string("Invalid operation: Cannot multiply sets of different types: ")+(yyvsp[-2].expr)->inner->print()+std::string(" and ")+(yyvsp[0].expr)->inner->print();
                        yyerror(error.c_str());
                    }
                    else
                        (yyval.expr)->inner = (yyvsp[-2].expr)->inner;
                }
                else
                    yyerror("Invalid operation: Multiplication can only be done between 'primitive' and 'set' types");
                (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" * ") + (yyvsp[0].expr)->cc;
          }
#line 3246 "parser.cc"
    break;

  case 75: /* expression: expression OPER_DIV expression  */
#line 1672 "../src/parser.y"
          {
            (yyval.expr) = new expr_attr();
            if((yyvsp[-2].expr)->indicator !=1 || (yyvsp[0].expr)->indicator !=1)
                yyerror("Invalid operation: Division can only be done between 'primitive' types");
            //check for division by zero (to be done)
            if((yyvsp[0].expr)->val && (((yyvsp[0].expr)->val->type == CINT && (yyvsp[0].expr)->val->ccint == 0) || ((yyvsp[0].expr)->val->type == CFLOAT && (yyvsp[0].expr)->val->ccfloat == 0.0) || ((yyvsp[0].expr)->val->type == CBOOL && (yyvsp[0].expr)->val->ccbool == false)||( (yyvsp[0].expr)->val->type == CCHAR && (yyvsp[0].expr)->val->ccchar == '\0')))
                yyerror("Invalid operation: Division by zero");
            (yyval.expr)->indicator = 1;
            (yyval.expr)->isConst = false;
            if((yyvsp[-2].expr)->vtp==TYPE_FLOAT_64 || (yyvsp[0].expr)->vtp==TYPE_FLOAT_64)
                (yyval.expr)->vtp = TYPE_FLOAT_64;
            else if((yyvsp[-2].expr)->vtp==TYPE_FLOAT_32 || (yyvsp[0].expr)->vtp==TYPE_FLOAT_32)
                (yyval.expr)->vtp = TYPE_FLOAT_32;
            else
                (yyval.expr)->vtp = TYPE_INT_64;
            if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
            {
                (yyval.expr)->isConst = true;
                (yyval.expr)->val = new constant();
                (yyval.expr)->val->type = getCTYPE((yyval.expr));
                if((yyval.expr)->val->type==CINT)
                    (yyval.expr)->val->ccint = getConst((yyvsp[-2].expr))/getConst((yyvsp[0].expr));
                else if((yyval.expr)->val->type==CFLOAT)
                    (yyval.expr)->val->ccfloat = getConst((yyvsp[-2].expr))/getConst((yyvsp[0].expr));
                else if((yyval.expr)->val->type==CBOOL)
                    (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr))/getConst((yyvsp[0].expr));
                else if((yyval.expr)->val->type==CCHAR)
                    (yyval.expr)->val->ccchar = getConst((yyvsp[-2].expr))/getConst((yyvsp[0].expr));
            }
            (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" / ") + (yyvsp[0].expr)->cc;
          }
#line 3282 "parser.cc"
    break;

  case 76: /* expression: expression OPER_MOD expression  */
#line 1704 "../src/parser.y"
          {
            (yyval.expr) = new expr_attr();
            if((yyvsp[-2].expr)->indicator !=1 || (yyvsp[0].expr)->indicator !=1)
                yyerror("Invalid operation: Modulo can only be done between 'integer' types");
            if((yyvsp[-2].expr)->vtp==TYPE_FLOAT_64 || (yyvsp[0].expr)->vtp==TYPE_FLOAT_64 || (yyvsp[-2].expr)->vtp==TYPE_FLOAT_32 || (yyvsp[0].expr)->vtp==TYPE_FLOAT_32)
                yyerror("Invalid operation: Modulo can only be done between 'integer' types");
            (yyval.expr)->indicator = 1;
            (yyval.expr)->isConst = false;
            (yyval.expr)->vtp = TYPE_INT_64;
            if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
            {
                (yyval.expr)->isConst = true;
                (yyval.expr)->val = new constant();
                (yyval.expr)->val->type = getCTYPE((yyval.expr));
                if((yyval.expr)->val->type==CINT)
                    (yyval.expr)->val->ccint = (yyvsp[-2].expr)->val->ccint % (yyvsp[0].expr)->val->ccint;
            }
            (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" % ") + (yyvsp[0].expr)->cc;
          }
#line 3306 "parser.cc"
    break;

  case 77: /* expression: expression OPER_COMP expression  */
#line 1724 "../src/parser.y"
          {
            (yyval.expr) = new expr_attr();
            if((yyvsp[-2].expr)->indicator !=1 || (yyvsp[0].expr)->indicator !=1)
                yyerror("Invalid comparison: Comparison can only be done between primitive types");
            (yyval.expr)->indicator = 1;
            (yyval.expr)->vtp = TYPE_BOOL;
            std::string comp((yyvsp[-1].comp)); //"<=",">=","==","!="
            (yyval.expr)->isConst = false;
            if(comp=="<=")
            {
                if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
                {
                    (yyval.expr)->isConst = true;
                    (yyval.expr)->val = new constant();
                    (yyval.expr)->val->type = CBOOL;
                    (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr))<=getConst((yyvsp[0].expr));
                }
            }
            if(comp==">=")
            {
                if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
                {
                    (yyval.expr)->isConst = true;
                    (yyval.expr)->val = new constant();
                    (yyval.expr)->val->type = CBOOL;
                    (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr))>=getConst((yyvsp[0].expr));
                }
            }
            if(comp=="==")
            {
                if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
                {
                    (yyval.expr)->isConst = true;
                    (yyval.expr)->val = new constant();
                    (yyval.expr)->val->type = CBOOL;
                    (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr))==getConst((yyvsp[0].expr));
                }
            }
            if(comp=="!=")
            {
                if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
                {
                    (yyval.expr)->isConst = true;
                    (yyval.expr)->val = new constant();
                    (yyval.expr)->val->type = CBOOL;
                    (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr))!=getConst((yyvsp[0].expr));
                }
            }
            (yyval.expr)->cc = (yyvsp[-2].expr)->cc + comp + (yyvsp[0].expr)->cc;
          }
#line 3361 "parser.cc"
    break;

  case 78: /* expression: expression OPER_POWER  */
#line 1775 "../src/parser.y"
          {
            (yyval.expr) = new expr_attr();
            if((yyvsp[-1].expr)->indicator !=2)
                yyerror("Invalid operation: Power set can only be computed for a set");
            (yyval.expr)->indicator = 2;
            (yyval.expr)->vts = (yyvsp[-1].expr)->vts;
            (yyval.expr)->isConst = false;
            std::string str = (yyvsp[-1].expr)->inner->print();
            if((yyval.expr)->vts==TYPE_OSET)
                str ="o_set " + trim(str);
            else
                str ="u_set " + trim(str);
            (yyval.expr)->inner = genInnerType(trim(str));
            (yyval.expr)->cc = (yyvsp[-1].expr)->cc+std::string(".power_set()");
          }
#line 3381 "parser.cc"
    break;

  case 79: /* expression: expression AT_THE_RATE expression  */
#line 1791 "../src/parser.y"
          {
            (yyval.expr) = new expr_attr();
            // What about regex? (to be done) cfg + pdas (to be done)
            if((yyvsp[-2].expr)->indicator !=2 || (yyvsp[0].expr)->indicator != 2)
                yyerror("Invalid operation: Automata can only be concatenated with Automata");
            (yyval.expr)->indicator = 2;
            if(((yyvsp[-2].expr)->vta == TYPE_NFA && (yyvsp[0].expr)->vta == TYPE_DFA) || ((yyvsp[0].expr)->vta == TYPE_NFA && (yyvsp[-2].expr)->vta == TYPE_DFA) || ((yyvsp[-2].expr)->vta == TYPE_NFA && (yyvsp[0].expr)->vta == TYPE_NFA))
                (yyval.expr)->vta = TYPE_NFA;
            else if((yyvsp[-2].expr)->vta == TYPE_DFA && (yyvsp[0].expr)->vta == TYPE_DFA)
                (yyval.expr)->vta = TYPE_DFA;
            else if((yyvsp[-2].expr)->vta == TYPE_PDA && (yyvsp[0].expr)->vta == TYPE_PDA)
                (yyval.expr)->vta = TYPE_PDA;
            else if((yyvsp[-2].expr)->vta == TYPE_CFG && (yyvsp[0].expr)->vta == TYPE_CFG)
                (yyval.expr)->vta = TYPE_CFG;
            else
                yyerror("Invalid operation: Automata can only be concatenated with Automata");
            (yyval.expr)->isConst = false;
            // codegen required
          }
#line 3405 "parser.cc"
    break;

  case 80: /* expression: expression OPER_OR expression  */
#line 1811 "../src/parser.y"
          {
            (yyval.expr) = new expr_attr();
            if((yyvsp[-2].expr)->indicator ==3 || (yyvsp[0].expr)->indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if((yyvsp[-2].expr)->indicator == 2 || (yyvsp[0].expr)->indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            (yyval.expr)->indicator = 1;
            (yyval.expr)->vtp = TYPE_BOOL;
            (yyval.expr)->isConst = false;
            if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
            {
                (yyval.expr)->isConst = true;
                (yyval.expr)->val = new constant();
                (yyval.expr)->val->type = CBOOL;
                (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr)) || getConst((yyvsp[0].expr));
            }
            else if((yyvsp[-2].expr)->isConst)
            {
                if(((yyvsp[-2].expr)->val->type==CINT && (yyvsp[-2].expr)->val->ccint!=0) || ((yyvsp[-2].expr)->val->type==CFLOAT && (yyvsp[-2].expr)->val->ccfloat!=0.0) || ((yyvsp[-2].expr)->val->type==CBOOL && (yyvsp[-2].expr)->val->ccbool!=false) || ((yyvsp[-2].expr)->val->type==CCHAR && (yyvsp[-2].expr)->val->ccchar!='\0'))
                {
                    (yyval.expr)->isConst = true;
                    (yyval.expr)->val = new constant();
                    (yyval.expr)->val->type = CBOOL;
                    (yyval.expr)->val->ccbool = true;
                }
            }
            else if((yyvsp[0].expr)->isConst)
            {
                if(((yyvsp[0].expr)->val->type==CINT && (yyvsp[0].expr)->val->ccint!=0) || ((yyvsp[0].expr)->val->type==CFLOAT && (yyvsp[0].expr)->val->ccfloat!=0.0) || ((yyvsp[0].expr)->val->type==CBOOL && (yyvsp[0].expr)->val->ccbool!=false) || ((yyvsp[0].expr)->val->type==CCHAR && (yyvsp[0].expr)->val->ccchar!='\0'))
                {
                    (yyval.expr)->isConst = true;
                    (yyval.expr)->val = new constant();
                    (yyval.expr)->val->type = CBOOL;
                    (yyval.expr)->val->ccbool = true;
                }
            }
            (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" || ") + (yyvsp[0].expr)->cc;
          }
#line 3448 "parser.cc"
    break;

  case 81: /* expression: expression OPER_AND expression  */
#line 1850 "../src/parser.y"
          {
            (yyval.expr) = new expr_attr();
            if((yyvsp[-2].expr)->indicator ==3 || (yyvsp[0].expr)->indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if((yyvsp[-2].expr)->indicator == 2 || (yyvsp[0].expr)->indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            (yyval.expr)->indicator = 1;
            (yyval.expr)->vtp = TYPE_BOOL;
            (yyval.expr)->isConst = false;
            if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
            {
                (yyval.expr)->val->type = CBOOL;
                (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr)) && getConst((yyvsp[0].expr));
            }
            else if((yyvsp[-2].expr)->isConst)
            {
                if(((yyvsp[-2].expr)->val->type==CINT && (yyvsp[-2].expr)->val->ccint==0) || ((yyvsp[-2].expr)->val->type==CFLOAT && (yyvsp[-2].expr)->val->ccfloat==0.0) || ((yyvsp[-2].expr)->val->type==CBOOL && (yyvsp[-2].expr)->val->ccbool==false) || ((yyvsp[-2].expr)->val->type==CCHAR && (yyvsp[-2].expr)->val->ccchar=='\0'))
                {
                    (yyval.expr)->isConst = true;
                    (yyval.expr)->val = new constant();
                    (yyval.expr)->val->type = CBOOL;
                    (yyval.expr)->val->ccbool = false;
                }
            }
            else if((yyvsp[0].expr)->isConst)
            {
                if(((yyvsp[0].expr)->val->type==CINT && (yyvsp[0].expr)->val->ccint==0) || ((yyvsp[0].expr)->val->type==CFLOAT && (yyvsp[0].expr)->val->ccfloat==0.0) || ((yyvsp[0].expr)->val->type==CBOOL && (yyvsp[0].expr)->val->ccbool==false) || ((yyvsp[0].expr)->val->type==CCHAR && (yyvsp[0].expr)->val->ccchar=='\0'))
                {
                    (yyval.expr)->isConst = true;
                    (yyval.expr)->val = new constant();
                    (yyval.expr)->val->type = CBOOL;
                    (yyval.expr)->val->ccbool = false;
                }
            }
            (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" && ") + (yyvsp[0].expr)->cc;
          }
#line 3489 "parser.cc"
    break;

  case 82: /* expression: expression COMP_GT expression  */
#line 1887 "../src/parser.y"
          {
            (yyval.expr) = new expr_attr();
            if((yyvsp[-2].expr)->indicator ==3 || (yyvsp[0].expr)->indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if((yyvsp[-2].expr)->indicator == 2 || (yyvsp[0].expr)->indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            (yyval.expr)->indicator = 1;
            (yyval.expr)->vtp = TYPE_BOOL;
            (yyval.expr)->isConst = false;
            //constant check
            if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
            {
                (yyval.expr)->isConst = true;
                (yyval.expr)->val = new constant();
                (yyval.expr)->val->type = CBOOL;
                (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr))>getConst((yyvsp[0].expr));
            }
            (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" > ") + (yyvsp[0].expr)->cc;
          }
#line 3513 "parser.cc"
    break;

  case 83: /* expression: expression COMP_LT expression  */
#line 1907 "../src/parser.y"
          {
            (yyval.expr) = new expr_attr();
            if((yyvsp[-2].expr)->indicator ==3 || (yyvsp[0].expr)->indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if((yyvsp[-2].expr)->indicator == 2 || (yyvsp[0].expr)->indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            (yyval.expr)->indicator = 1;
            (yyval.expr)->vtp = TYPE_BOOL;
            (yyval.expr)->isConst = false;
            //constant check
            if((yyvsp[-2].expr)->isConst && (yyvsp[0].expr)->isConst)
            {
                (yyval.expr)->isConst = true;
                (yyval.expr)->val = new constant();
                (yyval.expr)->val->type = CBOOL;
                (yyval.expr)->val->ccbool = getConst((yyvsp[-2].expr))<getConst((yyvsp[0].expr));
            }
            (yyval.expr)->cc = (yyvsp[-2].expr)->cc + std::string(" < ") + (yyvsp[0].expr)->cc;
          }
#line 3537 "parser.cc"
    break;

  case 84: /* expression: OPER_NOT expression  */
#line 1926 "../src/parser.y"
                                { 
            (yyval.expr) = new expr_attr();
            if((yyvsp[0].expr)->indicator ==2)
                yyerror("Invalid operator: Negation of Set not defined");
            if((yyvsp[0].expr)->indicator ==3 && ((yyvsp[0].expr)->vta == TYPE_CFG || (yyvsp[0].expr)->vta == TYPE_PDA))
                yyerror("Invalid operator: CFG/NDPDA not closed under complement");
            (yyval.expr)->indicator = (yyvsp[0].expr)->indicator;
            (yyval.expr)->isConst = false;
            if((yyvsp[0].expr)->indicator == 1)
            {
                if((yyvsp[0].expr)->isConst)
                {
                    (yyval.expr)->isConst = true;
                    (yyval.expr)->val = new constant();
                    (yyval.expr)->val->type = CBOOL;
                    if((yyvsp[0].expr)->val->type == CINT)
                        (yyval.expr)->val->ccbool = !((yyvsp[0].expr)->val->ccint);
                    else if((yyvsp[0].expr)->val->type == CFLOAT)
                        (yyval.expr)->val->ccbool = !((yyvsp[0].expr)->val->ccfloat);
                    else if((yyvsp[0].expr)->val->type == CBOOL)
                        (yyval.expr)->val->ccbool = !((yyvsp[0].expr)->val->ccbool);
                    else if((yyvsp[0].expr)->val->type == CCHAR)
                        (yyval.expr)->val->ccbool = !((yyvsp[0].expr)->val->ccchar);
                }
                else
                    (yyval.expr)->isConst = false;
                (yyval.expr)->vtp = TYPE_BOOL;
            }
            else if((yyvsp[0].expr)->indicator == 3)
                {(yyval.expr)->vta = (yyvsp[0].expr)->vta; (yyval.expr)->isConst = false;}
            (yyval.expr)->cc = std::string("!")+((yyvsp[0].expr)->cc);

          }
#line 3575 "parser.cc"
    break;

  case 85: /* expression: expression OPER_HASH  */
#line 1959 "../src/parser.y"
                                 { 
            (yyval.expr) = new expr_attr();
            if((yyvsp[-1].expr)->indicator !=3)
                yyerror("Invalid operator: Kleene Star can only be applied to Automata");
            (yyval.expr)->indicator = 3;
            (yyval.expr)->vta = (yyvsp[-1].expr)->vta;
            (yyval.expr)->isConst = false;
            //codegen required
          }
#line 3589 "parser.cc"
    break;

  case 86: /* expression: OPER_MINUS expression  */
#line 1968 "../src/parser.y"
                                  { 
                                    (yyval.expr) = new expr_attr();
                                    (yyval.expr)->indicator = (yyvsp[0].expr)->indicator; 
                                    (yyval.expr)->vtp = (yyvsp[0].expr)->vtp; 
                                    (yyval.expr)->vta = (yyvsp[0].expr)->vta; 
                                    (yyval.expr)->vts = (yyvsp[0].expr)->vts;
                                    (yyval.expr)->isConst = (yyvsp[0].expr)->isConst;
                                    (yyval.expr)->val = (yyvsp[0].expr)->val;
                                    if((yyval.expr)->val)
                                    {
                                        switch((yyval.expr)->val->type)
                                        {
                                            case CINT:
                                                    (yyval.expr)->val->ccint = -((yyval.expr)->val->ccint);
                                                    break;
                                            case CFLOAT:
                                                    (yyval.expr)->val->ccfloat = -((yyval.expr)->val->ccfloat);
                                                    break;
                                            case CBOOL:
                                                    (yyval.expr)->val->ccbool = !((yyval.expr)->val->ccbool);
                                                    break;
                                            case CCHAR:
                                                    (yyval.expr)->val->ccchar = -((yyval.expr)->val->ccchar);
                                                    break;
                                        }
                                    }
                                    (yyval.expr)->cc = std::string("-")+((yyvsp[0].expr)->cc);
                                }
#line 3622 "parser.cc"
    break;

  case 87: /* expression: OPER_PLUS expression  */
#line 1996 "../src/parser.y"
                                 { 
                                  (yyval.expr) = new expr_attr();
                                  (yyval.expr)->indicator = (yyvsp[0].expr)->indicator;
                                  (yyval.expr)->vtp = (yyvsp[0].expr)->vtp; 
                                  (yyval.expr)->vta = (yyvsp[0].expr)->vta; 
                                  (yyval.expr)->vts = (yyvsp[0].expr)->vts;
                                  (yyval.expr)->isConst = (yyvsp[0].expr)->isConst;
                                  (yyval.expr)->val = (yyvsp[0].expr)->val;
                                  (yyval.expr)->cc = std::string("+")+((yyvsp[0].expr)->cc);
                                 }
#line 3637 "parser.cc"
    break;

  case 88: /* expression: INT_CONST  */
#line 2006 "../src/parser.y"
                      { 
                        (yyval.expr) = new expr_attr();
                        (yyval.expr)->indicator = 1; 
                        (yyval.expr)->vtp = TYPE_INT_64; 
                        (yyval.expr)->val = new constant();
                        (yyval.expr)->val->ccint = (yyvsp[0].cint);
                        (yyval.expr)->val->type = CINT;
                        (yyval.expr)->isConst = true;
                        (yyval.expr)->cc = std::to_string((yyvsp[0].cint));
                      }
#line 3652 "parser.cc"
    break;

  case 89: /* expression: FLOAT_CONST  */
#line 2016 "../src/parser.y"
                        { 
                          (yyval.expr) = new expr_attr();
                          (yyval.expr)->indicator = 1; 
                          (yyval.expr)->vtp = TYPE_FLOAT_64; 
                          (yyval.expr)->val = new constant();
                          (yyval.expr)->val->ccfloat = (yyvsp[0].cfloat);
                          (yyval.expr)->val->type = CFLOAT;
                          (yyval.expr)->isConst = true;
                          (yyval.expr)->cc = std::to_string((yyvsp[0].cfloat));
                        }
#line 3667 "parser.cc"
    break;

  case 90: /* expression: BOOL_CONST  */
#line 2026 "../src/parser.y"
                       { 
                         (yyval.expr) = new expr_attr();
                         (yyval.expr)->indicator = 1; 
                         (yyval.expr)->vtp = TYPE_BOOL; 
                         (yyval.expr)->val = new constant();
                         (yyval.expr)->val->ccbool = (yyvsp[0].cbool);
                         (yyval.expr)->val->type = CBOOL;
                         (yyval.expr)->isConst = true;
                        (yyval.expr)->cc = std::to_string((yyvsp[0].cbool));
                       }
#line 3682 "parser.cc"
    break;

  case 91: /* expression: CHAR_CONST  */
#line 2036 "../src/parser.y"
                       { 
                        (yyval.expr) = new expr_attr();
                        (yyval.expr)->indicator = 1; 
                        (yyval.expr)->vtp = TYPE_CHAR;
                        (yyval.expr)->val = new constant();
                        (yyval.expr)->val->ccchar = (yyvsp[0].cchar);
                        (yyval.expr)->val->type = CBOOL;
                        (yyval.expr)->isConst = true;
                        (yyval.expr)->cc = std::string(1,(yyvsp[0].cchar));
                       }
#line 3697 "parser.cc"
    break;

  case 92: /* expression: pseudo_ID  */
#line 2046 "../src/parser.y"
                      { 
                        (yyval.expr) = new expr_attr();
                        (yyval.expr)->indicator = (yyvsp[0].id)->indicator; 
                        (yyval.expr)->vtp = (yyvsp[0].id)->vtp; 
                        (yyval.expr)->vta = (yyvsp[0].id)->vta; 
                        (yyval.expr)->vts = (yyvsp[0].id)->vts;
                        std::pair<bool,std::string> ret = checkPseudoID(NULL,(yyvsp[0].id)->name,"");
                        if(!ret.first)
                            yyerror(ret.second.c_str());
                        else
                        {

                            (yyval.expr)->isConst = false;
                            std::string type = ret.second.substr(ret.second.find(' ')+1);
                            if(type.find(" ")!=std::string::npos && type.find(" ")!=type.length()-1)
                                type = type.substr(0,type.find(' ') );
                            if(type=="int_8")
                            {
                                (yyval.expr)->indicator = 1;
                                (yyval.expr)->vtp = TYPE_INT_8;
                            }
                            else if(type=="int_16")
                            {
                                (yyval.expr)->indicator = 1;
                                (yyval.expr)->vtp = TYPE_INT_16;
                            }
                            else if(type=="int_32")
                            {
                                (yyval.expr)->indicator = 1;
                                (yyval.expr)->vtp = TYPE_INT_32;
                            }
                            else if(type=="int_64")
                            {
                                (yyval.expr)->indicator = 1;
                                (yyval.expr)->vtp = TYPE_INT_64;
                            }
                            else if(type=="float_32")
                            {
                                (yyval.expr)->indicator = 1;
                                (yyval.expr)->vtp = TYPE_FLOAT_32;
                            }
                            else if(type=="float_64")
                            {
                                (yyval.expr)->indicator = 1;
                                (yyval.expr)->vtp = TYPE_FLOAT_64;
                            }
                            else if(type=="bool")
                            {
                                (yyval.expr)->indicator = 1;
                                (yyval.expr)->vtp = TYPE_BOOL;
                            }
                            else if(type=="char")
                            {
                                (yyval.expr)->indicator = 1;
                                (yyval.expr)->vtp = TYPE_CHAR;
                            }
                            else if(type=="string")
                            {
                                (yyval.expr)->indicator = 4;
                                (yyval.expr)->vtsr = TYPE_STR;
                            }
                            else if(type=="regex")
                            {
                                (yyval.expr)->indicator = 5;
                                (yyval.expr)->vtsr = TYPE_REGEX;
                            }
                            else if(type=="o_set" || type=="u_set")
                            {
                                (yyval.expr)->indicator = 2;
                                (yyval.expr)->vts = getSetType(type.c_str());
                                size_t first_space = ret.second.find(" ");
                                size_t second = ret.second.find(" ",first_space+1);
                                (yyval.expr)->inner = genInnerType(ret.second.substr(second+1));
                            }
                            else if(type=="nfa")
                            {
                                (yyval.expr)->indicator = 3;
                                (yyval.expr)->vta = TYPE_NFA;
                            }
                            else if(type=="dfa")
                            {
                                (yyval.expr)->indicator = 3;
                                (yyval.expr)->vta = TYPE_DFA;
                            }
                            else if(type=="pda")
                            {
                                (yyval.expr)->indicator = 3;
                                (yyval.expr)->vta = TYPE_PDA;
                            }
                            else if(type=="cfg")
                            {
                                (yyval.expr)->indicator = 3;
                                (yyval.expr)->vta = TYPE_CFG;
                            }
                            else
                            {
                                (yyval.expr)->indicator = 7;
                                (yyval.expr)->vtsr = TYPE_STRU;
                                (yyval.expr)->ifStruct = type;
                            }
                        }
                        (yyval.expr)->cc = (yyvsp[0].id)->cc;
                      }
#line 3805 "parser.cc"
    break;

  case 93: /* expression: call  */
#line 2149 "../src/parser.y"
                 {
                    // To be handled (to be done)
                    (yyval.expr) = new expr_attr();
                    (yyval.expr)->indicator = (yyvsp[0].type)->indicator;
                    if((yyvsp[0].type)->indicator==1)
                        (yyval.expr)->vtp = (yyvsp[0].type)->vtp;
                    else if((yyvsp[0].type)->indicator==2)
                    {
                        (yyval.expr)->vts = (yyvsp[0].type)->vts;
                        (yyval.expr)->inner = (yyvsp[0].type)->inner;
                    }
                    else if((yyvsp[0].type)->indicator==3)
                        (yyval.expr)->vta = (yyvsp[0].type)->vta;
                    else if((yyvsp[0].type)->indicator==4)
                        (yyval.expr)->vtsr = (yyvsp[0].type)->vtsr;
                    else if((yyvsp[0].type)->indicator==5)
                        (yyval.expr)->vtsr = (yyvsp[0].type)->vtsr;
                    else if((yyvsp[0].type)->indicator==7)
                    {
                        (yyval.expr)->vtsr = (yyvsp[0].type)->vtsr;
                        (yyval.expr)->ifStruct = (yyvsp[0].type)->ifStruct;
                    }
                    (yyval.expr)->cc = (yyvsp[0].type)->cc;
                 }
#line 3834 "parser.cc"
    break;

  case 94: /* call: ID LPAREN argument_list RPAREN  */
#line 2176 "../src/parser.y"
     {
        //check if function exists
        if(!fst->lookup(std::string((yyvsp[-3].identifier))))
        {
            std::string error = "Function "+std::string((yyvsp[-3].identifier))+std::string(" not defined");
            yyerror(error.c_str());
        }
        if(fst->lookup(std::string((yyvsp[-3].identifier)))->isTemplate)
            yyerror("Function is a template function");
        //check if argument type matches (to be done)
        //create type of call from return type of function
        FunctionSymbolTableEntry *entry = fst->lookup(std::string((yyvsp[-3].identifier)));
        // return_type is complete with inner types as well(in case of sets)
        (yyval.type) = new type_attr();
        //get first word
        std::string type = entry->return_type;
        std::string outer_type = type.substr(0,type.find(' '));
        if(isSet(outer_type)) //set
        {
            (yyval.type)->indicator = 2;
            (yyval.type)->vts = getSetType(outer_type.c_str());
            //recursively generate all inner types
            type = type.substr(type.find(' ')+1);
            (yyval.type)->inner = genInnerType(type);
        }
        else if(isPrimitive(outer_type))
        {
            (yyval.type)->indicator = 1;
            (yyval.type)->vtp = getPrimitiveType(outer_type.c_str());
        }
        else if(isAutomata(outer_type))
        {
            (yyval.type)->indicator = 3;
            (yyval.type)->vta = getAutomataType(outer_type.c_str());
        }
        else if(isSR(outer_type))
        {
            if(outer_type=="string")
                (yyval.type)->indicator = 4;
            else
                (yyval.type)->indicator = 5;
            (yyval.type)->vtsr = getSRType(outer_type.c_str());
        }
        else
        {
            (yyval.type)->indicator = 7;
            (yyval.type)->vtsr = TYPE_STRU;
            (yyval.type)->ifStruct = outer_type;
        }
        // we also need to check argument types
        std::vector<std::string> arg_pos_list_rev = entry->id_list;
        VarSymbolTable *params_table = entry->params;
        auto it_list = arg_pos_list_rev.begin();
        auto it_arg_list = (yyvsp[-1].arg)->lst.begin();
        //compare types
        int i=1;
        while(it_list!=arg_pos_list_rev.end() && it_arg_list!=(yyvsp[-1].arg)->lst.end())
        {
            std::string type_expected = params_table->lookup(*it_list)->type;
            std::string type_actual = *it_arg_list;
            type_actual = trim(type_actual);
            if(type_expected=="o_set"||type_expected=="u_set"||type_expected=="o_set "|| type_expected=="u_set ")
            {
                //concat inner types
                type_expected=trim(trim(type_expected)+std::string(" ")+params_table->lookup(*it_list)->inner->print());
            }
            if(!isCoherent(type_expected,type_actual))
            {
                std::string error = std::string("Argument type mismatch at pos " + std::to_string(i)+ ": Expected ")+type_expected+std::string(" but found ")+type_actual;
                yyerror(error.c_str());
            }
            ++it_list;
            ++it_arg_list;
            ++i;
        }
        if(it_list!=arg_pos_list_rev.end())
            yyerror("Too few arguments");
        else if(it_arg_list!=(yyvsp[-1].arg)->lst.end())
            yyerror("Too many arguments");
        if(std::string((yyvsp[-3].identifier))=="cfg_add_P" || std::string((yyvsp[-3].identifier))=="cfg_remove_P")
        {
            std::string cfg_name = (yyvsp[-1].arg)->cc.substr(0,(yyvsp[-1].arg)->cc.find(","));
            cfg_name = trim(cfg_name);
            std::string next = (yyvsp[-1].arg)->cc.substr((yyvsp[-1].arg)->cc.find(",")+1);
            std::string x = next.substr(0,next.find(","));
            x = trim(x);
            x = x.substr(0,x.length()-1);
            next = next.substr(next.find(",")+1);
            std::string y = next.substr(0,next.find(","));
            y = trim(y);
            y = y.substr(2,y.length()-1);
            (yyval.type)->cc = std::string((yyvsp[-3].identifier)) + std::string("(") + cfg_name + std::string(", ") + x + std::string(" -> ") + y + std::string(")");
        }
        else
            (yyval.type)->cc = std::string((yyvsp[-3].identifier)) + std::string("(") + (yyvsp[-1].arg)->cc + std::string(")");
     }
#line 3935 "parser.cc"
    break;

  case 95: /* call: ID TEMP_LEFT type_list_call TEMP_RIGHT LPAREN argument_list RPAREN  */
#line 2273 "../src/parser.y"
     {
        //check if function exists and is a template function
        FunctionSymbolTableEntry *entry = fst->lookup(std::string((yyvsp[-6].identifier)));
        if(!entry)
        {
            std::string error = "Function "+std::string((yyvsp[-6].identifier))+std::string(" not defined");
            yyerror(error.c_str());
        }
        if(!entry->isTemplate)
            yyerror("Function is not a template function");
        //check type_list
        if(entry->template_params.size()!=(yyvsp[-4].state_lst)->lst.size())
            yyerror("Invalid number of template arguments");
        // handling return type
        (yyval.type) = new type_attr();
        std::string type = entry->return_type;
        std::string outer_type = type.substr(0,type.find(' '));
        if(isSet(outer_type)) //set
        {
            (yyval.type)->indicator = 2;
            (yyval.type)->vts = getSetType(outer_type.c_str());
            //recursively generate all inner types
            type = type.substr(type.find(' ')+1);
            (yyval.type)->inner = genInnerType(type);
        }
        else if(isPrimitive(outer_type))
        {
            (yyval.type)->indicator = 1;
            (yyval.type)->vtp = getPrimitiveType(outer_type.c_str());
        }
        else if(isAutomata(outer_type))
        {
            (yyval.type)->indicator = 3;
            (yyval.type)->vta = getAutomataType(outer_type.c_str());
        }
        else if(isSR(outer_type))
        {
            if(outer_type=="string")
                (yyval.type)->indicator = 4;
            else
                (yyval.type)->indicator = 5;
            (yyval.type)->vtsr = getSRType(outer_type.c_str());
        }
        else
        {
            (yyval.type)->indicator = 7;
            (yyval.type)->vtsr = TYPE_STRU;
            (yyval.type)->ifStruct = outer_type;
        }
        // we also need to check argument types
        std::vector<std::string> arg_pos_list_rev = entry->id_list;
        VarSymbolTable *params_table = entry->params;
        auto it_list = arg_pos_list_rev.begin();
        auto it_arg_list = (yyvsp[-1].arg)->lst.begin();
        //compare types
        int i=1;
        while(it_list!=arg_pos_list_rev.end() && it_arg_list!=(yyvsp[-1].arg)->lst.end())
        {
            std::string type_expected = params_table->lookup(*it_list)->type;
            std::string type_actual = *it_arg_list;
            type_actual = trim(type_actual);
            if(type_expected=="template")
                continue;
            if(type_expected=="o_set"||type_expected=="u_set"||type_expected=="o_set "|| type_expected=="u_set ")
            {
                //concat inner types 
                type_expected=trim(trim(type_expected)+std::string(" ")+params_table->lookup(*it_list)->inner->print());
            }
            if(!isCoherent(type_expected,type_actual))
            {
                std::string error = std::string("Argument type mismatch at pos " + std::to_string(i)+ ": Expected ")+type_expected+std::string(" but found ")+type_actual;
                yyerror(error.c_str());
            }
            ++it_list;
            ++it_arg_list;
            ++i;
        }
        if(it_list!=arg_pos_list_rev.end())
            yyerror("Too few arguments");
        else if(it_arg_list!=(yyvsp[-1].arg)->lst.end())
            yyerror("Too many arguments");
        if(std::find(set_funcs->begin(),set_funcs->end(),std::string((yyvsp[-6].identifier)))!=set_funcs->end())
            (yyval.type)->cc = std::string((yyvsp[-6].identifier)) + std::string("(") + (yyvsp[-1].arg)->cc + std::string(")");
        else if(std::string((yyvsp[-6].identifier))=="out")
        {
            (yyval.type)->cc = "std::cout<<"+(yyvsp[-1].arg)->cc+"<<std::endl";
        }
        else
            (yyval.type)->cc = std::string((yyvsp[-6].identifier)) + "<" + (yyvsp[-4].state_lst)->cc + std::string(">")+std::string("(") + (yyvsp[-1].arg)->cc + std::string(")");
     }
#line 4030 "parser.cc"
    break;

  case 96: /* type_list_call: type_call  */
#line 2366 "../src/parser.y"
              {
                (yyval.state_lst) = new state_list_attr();
                (yyval.state_lst)->lst.push_back(std::string("temp"));
                (yyval.state_lst)->cc = (yyvsp[0].c)->cc;
              }
#line 4040 "parser.cc"
    break;

  case 97: /* type_list_call: type_list_call COMMA type_call  */
#line 2372 "../src/parser.y"
              {
                (yyval.state_lst) = new state_list_attr();
                (yyval.state_lst)->lst = (yyvsp[-2].state_lst)->lst;
                (yyval.state_lst)->lst.push_back(std::string("temp"));
                (yyval.state_lst)->cc = (yyvsp[-2].state_lst)->cc + std::string(", ") + (yyvsp[0].c)->cc;
              }
#line 4051 "parser.cc"
    break;

  case 98: /* type_call: dtype  */
#line 2381 "../src/parser.y"
         {
            (yyval.c) = new cc_code();
            (yyval.c)->cc = (yyvsp[0].type)->cc;
         }
#line 4060 "parser.cc"
    break;

  case 99: /* type_call: ID  */
#line 2386 "../src/parser.y"
         {
            //check if struct exists
            if(!sst->lookup(std::string((yyvsp[0].identifier))))
            {
                std::string error = "Struct "+std::string((yyvsp[0].identifier))+std::string(" not defined");
                yyerror(error.c_str());
            }
            (yyval.c) = new cc_code();
            (yyval.c)->cc = std::string((yyvsp[0].identifier));
         }
#line 4075 "parser.cc"
    break;

  case 100: /* argument_list: %empty  */
#line 2399 "../src/parser.y"
             {
                //argument list is empty
                (yyval.arg) = new arg_list_attr();
                (yyval.arg)->cc = std::string("");
             }
#line 4085 "parser.cc"
    break;

  case 101: /* argument_list: expression arg_list_next  */
#line 2405 "../src/parser.y"
             {
                (yyval.arg) = new arg_list_attr();
                (yyval.arg)->lst = (yyvsp[0].arg)->lst;
                std::string type;
                if((yyvsp[-1].expr)->indicator==1)
                    type = getVTP((yyvsp[-1].expr)->vtp);
                else if((yyvsp[-1].expr)->indicator==2)
                {
                    type = getVTS((yyvsp[-1].expr)->vts);
                    type= type+std::string(" ")+(yyvsp[-1].expr)->inner->print();
                }
                else if((yyvsp[-1].expr)->indicator==3)
                    type = getVTA((yyvsp[-1].expr)->vta);
                else if((yyvsp[-1].expr)->indicator==4)
                    type=std::string("string");
                else if((yyvsp[-1].expr)->indicator==5)
                    type=std::string("regex");
                else if((yyvsp[-1].expr)->indicator ==7)
                    type=std::string((yyvsp[-1].expr)->ifStruct);
                (yyval.arg)->lst.push_back(type);
                (yyval.arg)->cc = (yyvsp[-1].expr)->cc + (yyvsp[0].arg)->cc;
             }
#line 4112 "parser.cc"
    break;

  case 102: /* argument_list: STRING_CONST arg_list_next  */
#line 2428 "../src/parser.y"
             {
                (yyval.arg) = new arg_list_attr();
                (yyval.arg)->lst = (yyvsp[0].arg)->lst;
                (yyval.arg)->lst.push_back(std::string("string"));
                (yyval.arg)->cc = std::string((yyvsp[-1].cstring)) + (yyvsp[0].arg)->cc;
             }
#line 4123 "parser.cc"
    break;

  case 103: /* arg_list_next: %empty  */
#line 2437 "../src/parser.y"
             {
                (yyval.arg) = new arg_list_attr();
                (yyval.arg)->cc = std::string("");
             }
#line 4132 "parser.cc"
    break;

  case 104: /* arg_list_next: COMMA expression arg_list_next  */
#line 2442 "../src/parser.y"
             {
                (yyval.arg) = new arg_list_attr();
                (yyval.arg)->lst = (yyvsp[0].arg)->lst;
                std::string type;
                if((yyvsp[-1].expr)->indicator==1)
                    type = getVTP((yyvsp[-1].expr)->vtp);
                else if((yyvsp[-1].expr)->indicator==2)
                {
                    type = getVTS((yyvsp[-1].expr)->vts);
                    type= type+std::string(" ")+(yyvsp[-1].expr)->inner->print();
                }
                else if((yyvsp[-1].expr)->indicator==3)
                    type = getVTA((yyvsp[-1].expr)->vta);
                else if((yyvsp[-1].expr)->indicator==4)
                    type=std::string("string");
                else if((yyvsp[-1].expr)->indicator==5)
                    type=std::string("regex");
                else if((yyvsp[-1].expr)->indicator ==7)
                    type=std::string((yyvsp[-1].expr)->ifStruct);
                (yyval.arg)->lst.push_back(type);
                (yyval.arg)->cc = std::string(", ")+(yyvsp[-1].expr)->cc + (yyvsp[0].arg)->cc;
             }
#line 4159 "parser.cc"
    break;

  case 105: /* arg_list_next: COMMA STRING_CONST arg_list_next  */
#line 2465 "../src/parser.y"
             {
                (yyval.arg) = new arg_list_attr();
                (yyval.arg)->lst = (yyvsp[0].arg)->lst;
                (yyval.arg)->lst.push_back(std::string("string"));
                (yyval.arg)->cc = std::string(", ")+std::string((yyvsp[-1].cstring)) + (yyvsp[0].arg)->cc;
             }
#line 4170 "parser.cc"
    break;

  case 106: /* rhs_automata: LBRACE alphabet_list RBRACE  */
#line 2474 "../src/parser.y"
            {
                (yyval.rhs_automata) = new rhs_automata_attr();
                (yyval.rhs_automata)->type=std::string("alphabets");
                (yyval.rhs_automata)->automata_type = std::string("");
            }
#line 4180 "parser.cc"
    break;

  case 107: /* rhs_automata: LBRACE rules_list RBRACE  */
#line 2480 "../src/parser.y"
            {
                (yyval.rhs_automata) = new rhs_automata_attr();
                (yyval.rhs_automata)->type=std::string("transitions");
                (yyval.rhs_automata)->automata_type = (yyvsp[-1].rules)->type;
            }
#line 4190 "parser.cc"
    break;

  case 110: /* alphabet: ID COLON STRING_CONST  */
#line 2492 "../src/parser.y"
         {
            if(current_alphabets==NULL)
                current_alphabets = new std::vector<std::pair<std::string,std::string>>();
            current_alphabets->push_back(std::make_pair(std::string("\"")+std::string((yyvsp[-2].identifier))+std::string("\""),std::string((yyvsp[0].cstring))));
         }
#line 4200 "parser.cc"
    break;

  case 111: /* rules_list: rule  */
#line 2500 "../src/parser.y"
           {
                (yyval.rules) = new rules_attr();
                (yyval.rules)->type = (yyvsp[0].rules)->type;
           }
#line 4209 "parser.cc"
    break;

  case 112: /* rules_list: rules_list COMMA rule  */
#line 2505 "../src/parser.y"
           {
                (yyval.rules) = new rules_attr();
                if((yyvsp[-2].rules)->type==(yyvsp[0].rules)->type)
                    (yyval.rules)->type = (yyvsp[-2].rules)->type;
                else if(((yyvsp[-2].rules)->type=="nfa" && (yyvsp[0].rules)->type=="dfa") || ((yyvsp[-2].rules)->type=="dfa" && (yyvsp[0].rules)->type=="nfa"))
                    (yyval.rules)->type = std::string("nfa");
                else
                    yyerror("Invalid rule: All rules must be of same type");
           }
#line 4223 "parser.cc"
    break;

  case 113: /* rule: LPAREN ID lhs_arrow ARROW rhs_arrow RPAREN  */
#line 2517 "../src/parser.y"
     {
        (yyval.rules) = new rules_attr();
        if((yyvsp[-3].lhs_arrow)->type==(yyvsp[-1].lhs_arrow)->type)
            (yyval.rules)->type = (yyvsp[-3].lhs_arrow)->type;
        else if(((yyvsp[-3].lhs_arrow)->type=="nfa" && (yyvsp[-1].lhs_arrow)->type=="dfa") || ((yyvsp[-3].lhs_arrow)->type=="dfa" && (yyvsp[-1].lhs_arrow)->type=="nfa"))
            (yyval.rules)->type = std::string("nfa");
        else
            yyerror("Invalid rule: All rules must be of same type");
        if((yyvsp[-3].lhs_arrow)->type=="dfa" && ((yyvsp[-1].lhs_arrow)->type!="nfa" && (yyvsp[-1].lhs_arrow)->type!="dfa"))
            yyerror("Invalid rule");
        if((yyvsp[-3].lhs_arrow)->type=="nfa" && ((yyvsp[-1].lhs_arrow)->type!="nfa" && (yyvsp[-1].lhs_arrow)->type!="dfa"))
            yyerror("Invalid rule");
        if((yyvsp[-3].lhs_arrow)->type=="pda" && ((yyvsp[-1].lhs_arrow)->type!="pda"))
            yyerror("Invalid rule");
        if(current_automata==0)
        {
            if((yyvsp[-3].lhs_arrow)->type=="dfa" && (yyvsp[-1].lhs_arrow)->type=="dfa")
                current_automata = 1;
            else if((yyvsp[-3].lhs_arrow)->type=="nfa" || (yyvsp[-1].lhs_arrow)->type=="nfa" )
                current_automata = 2;
            else if((yyvsp[-3].lhs_arrow)->type=="pda" && (yyvsp[-1].lhs_arrow)->type=="pda")
                current_automata = 3;
            // now insert the rules
            if(current_automata==1 || current_automata==2)
            {
                transition = new std::vector<std::vector<std::string>>();
                for(auto &it: *nfa_dfa_lhs)
                {
                    for(auto &it2: *nfa_dfa_rhs)
                    {
                        std::string alphabet = it;
                        std::string fin = it2;
                        std::string init = std::string((yyvsp[-4].identifier));
                        std::vector<std::string> *temp;
                        temp = new std::vector<std::string>();
                        temp->push_back(init);
                        temp->push_back(alphabet);
                        temp->push_back(fin);
                        transition->push_back(*temp);
                    }
                }
                nfa_dfa_lhs = NULL;
                nfa_dfa_rhs = NULL;
            }
            if(current_automata==3)
            {
                transition = new std::vector<std::vector<std::string>>();
                for(auto &it: *pda_lhs)
                {
                    for(auto &it2: *pda_rhs)
                    {
                        std::string state_alpha = it.first;
                        std::string stack = it.second;
                        std::string state_alpha2 = it2.first;
                        std::string stack2 = it2.second;
                        std::string init = std::string((yyvsp[-4].identifier));
                        std::vector<std::string> *temp;
                        temp = new std::vector<std::string>();
                        temp->push_back(init);
                        temp->push_back(state_alpha);
                        temp->push_back(stack);
                        temp->push_back(state_alpha2);
                        temp->push_back(stack2);
                        transition->push_back(*temp);
                    }
                }
                pda_lhs = NULL;
                pda_rhs = NULL;
            }
        }
        else 
        {
            if((current_automata==1 || current_automata==2) && (((yyvsp[-3].lhs_arrow)->type=="dfa" || (yyvsp[-3].lhs_arrow)->type=="nfa") && ((yyvsp[-1].lhs_arrow)->type=="dfa" || (yyvsp[-1].lhs_arrow)->type=="nfa")))
            {
                if((yyvsp[-3].lhs_arrow)->type=="nfa" || (yyvsp[-1].lhs_arrow)->type=="nfa")
                    current_automata = 2;
                for(auto &it: *nfa_dfa_lhs)
                {
                    for(auto &it2: *nfa_dfa_rhs)
                    {
                        std::string alphabet = it;
                        std::string fin = it2;
                        std::string init = std::string((yyvsp[-4].identifier));
                        std::vector<std::string> *temp;
                        temp = new std::vector<std::string>();
                        temp->push_back(init);
                        temp->push_back(alphabet);
                        temp->push_back(fin);
                        transition->push_back(*temp);
                    }
                }
                nfa_dfa_lhs = NULL;
                nfa_dfa_rhs = NULL;
            }
            else if(current_automata==3 && (yyvsp[-3].lhs_arrow)->type=="pda" && (yyvsp[-1].lhs_arrow)->type=="pda")
            {
                for(auto &it: *pda_lhs)
                {
                    for(auto &it2: *pda_rhs)
                    {
                        std::string state_alpha = it.first;
                        std::string stack = it.second;
                        std::string state_alpha2 = it2.first;
                        std::string stack2 = it2.second;
                        std::string init = std::string((yyvsp[-4].identifier));
                        std::vector<std::string> *temp;
                        temp = new std::vector<std::string>();
                        temp->push_back(init);
                        temp->push_back(state_alpha);
                        temp->push_back(stack);
                        temp->push_back(state_alpha2);
                        temp->push_back(stack2);
                        transition->push_back(*temp);
                    }
                }
                pda_lhs = NULL;
                pda_rhs = NULL;
            }
            else
                yyerror("Invalid set of rules");
        }
     }
#line 4350 "parser.cc"
    break;

  case 114: /* lhs_arrow: COMMA ID  */
#line 2642 "../src/parser.y"
          {
            (yyval.lhs_arrow) = new lhs_arrow_attr();
            (yyval.lhs_arrow)->type = std::string("dfa");
            nfa_dfa_lhs = new std::vector<std::string>();
            nfa_dfa_lhs->push_back(std::string((yyvsp[0].identifier)));
          }
#line 4361 "parser.cc"
    break;

  case 115: /* lhs_arrow: COMMA element_PDA  */
#line 2649 "../src/parser.y"
          {
            (yyval.lhs_arrow) = new lhs_arrow_attr();
            (yyval.lhs_arrow)->type = std::string("pda");
            pda_lhs = new std::vector<std::pair<std::string,std::string>>();
            std::pair<std::string,std::string> str;
            str = std::make_pair((yyvsp[0].ele_pda)->state_alpha,(yyvsp[0].ele_pda)->stack);
            pda_lhs->push_back(str);
          }
#line 4374 "parser.cc"
    break;

  case 116: /* lhs_arrow: COMMA EPSILON  */
#line 2658 "../src/parser.y"
          {
            (yyval.lhs_arrow) = new lhs_arrow_attr();
            (yyval.lhs_arrow)->type = std::string("nfa");
            nfa_dfa_lhs = new std::vector<std::string>();
            nfa_dfa_lhs->push_back("\\\\e");
          }
#line 4385 "parser.cc"
    break;

  case 117: /* lhs_arrow: COMMA LBRACE elements_PDA RBRACE  */
#line 2665 "../src/parser.y"
          {
            (yyval.lhs_arrow) = new lhs_arrow_attr();
            (yyval.lhs_arrow)->type = std::string("pda");
            pda_lhs = new std::vector<std::pair<std::string,std::string>>();
            for(auto &it: *((yyvsp[-1].eles_pda)->lst))
            {
                std::pair<std::string,std::string> str;
                str = std::make_pair(it->state_alpha,it->stack);
                pda_lhs->push_back(str);
            }
          }
#line 4401 "parser.cc"
    break;

  case 118: /* lhs_arrow: COMMA LBRACE elements_others RBRACE  */
#line 2677 "../src/parser.y"
          {
            (yyval.lhs_arrow) = new lhs_arrow_attr();
            (yyval.lhs_arrow)->type = (yyvsp[-1].lhs_arrow)->type;
            nfa_dfa_lhs = new std::vector<std::string>();
            for(auto &it: (yyvsp[-1].lhs_arrow)->lst)
            {
                nfa_dfa_lhs->push_back(it);
            }
          }
#line 4415 "parser.cc"
    break;

  case 119: /* elements_PDA: element_PDA  */
#line 2689 "../src/parser.y"
             {
                (yyval.eles_pda) = new elements_PDA_attr();
                (yyval.eles_pda)->lst = new std::vector<element_PDA_attr*>();
                (yyval.eles_pda)->lst->push_back((yyvsp[0].ele_pda));
             }
#line 4425 "parser.cc"
    break;

  case 120: /* elements_PDA: elements_PDA COMMA element_PDA  */
#line 2695 "../src/parser.y"
             {
                (yyval.eles_pda) = (yyvsp[-2].eles_pda);
                (yyval.eles_pda)->lst->push_back((yyvsp[0].ele_pda));
             }
#line 4434 "parser.cc"
    break;

  case 121: /* element_PDA: LPAREN ID COMMA ID RPAREN  */
#line 2702 "../src/parser.y"
            {
                (yyval.ele_pda) = new element_PDA_attr();
                (yyval.ele_pda)->state_alpha = std::string((yyvsp[-3].identifier));
                (yyval.ele_pda)->stack = std::string((yyvsp[-1].identifier));
            }
#line 4444 "parser.cc"
    break;

  case 122: /* element_PDA: LPAREN ID COMMA EPSILON RPAREN  */
#line 2708 "../src/parser.y"
            {
                (yyval.ele_pda) = new element_PDA_attr();
                (yyval.ele_pda)->state_alpha = std::string((yyvsp[-3].identifier));
                (yyval.ele_pda)->stack = std::string("\\\\e");
            }
#line 4454 "parser.cc"
    break;

  case 123: /* elements_others: ID  */
#line 2716 "../src/parser.y"
                {
                    (yyval.lhs_arrow) = new lhs_arrow_attr();
                    (yyval.lhs_arrow)->type = std::string("dfa");
                    (yyval.lhs_arrow)->lst = *(new std::vector<std::string>());
                    (yyval.lhs_arrow)->lst.push_back(std::string((yyvsp[0].identifier)));
                }
#line 4465 "parser.cc"
    break;

  case 124: /* elements_others: EPSILON  */
#line 2723 "../src/parser.y"
                {
                    (yyval.lhs_arrow) = new lhs_arrow_attr();
                    (yyval.lhs_arrow)->type = std::string("nfa");
                    (yyval.lhs_arrow)->lst = *(new std::vector<std::string>());
                    (yyval.lhs_arrow)->lst.push_back(std::string("\\\\e"));
                }
#line 4476 "parser.cc"
    break;

  case 125: /* elements_others: elements_others COMMA ID  */
#line 2730 "../src/parser.y"
                {
                    (yyval.lhs_arrow) = new lhs_arrow_attr();
                    if((yyvsp[-2].lhs_arrow)->type=="dfa")
                        (yyval.lhs_arrow)->type = std::string("dfa");
                    else
                        (yyval.lhs_arrow)->type = std::string("nfa");
                    (yyval.lhs_arrow)->lst = (yyvsp[-2].lhs_arrow)->lst;
                    (yyval.lhs_arrow)->lst.push_back(std::string((yyvsp[0].identifier)));

                }
#line 4491 "parser.cc"
    break;

  case 126: /* elements_others: elements_others COMMA EPSILON  */
#line 2741 "../src/parser.y"
                {
                    (yyval.lhs_arrow) = new lhs_arrow_attr();
                    (yyval.lhs_arrow)->type = std::string("nfa");
                    (yyval.lhs_arrow)->lst = (yyvsp[-2].lhs_arrow)->lst;
                    (yyval.lhs_arrow)->lst.push_back(std::string("\\\\e"));
                }
#line 4502 "parser.cc"
    break;

  case 127: /* rhs_arrow: ID  */
#line 2750 "../src/parser.y"
          {
            (yyval.lhs_arrow) = new lhs_arrow_attr();
            (yyval.lhs_arrow)->type = std::string("dfa");
            nfa_dfa_rhs = new std::vector<std::string>();
            nfa_dfa_rhs->push_back(std::string((yyvsp[0].identifier)));
          }
#line 4513 "parser.cc"
    break;

  case 128: /* rhs_arrow: LBRACE elements_others RBRACE  */
#line 2757 "../src/parser.y"
          {
            (yyval.lhs_arrow) = new lhs_arrow_attr();
            (yyval.lhs_arrow)->type = std::string("nfa");
            nfa_dfa_rhs = new std::vector<std::string>();
            for(auto &it: (yyvsp[-1].lhs_arrow)->lst)
            {
                nfa_dfa_rhs->push_back(it);
            }
          }
#line 4527 "parser.cc"
    break;

  case 129: /* rhs_arrow: element_PDA  */
#line 2767 "../src/parser.y"
          {
            (yyval.lhs_arrow) = new lhs_arrow_attr();
            (yyval.lhs_arrow)->type = std::string("pda");
            pda_rhs = new std::vector<std::pair<std::string,std::string>>();
            std::pair<std::string,std::string> str;
            str=std::make_pair((yyvsp[0].ele_pda)->state_alpha,(yyvsp[0].ele_pda)->stack);
            pda_rhs->push_back(str);
          }
#line 4540 "parser.cc"
    break;

  case 130: /* rhs_arrow: LBRACE elements_PDA RBRACE  */
#line 2776 "../src/parser.y"
          {
            (yyval.lhs_arrow) = new lhs_arrow_attr();
            (yyval.lhs_arrow)->type = std::string("pda");
            pda_rhs = new std::vector<std::pair<std::string,std::string>>();
            for(auto &it: *((yyvsp[-1].eles_pda)->lst))
            {
                std::pair<std::string,std::string> str;
                str = std::make_pair(it->state_alpha,it->stack);
                pda_rhs->push_back(str);
            }
          }
#line 4556 "parser.cc"
    break;

  case 131: /* cfg_rhs: cfg_rhs_ele  */
#line 2790 "../src/parser.y"
        {
            cfg_rhs_current = new std::vector<std::string>();
            cfg_rhs_current->push_back((yyvsp[0].c)->cc);
        }
#line 4565 "parser.cc"
    break;

  case 133: /* cfg_rhs_ele: cfg_rhs_ele OPER_MOD LBRACE ID RBRACE  */
#line 2798 "../src/parser.y"
            {
                (yyval.c) = new cc_code();
                (yyval.c)->cc = (yyvsp[-4].c)->cc + std::string("%{")+std::string((yyvsp[-1].identifier))+"}";
            }
#line 4574 "parser.cc"
    break;

  case 134: /* cfg_rhs_ele: cfg_rhs_ele DOLLAR LBRACE ID RBRACE  */
#line 2803 "../src/parser.y"
            {
                (yyval.c) = new cc_code();
                (yyval.c)->cc = (yyvsp[-4].c)->cc + std::string("${")+std::string((yyvsp[-1].identifier)) +"}";
            }
#line 4583 "parser.cc"
    break;

  case 135: /* cfg_rhs_ele: cfg_rhs_ele EPSILON  */
#line 2808 "../src/parser.y"
            {
                (yyval.c) = new cc_code();
                (yyval.c)->cc = (yyvsp[-1].c)->cc + std::string("");
            }
#line 4592 "parser.cc"
    break;

  case 136: /* cfg_rhs_ele: OPER_MOD LBRACE ID RBRACE  */
#line 2813 "../src/parser.y"
            {
                (yyval.c) = new cc_code();
                (yyval.c)->cc = std::string("%{")+std::string((yyvsp[-1].identifier))+"}";
            }
#line 4601 "parser.cc"
    break;

  case 137: /* cfg_rhs_ele: EPSILON  */
#line 2818 "../src/parser.y"
            {
                (yyval.c) = new cc_code();
                (yyval.c)->cc = std::string("");
            }
#line 4610 "parser.cc"
    break;

  case 138: /* cfg_rhs_ele: DOLLAR LBRACE ID RBRACE  */
#line 2823 "../src/parser.y"
            {
                (yyval.c) = new cc_code();
                (yyval.c)->cc = std::string("${")+std::string((yyvsp[-1].identifier)) +"}";
            }
#line 4619 "parser.cc"
    break;

  case 140: /* cfg_rhs_ele_list: cfg_rhs_ele  */
#line 2832 "../src/parser.y"
                 {
                    if(cfg_rhs_current==NULL)
                        cfg_rhs_current = new std::vector<std::string>();
                    if((yyvsp[0].c)->cc!="")
                        cfg_rhs_current->push_back((yyvsp[0].c)->cc);
                    else
                        cfg_rhs_current->push_back(std::string("\\\\e"));
                 }
#line 4632 "parser.cc"
    break;

  case 141: /* cfg_rhs_ele_list: cfg_rhs_ele_list COMMA cfg_rhs_ele  */
#line 2841 "../src/parser.y"
                 {
                    if(cfg_rhs_current==NULL)
                        cfg_rhs_current = new std::vector<std::string>();
                    if((yyvsp[0].c)->cc!="")
                        cfg_rhs_current->push_back((yyvsp[0].c)->cc);
                    else
                        cfg_rhs_current->push_back(std::string("\\\\e"));
                 }
#line 4645 "parser.cc"
    break;

  case 145: /* $@5: %empty  */
#line 2857 "../src/parser.y"
               {
                 //create a new symbol table
                 VarSymbolTable *table = new VarSymbolTable();
                 vstl->insert(table);
                 current_vst = table;
                 cc_file<<"\t{"<<std::endl;
               }
#line 4657 "parser.cc"
    break;

  case 146: /* $@6: %empty  */
#line 2865 "../src/parser.y"
               {
                    //delete the symbol table
                    vstl->remove();
                    current_vst = vstl->getTop();
                    cc_file<<"}"<<std::endl;
               }
#line 4668 "parser.cc"
    break;

  case 148: /* ifexp: IF_KW LPAREN expression RPAREN  */
#line 2874 "../src/parser.y"
                                       {
        if((yyvsp[-1].expr)->indicator!=1)
            yyerror("Invalid expression in if statement");
        printlog("If");
        cc_file<<"if("<<(yyvsp[-1].expr)->cc<<")"<<std::endl;
        }
#line 4679 "parser.cc"
    break;

  case 149: /* $@7: %empty  */
#line 2883 "../src/parser.y"
                {
                    //create a new symbol table
                    VarSymbolTable *table = new VarSymbolTable();
                    vstl->insert(table);
                    current_vst = table;
                    cc_file<<"\t{"<<std::endl;
                }
#line 4691 "parser.cc"
    break;

  case 150: /* elif_statement: elif LBRACE $@7 control_body RBRACE  */
#line 2891 "../src/parser.y"
                {
                    //delete the symbol table
                    vstl->remove();
                    current_vst = vstl->getTop();
                    cc_file<<"}"<<std::endl;
                }
#line 4702 "parser.cc"
    break;

  case 152: /* elif: ELIF_KW LPAREN expression RPAREN  */
#line 2901 "../src/parser.y"
       {
        if((yyvsp[-1].expr)->indicator!=1)
            yyerror("Invalid expression in elif statement");
        printlog("Elif");
        cc_file<<"else if("<<(yyvsp[-1].expr)->cc<<")"<<std::endl;
       }
#line 4713 "parser.cc"
    break;

  case 153: /* $@8: %empty  */
#line 2910 "../src/parser.y"
                {
                    //create a new symbol table
                    VarSymbolTable *table = new VarSymbolTable();
                    vstl->insert(table);
                    current_vst = table;
                    printlog("Else");
                    cc_file<<"else \t{"<<std::endl;
                }
#line 4726 "parser.cc"
    break;

  case 154: /* else_statement: ELSE_KW LBRACE $@8 control_body RBRACE  */
#line 2918 "../src/parser.y"
                {
                    //delete the symbol table
                    vstl->remove();
                    current_vst = vstl->getTop();
                    cc_file<<"}"<<std::endl;
                }
#line 4737 "parser.cc"
    break;

  case 156: /* $@9: %empty  */
#line 2928 "../src/parser.y"
                {
                   //create a new symbol table
                   VarSymbolTable *table = new VarSymbolTable();
                   vstl->insert(table);
                   current_vst = table;
                   in_loop++;
                }
#line 4749 "parser.cc"
    break;

  case 157: /* while_statement: whileexp LBRACE $@9 control_body RBRACE  */
#line 2935 "../src/parser.y"
                {
                    //delete the symbol table
                    vstl->remove();
                    current_vst = vstl->getTop();
                    in_loop--;
                }
#line 4760 "parser.cc"
    break;

  case 158: /* whileexp: WHILE_KW LPAREN expression RPAREN  */
#line 2944 "../src/parser.y"
           {
                if((yyvsp[-1].expr)->indicator!=1)
                    yyerror("Invalid expression in while statement");
                printlog("While");
           }
#line 4770 "parser.cc"
    break;

  case 159: /* call_statement: call SEMICOLON  */
#line 2952 "../src/parser.y"
                {
                    cc_file<<(yyvsp[-1].type)->cc<<" ;"<<std::endl;
                }
#line 4778 "parser.cc"
    break;

  case 160: /* return_statement: RETURN_KW expression SEMICOLON  */
#line 2958 "../src/parser.y"
                 {
                    if(!current_function)
                        yyerror("Return statement outside function");
                    type_attr *type = new type_attr();
                    type->indicator = (yyvsp[-1].expr)->indicator;
                    type->vtp = (yyvsp[-1].expr)->vtp;
                    type->vta = (yyvsp[-1].expr)->vta;
                    type->vts = (yyvsp[-1].expr)->vts;
                    type->vtsr = (yyvsp[-1].expr)->vtsr;
                    type->ifStruct = (yyvsp[-1].expr)->ifStruct;
                    type->inner = (yyvsp[-1].expr)->inner;
                    if(current_function->return_type == std::string("void"))
                        yyerror("Return type mismatch/ function returns void");
                    std::string inner = type->inner->print();
                    if(inner[inner.length()-1]==' ')
                        inner = inner.substr(0,inner.length()-1);
                    
                    if(!isCoherent(current_function->return_type,(trim(getType(type) + std::string(" ")+inner))))
                    {
                        std::string str = std::string("Return type mismatch, expecting ")+current_function->return_type;
                        yyerror(str.c_str());
                    }
                    //struct handling (to be done)
                    (yyval.type) = new type_attr();
                    (yyval.type)->indicator = (yyvsp[-1].expr)->indicator;
                    (yyval.type)->vtp = (yyvsp[-1].expr)->vtp;
                    (yyval.type)->vta = (yyvsp[-1].expr)->vta;
                    (yyval.type)->vts = (yyvsp[-1].expr)->vts;
                   cc_file<<"return "<<(yyvsp[-1].expr)->cc<<" ;"<<std::endl;
                 }
#line 4813 "parser.cc"
    break;

  case 161: /* return_statement: RETURN_KW SEMICOLON  */
#line 2989 "../src/parser.y"
                 {
                    if(!current_function)
                        yyerror("Return statement outside function");
                    if(current_function->return_type != "void")
                    {
                        std::string error = "Return type mismatch/ function returns "+current_function->return_type;
                        yyerror(error.c_str());
                    }
                    (yyval.type) = new type_attr();
                    (yyval.type)->indicator = 0;
                    cc_file<<"return ;"<<std::endl;

                 }
#line 4831 "parser.cc"
    break;

  case 162: /* break_statement: BREAK_KW SEMICOLON  */
#line 3004 "../src/parser.y"
                                     {
                                    if(!in_loop) 
                                        yyerror("Break statement outside loop");
                                    cc_file<<"break ;"<<std::endl;
                                    }
#line 4841 "parser.cc"
    break;

  case 163: /* continue_statement: CONTINUE_KW SEMICOLON  */
#line 3011 "../src/parser.y"
                                           {
                                            if(!in_loop) 
                                                yyerror("Continue statement outside loop");
                                            cc_file<<"continue ;"<<std::endl;
                                            }
#line 4851 "parser.cc"
    break;

  case 164: /* dtype: TYPE_PRIMITIVE  */
#line 3018 "../src/parser.y"
                       { 
                        (yyval.type) = new type_attr();
                        (yyval.type)->indicator = 1;
                        (yyval.type)->vtp = (yyvsp[0].dtype_primitive);
                        (yyval.type)->cc = type_maps_prim[(yyval.type)->vtp];
                      }
#line 4862 "parser.cc"
    break;

  case 165: /* dtype: TYPE_SET COMP_LT set_type COMP_GT  */
#line 3024 "../src/parser.y"
                                          {
                                            (yyval.type) = new type_attr();
                                            (yyval.type)->indicator = 2;
                                            (yyval.type)->vts = (yyvsp[-3].dtype_set); 
                                            // start from here 
                                            (yyval.type)->inner = (yyvsp[-1].type)->inner;
                                            (yyval.type)->cc = type_maps_set[(yyval.type)->vts] +"<"+(yyvsp[-1].type)->cc+">";
                                          }
#line 4875 "parser.cc"
    break;

  case 166: /* dtype: TYPE_AUTOMATA  */
#line 3032 "../src/parser.y"
                      {
                        (yyval.type) = new type_attr();
                        (yyval.type)->indicator = 3;
                        (yyval.type)->vta = (yyvsp[0].dtype_automata);
                        (yyval.type)->cc = type_maps_auto[(yyval.type)->vta];
                      }
#line 4886 "parser.cc"
    break;

  case 167: /* dtype: TYPE_STRING  */
#line 3038 "../src/parser.y"
                    {
                        (yyval.type) = new type_attr();
                        (yyval.type)->indicator = 4;
                        (yyval.type)->vtsr = (yyvsp[0].dtype_SR);
                        (yyval.type)->cc = type_maps_sr[(yyval.type)->vtsr];
                    }
#line 4897 "parser.cc"
    break;

  case 168: /* dtype: TYPE_REG  */
#line 3044 "../src/parser.y"
                 {
                        (yyval.type) = new type_attr();
                        (yyval.type)->indicator = 5;
                        (yyval.type)->vtsr = (yyvsp[0].dtype_SR);
                        (yyval.type)->cc = type_maps_sr[(yyval.type)->vtsr];
                 }
#line 4908 "parser.cc"
    break;

  case 169: /* set_type: dtype  */
#line 3052 "../src/parser.y"
                 {
                    (yyval.type) = new type_attr();
                    (yyval.type)->inner = new inner_type((yyvsp[0].type)->inner,getType((yyvsp[0].type)));
                    (yyval.type)->cc = (yyvsp[0].type)->cc;

                 }
#line 4919 "parser.cc"
    break;

  case 170: /* set_type: ID  */
#line 3058 "../src/parser.y"
              {
                (yyval.type) = new type_attr();
                (yyval.type)->inner = new inner_type(NULL,std::string((yyvsp[0].identifier)));
                (yyval.type)->cc = std::string((yyvsp[0].identifier));
              }
#line 4929 "parser.cc"
    break;


#line 4933 "parser.cc"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 3065 "../src/parser.y"


void yyerror(const char *s) {

    fprintf(parse_log, "Parser error: %d\n", yylineno);
    std::cout<<RED<<"Parser error: "<<yylineno<<RESET;
    std::cout<<": "<<s<<std::endl;
    terminate();

}

int main(int argc, char **argv) {
    // #ifdef YYDEBUG
    //      yydebug = 1;
    // #endif
    initST();
    initData();
    yyin = fopen(argv[1],"r");
    std::string filename,path;
    std::string arg_1 = std::string(argv[1]);
    if(arg_1.find_last_of("/")!=std::string::npos)
    {
        filename = arg_1.substr(arg_1.find_last_of("/")+1);
        filename = filename.substr(0,filename.find_last_of("."));
        path = arg_1.substr(0,arg_1.find_last_of("/"));
        path = path.substr(0,path.find_last_of("/"));
    }
    else
    {
        path = std::string(".");
        filename = arg_1.substr(0,arg_1.find_last_of("."));
    }

    // path to the folder of test file
    std::string seq = std::string(path)+std::string("/logs/seq_tokens_")+std::string(filename)+std::string(".tok");
    std::string parser_log = std::string(path)+std::string("/logs/parser_log_")+std::string(filename)+std::string(".log");
    std::string cc_file_name = std::string(path)+std::string("/cc_files/cc_file_")+std::string(filename)+std::string(".cc");
    // tokens file path
    if(argc==3)
    {
        seq = std::string(argv[2]) + std::string("/seq_tokens_")+std::string(filename)+std::string(".tok");
        parser_log = std::string(argv[2]) + std::string("/parser_log_")+std::string(filename)+std::string(".log");
    }
    cc_file.open(cc_file_name,std::ios::out);
    cc_file<<"#include \"../../../code/includes/fsm.hh\"\n";
    cc_file<<"#include \"../../../code/includes/macros.hh\"\n";
    seq_token.open(seq,std::ios::out);
    parse_log = fopen(parser_log.c_str(),"w");
    yyparse();
    fclose(yyin);
    seq_token.close();
    fclose(parse_log);
    cc_file.close();
    return 0;
}
