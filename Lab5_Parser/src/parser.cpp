/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 1 "src/parser.y"

    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    Type *declType; // The Type in DeclStmt 

#line 78 "src/parser.cpp"




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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_INCLUDE_PARSER_H_INCLUDED
# define YY_YY_INCLUDE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 12 "src/parser.y"

    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"

#line 130 "src/parser.cpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTEGER = 259,
    FLOATNUM = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    BREAK = 264,
    CONTINUE = 265,
    INT = 266,
    VOID = 267,
    CONST = 268,
    FLOAT = 269,
    LPAREN = 270,
    RPAREN = 271,
    LBRACE = 272,
    RBRACE = 273,
    SEMICOLON = 274,
    COMMA = 275,
    LBRACKET = 276,
    RBRACKET = 277,
    ADD = 278,
    SUB = 279,
    MINUS = 280,
    STAR = 281,
    SLASH = 282,
    PERCENT = 283,
    AND = 284,
    OR = 285,
    NOT = 286,
    LESS = 287,
    LESSEQ = 288,
    GREAT = 289,
    GREATEQ = 290,
    EQ = 291,
    NEQ = 292,
    ASSIGN = 293,
    RETURN = 294,
    THEN = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "src/parser.y"

    int itype;
    float ftype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;

#line 191 "src/parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INCLUDE_PARSER_H_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  52
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   184

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

#define YYUNDEFTOK  2
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    49,    49,    54,    55,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    71,    83,    98,   104,   103,   112,
     115,   118,   124,   129,   133,   138,   144,   148,   152,   156,
     161,   166,   172,   176,   180,   186,   194,   196,   203,   210,
     219,   221,   228,   237,   239,   246,   253,   260,   267,   274,
     283,   285,   294,   296,   304,   310,   315,   320,   326,   330,
     336,   336,   358,   364,   371,   376,   384,   389,   393,   400,
     406,   414,   422,   430,   451,   473,   479,   486,   491,   495,
     501,   507,   514,   522,   544,   550
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTEGER", "FLOATNUM", "IF",
  "ELSE", "WHILE", "BREAK", "CONTINUE", "INT", "VOID", "CONST", "FLOAT",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON", "COMMA", "LBRACKET",
  "RBRACKET", "ADD", "SUB", "MINUS", "STAR", "SLASH", "PERCENT", "AND",
  "OR", "NOT", "LESS", "LESSEQ", "GREAT", "GREATEQ", "EQ", "NEQ", "ASSIGN",
  "RETURN", "THEN", "$accept", "Stmts", "Stmt", "AssignStmt", "BlockStmt",
  "IfStmt", "ReturnStmt", "DeclStmt", "FuncDef", "Exp", "AddExp", "Cond",
  "LOrExp", "PrimaryExp", "LVal", "RelExp", "LAndExp", "StarExp",
  "UnaryExp", "ConstExp", "Type", "VarDefList", "VarDef",
  "ConstArrayIndex", "InitVal", "InitValList", "ArrayIndex",
  "ConstDefList", "ConstDef", "ConstInitVal", "ConstInitValList",
  "WhileStmt", "BreakStmt", "ContinueStmt", "Program", "$@1", "$@2", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-61)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      86,    -8,    23,    37,    30,    44,  -106,  -106,    36,  -106,
      65,   153,    86,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
      52,   103,  -106,  -106,  -106,   108,   153,    88,   153,   153,
    -106,  -106,   112,  -106,    86,  -106,  -106,   153,   153,   153,
     153,    92,    62,  -106,  -106,   -22,  -106,  -106,   153,    -5,
      68,  -106,  -106,    94,   153,    62,   104,    91,    25,    93,
     107,    -7,    82,  -106,    12,   125,  -106,  -106,  -106,  -106,
     153,   153,   153,   153,   153,   123,   153,   114,    -2,   128,
    -106,   141,  -106,   137,    86,   153,   153,   153,   153,   153,
     153,   153,   153,    86,   148,     6,  -106,   112,  -106,  -106,
     -22,   -22,  -106,  -106,  -106,  -106,    62,   138,   109,  -106,
    -106,   153,   114,   134,    16,  -106,  -106,   140,    93,    62,
      62,    62,    62,    62,    62,    25,  -106,   131,  -106,  -106,
     148,  -106,  -106,  -106,  -106,    60,   139,  -106,   147,    86,
    -106,  -106,    61,  -106,  -106,   114,  -106,  -106,  -106,  -106,
     148,  -106,  -106
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    14,     0,     0,     0,     0,    55,    57,     0,    56,
      17,     0,     2,     3,     5,     6,     7,    11,    12,    13,
       0,     0,     8,     9,    10,     0,     0,    15,     0,     0,
      24,    25,     0,    19,     0,    29,    30,     0,     0,     0,
       0,     0,    26,    32,    28,    40,    36,     4,     0,    71,
       0,    76,     1,     0,     0,    43,     0,    27,    50,    52,
       0,     0,     0,    85,     0,     0,    33,    34,    35,    22,
       0,     0,     0,     0,     0,     0,     0,     0,    73,     0,
      58,     0,    65,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,     0,    18,    31,
      41,    42,    37,    38,    39,    16,    54,     0,     0,    66,
      72,     0,     0,     0,    71,    75,    64,    20,    53,    44,
      45,    46,    47,    48,    49,    51,    23,     0,    77,    82,
       0,    84,    63,    68,    70,     0,     0,    74,     0,     0,
      79,    81,     0,    83,    67,     0,    62,    61,    21,    78,
       0,    69,    80
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -106,   132,   -11,  -106,    29,  -106,  -106,  -106,  -106,    -9,
     -20,   144,  -106,  -106,     0,    77,    85,    34,     3,   -65,
     166,  -106,    97,   119,  -105,  -106,  -106,  -106,    78,   -95,
    -106,  -106,  -106,  -106,  -106,  -106,  -106
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,    17,    18,    19,   109,
      42,    56,    57,    43,    44,    58,    59,    45,    46,   128,
      21,    50,    51,    78,   110,   135,    27,    62,    63,   129,
     142,    22,    23,    24,    25,    34,    79
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      20,    47,    41,   134,    72,    73,    74,   137,    55,    55,
     -60,   107,    20,    26,    76,     1,    76,    53,     2,   111,
       3,     4,     5,     6,     7,     8,     9,   111,    65,    10,
      98,    94,   141,    77,    20,   143,   112,    76,    28,    75,
     151,    66,    67,    68,   130,    83,   136,     6,     7,    30,
       9,    11,    29,    47,    77,   152,   106,    86,    87,    88,
      89,    90,    91,    31,    20,    55,   119,   120,   121,   122,
     123,   124,    55,   117,   106,   102,   103,   104,   144,   149,
     145,   150,   126,    33,    20,    70,    71,    80,    81,     1,
      48,   106,     2,    20,     3,     4,     5,     6,     7,     8,
       9,    96,    97,    10,   100,   101,    49,   106,    52,    54,
     106,    69,     1,    35,    36,    61,    82,     1,    35,    36,
      84,    85,    92,    93,    37,    11,   108,   133,   148,    37,
     106,   108,    38,    39,     1,    35,    36,    38,    39,    20,
      40,    99,   105,   113,   114,    40,    37,   139,   127,   140,
     138,     1,    35,    36,    38,    39,     1,    35,    36,   116,
     132,   146,    40,    37,    10,   127,    64,   147,    37,   125,
     118,    38,    39,    60,    32,   131,    38,    39,   115,    40,
      95,     0,     0,     0,    40
};

static const yytype_int16 yycheck[] =
{
       0,    12,    11,   108,    26,    27,    28,   112,    28,    29,
      15,    76,    12,    21,    21,     3,    21,    26,     6,    21,
       8,     9,    10,    11,    12,    13,    14,    21,    37,    17,
      18,    38,   127,    38,    34,   130,    38,    21,    15,    48,
     145,    38,    39,    40,    38,    54,   111,    11,    12,    19,
      14,    39,    15,    64,    38,   150,    76,    32,    33,    34,
      35,    36,    37,    19,    64,    85,    86,    87,    88,    89,
      90,    91,    92,    84,    94,    72,    73,    74,    18,    18,
      20,    20,    93,    18,    84,    23,    24,    19,    20,     3,
      38,   111,     6,    93,     8,     9,    10,    11,    12,    13,
      14,    19,    20,    17,    70,    71,     3,   127,     0,    21,
     130,    19,     3,     4,     5,     3,    22,     3,     4,     5,
      16,    30,    29,    16,    15,    39,    17,    18,   139,    15,
     150,    17,    23,    24,     3,     4,     5,    23,    24,   139,
      31,    16,    19,    15,     3,    31,    15,     7,    17,    18,
      16,     3,     4,     5,    23,    24,     3,     4,     5,    22,
      22,    22,    31,    15,    17,    17,    34,   138,    15,    92,
      85,    23,    24,    29,     8,    97,    23,    24,    81,    31,
      61,    -1,    -1,    -1,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     6,     8,     9,    10,    11,    12,    13,    14,
      17,    39,    42,    43,    44,    45,    46,    47,    48,    49,
      55,    61,    72,    73,    74,    75,    21,    67,    15,    15,
      19,    19,    61,    18,    76,     4,     5,    15,    23,    24,
      31,    50,    51,    54,    55,    58,    59,    43,    38,     3,
      62,    63,     0,    50,    21,    51,    52,    53,    56,    57,
      52,     3,    68,    69,    42,    50,    59,    59,    59,    19,
      23,    24,    26,    27,    28,    50,    21,    38,    64,    77,
      19,    20,    22,    50,    16,    30,    32,    33,    34,    35,
      36,    37,    29,    16,    38,    64,    19,    20,    18,    16,
      58,    58,    59,    59,    59,    19,    51,    60,    17,    50,
      65,    21,    38,    15,     3,    63,    22,    43,    57,    51,
      51,    51,    51,    51,    51,    56,    43,    17,    60,    70,
      38,    69,    22,    18,    65,    66,    60,    65,    16,     7,
      18,    70,    71,    70,    18,    20,    22,    45,    43,    18,
      20,    65,    70
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    75,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    55,    55,    44,    76,    45,    45,
      46,    46,    47,    72,    73,    74,    50,    52,    54,    54,
      54,    54,    59,    59,    59,    59,    58,    58,    58,    58,
      51,    51,    51,    56,    56,    56,    56,    56,    56,    56,
      57,    57,    53,    53,    60,    61,    61,    61,    48,    48,
      77,    49,    64,    64,    67,    67,    65,    65,    65,    66,
      66,    63,    63,    63,    63,    62,    62,    70,    70,    70,
      71,    71,    69,    69,    68,    68
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     0,     4,     2,
       5,     7,     3,     5,     2,     2,     1,     1,     1,     1,
       1,     3,     1,     2,     2,     2,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     3,     4,
       0,     6,     4,     3,     4,     3,     1,     3,     2,     3,
       1,     1,     3,     2,     4,     3,     1,     1,     3,     2,
       3,     1,     3,     4,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 49 "src/parser.y"
            {
        ast.setRoot((yyvsp[0].stmttype));
    }
#line 1484 "src/parser.cpp"
    break;

  case 3:
#line 54 "src/parser.y"
           {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1490 "src/parser.cpp"
    break;

  case 4:
#line 55 "src/parser.y"
                {
        (yyval.stmttype) = new SeqNode((yyvsp[-1].stmttype), (yyvsp[0].stmttype));
    }
#line 1498 "src/parser.cpp"
    break;

  case 5:
#line 60 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1504 "src/parser.cpp"
    break;

  case 6:
#line 61 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1510 "src/parser.cpp"
    break;

  case 7:
#line 62 "src/parser.y"
             {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1516 "src/parser.cpp"
    break;

  case 8:
#line 63 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1522 "src/parser.cpp"
    break;

  case 9:
#line 64 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1528 "src/parser.cpp"
    break;

  case 10:
#line 65 "src/parser.y"
                   {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1534 "src/parser.cpp"
    break;

  case 11:
#line 66 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1540 "src/parser.cpp"
    break;

  case 12:
#line 67 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1546 "src/parser.cpp"
    break;

  case 13:
#line 68 "src/parser.y"
              {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1552 "src/parser.cpp"
    break;

  case 14:
#line 71 "src/parser.y"
         {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[0].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[0].strtype));
            delete [](char*)(yyvsp[0].strtype);
            assert(se != nullptr);
        }
        (yyval.exprtype) = new Id(se);
        delete [](yyvsp[0].strtype);
    }
#line 1569 "src/parser.cpp"
    break;

  case 15:
#line 83 "src/parser.y"
                    {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-1].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[-1].strtype));
            delete [](char*)(yyvsp[-1].strtype);
            assert(se != nullptr);
        }
        (yyval.exprtype) = new Id(se, (ArrayIndexNode *)(yyvsp[0].stmttype) );
        delete [](yyvsp[-1].strtype);
    }
#line 1586 "src/parser.cpp"
    break;

  case 16:
#line 98 "src/parser.y"
                              {
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[-1].exprtype));
    }
#line 1594 "src/parser.cpp"
    break;

  case 17:
#line 104 "src/parser.y"
        {identifiers = new SymbolTable(identifiers);}
#line 1600 "src/parser.cpp"
    break;

  case 18:
#line 106 "src/parser.y"
        {
            (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
#line 1611 "src/parser.cpp"
    break;

  case 19:
#line 112 "src/parser.y"
                        { (yyval.stmttype) = new CompoundStmt(nullptr); }
#line 1617 "src/parser.cpp"
    break;

  case 20:
#line 115 "src/parser.y"
                                            {
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1625 "src/parser.cpp"
    break;

  case 21:
#line 118 "src/parser.y"
                                           {
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1633 "src/parser.cpp"
    break;

  case 22:
#line 124 "src/parser.y"
                        {
        (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
    }
#line 1641 "src/parser.cpp"
    break;

  case 23:
#line 129 "src/parser.y"
                                    {
        (yyval.stmttype) = new WhileStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1649 "src/parser.cpp"
    break;

  case 24:
#line 133 "src/parser.y"
                      {
        (yyval.stmttype) = new BreakStmt();
    }
#line 1657 "src/parser.cpp"
    break;

  case 25:
#line 138 "src/parser.y"
                         {
        (yyval.stmttype) = new ContinueStmt();
    }
#line 1665 "src/parser.cpp"
    break;

  case 26:
#line 144 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1671 "src/parser.cpp"
    break;

  case 27:
#line 148 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1677 "src/parser.cpp"
    break;

  case 28:
#line 152 "src/parser.y"
         {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1685 "src/parser.cpp"
    break;

  case 29:
#line 156 "src/parser.y"
            {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constIntType, (yyvsp[0].itype));
        (yyval.exprtype) = new Constant(se);
    }
#line 1694 "src/parser.cpp"
    break;

  case 30:
#line 161 "src/parser.y"
             {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constFloatType, (yyvsp[0].ftype));
        (yyval.exprtype) = new Constant(se);
    }
#line 1703 "src/parser.cpp"
    break;

  case 31:
#line 166 "src/parser.y"
                      {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 1711 "src/parser.cpp"
    break;

  case 32:
#line 172 "src/parser.y"
               {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1719 "src/parser.cpp"
    break;

  case 33:
#line 176 "src/parser.y"
                 {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1727 "src/parser.cpp"
    break;

  case 34:
#line 180 "src/parser.y"
                 {
        SymbolEntry *tmp = new TemporarySymbolEntry((yyvsp[0].exprtype)->getType(), 
            SymbolTable::getLabel());
        (yyval.exprtype) = new OneOpExpr(tmp, OneOpExpr::SUB, (yyvsp[0].exprtype));
    }
#line 1737 "src/parser.cpp"
    break;

  case 35:
#line 186 "src/parser.y"
                 {
        SymbolEntry *tmp = new TemporarySymbolEntry((yyvsp[0].exprtype)->getType(), 
            SymbolTable::getLabel());
        (yyval.exprtype) = new OneOpExpr(tmp, OneOpExpr::NOT, (yyvsp[0].exprtype));
    }
#line 1747 "src/parser.cpp"
    break;

  case 36:
#line 194 "src/parser.y"
             { (yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1753 "src/parser.cpp"
    break;

  case 37:
#line 197 "src/parser.y"
    {
        Type *expType = BinaryExpr::getResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::STAR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));  
    }
#line 1763 "src/parser.cpp"
    break;

  case 38:
#line 204 "src/parser.y"
    {
        Type *expType = BinaryExpr::getResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SLASH, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1773 "src/parser.cpp"
    break;

  case 39:
#line 211 "src/parser.y"
    {
        Type *expType = BinaryExpr::getResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::PERCENT, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1783 "src/parser.cpp"
    break;

  case 40:
#line 219 "src/parser.y"
            {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1789 "src/parser.cpp"
    break;

  case 41:
#line 222 "src/parser.y"
    {
        Type *expType = BinaryExpr::getResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1799 "src/parser.cpp"
    break;

  case 42:
#line 229 "src/parser.y"
    {
        Type *expType = BinaryExpr::getResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1809 "src/parser.cpp"
    break;

  case 43:
#line 237 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1815 "src/parser.cpp"
    break;

  case 44:
#line 240 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1825 "src/parser.cpp"
    break;

  case 45:
#line 247 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESSEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1835 "src/parser.cpp"
    break;

  case 46:
#line 254 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREAT, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1845 "src/parser.cpp"
    break;

  case 47:
#line 261 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1855 "src/parser.cpp"
    break;

  case 48:
#line 268 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::EQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1865 "src/parser.cpp"
    break;

  case 49:
#line 275 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::NEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1875 "src/parser.cpp"
    break;

  case 50:
#line 283 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1881 "src/parser.cpp"
    break;

  case 51:
#line 286 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1891 "src/parser.cpp"
    break;

  case 52:
#line 294 "src/parser.y"
            {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1897 "src/parser.cpp"
    break;

  case 53:
#line 297 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1907 "src/parser.cpp"
    break;

  case 54:
#line 304 "src/parser.y"
             {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1915 "src/parser.cpp"
    break;

  case 55:
#line 310 "src/parser.y"
        {
        declType = TypeSystem::intType;
        (yyval.type) = TypeSystem::intType;
    }
#line 1924 "src/parser.cpp"
    break;

  case 56:
#line 315 "src/parser.y"
          {
        declType = TypeSystem::floatType;
        (yyval.type) = TypeSystem::floatType;
    }
#line 1933 "src/parser.cpp"
    break;

  case 57:
#line 320 "src/parser.y"
         {
        (yyval.type) = TypeSystem::voidType;
    }
#line 1941 "src/parser.cpp"
    break;

  case 58:
#line 326 "src/parser.y"
                              {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1949 "src/parser.cpp"
    break;

  case 59:
#line 330 "src/parser.y"
                                      {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1957 "src/parser.cpp"
    break;

  case 60:
#line 336 "src/parser.y"
            {
        Type *funcType;
        funcType = new FunctionType((yyvsp[-1].type),{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, (yyvsp[0].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[0].strtype), se);
        identifiers = new SymbolTable(identifiers);
    }
#line 1969 "src/parser.cpp"
    break;

  case 61:
#line 345 "src/parser.y"
    {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-4].strtype));
        assert(se != nullptr);
        (yyval.stmttype) = new FunctionDef(se, (yyvsp[0].stmttype));
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete [](yyvsp[-4].strtype);
    }
#line 1984 "src/parser.cpp"
    break;

  case 62:
#line 358 "src/parser.y"
                                               {
        ArrayIndexNode *node = (ArrayIndexNode *)(yyvsp[-3].stmttype);
        node->append( (ExprNode *)(yyvsp[-1].exprtype) );
        (yyval.stmttype) = node;
    }
#line 1994 "src/parser.cpp"
    break;

  case 63:
#line 364 "src/parser.y"
                               {
        ArrayIndexNode *node = new ArrayIndexNode(true);
        node->append( (ExprNode *)(yyvsp[-1].exprtype) );
        (yyval.stmttype) = node;
    }
#line 2004 "src/parser.cpp"
    break;

  case 64:
#line 371 "src/parser.y"
                                       {
        ArrayIndexNode *node = (ArrayIndexNode *)(yyvsp[-3].stmttype);
        node->append( (ExprNode *)(yyvsp[-1].exprtype) );
        (yyval.stmttype) = node;
    }
#line 2014 "src/parser.cpp"
    break;

  case 65:
#line 376 "src/parser.y"
                            {
        ArrayIndexNode *node = new ArrayIndexNode();
        node->append( (ExprNode *)(yyvsp[-1].exprtype) );
        (yyval.stmttype) = node;
    }
#line 2024 "src/parser.cpp"
    break;

  case 66:
#line 384 "src/parser.y"
        {
        InitValNode *node = new InitValNode( (ExprNode *)(yyvsp[0].exprtype) );
        (yyval.stmttype) = node;
    }
#line 2033 "src/parser.cpp"
    break;

  case 67:
#line 389 "src/parser.y"
                              {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 2041 "src/parser.cpp"
    break;

  case 68:
#line 393 "src/parser.y"
                  {
        InitValNode *node = new InitValNode();
        (yyval.stmttype) = node;
    }
#line 2050 "src/parser.cpp"
    break;

  case 69:
#line 400 "src/parser.y"
                              {
        InitValNode *node = (InitValNode *)(yyvsp[-2].stmttype);
        node->append( (InitValNode *)(yyvsp[0].stmttype) );
        (yyval.stmttype) = node;
    }
#line 2060 "src/parser.cpp"
    break;

  case 70:
#line 406 "src/parser.y"
            {
        InitValNode *node = new InitValNode();
        node->append( (InitValNode *)(yyvsp[0].stmttype) );
        (yyval.stmttype) = node;
    }
#line 2070 "src/parser.cpp"
    break;

  case 71:
#line 414 "src/parser.y"
       {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(declType, (yyvsp[0].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[0].strtype), se);
        (yyval.stmttype) = new DefNode(new Id(se), nullptr);
        delete [](yyvsp[0].strtype);
    }
#line 2082 "src/parser.cpp"
    break;

  case 72:
#line 422 "src/parser.y"
                      {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(declType, (yyvsp[-2].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[-2].strtype), se);
        (yyval.stmttype) = new DefNode(new Id(se), (InitValNode *)(yyvsp[0].stmttype) );
        delete [](yyvsp[-2].strtype);
    }
#line 2094 "src/parser.cpp"
    break;

  case 73:
#line 430 "src/parser.y"
                       {
        Type *type;
        if (declType->isInt()) {
            type = new IntArrayType();
        } else {
            type = new FloatArrayType();
        }
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(type, (yyvsp[-1].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[-1].strtype), se);
        Id *id = new Id(se, (ArrayIndexNode *)(yyvsp[0].stmttype) );
        (yyval.stmttype) = new DefNode(id, nullptr);

        int demension = ( (ArrayIndexNode *)(yyvsp[0].stmttype) )->getDemension();
        if (declType->isInt()) {
            ( (IntArrayType *)type )->setDimension(demension);
        } else {
            ( (FloatArrayType *)type )->setDimension(demension);
        }
    }
#line 2119 "src/parser.cpp"
    break;

  case 74:
#line 451 "src/parser.y"
                                      {
        Type *type;
        if (declType->isInt()) {
            type = new IntArrayType();
        } else {
            type = new FloatArrayType();
        }
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(type, (yyvsp[-3].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[-3].strtype), se);
        Id *id = new Id(se, (ArrayIndexNode *)(yyvsp[-2].stmttype) );
        (yyval.stmttype) = new DefNode(id, (InitValNode *)(yyvsp[0].stmttype) );

        int demension = ( (ArrayIndexNode *)(yyvsp[-2].stmttype) )->getDemension();
        if (declType->isInt()) {
            ( (IntArrayType *)type )->setDimension(demension);
        } else {
            ( (FloatArrayType *)type )->setDimension(demension);
        }
    }
#line 2144 "src/parser.cpp"
    break;

  case 75:
#line 473 "src/parser.y"
                              {
        DeclStmt *node = (DeclStmt *)(yyvsp[-2].stmttype);
        node->append( (DefNode *)(yyvsp[0].stmttype) );
        (yyval.stmttype) = node;
    }
#line 2154 "src/parser.cpp"
    break;

  case 76:
#line 479 "src/parser.y"
           {
        DeclStmt *node = new DeclStmt();
        node->append( (DefNode *)(yyvsp[0].stmttype) );
        (yyval.stmttype) = node;
    }
#line 2164 "src/parser.cpp"
    break;

  case 77:
#line 486 "src/parser.y"
               {
        InitValNode *node = new InitValNode( (ExprNode *)(yyvsp[0].exprtype) , true);
        (yyval.stmttype) = node;
    }
#line 2173 "src/parser.cpp"
    break;

  case 78:
#line 491 "src/parser.y"
                                   {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 2181 "src/parser.cpp"
    break;

  case 79:
#line 495 "src/parser.y"
                  {
        InitValNode *node = new InitValNode(nullptr, true);
        (yyval.stmttype) = node;
    }
#line 2190 "src/parser.cpp"
    break;

  case 80:
#line 501 "src/parser.y"
                                          {
        InitValNode *node = (InitValNode *)(yyvsp[-2].stmttype);
        node->append( (InitValNode *)(yyvsp[0].stmttype) );
        (yyval.stmttype) = node;
    }
#line 2200 "src/parser.cpp"
    break;

  case 81:
#line 507 "src/parser.y"
                 {
        InitValNode *node = new InitValNode(nullptr, true);
        node->append( (InitValNode *)(yyvsp[0].stmttype) );
        (yyval.stmttype) = node;
    }
#line 2210 "src/parser.cpp"
    break;

  case 82:
#line 514 "src/parser.y"
                             {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(declType, (yyvsp[-2].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[-2].strtype), se);
        (yyval.stmttype) = new DefNode(new Id(se, true), (InitValNode *)(yyvsp[0].stmttype) , true);
        delete [](yyvsp[-2].strtype);
    }
#line 2222 "src/parser.cpp"
    break;

  case 83:
#line 522 "src/parser.y"
                                           {
        Type *type;
        if (declType->isInt()) {
            type = new ConstIntArrayType();
        } else {
            type = new ConstFloatArrayType();
        }
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(type, (yyvsp[-3].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[-3].strtype), se);
        Id *id = new Id(se, (ArrayIndexNode *)(yyvsp[-2].stmttype) , true);
        (yyval.stmttype) = new DefNode(id, (InitValNode *)(yyvsp[0].stmttype) , true);

        int demension = ( (ArrayIndexNode *)(yyvsp[-2].stmttype) )->getDemension();
        if (declType->isInt()) {
            ( (ConstIntArrayType *)type )->setDimension(demension);
        } else {
            ( (ConstFloatArrayType *)type )->setDimension(demension);
        }
    }
#line 2247 "src/parser.cpp"
    break;

  case 84:
#line 544 "src/parser.y"
                                    {
        DeclStmt *node = (DeclStmt *)(yyvsp[-2].stmttype);
        node->append( (DefNode *)(yyvsp[0].stmttype) );
        (yyval.stmttype) = node;
    }
#line 2257 "src/parser.cpp"
    break;

  case 85:
#line 550 "src/parser.y"
             {
        DeclStmt *node = new DeclStmt(true);
        node->append( (DefNode *)(yyvsp[0].stmttype) );
        (yyval.stmttype) = node;
    }
#line 2267 "src/parser.cpp"
    break;


#line 2271 "src/parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 556 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
