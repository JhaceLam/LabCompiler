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
    #include <cstring>
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    Type *declType; // The Basic Type in DeclStmt
    ArrayType *initArrayType; // ArrayType for InitValNode
    std::stack<InitValNode *> initValNodeStack; // Used for initializing array
    int lbraceCount = 0;
    int idx;
    double *initArrayValue; 
    int givenInitValNum = 0;
    int intParamNo;
    int floatParamNo;
    int stackParamNo;
    std::stack<StmtNode *> whileStack;
    FunctionType *lastDefFuncType;

#line 90 "src/parser.cpp"




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
#line 24 "src/parser.y"

    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"

#line 142 "src/parser.cpp"

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
    STAR = 280,
    SLASH = 281,
    PERCENT = 282,
    AND = 283,
    OR = 284,
    NOT = 285,
    LESS = 286,
    LESSEQ = 287,
    GREATER = 288,
    GREATEQ = 289,
    EQ = 290,
    NEQ = 291,
    ASSIGN = 292,
    RETURN = 293,
    THEN = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 30 "src/parser.y"

    int itype;
    float ftype;
    char *strtype;
    StmtNode *stmttype;
    ExprNode *exprtype;
    Type *type;
    SymbolEntry *se;

#line 203 "src/parser.cpp"

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
#define YYFINAL  59
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   195

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  174

#define YYUNDEFTOK  2
#define YYMAXUTOK   294


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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    62,    62,    67,    68,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    87,   104,   116,   153,
     153,   201,   207,   215,   230,   230,   281,   287,   294,   306,
     321,   327,   327,   337,   342,   345,   351,   372,   383,   387,
     391,   394,   398,   402,   408,   410,   417,   424,   433,   435,
     442,   451,   453,   460,   467,   474,   481,   488,   497,   499,
     508,   510,   519,   524,   529,   535,   539,   545,   551,   551,
     566,   574,   566,   605,   610,   618,   622,   639,   643,   655,
     671,   719,   746,   746,   795,   799,   805,   811,   819,   842,
     868,   893,   920,   926,   932,   938,   944,   950,   956,   956,
     970,   980,   990,   995
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
  "RBRACKET", "ADD", "SUB", "STAR", "SLASH", "PERCENT", "AND", "OR", "NOT",
  "LESS", "LESSEQ", "GREATER", "GREATEQ", "EQ", "NEQ", "ASSIGN", "RETURN",
  "THEN", "$accept", "Program", "Stmts", "Stmt", "VarDef", "@1",
  "VarDefList", "ConstDef", "@2", "ConstDefList", "LVal", "AssignStmt",
  "BlockStmt", "$@3", "IfStmt", "ReturnStmt", "Exp", "Cond", "PrimaryExp",
  "StarExp", "AddExp", "RelExp", "LAndExp", "LOrExp", "Type", "DeclStmt",
  "VarDeclStmt", "ConstDeclStmt", "$@4", "FuncDef", "$@5", "@6",
  "ArrayIndex", "UnaryExp", "InitVal", "@7", "InitValList",
  "FuncArrayIndex", "FuncFParam", "FuncFParams", "FuncRParams",
  "WhileStmt", "@8", "BreakStmt", "ContinueStmt", "ExprStmt", "EmptyStmt", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      86,    -7,  -106,  -106,    -8,     5,    32,    65,  -106,  -106,
      64,  -106,   115,    -3,  -106,   115,   115,   115,    13,    83,
      86,  -106,    49,  -106,  -106,  -106,  -106,    69,  -106,     0,
      21,    90,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,   115,   115,    81,   115,   115,  -106,  -106,  -106,
    -106,    92,  -106,    86,  -106,  -106,  -106,  -106,    93,  -106,
    -106,   115,  -106,   115,   115,   115,   115,   115,    37,  -106,
      87,  -106,    30,    95,   115,    99,    21,   152,    97,    94,
     105,   128,  -106,   151,  -106,   117,  -106,  -106,  -106,     0,
       0,    18,   132,   -18,  -106,   141,  -106,   115,  -106,   130,
      86,   115,   115,   115,   115,   115,   115,   115,   115,  -106,
      17,  -106,   109,  -106,  -106,   133,  -106,  -106,   129,  -106,
      19,  -106,  -106,  -106,   146,    21,    21,    21,    21,    21,
      21,   152,    97,    86,    18,    26,  -106,   128,  -106,    18,
      64,   164,  -106,    57,    18,    86,  -106,  -106,  -106,  -106,
    -106,    62,   168,   155,  -106,   129,  -106,  -106,    18,  -106,
      18,   155,   150,   156,   161,  -106,  -106,  -106,   156,  -106,
     115,  -106,   157,  -106
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    28,    41,    42,     0,     0,     0,     0,    62,    64,
       0,    63,     0,    31,   103,     0,     0,     0,     0,     0,
       2,     3,    40,     5,     6,     7,     8,     0,    75,    48,
      38,     0,     9,    65,    66,    10,    44,    13,    14,    15,
      11,    12,    97,     0,    29,     0,     0,   100,   101,    68,
      40,     0,    33,     0,    77,    78,    79,    37,     0,     1,
       4,     0,   102,     0,     0,     0,     0,     0,    16,    22,
       0,    96,     0,     0,     0,     0,    51,    58,    60,    39,
       0,     0,    43,     0,    36,     0,    45,    46,    47,    49,
      50,     0,     0,    18,    67,     0,    76,     0,    74,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    98,
       0,    27,     0,    32,    30,    82,    80,    17,    94,    19,
      16,    21,    95,    73,    34,    52,    53,    54,    55,    56,
      57,    59,    61,     0,     0,     0,    69,     0,    81,     0,
       0,     0,    93,     0,     0,     0,    99,    23,    24,    26,
      84,     0,     0,    88,    71,     0,    20,    35,     0,    83,
       0,    89,     0,    90,     0,    92,    25,    85,    91,    87,
       0,    72,     0,    86
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -106,  -106,   120,   -19,    85,  -106,  -106,    45,  -106,  -106,
       4,  -106,    27,  -106,  -106,  -106,   -12,   144,  -106,    67,
     -36,    88,    84,  -106,    -5,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,     1,    -4,  -105,  -106,  -106,    33,    38,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    69,   144,    70,   111,   158,   112,
      50,    23,    24,    53,    25,    26,    27,    75,    28,    29,
      30,    77,    78,    79,    31,    32,    33,    34,    81,    35,
      92,   164,    93,    36,   117,   139,   151,   163,   142,   143,
      72,    37,   133,    38,    39,    40,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,    60,    44,    74,    22,    49,    58,    45,    42,    76,
      76,    54,    55,    56,    43,    52,     1,     2,     3,   119,
      46,     1,     2,     3,    22,    63,    64,    65,    12,   147,
      71,    73,    57,    12,   150,   115,    15,    16,    43,   156,
      43,    15,    16,    17,    66,    67,    96,    74,    17,    85,
      97,    47,   -70,   166,   134,   167,    91,    22,    43,    86,
      87,    88,    99,   148,    60,   125,   126,   127,   128,   129,
     130,    76,    76,   154,    91,     8,     9,   155,    11,   116,
     159,   124,   160,    59,    48,   122,    61,    22,    62,     1,
       2,     3,     4,    68,     5,     6,     7,     8,     9,    10,
      11,    12,    74,    13,    22,    14,    94,    95,    82,    15,
      16,   135,    84,   141,   146,   100,    17,    98,     1,     2,
       3,   109,   116,   108,    18,   107,   157,   116,   136,   137,
      12,   110,   116,    89,    90,   152,   114,    22,    15,    16,
       8,     9,   140,    11,   120,    17,   116,   118,   116,    22,
     141,   138,   123,   145,     1,     2,     3,     4,   172,     5,
       6,     7,     8,     9,    10,    11,    12,   153,    13,   113,
      14,   161,   169,    83,    15,    16,   162,   170,    13,   173,
     121,    17,   149,   101,   102,   103,   104,   105,   106,    18,
      80,   171,   132,   165,   168,   131
};

static const yytype_uint8 yycheck[] =
{
      12,    20,     1,    21,     0,    10,    18,    15,    15,    45,
      46,    15,    16,    17,    21,    18,     3,     4,     5,    37,
      15,     3,     4,     5,    20,    25,    26,    27,    15,   134,
      42,    43,    19,    15,   139,    17,    23,    24,    21,   144,
      21,    23,    24,    30,    23,    24,    16,    21,    30,    61,
      20,    19,    15,   158,    37,   160,    37,    53,    21,    63,
      64,    65,    74,    37,    83,   101,   102,   103,   104,   105,
     106,   107,   108,    16,    37,    11,    12,    20,    14,    91,
      18,   100,    20,     0,    19,    97,    37,    83,    19,     3,
       4,     5,     6,     3,     8,     9,    10,    11,    12,    13,
      14,    15,    21,    17,   100,    19,    19,    20,    16,    23,
      24,   110,    19,   118,   133,    16,    30,    22,     3,     4,
       5,    16,   134,    29,    38,    28,   145,   139,    19,    20,
      15,     3,   144,    66,    67,   140,    19,   133,    23,    24,
      11,    12,    13,    14,     3,    30,   158,    15,   160,   145,
     155,    18,    22,     7,     3,     4,     5,     6,   170,     8,
       9,    10,    11,    12,    13,    14,    15,     3,    17,    18,
      19,     3,    22,    53,    23,    24,    21,    21,    17,    22,
      95,    30,   137,    31,    32,    33,    34,    35,    36,    38,
      46,   164,   108,   155,   161,   107
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      13,    14,    15,    17,    19,    23,    24,    30,    38,    41,
      42,    43,    50,    51,    52,    54,    55,    56,    58,    59,
      60,    64,    65,    66,    67,    69,    73,    81,    83,    84,
      85,    86,    15,    21,    72,    15,    15,    19,    19,    64,
      50,    56,    18,    53,    73,    73,    73,    19,    56,     0,
      43,    37,    19,    25,    26,    27,    23,    24,     3,    44,
      46,    56,    80,    56,    21,    57,    60,    61,    62,    63,
      57,    68,    16,    42,    19,    56,    73,    73,    73,    59,
      59,    37,    70,    72,    19,    20,    16,    20,    22,    56,
      16,    31,    32,    33,    34,    35,    36,    28,    29,    16,
       3,    47,    49,    18,    19,    17,    56,    74,    15,    37,
       3,    44,    56,    22,    43,    60,    60,    60,    60,    60,
      60,    61,    62,    82,    37,    72,    19,    20,    18,    75,
      13,    64,    78,    79,    45,     7,    43,    74,    37,    47,
      74,    76,    64,     3,    16,    20,    74,    43,    48,    18,
      20,     3,    21,    77,    71,    78,    74,    74,    77,    22,
      21,    52,    56,    22
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    44,    44,    45,
      44,    46,    46,    47,    48,    47,    49,    49,    50,    50,
      51,    53,    52,    52,    54,    54,    55,    55,    56,    57,
      58,    58,    58,    58,    59,    59,    59,    59,    60,    60,
      60,    61,    61,    61,    61,    61,    61,    61,    62,    62,
      63,    63,    64,    64,    64,    65,    65,    66,    68,    67,
      70,    71,    69,    72,    72,    73,    73,    73,    73,    73,
      74,    74,    75,    74,    76,    76,    77,    77,    78,    78,
      78,    78,    79,    79,    79,    80,    80,    80,    82,    81,
      83,    84,    85,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     0,
       5,     3,     1,     3,     0,     5,     3,     1,     1,     2,
       4,     0,     4,     2,     5,     7,     3,     2,     1,     1,
       1,     1,     1,     3,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     3,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     3,     0,     5,
       0,     0,     8,     4,     3,     1,     4,     2,     2,     2,
       1,     2,     0,     4,     1,     3,     4,     2,     2,     3,
       3,     4,     3,     1,     0,     3,     1,     0,     0,     6,
       2,     2,     2,     1
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
#line 62 "src/parser.y"
            {
        ast.setRoot((yyvsp[0].stmttype));
    }
#line 1512 "src/parser.cpp"
    break;

  case 3:
#line 67 "src/parser.y"
           {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1518 "src/parser.cpp"
    break;

  case 4:
#line 68 "src/parser.y"
                {
        (yyval.stmttype) = new SeqNode((yyvsp[-1].stmttype), (yyvsp[0].stmttype));
    }
#line 1526 "src/parser.cpp"
    break;

  case 5:
#line 73 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype); }
#line 1532 "src/parser.cpp"
    break;

  case 6:
#line 74 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype); }
#line 1538 "src/parser.cpp"
    break;

  case 7:
#line 75 "src/parser.y"
             {(yyval.stmttype)=(yyvsp[0].stmttype); }
#line 1544 "src/parser.cpp"
    break;

  case 8:
#line 76 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype); }
#line 1550 "src/parser.cpp"
    break;

  case 9:
#line 77 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype); }
#line 1556 "src/parser.cpp"
    break;

  case 10:
#line 78 "src/parser.y"
              {(yyval.stmttype)=(yyvsp[0].stmttype); }
#line 1562 "src/parser.cpp"
    break;

  case 11:
#line 79 "src/parser.y"
               {(yyval.stmttype) = (yyvsp[0].stmttype); }
#line 1568 "src/parser.cpp"
    break;

  case 12:
#line 80 "src/parser.y"
                {(yyval.stmttype) = (yyvsp[0].stmttype); }
#line 1574 "src/parser.cpp"
    break;

  case 13:
#line 81 "src/parser.y"
                {(yyval.stmttype) = (yyvsp[0].stmttype); }
#line 1580 "src/parser.cpp"
    break;

  case 14:
#line 82 "src/parser.y"
                {(yyval.stmttype) = (yyvsp[0].stmttype); }
#line 1586 "src/parser.cpp"
    break;

  case 15:
#line 83 "src/parser.y"
                   {(yyval.stmttype) = (yyvsp[0].stmttype); }
#line 1592 "src/parser.cpp"
    break;

  case 16:
#line 87 "src/parser.y"
       {
        SymbolEntry *se = new IdentifierSymbolEntry(declType, (yyvsp[0].strtype), identifiers->getLevel());
        if (!identifiers->install((yyvsp[0].strtype), se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", (char*)(yyvsp[0].strtype));
            assert(identifiers->install((yyvsp[0].strtype), se) != false);
        }
        ExprNode *initVal;
        if (declType->isInt()) {
            initVal = new Constant(new ConstantSymbolEntry(TypeSystem::constIntType));
        } else {
            initVal = new Constant(new ConstantSymbolEntry(TypeSystem::constFloatType));
        }
        (yyval.stmttype) = new DefNode(new Id(se), initVal);

        delete [](yyvsp[0].strtype);
    }
#line 1613 "src/parser.cpp"
    break;

  case 17:
#line 104 "src/parser.y"
                      {
        SymbolEntry *se = new IdentifierSymbolEntry(declType, (yyvsp[-2].strtype), identifiers->getLevel());
        if (!identifiers->install((yyvsp[-2].strtype), se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", (yyvsp[-2].strtype));
            assert(identifiers->install((yyvsp[-2].strtype), se) != false);
        }
        se->setValue((yyvsp[0].exprtype)->getValue());
        (yyval.stmttype) = new DefNode(new Id(se), (yyvsp[0].exprtype));
        
        delete [](yyvsp[-2].strtype);
    }
#line 1629 "src/parser.cpp"
    break;

  case 18:
#line 116 "src/parser.y"
                  {
        if (!dynamic_cast<ArrayIndexNode *>((yyvsp[0].stmttype))->isConst()) {
            fprintf(stderr, "Error in VarDef -> ID ConstArrayIndex ASSIGN InitVal : not ConstArrayIndex\n");
        }

        Type *currentType = declType;
        ArrayType *parentType;
        std::vector<ExprNode *> exprList = dynamic_cast<ArrayIndexNode *>((yyvsp[0].stmttype))->getExprList();
        for (auto iter = exprList.rbegin(); iter != exprList.rend(); iter++) {
            parentType = new ArrayType(currentType, (*iter)->getValue());
            if (currentType->isArray()) {
                dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
            }
            currentType = parentType;
        }
        initArrayType = dynamic_cast<ArrayType *>(currentType);

        initArrayValue = new double[initArrayType->getSize() / declType->getSize()];
        memset(initArrayValue, 0, initArrayType->getSize() / declType->getSize() * sizeof(double));
        SymbolEntry *seForInitVal = new ConstantSymbolEntry(initArrayType, initArrayValue);
        InitValNode *initValNode = new InitValNode(seForInitVal);
        // initValNode->fill();
        initValNode->setUseZeroinitializer();

        Type *seType = initArrayType->deepCopy();
        SymbolEntry* se = new IdentifierSymbolEntry(seType, (yyvsp[-1].strtype), identifiers->getLevel());
        se->setArrayValue(initArrayValue);
        dynamic_cast<IdentifierSymbolEntry *>(se)->setUseZeroinitializer();
        if (!identifiers->install((yyvsp[-1].strtype), se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", (yyvsp[-1].strtype));
            assert(identifiers->install((yyvsp[-1].strtype), se) != false);
        }
        (yyval.stmttype) = new DefNode(new Id(se), initValNode);
  
        delete [](yyvsp[-1].strtype);
    }
#line 1670 "src/parser.cpp"
    break;

  case 19:
#line 153 "src/parser.y"
                         {
        if (!dynamic_cast<ArrayIndexNode *>((yyvsp[-1].stmttype))->isConst()) {
            fprintf(stderr, "Error in VarDef -> ID ConstArrayIndex ASSIGN InitVal : not ConstArrayIndex\n");
        }

        Type *currentType = declType;
        ArrayType *parentType;
        std::vector<ExprNode *> exprList = dynamic_cast<ArrayIndexNode *>((yyvsp[-1].stmttype))->getExprList();
        for (auto iter = exprList.rbegin(); iter != exprList.rend(); iter++) {
            parentType = new ArrayType(currentType, (*iter)->getValue());
            if (currentType->isArray()) {
                dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
            }
            currentType = parentType;
        }
        initArrayType = dynamic_cast<ArrayType *>(currentType);
        while (!initValNodeStack.empty()) {
            initValNodeStack.pop();
        }

        idx = 0;
        initArrayValue = new double[initArrayType->getSize() / declType->getSize()];
        memset(initArrayValue, 0, initArrayType->getSize() / declType->getSize() * sizeof(double));

        Type *seType = initArrayType->deepCopy();
        SymbolEntry* se = new IdentifierSymbolEntry(seType, (yyvsp[-2].strtype), identifiers->getLevel());
        se->setArrayValue(initArrayValue);
        if (!identifiers->install((yyvsp[-2].strtype), se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", (yyvsp[-2].strtype));
            assert(identifiers->install((yyvsp[-2].strtype), se) != false);
        }
        (yyval.se) = se;
        givenInitValNum = 0;
    }
#line 1709 "src/parser.cpp"
    break;

  case 20:
#line 187 "src/parser.y"
            {
        (yyvsp[-1].se)->setArrayValue(initArrayValue);
        if (dynamic_cast<InitValNode *>((yyvsp[0].exprtype))->getUseZeroinitializer()) {
            dynamic_cast<IdentifierSymbolEntry *>((yyvsp[-1].se))->setUseZeroinitializer();
        }
        dynamic_cast<IdentifierSymbolEntry *>((yyvsp[-1].se))->setGivenInitValNum(givenInitValNum);

        (yyval.stmttype) = new DefNode(new Id((yyvsp[-1].se)), (yyvsp[0].exprtype));

        delete [](yyvsp[-4].strtype);
    }
#line 1725 "src/parser.cpp"
    break;

  case 21:
#line 201 "src/parser.y"
                            {
        DeclStmt *node = dynamic_cast<DeclStmt *>((yyvsp[-2].stmttype));
        node->append(dynamic_cast<DefNode *>((yyvsp[0].stmttype)));
        (yyval.stmttype) = node;
    }
#line 1735 "src/parser.cpp"
    break;

  case 22:
#line 207 "src/parser.y"
           {
        DeclStmt *node = new DeclStmt();
        node->append(dynamic_cast<DefNode *>((yyvsp[0].stmttype)));
        (yyval.stmttype) = node;
    }
#line 1745 "src/parser.cpp"
    break;

  case 23:
#line 215 "src/parser.y"
                      {
        if (!((yyvsp[0].exprtype)->getType()->isConst())) {
            fprintf(stderr, "Error in ConstDef -> ID ASSIGN ConstInitVal : not ConstInitVal\n");
        }

        SymbolEntry *se = new IdentifierSymbolEntry(declType, (yyvsp[-2].strtype), identifiers->getLevel());
        if (!identifiers->install((yyvsp[-2].strtype), se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", (yyvsp[-2].strtype));
        }
        se->setValue((yyvsp[0].exprtype)->getValue());
        (yyval.stmttype) = new DefNode(new Id(se), (yyvsp[0].exprtype));

        delete [](yyvsp[-2].strtype);
    }
#line 1764 "src/parser.cpp"
    break;

  case 24:
#line 230 "src/parser.y"
                         {
        if (!dynamic_cast<ArrayIndexNode *>((yyvsp[-1].stmttype))->isConst()) {
            fprintf(stderr, "Error in ConstDef -> ID ConstArrayIndex ASSIGN ConstInitVal : not ConstArrayIndex\n");
        }

        Type *currentType = declType;
        ArrayType *parentType;
        std::vector<ExprNode *> exprList = dynamic_cast<ArrayIndexNode *>((yyvsp[-1].stmttype))->getExprList();
        for (auto iter = exprList.rbegin(); iter != exprList.rend(); iter++) {
            parentType = new ArrayType(currentType, (*iter)->getValue());
            if (currentType->isArray()) {
                dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
            }
            currentType = parentType;
        }
        initArrayType = dynamic_cast<ArrayType *>(currentType);
        while (!initValNodeStack.empty()) {
            initValNodeStack.pop();
        }

        idx = 0;
        initArrayValue = new double[initArrayType->getSize() / declType->getSize()];
        memset(initArrayValue, 0, initArrayType->getSize() / declType->getSize() * sizeof(double));

        Type *seType = initArrayType->deepCopy();
        dynamic_cast<ArrayType *>(seType)->deepSetConst();
        SymbolEntry* se = new IdentifierSymbolEntry(seType, (yyvsp[-2].strtype), identifiers->getLevel());
        se->setArrayValue(initArrayValue);
        if (!identifiers->install((yyvsp[-2].strtype), se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", (yyvsp[-2].strtype));
        }
        (yyval.se) = se;
        givenInitValNum = 0;
    }
#line 1803 "src/parser.cpp"
    break;

  case 25:
#line 264 "src/parser.y"
            {
        if (!dynamic_cast<InitValNode *>((yyvsp[0].exprtype))->getUseZeroinitializer() && !((yyvsp[0].exprtype)->getType()->isConst())) {
            fprintf(stderr, "Error in ConstDef -> ID ConstArrayIndex ASSIGN ConstInitVal : not ConstInitVal\n");
        }

        if (dynamic_cast<InitValNode *>((yyvsp[0].exprtype))->getUseZeroinitializer()) {
            dynamic_cast<IdentifierSymbolEntry *>((yyvsp[-1].se))->setUseZeroinitializer();
        }
        dynamic_cast<IdentifierSymbolEntry *>((yyvsp[-1].se))->setGivenInitValNum(givenInitValNum);

        (yyval.stmttype) = new DefNode(new Id((yyvsp[-1].se)), (yyvsp[0].exprtype));

        delete [](yyvsp[-4].strtype);
    }
#line 1822 "src/parser.cpp"
    break;

  case 26:
#line 281 "src/parser.y"
                                {
        DeclStmt *node = dynamic_cast<DeclStmt *>((yyvsp[-2].stmttype));
        node->append(dynamic_cast<DefNode *>((yyvsp[0].stmttype)));
        (yyval.stmttype) = node;
    }
#line 1832 "src/parser.cpp"
    break;

  case 27:
#line 287 "src/parser.y"
             {
        DeclStmt *node = new DeclStmt();
        node->append(dynamic_cast<DefNode *>((yyvsp[0].stmttype)));
        (yyval.stmttype) = node;
    }
#line 1842 "src/parser.cpp"
    break;

  case 28:
#line 294 "src/parser.y"
         {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[0].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "Error: identifier \"%s\" is undefined\n", (char*)(yyvsp[0].strtype));
            delete [](char*)(yyvsp[0].strtype);
            assert(se != nullptr);
        }
        (yyval.exprtype) = new Id(se);
        delete [](yyvsp[0].strtype);
    }
#line 1859 "src/parser.cpp"
    break;

  case 29:
#line 306 "src/parser.y"
                    {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-1].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "Error: identifier \"%s\" is undefined\n", (char*)(yyvsp[-1].strtype));
            delete [](char*)(yyvsp[-1].strtype);
            assert(se != nullptr);
        }
        (yyval.exprtype) = new Id(se, (ArrayIndexNode *)(yyvsp[0].stmttype) );
        delete [](yyvsp[-1].strtype);
    }
#line 1876 "src/parser.cpp"
    break;

  case 30:
#line 321 "src/parser.y"
                              {
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[-1].exprtype));
    }
#line 1884 "src/parser.cpp"
    break;

  case 31:
#line 327 "src/parser.y"
           {
        identifiers = new SymbolTable(identifiers);
    }
#line 1892 "src/parser.cpp"
    break;

  case 32:
#line 330 "src/parser.y"
                 {
        (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
    }
#line 1903 "src/parser.cpp"
    break;

  case 33:
#line 337 "src/parser.y"
                  {
        (yyval.stmttype) = new EmptyStmt();
    }
#line 1911 "src/parser.cpp"
    break;

  case 34:
#line 342 "src/parser.y"
                                            {
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1919 "src/parser.cpp"
    break;

  case 35:
#line 345 "src/parser.y"
                                           {
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1927 "src/parser.cpp"
    break;

  case 36:
#line 351 "src/parser.y"
                        {
        if (lastDefFuncType->getRetType()->isVoid()) {
            fprintf(stderr, "Error : return-statement with a value, in function returning \'void\'.\n");
            (yyval.stmttype) = new ReturnStmt(nullptr);
        } else {
            Type *exprType = (yyvsp[-1].exprtype)->getFormedType();
            if (exprType->sameType(lastDefFuncType->getRetType())) {
                (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
            } else if ((exprType->isFloat() && lastDefFuncType->getRetType()->isInt()) ||
                (exprType->isInt() && lastDefFuncType->getRetType()->isFloat())) {
                    ImplicitCastExpr* tempExpr = new ImplicitCastExpr((yyvsp[-1].exprtype), lastDefFuncType->getRetType());
                    (yyval.stmttype) = new ReturnStmt(tempExpr);
            } else {
                fprintf(stderr, "Error : return-statement with type \'%s\', in function returning \'%s\'.\n", 
                    exprType->toStr().c_str(), lastDefFuncType->getRetType()->toStr().c_str());
                assert(false);
            }
            
        }
    }
#line 1952 "src/parser.cpp"
    break;

  case 37:
#line 372 "src/parser.y"
                     {
        if (!lastDefFuncType->getRetType()->isVoid()) {
            fprintf(stderr, "Error : return-statement with no value, in function returning \'%s\'.\n", lastDefFuncType->getRetType()->toStr().c_str());
            assert(lastDefFuncType->getRetType()->isVoid());
        } else {
            (yyval.stmttype) = new ReturnStmt(nullptr);
        }
    }
#line 1965 "src/parser.cpp"
    break;

  case 38:
#line 383 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1971 "src/parser.cpp"
    break;

  case 39:
#line 387 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1977 "src/parser.cpp"
    break;

  case 40:
#line 391 "src/parser.y"
         {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1985 "src/parser.cpp"
    break;

  case 41:
#line 394 "src/parser.y"
              {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constIntType, (yyvsp[0].itype));
        (yyval.exprtype) = new Constant(se);
    }
#line 1994 "src/parser.cpp"
    break;

  case 42:
#line 398 "src/parser.y"
               {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constFloatType, (yyvsp[0].ftype));
        (yyval.exprtype) = new Constant(se);
    }
#line 2003 "src/parser.cpp"
    break;

  case 43:
#line 402 "src/parser.y"
                        {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 2011 "src/parser.cpp"
    break;

  case 44:
#line 408 "src/parser.y"
             { (yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2017 "src/parser.cpp"
    break;

  case 45:
#line 411 "src/parser.y"
    {
        Type *expType = BinaryExpr::getArithmeticResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::STAR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));  
    }
#line 2027 "src/parser.cpp"
    break;

  case 46:
#line 418 "src/parser.y"
    {
        Type *expType = BinaryExpr::getArithmeticResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SLASH, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2037 "src/parser.cpp"
    break;

  case 47:
#line 425 "src/parser.y"
    {
        Type *expType = BinaryExpr::getArithmeticResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::PERCENT, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2047 "src/parser.cpp"
    break;

  case 48:
#line 433 "src/parser.y"
            {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2053 "src/parser.cpp"
    break;

  case 49:
#line 436 "src/parser.y"
    {
        Type *expType = BinaryExpr::getArithmeticResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2063 "src/parser.cpp"
    break;

  case 50:
#line 443 "src/parser.y"
    {
        Type *expType = BinaryExpr::getArithmeticResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2073 "src/parser.cpp"
    break;

  case 51:
#line 451 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2079 "src/parser.cpp"
    break;

  case 52:
#line 454 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelationalResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2089 "src/parser.cpp"
    break;

  case 53:
#line 461 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelationalResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESSEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2099 "src/parser.cpp"
    break;

  case 54:
#line 468 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelationalResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATER, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2109 "src/parser.cpp"
    break;

  case 55:
#line 475 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelationalResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2119 "src/parser.cpp"
    break;

  case 56:
#line 482 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelationalResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::EQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2129 "src/parser.cpp"
    break;

  case 57:
#line 489 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelationalResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::NEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2139 "src/parser.cpp"
    break;

  case 58:
#line 497 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2145 "src/parser.cpp"
    break;

  case 59:
#line 500 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelationalResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2155 "src/parser.cpp"
    break;

  case 60:
#line 508 "src/parser.y"
            {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2161 "src/parser.cpp"
    break;

  case 61:
#line 511 "src/parser.y"
    {
        Type *expType = BinaryExpr::getRelationalResultType((yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2171 "src/parser.cpp"
    break;

  case 62:
#line 519 "src/parser.y"
        {
        declType = TypeSystem::intType;
        (yyval.type) = TypeSystem::intType;
    }
#line 2180 "src/parser.cpp"
    break;

  case 63:
#line 524 "src/parser.y"
          {
        declType = TypeSystem::floatType;
        (yyval.type) = TypeSystem::floatType;
    }
#line 2189 "src/parser.cpp"
    break;

  case 64:
#line 529 "src/parser.y"
         {
        (yyval.type) = TypeSystem::voidType;
    }
#line 2197 "src/parser.cpp"
    break;

  case 65:
#line 535 "src/parser.y"
                {
        (yyval.stmttype) = (yyvsp[0].stmttype);
    }
#line 2205 "src/parser.cpp"
    break;

  case 66:
#line 539 "src/parser.y"
                  {
        (yyval.stmttype) = (yyvsp[0].stmttype);
    }
#line 2213 "src/parser.cpp"
    break;

  case 67:
#line 545 "src/parser.y"
                              {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 2221 "src/parser.cpp"
    break;

  case 68:
#line 551 "src/parser.y"
               {
        if (declType->isInt()) {
            declType = TypeSystem::constIntType;
        } else if (declType->isFloat()) {
            declType = TypeSystem::constFloatType;
        } else {
            fprintf(stderr, "Error: Invalid type \'const void\' \n"); 
        }
    }
#line 2235 "src/parser.cpp"
    break;

  case 69:
#line 560 "src/parser.y"
                           {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 2243 "src/parser.cpp"
    break;

  case 70:
#line 566 "src/parser.y"
            {
        SymbolTable::resetLabel();
        identifiers = new SymbolTable(identifiers);

        intParamNo = 0;
        floatParamNo = 0;
        stackParamNo = 0;
    }
#line 2256 "src/parser.cpp"
    break;

  case 71:
#line 574 "src/parser.y"
                              {
        std::vector<Type*> paramsType;
        std::vector<SymbolEntry *> paramsSe;
        if ((yyvsp[-1].stmttype)) {
            for (DefNode *defNode : dynamic_cast<DeclStmt *>((yyvsp[-1].stmttype))->getDefNodeList()) {
                paramsType.push_back(defNode->getId()->getType());
                paramsSe.push_back(defNode->getId()->getSymPtr());
            }
        }
        
        Type *funcType = new FunctionType((yyvsp[-5].type), paramsType, paramsSe);
        lastDefFuncType = dynamic_cast<FunctionType *>(funcType);
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(funcType, (yyvsp[-4].strtype), identifiers->getPrev()->getLevel());
        dynamic_cast<IdentifierSymbolEntry *>(se)->setIntParamCount(intParamNo);
        dynamic_cast<IdentifierSymbolEntry *>(se)->setFloatParamCount(floatParamNo);
        if (!identifiers->getPrev()->install((yyvsp[-4].strtype), se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", (yyvsp[-4].strtype));
        }
        (yyval.se) = se; 
    }
#line 2282 "src/parser.cpp"
    break;

  case 72:
#line 596 "src/parser.y"
    {
        (yyval.stmttype) = new FunctionDef((yyvsp[-1].se), dynamic_cast<DeclStmt *>((yyvsp[-3].stmttype)), (yyvsp[0].stmttype));
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete [](yyvsp[-6].strtype);
    }
#line 2294 "src/parser.cpp"
    break;

  case 73:
#line 605 "src/parser.y"
                                       {
        ArrayIndexNode *node = dynamic_cast<ArrayIndexNode *>((yyvsp[-3].stmttype));
        node->append((yyvsp[-1].exprtype));
        (yyval.stmttype) = node;
    }
#line 2304 "src/parser.cpp"
    break;

  case 74:
#line 610 "src/parser.y"
                            {
        ArrayIndexNode *node = new ArrayIndexNode();
        node->append((yyvsp[-1].exprtype));
        (yyval.stmttype) = node;
    }
#line 2314 "src/parser.cpp"
    break;

  case 75:
#line 618 "src/parser.y"
               {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 2322 "src/parser.cpp"
    break;

  case 76:
#line 622 "src/parser.y"
                                 {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-3].strtype));
        if(se == nullptr) {
            fprintf(stderr, "identifier \"%s\" has not been defined.\n", (char*)(yyvsp[-3].strtype));
            delete [](char*)(yyvsp[-3].strtype);
            assert(se != nullptr);
        }
        if (!se->getType()->isFunc()) {
            fprintf(stderr, "function \"%s\" has not been defined.\n", (char*)(yyvsp[-3].strtype));
            delete [](char*)(yyvsp[-3].strtype);
            assert(se != nullptr);
        }

        (yyval.exprtype) = new FuncCallExpr(se, dynamic_cast<FuncCallParamsNode *>((yyvsp[-1].stmttype)));
    }
#line 2343 "src/parser.cpp"
    break;

  case 77:
#line 639 "src/parser.y"
                 {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 2351 "src/parser.cpp"
    break;

  case 78:
#line 643 "src/parser.y"
                 {
        Type *type = (yyvsp[0].exprtype)->getFormedType();
        Type *exprType;
        if (type->isInt()) {
            exprType = type->isConst() ? TypeSystem::constIntType : TypeSystem::intType;
        } else if (type->isFloat()) {
            exprType = type->isConst() ? TypeSystem::constFloatType : TypeSystem::floatType;
        }
        SymbolEntry *tmp = new TemporarySymbolEntry(exprType, SymbolTable::getLabel());
        (yyval.exprtype) = new UnaryExpr(tmp, UnaryExpr::SUB, (yyvsp[0].exprtype));
    }
#line 2367 "src/parser.cpp"
    break;

  case 79:
#line 655 "src/parser.y"
                 {
        Type *type = (yyvsp[0].exprtype)->getFormedType();
        Type *exprType;
        if (type->isInt() || type->isFloat()) {
            if (type->isConst()) {
                exprType = TypeSystem::constBoolType;
            } else {
                exprType = TypeSystem::boolType;
            }
        }
        SymbolEntry *tmp = new TemporarySymbolEntry(exprType, SymbolTable::getLabel());
        (yyval.exprtype) = new UnaryExpr(tmp, UnaryExpr::NOT, (yyvsp[0].exprtype));
    }
#line 2385 "src/parser.cpp"
    break;

  case 80:
#line 671 "src/parser.y"
        {
        (yyval.exprtype) = (yyvsp[0].exprtype);

        if (!initValNodeStack.empty()) {
            double val = (yyvsp[0].exprtype)->getValue();
            if (declType->isInt() && (yyvsp[0].exprtype)->getType()->isFloat()) {
                val = (int)val;
            }
            initArrayValue[idx++] = val;
            givenInitValNum++;

            if (!initValNodeStack.top()->getType()->isArray()) {
                ExprNode *temp = (yyvsp[0].exprtype);
                if (initValNodeStack.top()->getType()->isInt() && (yyvsp[0].exprtype)->getType()->isFloat()) {
                    temp = ImplicitCastExpr::floatToInt(temp);
                }
                if (initValNodeStack.top()->getType()->isFloat() && (yyvsp[0].exprtype)->getType()->isInt()) {
                    temp = ImplicitCastExpr::intToFloat(temp);
                }
                initValNodeStack.top()->append(temp);
            } else {
                ArrayType *arrType = dynamic_cast<ArrayType *>(initValNodeStack.top()->getType());
                while (arrType) {
                    if (arrType->getElementType()->isArray()) {
                        arrType = dynamic_cast<ArrayType *>(arrType->getElementType());
                        SymbolEntry *se = new ConstantSymbolEntry(arrType, initArrayValue + idx - 1);
                        InitValNode *node = new InitValNode(se);
                        initValNodeStack.top()->append(node);
                        initValNodeStack.push(node);
                    } else {
                        ExprNode *temp = (yyvsp[0].exprtype);
                        if (arrType->getElementType()->isInt() && (yyvsp[0].exprtype)->getType()->isFloat()) {
                            temp = ImplicitCastExpr::floatToInt(temp);
                        }
                        if (arrType->getElementType()->isFloat() && (yyvsp[0].exprtype)->getType()->isInt()) {
                            temp = ImplicitCastExpr::intToFloat(temp);
                        }
                        initValNodeStack.top()->append(temp);
                        while (initValNodeStack.top()->isFull() && (int)initValNodeStack.size() != lbraceCount) {
                            initValNodeStack.pop();
                        }
                        break;
                    }
                }
            }
        }
    }
#line 2437 "src/parser.cpp"
    break;

  case 81:
#line 719 "src/parser.y"
                  {
        SymbolEntry* se;
        InitValNode *node;
        if (initValNodeStack.empty()) {
            se = new ConstantSymbolEntry(initArrayType, initArrayValue + idx);
            node = new InitValNode(se);
            idx += initArrayType->getSize() / declType->getSize();
        } else {
            Type *type = dynamic_cast<ArrayType *>(initValNodeStack.top()->getType())->getElementType();
            int elemNum = type->getSize() / declType->getSize();
            se = new ConstantSymbolEntry(type, initArrayValue + idx);
            node = new InitValNode(se);
            initValNodeStack.top()->append(node);
            idx += elemNum;
            
            while (initValNodeStack.top()->isFull() && (int)initValNodeStack.size() != lbraceCount) {
                initValNodeStack.pop();
            }
        }
        node->setUseZeroinitializer();
        (yyval.exprtype) = node;

        if (lbraceCount == 0) {
            dynamic_cast<InitValNode *>((yyval.exprtype))->fill();
        }
    }
#line 2468 "src/parser.cpp"
    break;

  case 82:
#line 746 "src/parser.y"
           {
        lbraceCount++;

        if (!initValNodeStack.empty()) {
            Type *subType = dynamic_cast<ArrayType *>(initValNodeStack.top()->getType())->getElementType();
            initArrayType = dynamic_cast<ArrayType *>(subType);
        }
        SymbolEntry *se = new ConstantSymbolEntry(initArrayType, initArrayValue + idx);
        InitValNode* node = new InitValNode(se);
        if (!initValNodeStack.empty()) {
            initValNodeStack.top()->append(node);
        }
        initValNodeStack.push(node);
        (yyval.exprtype) = node;

        if (initArrayType->getElementType()->isArray()) {
            initArrayType = dynamic_cast<ArrayType *>(initArrayType->getElementType());
        }
    }
#line 2492 "src/parser.cpp"
    break;

  case 83:
#line 765 "src/parser.y"
                       {
        lbraceCount--;
        while (initValNodeStack.top() != (yyvsp[-2].exprtype) && (int)initValNodeStack.size() > lbraceCount + 1) {
            initValNodeStack.pop();
        }
        if (initValNodeStack.top() == (yyvsp[-2].exprtype)) {
            initValNodeStack.pop();
        }
        (yyval.exprtype) = (yyvsp[-2].exprtype);
        if (!initValNodeStack.empty()) {
            while (initValNodeStack.top()->isFull() && (int)initValNodeStack.size() != lbraceCount) {
                initValNodeStack.pop();
            }
        }
        int elemNum = dynamic_cast<ArrayType *>((yyval.exprtype)->getType())->getSize() / declType->getSize();
        while (idx % elemNum) {
            idx++;
        }
        if (!initValNodeStack.empty()) {
            Type *subType = dynamic_cast<ArrayType *>(initValNodeStack.top()->getType())->getElementType();
            initArrayType = dynamic_cast<ArrayType *>(subType);
        }

        if (lbraceCount == 0) {
            dynamic_cast<InitValNode *>((yyval.exprtype))->fill();
        }
    }
#line 2524 "src/parser.cpp"
    break;

  case 84:
#line 795 "src/parser.y"
            {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 2532 "src/parser.cpp"
    break;

  case 85:
#line 799 "src/parser.y"
                              {
        (yyval.exprtype) = (yyvsp[-2].exprtype);
    }
#line 2540 "src/parser.cpp"
    break;

  case 86:
#line 805 "src/parser.y"
                                         {
        ArrayIndexNode *node = dynamic_cast<ArrayIndexNode *>((yyvsp[-3].stmttype));
        node->append((yyvsp[-1].exprtype));
        (yyval.stmttype) = node;
    }
#line 2550 "src/parser.cpp"
    break;

  case 87:
#line 811 "src/parser.y"
                      {
        ArrayIndexNode *node = new ArrayIndexNode();
        node->append(nullptr);
        (yyval.stmttype) = node;
    }
#line 2560 "src/parser.cpp"
    break;

  case 88:
#line 819 "src/parser.y"
            {
        SymbolEntry *se;
        if ((yyvsp[-1].type)->isFloat()) {
            se = new IdentifierSymbolEntry((yyvsp[-1].type), (yyvsp[0].strtype), identifiers->getLevel(), floatParamNo++);
            dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
            if (floatParamNo > 4) {
                dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
            }
        } else {
            se = new IdentifierSymbolEntry((yyvsp[-1].type), (yyvsp[0].strtype), identifiers->getLevel(), intParamNo++);
            dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
            if (intParamNo > 4) {
                dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
            }
        }
        dynamic_cast<IdentifierSymbolEntry *>(se)->setLabel();
        dynamic_cast<IdentifierSymbolEntry *>(se)->setAddr(new Operand(se));

        identifiers->install((yyvsp[0].strtype), se);
        (yyval.stmttype) = new DefNode(new Id(se), nullptr);
        delete [](yyvsp[0].strtype);
    }
#line 2587 "src/parser.cpp"
    break;

  case 89:
#line 842 "src/parser.y"
                  {
        Type *seType = (yyvsp[-1].type)->deepCopy();
        seType->setConst();

        SymbolEntry *se;
        if ((yyvsp[-1].type)->isFloat()) {
            se = new IdentifierSymbolEntry(seType, (yyvsp[0].strtype), identifiers->getLevel(), floatParamNo++);
            dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
            if (floatParamNo > 4) {
                dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
            }
        } else {
            se = new IdentifierSymbolEntry(seType, (yyvsp[0].strtype), identifiers->getLevel(), intParamNo++);
            dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
            if (intParamNo > 4) {
                dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
            }
        }
        dynamic_cast<IdentifierSymbolEntry *>(se)->setLabel();
        dynamic_cast<IdentifierSymbolEntry *>(se)->setAddr(new Operand(se));

        identifiers->install((yyvsp[0].strtype), se);
        (yyval.stmttype) = new DefNode(new Id(se), nullptr);
        delete [](yyvsp[0].strtype);
    }
#line 2617 "src/parser.cpp"
    break;

  case 90:
#line 868 "src/parser.y"
                           {
        Type *currentType = declType;
        ArrayType *parentType;
        std::vector<ExprNode *> exprList = dynamic_cast<ArrayIndexNode *>((yyvsp[0].stmttype))->getExprList();
        for (auto iter = exprList.rbegin(); iter != exprList.rend(); iter++) {
            parentType = new ArrayType(currentType, (*iter) ? (*iter)->getValue() : -1);
            if (currentType->isArray()) {
                dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
            }
            currentType = parentType;
        }
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(currentType, (yyvsp[-1].strtype), identifiers->getLevel(), intParamNo++);
        dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
        if (intParamNo > 4) {
            dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
        }
        dynamic_cast<IdentifierSymbolEntry *>(se)->setLabel();
        dynamic_cast<IdentifierSymbolEntry *>(se)->setAddr(new Operand(se));

        identifiers->install((yyvsp[-1].strtype), se);
        (yyval.stmttype) = new DefNode(new Id(se), nullptr);
        delete [](yyvsp[-1].strtype);
    }
#line 2646 "src/parser.cpp"
    break;

  case 91:
#line 893 "src/parser.y"
                                 {
        Type *currentType = declType;
        ArrayType *parentType;
        std::vector<ExprNode *> exprList = dynamic_cast<ArrayIndexNode *>((yyvsp[0].stmttype))->getExprList();
        for (auto iter = exprList.rbegin(); iter != exprList.rend(); iter++) {
            parentType = new ArrayType(currentType, (*iter) ? (*iter)->getValue() : -1);
            if (currentType->isArray()) {
                dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
            }
            currentType = parentType;
        }
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(currentType, (yyvsp[-1].strtype), identifiers->getLevel(), intParamNo++);
        dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
        if (intParamNo > 4) {
            dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
        }
        dynamic_cast<IdentifierSymbolEntry *>(se)->setLabel();
        dynamic_cast<IdentifierSymbolEntry *>(se)->setAddr(new Operand(se));

        identifiers->install((yyvsp[-1].strtype), se);
        (yyval.stmttype) = new DefNode(new Id(se), nullptr);
        delete [](yyvsp[-1].strtype);
    }
#line 2675 "src/parser.cpp"
    break;

  case 92:
#line 920 "src/parser.y"
                                 {
        DeclStmt *node = dynamic_cast<DeclStmt *>((yyvsp[-2].stmttype));
        node->append(dynamic_cast<DefNode *>((yyvsp[0].stmttype)));
        (yyval.stmttype) = node;
    }
#line 2685 "src/parser.cpp"
    break;

  case 93:
#line 926 "src/parser.y"
               {
        DeclStmt *node = new DeclStmt();
        node->append(dynamic_cast<DefNode *>((yyvsp[0].stmttype)));
        (yyval.stmttype) = node;
    }
#line 2695 "src/parser.cpp"
    break;

  case 94:
#line 932 "src/parser.y"
           {
        (yyval.stmttype) = nullptr;
    }
#line 2703 "src/parser.cpp"
    break;

  case 95:
#line 938 "src/parser.y"
                          {
        FuncCallParamsNode* node = (FuncCallParamsNode*) (yyvsp[-2].stmttype);
        node->append((yyvsp[0].exprtype));
        (yyval.stmttype) = node;
    }
#line 2713 "src/parser.cpp"
    break;

  case 96:
#line 944 "src/parser.y"
        {
        FuncCallParamsNode* node = new FuncCallParamsNode();
        node->append((yyvsp[0].exprtype));
        (yyval.stmttype) = node;
    }
#line 2723 "src/parser.cpp"
    break;

  case 97:
#line 950 "src/parser.y"
           {
        (yyval.stmttype) = nullptr;
    }
#line 2731 "src/parser.cpp"
    break;

  case 98:
#line 956 "src/parser.y"
                             {
        WhileStmt *node = new WhileStmt((yyvsp[-1].exprtype), nullptr);
        whileStack.push(node);
        (yyval.stmttype) = node;
    }
#line 2741 "src/parser.cpp"
    break;

  case 99:
#line 961 "src/parser.y"
         {
        WhileStmt *node = dynamic_cast<WhileStmt *>((yyvsp[-1].stmttype));
        node->setStmt((yyvsp[0].stmttype));
        whileStack.pop();
        (yyval.stmttype) = node;
    }
#line 2752 "src/parser.cpp"
    break;

  case 100:
#line 970 "src/parser.y"
                    {
        if (!whileStack.empty()) {
            (yyval.stmttype) = new BreakStmt(whileStack.top());
        } else {
            fprintf(stderr, "Error : break statement not within a while loop\n");
        }
    }
#line 2764 "src/parser.cpp"
    break;

  case 101:
#line 980 "src/parser.y"
                       {
        if (!whileStack.empty()) {
            (yyval.stmttype) = new ContinueStmt(whileStack.top());
        } else {
            fprintf(stderr, "Error : continue statement not within a while loop\n");
        }
    }
#line 2776 "src/parser.cpp"
    break;

  case 102:
#line 990 "src/parser.y"
                  {
        (yyval.stmttype) = new ExprStmt((yyvsp[-1].exprtype));
    }
#line 2784 "src/parser.cpp"
    break;

  case 103:
#line 995 "src/parser.y"
                {
        (yyval.stmttype) = new EmptyStmt();
    }
#line 2792 "src/parser.cpp"
    break;


#line 2796 "src/parser.cpp"

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
#line 999 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
