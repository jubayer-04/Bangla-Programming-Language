
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);
extern FILE *yyin;
extern int yylineno;

typedef struct Expr Expr;
typedef struct Stmt Stmt;

typedef enum { VT_UNDEF, VT_INT, VT_FLOAT, VT_STRING } VarType;
typedef enum { EX_NUM, EX_VAR, EX_STR, EX_BINOP, EX_CMPOP } ExprKind;
typedef enum { ST_PRINT, ST_ASSIGN, ST_SCAN, ST_IF, ST_FOR, ST_RETURN } StmtKind;
typedef enum { VAL_INT, VAL_FLOAT, VAL_STRING } ValueKind;

typedef struct Var {
    VarType type;
    double num;
    char *str;
} Var;

typedef struct Value {
    ValueKind kind;
    double num;
    char *str;
} Value;

struct Expr {
    ExprKind kind;
    int op;
    double num;
    char *var;
    char *sval;
    Expr *left;
    Expr *right;
};

struct Stmt {
    StmtKind kind;
    Stmt *next;
    union {
        struct { char *text; char *var; } print;
        struct { char *var; Expr *value; int is_string_assign; char *sval; int declared_type; } assign;
        struct { char *var; } scan;
        struct { Expr *cond; Stmt *then_branch; Stmt *else_branch; } if_stmt;
        struct { char *var; Expr *limit; Stmt *body; } for_stmt;
        struct { Expr *value; } ret;
    } u;
};

Var vars[256];
Stmt *root = NULL;
int type_error_count = 0;

Expr *make_num(double n);
Expr *make_var(char *name);
Expr *make_strlit(char *s);
Expr *make_bin(int op, Expr *l, Expr *r, int is_cmp);
Stmt *make_print_text(char *s);
Stmt *make_print_var(char *name);
Stmt *make_assign_expr(char *name, Expr *e);
Stmt *make_assign_string(char *name, char *s);
Stmt *make_scan(char *name);
Stmt *make_if(Expr *cond, Stmt *then_b, Stmt *else_b);
Stmt *make_for(char *var, Expr *limit, Stmt *body);
Stmt *make_return(Expr *e);
Stmt *append_stmt(Stmt *list, Stmt *s);

Value eval_value(Expr *e);
void exec_stmt_list(Stmt *s);
void exec_stmt(Stmt *s);

static Var *get_var_slot(const char *name);
static void set_num(const char *name, double v, VarType t);
static void set_str(const char *name, const char *s);
static const char *expr_get_str(Expr *e);
static Value make_int_value(int x);
static Value make_float_value(double x);
static Value make_string_value(const char *s);


/* Line 189 of yacc.c  */
#line 158 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 85 "parser.y"

    struct Expr;
    struct Stmt;



/* Line 209 of yacc.c  */
#line 189 "parser.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PRINT = 258,
     IF = 259,
     THEN = 260,
     ELSE = 261,
     END = 262,
     FOR = 263,
     RETURN = 264,
     SCAN = 265,
     LET = 266,
     CHOLO = 267,
     INT_T = 268,
     FLOAT_T = 269,
     STRING_T = 270,
     NUMBER = 271,
     ID = 272,
     STRING = 273,
     ASSIGN = 274,
     GT = 275,
     LT = 276,
     EQ = 277,
     INC = 278,
     DEC = 279
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 90 "parser.y"

    double num;
    char *str;
    struct Expr *expr;
    struct Stmt *stmt;



/* Line 214 of yacc.c  */
#line 239 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 251 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   95

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  6
/* YYNRULES -- Number of rules.  */
#define YYNRULES  33
/* YYNRULES -- Number of states.  */
#define YYNSTATES  64

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    27,    25,     2,    26,     2,    28,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    15,    18,    23,
      28,    32,    36,    40,    46,    52,    58,    62,    66,    69,
      76,    83,    86,    87,    90,    94,    98,   102,   106,   110,
     114,   118,   120,   122
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      30,     0,    -1,    31,    -1,    -1,    31,    32,    -1,     3,
      18,    -1,     3,    17,    -1,    11,    17,    -1,    11,    17,
      19,    18,    -1,    11,    17,    19,    34,    -1,    11,    13,
      17,    -1,    11,    14,    17,    -1,    11,    15,    17,    -1,
      11,    13,    17,    19,    34,    -1,    11,    14,    17,    19,
      34,    -1,    11,    15,    17,    19,    34,    -1,    17,    19,
      34,    -1,    17,    19,    18,    -1,    10,    17,    -1,     4,
      34,     5,    31,    33,     7,    -1,    12,    17,     8,    34,
      31,     7,    -1,     9,    34,    -1,    -1,     6,    31,    -1,
      34,    20,    34,    -1,    34,    21,    34,    -1,    34,    22,
      34,    -1,    34,    25,    34,    -1,    34,    26,    34,    -1,
      34,    27,    34,    -1,    34,    28,    34,    -1,    16,    -1,
      17,    -1,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   113,   113,   117,   118,   122,   123,   125,   127,   128,
     130,   131,   132,   134,   135,   136,   138,   139,   141,   143,
     146,   149,   153,   154,   158,   159,   160,   162,   163,   164,
     165,   167,   168,   169
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PRINT", "IF", "THEN", "ELSE", "END",
  "FOR", "RETURN", "SCAN", "LET", "CHOLO", "INT_T", "FLOAT_T", "STRING_T",
  "NUMBER", "ID", "STRING", "ASSIGN", "GT", "LT", "EQ", "INC", "DEC",
  "'+'", "'-'", "'*'", "'/'", "$accept", "program", "stmt_list",
  "statement", "opt_else", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    43,    45,    42,    47
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    29,    30,    31,    31,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    33,    33,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    34
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     2,     4,     4,
       3,     3,     3,     5,     5,     5,     3,     3,     2,     6,
       6,     2,     0,     2,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,     4,     6,     5,    31,    32,    33,     0,    21,    18,
       0,     0,     0,     7,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,    10,    11,    12,     0,     0,    17,
      16,    22,    24,    25,    26,    27,    28,    29,    30,     0,
       0,     0,     8,     9,     3,     3,     0,    13,    14,    15,
       0,    23,    19,    20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    11,    56,    17
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -26
static const yytype_int8 yypact[] =
{
     -26,     4,     3,   -26,    19,    67,    67,     0,    61,    11,
      23,   -26,   -26,   -26,   -26,   -26,   -26,    13,    36,   -26,
      34,    42,    51,    50,    69,    70,   -26,    67,    67,    67,
      67,    67,    67,    67,    74,    75,    76,    73,    67,    45,
      36,    -1,    54,    54,    54,    21,    21,   -26,   -26,    67,
      67,    67,    45,    36,    36,   -26,    85,    36,    36,    36,
      43,     3,   -26,   -26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -26,   -26,   -25,   -26,   -26,    -6
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -34
static const yytype_int8 yytable[] =
{
      18,    41,     4,     5,     3,    55,     4,     5,     6,     7,
       8,     9,     6,     7,     8,     9,    10,    19,    26,    40,
      10,    42,    43,    44,    45,    46,    47,    48,    24,    60,
      61,    53,    54,    27,    28,    29,    12,    13,    30,    31,
      32,    33,    25,    57,    58,    59,     4,     5,    32,    33,
      63,    34,     6,     7,     8,     9,    27,    28,    29,    35,
      10,    30,    31,    32,    33,   -33,   -33,   -33,    36,    37,
     -33,   -33,   -33,   -33,    20,    21,    22,    38,    23,    30,
      31,    32,    33,    14,    15,    16,    14,    15,    39,    14,
      15,    52,    62,    49,    50,    51
};

static const yytype_uint8 yycheck[] =
{
       6,    26,     3,     4,     0,     6,     3,     4,     9,    10,
      11,    12,     9,    10,    11,    12,    17,    17,     5,    25,
      17,    27,    28,    29,    30,    31,    32,    33,    17,    54,
      55,    37,    38,    20,    21,    22,    17,    18,    25,    26,
      27,    28,    19,    49,    50,    51,     3,     4,    27,    28,
       7,    17,     9,    10,    11,    12,    20,    21,    22,    17,
      17,    25,    26,    27,    28,    20,    21,    22,    17,    19,
      25,    26,    27,    28,    13,    14,    15,     8,    17,    25,
      26,    27,    28,    16,    17,    18,    16,    17,    18,    16,
      17,    18,     7,    19,    19,    19
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    31,     0,     3,     4,     9,    10,    11,    12,
      17,    32,    17,    18,    16,    17,    18,    34,    34,    17,
      13,    14,    15,    17,    17,    19,     5,    20,    21,    22,
      25,    26,    27,    28,    17,    17,    17,    19,     8,    18,
      34,    31,    34,    34,    34,    34,    34,    34,    34,    19,
      19,    19,    18,    34,    34,     6,    33,    34,    34,    34,
      31,    31,     7,     7
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    { root = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 117 "parser.y"
    { (yyval.stmt) = NULL; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 118 "parser.y"
    { (yyval.stmt) = append_stmt((yyvsp[(1) - (2)].stmt), (yyvsp[(2) - (2)].stmt)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 122 "parser.y"
    { (yyval.stmt) = make_print_text((yyvsp[(2) - (2)].str)); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 123 "parser.y"
    { (yyval.stmt) = make_print_var((yyvsp[(2) - (2)].str)); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 125 "parser.y"
    { (yyval.stmt) = make_assign_expr((yyvsp[(2) - (2)].str), make_num(0.0)); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 127 "parser.y"
    { (yyval.stmt) = make_assign_string((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].str)); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    { (yyval.stmt) = make_assign_expr((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].expr)); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    { (yyval.stmt) = make_assign_expr((yyvsp[(3) - (3)].str), make_num(0.0)); ((Stmt*)(yyval.stmt))->u.assign.declared_type = VT_INT; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    { (yyval.stmt) = make_assign_expr((yyvsp[(3) - (3)].str), make_num(0.0)); ((Stmt*)(yyval.stmt))->u.assign.declared_type = VT_FLOAT; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
    { (yyval.stmt) = make_assign_string((yyvsp[(3) - (3)].str), strdup("")); ((Stmt*)(yyval.stmt))->u.assign.declared_type = VT_STRING; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 134 "parser.y"
    { (yyval.stmt) = make_assign_expr((yyvsp[(3) - (5)].str), (yyvsp[(5) - (5)].expr)); ((Stmt*)(yyval.stmt))->u.assign.declared_type = VT_INT; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 135 "parser.y"
    { (yyval.stmt) = make_assign_expr((yyvsp[(3) - (5)].str), (yyvsp[(5) - (5)].expr)); ((Stmt*)(yyval.stmt))->u.assign.declared_type = VT_FLOAT; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 136 "parser.y"
    { (yyval.stmt) = make_assign_expr((yyvsp[(3) - (5)].str), (yyvsp[(5) - (5)].expr)); ((Stmt*)(yyval.stmt))->u.assign.declared_type = VT_STRING; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 138 "parser.y"
    { (yyval.stmt) = make_assign_expr((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 139 "parser.y"
    { (yyval.stmt) = make_assign_string((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str)); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 141 "parser.y"
    { (yyval.stmt) = make_scan((yyvsp[(2) - (2)].str)); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 144 "parser.y"
    { (yyval.stmt) = make_if((yyvsp[(2) - (6)].expr), (yyvsp[(4) - (6)].stmt), (yyvsp[(5) - (6)].stmt)); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    { (yyval.stmt) = make_for((yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].expr), (yyvsp[(5) - (6)].stmt)); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    { (yyval.stmt) = make_return((yyvsp[(2) - (2)].expr)); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    { (yyval.stmt) = NULL; ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 154 "parser.y"
    { (yyval.stmt) = (yyvsp[(2) - (2)].stmt); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    { (yyval.expr) = make_bin(GT,  (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), 1); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    { (yyval.expr) = make_bin(LT,  (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), 1); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    { (yyval.expr) = make_bin(EQ,  (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), 1); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 162 "parser.y"
    { (yyval.expr) = make_bin('+', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), 0); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    { (yyval.expr) = make_bin('-', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), 0); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    { (yyval.expr) = make_bin('*', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), 0); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    { (yyval.expr) = make_bin('/', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), 0); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    { (yyval.expr) = make_num((yyvsp[(1) - (1)].num)); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 168 "parser.y"
    { (yyval.expr) = make_var((yyvsp[(1) - (1)].str)); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    { (yyval.expr) = make_strlit((yyvsp[(1) - (1)].str)); ;}
    break;



/* Line 1455 of yacc.c  */
#line 1719 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 171 "parser.y"


Expr *make_num(double n){
    Expr *e = malloc(sizeof(Expr));
    memset(e,0,sizeof(*e));
    e->kind = EX_NUM;
    e->num = n;
    return e;
}

Expr *make_var(char *name){
    Expr *e = malloc(sizeof(Expr));
    memset(e,0,sizeof(*e));
    e->kind = EX_VAR;
    e->var = name;
    return e;
}

Expr *make_strlit(char *s){
    Expr *e = malloc(sizeof(Expr));
    memset(e,0,sizeof(*e));
    e->kind = EX_STR;
    e->sval = s;
    return e;
}

Expr *make_bin(int op, Expr *l, Expr *r, int is_cmp){
    Expr *e = malloc(sizeof(Expr));
    memset(e,0,sizeof(*e));
    e->kind = is_cmp ? EX_CMPOP : EX_BINOP;
    e->op = op;
    e->left = l;
    e->right = r;
    return e;
}

Stmt *make_print_text(char *s){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_PRINT;
    st->next = NULL;
    st->u.print.text = s;
    st->u.print.var = NULL;
    return st;
}

Stmt *make_print_var(char *name){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_PRINT;
    st->next = NULL;
    st->u.print.text = NULL;
    st->u.print.var = name;
    return st;
}

Stmt *make_assign_expr(char *name, Expr *e){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_ASSIGN;
    st->next = NULL;
    st->u.assign.var = name;
    st->u.assign.value = e;
    st->u.assign.is_string_assign = 0;
    st->u.assign.sval = NULL;
    st->u.assign.declared_type = VT_UNDEF;
    return st;
}

Stmt *make_assign_string(char *name, char *s){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_ASSIGN;
    st->next = NULL;
    st->u.assign.var = name;
    st->u.assign.value = NULL;
    st->u.assign.is_string_assign = 1;
    st->u.assign.sval = s;
    st->u.assign.declared_type = VT_UNDEF;
    return st;
}

Stmt *make_scan(char *name){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_SCAN;
    st->next = NULL;
    st->u.scan.var = name;
    return st;
}

Stmt *make_if(Expr *cond, Stmt *t, Stmt *e){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_IF;
    st->next = NULL;
    st->u.if_stmt.cond = cond;
    st->u.if_stmt.then_branch = t;
    st->u.if_stmt.else_branch = e;
    return st;
}

Stmt *make_for(char *var, Expr *limit, Stmt *body){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_FOR;
    st->next = NULL;
    st->u.for_stmt.var = var;
    st->u.for_stmt.limit = limit;
    st->u.for_stmt.body = body;
    return st;
}

Stmt *make_return(Expr *e){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_RETURN;
    st->next = NULL;
    st->u.ret.value = e;
    return st;
}

Stmt *append_stmt(Stmt *list, Stmt *s){
    if(!list) return s;
    Stmt *p = list;
    while(p->next) p = p->next;
    p->next = s;
    return list;
}

static Var *get_var_slot(const char *name){
    unsigned char idx = (unsigned char)name[0];
    return &vars[idx];
}

static void set_num(const char *name, double v, VarType t){
    Var *slot = get_var_slot(name);
    slot->type = t;
    slot->num = v;
    if(slot->str){
        free(slot->str);
        slot->str = NULL;
    }
}

static void set_str(const char *name, const char *s){
    Var *slot = get_var_slot(name);
    slot->type = VT_STRING;
    slot->num = 0.0;
    if(slot->str) free(slot->str);
    slot->str = s ? strdup(s) : strdup("");
}

static const char *expr_get_str(Expr *e){
    if(!e) return NULL;
    if(e->kind == EX_STR) return e->sval;
    if(e->kind == EX_VAR){
        Var *slot = get_var_slot(e->var);
        if(slot->type == VT_STRING) return slot->str;
        return NULL;
    }
    return NULL;
}

static Value make_int_value(int x){
    Value v; v.kind = VAL_INT; v.num = x; v.str = NULL; return v;
}

static Value make_float_value(double x){
    Value v; v.kind = VAL_FLOAT; v.num = x; v.str = NULL; return v;
}

static Value make_string_value(const char *s){
    Value v; v.kind = VAL_STRING; v.num = 0.0; v.str = (char*)s; return v;
}

Value eval_value(Expr *e){
    if(!e) return make_int_value(0);
    switch(e->kind){
    case EX_NUM:
        if(e->num == (int)e->num) return make_int_value((int)e->num);
        return make_float_value(e->num);

    case EX_VAR: {
        Var *slot = get_var_slot(e->var);
        if(slot->type == VT_STRING) return make_string_value(slot->str);
        if(slot->type == VT_FLOAT)  return make_float_value(slot->num);
        return make_int_value((int)slot->num);
    }

    case EX_STR:
        return make_string_value(e->sval);

    case EX_BINOP: {
        Value a = eval_value(e->left);
        Value b = eval_value(e->right);
        if(a.kind == VAL_STRING || b.kind == VAL_STRING){
            fprintf(stderr, "Type error (line %d): string used in arithmetic\n", yylineno);
            type_error_count++;
            return make_int_value(0);
        }
        double na = a.num, nb = b.num, r = 0.0;
        switch(e->op){
            case '+': r = na + nb; break;
            case '-': r = na - nb; break;
            case '*': r = na * nb; break;
            case '/': r = (nb != 0.0) ? na / nb : 0.0; break;
        }
        if(a.kind == VAL_FLOAT || b.kind == VAL_FLOAT || r != (int)r)
            return make_float_value(r);
        return make_int_value((int)r);
    }

    case EX_CMPOP: {
        Value a = eval_value(e->left);
        Value b = eval_value(e->right);

        if(a.kind == VAL_STRING || b.kind == VAL_STRING){
            if(a.kind != VAL_STRING || b.kind != VAL_STRING){
                fprintf(stderr, "Type error (line %d): cannot compare string with number\n", yylineno);
                type_error_count++;
                return make_int_value(0);
            }
            if(e->op != EQ){
                fprintf(stderr, "Type error (line %d): only == allowed for strings\n", yylineno);
                type_error_count++;
                return make_int_value(0);
            }
            const char *sa = a.str ? a.str : "";
            const char *sb = b.str ? b.str : "";
            return make_int_value(strcmp(sa, sb) == 0);
        }

        double na = a.num, nb = b.num;
        int res = 0;
        switch(e->op){
            case GT: res = na > nb; break;
            case LT: res = na < nb; break;
            case EQ: res = na == nb; break;
        }
        return make_int_value(res);
    }
    }
    return make_int_value(0);
}

void exec_stmt_list(Stmt *s){
    while(s){
        exec_stmt(s);
        s = s->next;
    }
}

void exec_stmt(Stmt *s){
    if(!s) return;
    switch(s->kind){

    case ST_PRINT: {
        if(s->u.print.text){
            printf("%s\n", s->u.print.text);
        } else {
            Var *slot = get_var_slot(s->u.print.var);
            if(slot->type == VT_STRING)
                printf("%s\n", slot->str ? slot->str : "");
            else if(slot->type == VT_FLOAT)
                printf("%g\n", slot->num);
            else
                printf("%d\n", (int)slot->num);
        }
        break;
    }

    case ST_ASSIGN: {
        Value v;
        if(s->u.assign.is_string_assign)
            v = make_string_value(s->u.assign.sval);
        else
            v = eval_value(s->u.assign.value);

        Var *slot = get_var_slot(s->u.assign.var);
        VarType t = slot->type;
        VarType declared = (VarType)s->u.assign.declared_type;
        if(declared != VT_UNDEF)
            t = declared;

        if(t == VT_UNDEF){
            if(v.kind == VAL_STRING) t = VT_STRING;
            else if(v.kind == VAL_FLOAT) t = VT_FLOAT;
            else t = VT_INT;
        }

        if(t == VT_STRING){
            if(v.kind != VAL_STRING){
                fprintf(stderr,
                        "Type error (line %d): cannot assign numeric value to string variable '%s'\n",
                        yylineno, s->u.assign.var);
                type_error_count++;
                break;
            }
            set_str(s->u.assign.var, v.str);
        } else if(t == VT_INT){
            if(v.kind == VAL_STRING){
                fprintf(stderr,
                        "Type error (line %d): cannot assign string value to numeric variable '%s'\n",
                        yylineno, s->u.assign.var);
                type_error_count++;
                break;
            }
            if(v.num != (int)v.num){
                fprintf(stderr,
                        "Type error (line %d): cannot assign non-integer value %f to int variable '%s'\n",
                        yylineno, v.num, s->u.assign.var);
                type_error_count++;
                break;
            }
            set_num(s->u.assign.var, (int)v.num, VT_INT);
        } else if(t == VT_FLOAT){
            if(v.kind == VAL_STRING){
                fprintf(stderr,
                        "Type error (line %d): cannot assign string value to numeric variable '%s'\n",
                        yylineno, s->u.assign.var);
                type_error_count++;
                break;
            }
            set_num(s->u.assign.var, v.num, VT_FLOAT);
        }
        break;
    }

    case ST_SCAN: {
        char buf[1024];
        printf("Enter value for %s: ", s->u.scan.var);
        if(!fgets(buf, sizeof(buf), stdin)){
            fprintf(stderr, "Input error\n");
            type_error_count++;
            break;
        }
        size_t L = strlen(buf);
        if(L && buf[L-1] == '\n') buf[L-1] = '\0';

        Var *slot = get_var_slot(s->u.scan.var);
        VarType t = slot->type;

        int has_digit = 0, has_dot = 0;
        char *p = buf;
        if(*p == '+' || *p == '-') p++;
        while(*p){
            if(*p >= '0' && *p <= '9') has_digit = 1;
            else if(*p == '.'){
                if(has_dot){ has_dot = 2; break; }
                has_dot = 1;
            } else { has_digit = 0; break; }
            p++;
        }
        int is_num = has_digit && has_dot != 2;

        if(t == VT_STRING){
            set_str(s->u.scan.var, buf);
        } else if(is_num){
            double val = atof(buf);
            if(t == VT_UNDEF){
                if(has_dot) t = VT_FLOAT;
                else t = VT_INT;
            }
            if(t == VT_INT){
                if(val != (int)val){
                    fprintf(stderr,
                            "Type error (line %d): cannot assign non-integer input to int variable '%s'\n",
                            yylineno, s->u.scan.var);
                    type_error_count++;
                    break;
                }
                set_num(s->u.scan.var, (int)val, VT_INT);
            } else {
                set_num(s->u.scan.var, val, VT_FLOAT);
            }
        } else {
            if(t != VT_UNDEF && t != VT_STRING){
                fprintf(stderr,
                        "Type error (line %d): non-numeric input for numeric variable '%s'\n",
                        yylineno, s->u.scan.var);
                type_error_count++;
                break;
            }
            set_str(s->u.scan.var, buf);
        }
        break;
    }

    case ST_IF: {
        Value v = eval_value(s->u.if_stmt.cond);
        if(v.kind == VAL_STRING){
            fprintf(stderr,
                    "Type error (line %d): string used as condition\n",
                    yylineno);
            type_error_count++;
            break;
        }
        if((int)v.num)
            exec_stmt_list(s->u.if_stmt.then_branch);
        else if(s->u.if_stmt.else_branch)
            exec_stmt_list(s->u.if_stmt.else_branch);
        break;
    }

    case ST_FOR: {
        Var *slot = get_var_slot(s->u.for_stmt.var);
        if(slot->type == VT_UNDEF)
            set_num(s->u.for_stmt.var, 0.0, VT_INT);
        Value lim = eval_value(s->u.for_stmt.limit);
        if(lim.kind == VAL_STRING){
            fprintf(stderr,
                    "Type error (line %d): string used as loop limit\n",
                    yylineno);
            type_error_count++;
            break;
        }
        int limit = (int)lim.num;
        while((int)get_var_slot(s->u.for_stmt.var)->num < limit){
            exec_stmt_list(s->u.for_stmt.body);
            double now = get_var_slot(s->u.for_stmt.var)->num;
            set_num(s->u.for_stmt.var, now + 1.0, VT_INT);
        }
        break;
    }

    case ST_RETURN: {
        Value v = eval_value(s->u.ret.value);
        if(v.kind == VAL_STRING)
            printf("Return: %s\n", v.str ? v.str : "");
        else
            printf("Return: %g\n", v.num);
        exit(0);
    }
    }
}

void yyerror(const char *s){
    fprintf(stderr, "Parse error (line %d): %s\n", yylineno, s);
}

int main(int argc,char **argv){
    int i;
    for(i = 0; i < 256; i++){
        vars[i].type = VT_UNDEF;
        vars[i].num = 0.0;
        vars[i].str = NULL;
    }
    FILE *src = NULL;
    if(argc > 1){
        src = fopen(argv[1], "r");
        if(!src){
            perror("Cannot open source file");
            return 1;
        }
        yyin = src;
    } else {
        yyin = stdin;
    }
    if(yyparse() == 0)
        exec_stmt_list(root);

    if(type_error_count > 0){
        fprintf(stderr, "\nProgram finished with %d type error(s).\n", type_error_count);
    }

    if(src) fclose(src);
    return 0;
}

