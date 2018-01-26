/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "csgl.y"


#include "csgl.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <set>
#include <cassert>
#include <json/json.h>

//the following are UBUNTU/LINUX ONLY terminal color codes.
#ifdef _CSG_LINUX_
	#define RESET   "\033[0m"
	#define BLACK   "\033[30m"      /* Black */
	#define RED     "\033[31m"      /* Red */
	#define GREEN   "\033[32m"      /* Green */
	#define YELLOW  "\033[33m"      /* Yellow */
	#define BLUE    "\033[34m"      /* Blue */
	#define MAGENTA "\033[35m"      /* Magenta */
	#define CYAN    "\033[36m"      /* Cyan */
	#define WHITE   "\033[37m"      /* White */
	#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
	#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
	#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
	#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
	#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
	#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
	#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
	#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#else
	#define RESET   ""
	#define BLACK   ""      /* Black */
	#define RED     ""      /* Red */
	#define GREEN   ""      /* Green */
	#define YELLOW  ""      /* Yellow */
	#define BLUE    ""      /* Blue */
	#define MAGENTA ""      /* Magenta */
	#define CYAN    ""      /* Cyan */
	#define WHITE   ""      /* White */
	#define BOLDBLACK   ""      /* Bold Black */
	#define BOLDRED     ""      /* Bold Red */
	#define BOLDGREEN   ""      /* Bold Green */
	#define BOLDYELLOW  ""      /* Bold Yellow */
	#define BOLDBLUE    ""      /* Bold Blue */
	#define BOLDMAGENTA ""      /* Bold Magenta */
	#define BOLDCYAN    ""      /* Bold Cyan */
	#define BOLDWHITE   ""      /* Bold White */

#endif

using namespace std;

void csgInfo(std::string type,std::string s);

std::string toStr(int);


extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;

ofstream ofs;
ofstream ofscpp;

fstream  jsonfs;
ofstream  jsonofs;

// headfile content
CSGStream headDefStream;
CSGStream endDefStream;
CSGStream headIncludeStream;
CSGStream headfileContentStream;

//cppfile content
CSGStream cppContentStream;

//output info stream
CSGStream outputInfo;


//interface content
CSGStream headInterfaceStream;
CSGStream cppInterfaceStream;

bool globalError=false;

std::vector<std::string> structVec;


//唯一key,id等
MapStructId mapStructId;
MapStructName mapStructName;
MapInterfaceId mapInterfaceId;
MapInterfaceFileName mapInterfaceFileName;
std::string nowInputFile;

bool checkIsCsglType(std::string type,std::string msg){
	if(mapStructName.find(type)==mapStructName.end()){
		csgInfo(msg,type);
		globalError=true;
		assert(false);
	}
};



/* Line 371 of yacc.c  */
#line 178 "csgl.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "csgl.tab.h".  */
#ifndef YY_YY_CSGL_TAB_H_INCLUDED
# define YY_YY_CSGL_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_IFNDEF = 258,
     TOKEN_IFNDEF_END = 259,
     TOKEN_IFDEF = 260,
     TOKEN_IFDEF_END = 261,
     TOKEN_IFNDEF_FILE = 262,
     TOKEN_IFDEF_FILE = 263,
     TOKEN_ENDIF = 264,
     TOKEN_COMMENT_START = 265,
     TOKEN_COMMENT_END = 266,
     TOKEN_COMMENT_EX_START = 267,
     TOKEN_COMMENT_EX_END = 268,
     TOKEN_COMMENT_FILE = 269,
     TOKEN_COMMENT_EX_FILE = 270,
     TOKEN_INCLUDE_START = 271,
     TOKEN_INCLUDE_END = 272,
     TOKEN_INCLUDE_SIGN = 273,
     TOKEN_INCLUDE_FILE = 274,
     TOKEN_ENUM_START = 275,
     TOKEN_ENUM_CONTENT = 276,
     TOKEN_STRUCT_START = 277,
     TOKEN_STRUCT_END = 278,
     TOKEN_STRUCT_NAME = 279,
     TOKEN_STRUCT_CONTENT = 280,
     TOKEN_ID_START = 281,
     TOKEN_ID_END = 282,
     TOKEN_ID_NUM = 283,
     TOKEN_INTERFACE_END = 284,
     TOKEN_INTERFACE_ID_START = 285,
     TOKEN_INTERFACE_ID_NUM = 286,
     TOKEN_INTERFACE_ID_END = 287,
     TOKEN_INTERFACE_NAME = 288,
     TOKEN_INTERFACE_CONTENT = 289,
     TOKEN_INTERFACE_FUNCTION_NAME = 290
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_CSGL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 278 "csgl.tab.c"

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  26
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   45

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  18
/* YYNRULES -- Number of states.  */
#define YYNSTATES  38

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    12,    14,    16,    18,
      20,    23,    27,    31,    33,    37,    41,    46,    49
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    37,    38,    -1,    38,    -1,    40,    -1,
      41,    -1,    42,    -1,    43,    -1,    44,    -1,    39,    -1,
      33,    34,    -1,     3,     7,     4,    -1,     5,     8,     6,
      -1,     9,    -1,    10,    14,    11,    -1,    12,    15,    13,
      -1,    16,    18,    19,    17,    -1,    20,    21,    -1,    26,
      28,    27,    22,    24,    25,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   147,   147,   147,   149,   149,   149,   149,   149,   149,
     153,   872,   874,   876,   886,   888,   901,   911,   987
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_IFNDEF", "TOKEN_IFNDEF_END",
  "TOKEN_IFDEF", "TOKEN_IFDEF_END", "TOKEN_IFNDEF_FILE",
  "TOKEN_IFDEF_FILE", "TOKEN_ENDIF", "TOKEN_COMMENT_START",
  "TOKEN_COMMENT_END", "TOKEN_COMMENT_EX_START", "TOKEN_COMMENT_EX_END",
  "TOKEN_COMMENT_FILE", "TOKEN_COMMENT_EX_FILE", "TOKEN_INCLUDE_START",
  "TOKEN_INCLUDE_END", "TOKEN_INCLUDE_SIGN", "TOKEN_INCLUDE_FILE",
  "TOKEN_ENUM_START", "TOKEN_ENUM_CONTENT", "TOKEN_STRUCT_START",
  "TOKEN_STRUCT_END", "TOKEN_STRUCT_NAME", "TOKEN_STRUCT_CONTENT",
  "TOKEN_ID_START", "TOKEN_ID_END", "TOKEN_ID_NUM", "TOKEN_INTERFACE_END",
  "TOKEN_INTERFACE_ID_START", "TOKEN_INTERFACE_ID_NUM",
  "TOKEN_INTERFACE_ID_END", "TOKEN_INTERFACE_NAME",
  "TOKEN_INTERFACE_CONTENT", "TOKEN_INTERFACE_FUNCTION_NAME", "$accept",
  "program", "statement", "interface", "define_line", "comment", "include",
  "enum", "struct", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    38,    38,    38,    38,    38,    38,
      39,    40,    40,    40,    41,    41,    42,    43,    44
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     3,     1,     3,     3,     4,     2,     6
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    13,     0,     0,     0,     0,     0,     0,
       0,     3,     9,     4,     5,     6,     7,     8,     0,     0,
       0,     0,     0,    17,     0,    10,     1,     2,    11,    12,
      14,    15,     0,     0,    16,     0,     0,    18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    14,    15,    16,    17
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -22
static const yytype_int8 yypact[] =
{
      12,    -6,    -4,   -22,   -12,    -9,   -11,   -13,   -17,   -21,
       0,   -22,   -22,   -22,   -22,   -22,   -22,   -22,    10,    13,
       7,    14,     4,   -22,    -2,   -22,   -22,   -22,   -22,   -22,
     -22,   -22,    17,     8,   -22,     5,     6,   -22
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -22,   -22,    25,   -22,   -22,   -22,   -22,   -22,   -22
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      26,    18,    20,     1,    19,     2,    21,    22,    23,     3,
       4,    24,     5,    25,    28,     1,     6,     2,    30,    29,
       7,     3,     4,    32,     5,    33,     8,    31,     6,    36,
      35,    37,     7,     9,    34,    27,     0,     0,     8,     0,
       0,     0,     0,     0,     0,     9
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-22)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       0,     7,    14,     3,     8,     5,    15,    18,    21,     9,
      10,    28,    12,    34,     4,     3,    16,     5,    11,     6,
      20,     9,    10,    19,    12,    27,    26,    13,    16,    24,
      22,    25,    20,    33,    17,    10,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     9,    10,    12,    16,    20,    26,    33,
      37,    38,    39,    40,    41,    42,    43,    44,     7,     8,
      14,    15,    18,    21,    28,    34,     0,    38,     4,     6,
      11,    13,    19,    27,    17,    22,    24,    25
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

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

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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
  if (yypact_value_is_default (yyn))
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 3:
/* Line 1792 of yacc.c  */
#line 147 "csgl.y"
    {}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 149 "csgl.y"
    {}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 153 "csgl.y"
    {
	//classNameDef

	std::string interfaceName=(yyvsp[(1) - (2)].t_string);
	std::vector<CSGInterface> interfaceList=(yyvsp[(2) - (2)].tinterface_list);

	outputInfo<<"yacc match interface:"<<interfaceName<<"\n";
	//classNameDef
	std::string interfaceClassName=interfaceName;
	std::string srvCBprefix="CSrv_"+interfaceClassName+"_";
	std::string cliCBprefix="CCli_"+interfaceClassName+"_";

	std::string mNamespace="Message";
	std::string proxyNamespace="csg_proxy";

	//======================Server callBack start============== 服务器回调对象定义及实现
	CSGStream callBackDef;
	CSGStream cppCallBack;

	
	callBackDef<<"namespace "<<mNamespace<<"\n"
				<<"{\n";

	std::set<std::string> interfaceNameSet;

	for(int i=0;i<interfaceList.size();i++){
		CSGInterface tmp=interfaceList[i];
		std::string functionName=tmp.funcName;
		//check
		if(interfaceNameSet.count(functionName)>0){
			std::cerr<<"error interface function,duplicate function file:"<<interfaceName<<",identify:"<<functionName<<std::endl;
			globalError=true;
			assert(false);
		}
		interfaceNameSet.insert(functionName);
		//check
		MapInterfaceId::iterator rpcIdIter=mapInterfaceId.find(tmp.rpcId);
		if(rpcIdIter!=mapInterfaceId.end()){
			if(rpcIdIter->second.interfaceFile!=interfaceClassName||rpcIdIter->second.interface!=functionName){
				std::cout<<"rpcid:"<<tmp.rpcId<<" had already be use!"<<std::endl;
				globalError=true;
				assert(false);
			}
		}
		MapInterfaceFileName::iterator fileIter=mapInterfaceFileName.find(interfaceClassName);
		if(fileIter!=mapInterfaceFileName.end()){
			MapInterfaceName::iterator nameIt=fileIter->second.find(functionName);
			if(nameIt!=fileIter->second.end()){
				if(nameIt->second.rpcId!=tmp.rpcId){
				std::cout<<"interface functionName:"<<functionName<<" had already be use!"<<std::endl;
				globalError=true;
				assert(false);
				}
			}
		}


		CSGInterfaceKey tmpIkey;
		tmpIkey.rpcId=tmp.rpcId;
		tmpIkey.interface=functionName;
		tmpIkey.interfaceFile=interfaceClassName;
		mapInterfaceId[tmp.rpcId]=tmpIkey;
		mapInterfaceFileName[interfaceClassName][functionName]=tmpIkey;

		//class def
		std::string srvCB=srvCBprefix+functionName;
		std::string srvCBPtr=srvCB+"_Ptr";
		std::string cliCB=cliCBprefix+functionName;
		std::string cliCBPtr=cliCB+"_Ptr";

		callBackDef<<"	class "<<srvCB<<":public virtual CRMIObjectCallBackObject\n"
								<<"	{\n"
								<<"	public:\n"
								<<"		virtual void response(";
		cppCallBack<<"void Message::"<<srvCB<<"::response(";

		CSGStream cppCallBackWrite;

		bool isFirstOutParam=true;
		bool isFirstParam=true;
		CSGStream callBackStlWriteDef;
		CSGStream cppCallStlWriteBack;


		std::set<std::string> paramNameSet;
		for(int j=0;j<tmp.paramList.size();j++){
			CSGInterfaceParam param=tmp.paramList[j];
			bool isOut=param.isOut;
			std::string type=param.type;
			std::string identify=param.identify;
			//检测重复的参数
			if(paramNameSet.count(identify)>0){
				std::cerr<<"error interface function,duplicate param file:"<<interfaceName<<",identify:"<<functionName<<",param:"<<identify<<std::endl;
				globalError=true;
				assert(false);
			}
			paramNameSet.insert(identify);

			CSGStream tmpCallBack;

			if(isOut){
				if(!isFirstOutParam) //第一个回调参数前不需要加逗号
				{
					tmpCallBack<<",";		
				}
				if(isBaseType(param.type)){ //返回值类型参数为基础类型
					tmpCallBack<<"const "<<getCsglType(param.type)<<" "<<param.identify;
					cppCallBackWrite<<"	__os->write("<<param.identify<<");\n";
				}else if(CSGStlTypeOne==param.stlTypeNum){ //返回值类型参数为vector
					if(!isBaseType(param.stlType)){
						 //元素类型为自定义结构类型
						checkIsCsglType(param.stlType,"out param stl one is not a define struct");

						//额外的写方法(回调对象只需要写方法),命名规则=前缀+接口文件名+接口名+类型+元素类型+identify
						std::string classWriteName="__STL_TYPE_ONE__Interface__CSrv__Write__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.identify;

						callBackStlWriteDef<<"	class "<<classWriteName<<"{};\n"
											<<"	void __write(csg::CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&,"<<classWriteName<<");\n\n";
						cppCallStlWriteBack<<"void Message::__write(csg::CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& __data,"<<classWriteName<<")\n"
											<<"{\n"
											<<"	int size=__data.size();\n"
											<<"	__os.writeSize(size);\n"
											<<"	for(int i=0;i<size;i++)\n"
											<<"	{\n"
											<<"		__data[i]._csg_write(__os);\n"
											<<"	}\n"
											<<"};\n\n";
						cppCallBackWrite<<"	Message::__write(*__os,"<<param.identify<<","<<classWriteName<<"());\n";
					}else{
						cppCallBackWrite<<"	__os->write("<<param.identify<<");\n";
					}
					tmpCallBack<<"const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& "<<param.identify;

				}else if(CSGStlTypeDouble==param.stlTypeNum){
					if(!isBaseType(param.stlType)){
						 //元素类型为自定义结构类型
						checkIsCsglType(param.stlType,"out param stl double left key is not a define struct");
					}
					if(!isBaseType(param.stlTypeEx)){
						 //元素类型为自定义结构类型
						checkIsCsglType(param.stlTypeEx,"out param stl double right key is not a define struct");
					}

					//额外的写方法(回调对象只需要写方法),命名规则=前缀+接口文件名+接口名+类型+元素类型+identify
					std::string classWriteName="__STL_TYPE_ONE__Interface__CSrv__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;
					callBackStlWriteDef<<"	class "<<classWriteName<<"{};\n"
											<<"	void __write(csg::CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&,"<<classWriteName<<");\n\n";
					cppCallStlWriteBack<<"void Message::__write(csg::CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& __data,"<<classWriteName<<")\n"
										<<"{\n"
										<<"	int size=__data.size();\n"
										<<"	__os.writeSize(size);\n"
										<<"	for(std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">::const_iterator it=__data.cbegin();it!=__data.cend();++it)\n"
										<<"	{\n";
					if(!isBaseType(param.stlType)){
						 //元素类型为自定义结构类型
						cppCallStlWriteBack<<"		it->first._csg_write(__os);\n";
					}else{
						cppCallStlWriteBack<<"		__os.write(it->first);\n";
					}
					if(!isBaseType(param.stlTypeEx)){
						 //元素类型为自定义结构类型
						cppCallStlWriteBack<<"		it->second._csg_write(__os);\n";
					}else{
						cppCallStlWriteBack<<"		__os.write(it->second);\n";
					}
					
					cppCallStlWriteBack<<"	}\n"
										<<"};\n\n";

					cppCallBackWrite<<"	Message::__write(*__os,"<<param.identify<<","<<classWriteName<<"());\n";


					tmpCallBack<<"const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& "<<param.identify;
					
				}else{ //自定义结构体返回值

					checkIsCsglType(param.type,"interface unknow csgl struct type");
					tmpCallBack<<"const "<<getCsglType(param.type)<<"& "<<param.identify;

					cppCallBackWrite<<"	"<<param.identify<<"._csg_write(*__os);\n";
				}
				isFirstOutParam=false;
			}

			callBackDef<<tmpCallBack.content;
			cppCallBack<<tmpCallBack.content;
		}



		callBackDef<<");\n"
					<<"	};\n"
					<<"	typedef CSmartPointShare<"<<srvCB<<"> "<<srvCBPtr<<";\n\n";
		callBackDef<<callBackStlWriteDef.content;

		cppCallBack<<")\n"
					<<"{\n"
					<<"	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());\n"
					<<"	SRMIReturn rmiReturn;\n"
					<<"	rmiReturn.dispatchStatus = ERMIDispatchResultOk;\n"
					<<"	rmiReturn.messageId = _rmiCall.messageId;\n\n"
					<<"	CRpcHelper::prepareToReturn(_session,__os,rmiReturn);\n\n"
					<<"	__os->setUseBitMark(true);\n\n"
					<<cppCallBackWrite.content<<"\n"
					<<"	CRpcHelper::toReturn(_session,__os);\n\n"
					<<"}\n\n";	
		cppCallBack<<cppCallStlWriteBack.content;

	}

	callBackDef<<"}\n\n"<<"\n";
	
	headInterfaceStream<<callBackDef.content<<"\n";

	cppInterfaceStream<<cppCallBack.content;

	//*************************Server callBack end******************************

	//======================Server interface class struct and onCall Def start============== 服务器onCall函数+ rpc注册(cpp部分)

	CSGStream cppClassStruct;
	CSGStream cppClassOncall;

	
	cppClassStruct<<"Message::"<<interfaceClassName<<"::"<<interfaceClassName<<"()\n"
					<<"{\n"
					<<"	SRMIInfo rmiInfo;\n"
					<<"	rmiInfo.identify=\""<<interfaceClassName<<"\";\n\n";
	cppClassOncall<<"csg::ERMIDispatchResult Message::"<<interfaceClassName<<"::__onCall(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)\n"
					<<"{\n"
					<<"	switch(rmiCall.rpcId)\n"
					<<"	{\n";

	for(int i=0;i<interfaceList.size();i++){
		CSGInterface tmp=interfaceList[i];
		std::string functionName=tmp.funcName;
		outputInfo<<"functionName:"<<tmp.funcName<<",rpcid:"<<toStr(tmp.rpcId)<<"\n";

		//class def
		std::string srvCB=srvCBprefix+functionName;
		std::string srvCBPtr=srvCB+"_Ptr";
		std::string cliCB=cliCBprefix+functionName;
		std::string cliCBPtr=cliCB+"_Ptr";
		CSGStream cppProxyCallBackRead;
		CSGStream cppProxyCallBackParam;
		CSGStream cppProxyReturnParam;

		CSGStream cppProxyFunction;
		CSGStream cppProxyCallWrite;
	

		cppClassStruct<<"	rmiInfo.operation=\""<<functionName<<"\";\n"
						<<"	addRMIInfo("<<toStr(tmp.rpcId)<<",rmiInfo);\n"
						<<"	addRpcId("<<toStr(tmp.rpcId)<<");\n\n";
		cppClassOncall<<"		case "<<toStr(tmp.rpcId)<<":\n"
						<<"		{\n"
						<<"			return __"<<functionName<<"_async(session,rmiCall,__is);\n"
						<<"		}\n"
						<<"		break;\n";
	}
	cppClassStruct<<"}\n\n";	
	cppClassOncall<<"		default:\n"
					<<"		break;\n"
					<<"	}\n\n"
					<<"	return ERMIDispatchObjectNotExist;\n\n"
					<<"}\n\n";
		

	cppInterfaceStream<<cppClassStruct.content;
	cppInterfaceStream<<cppClassOncall.content;

	//*********************Server interface class struct  and onCall Def end*************

	//======================Server interface class start============== 服务器onCall函数+ rpc注册+rpc分发

	CSGStream classDef;
	CSGStream cppClassInterface;

	CSGStream functionDefStlWrite; //额外的读函数
	CSGStream functionCppStlWrite; //额外的读函数
	
	classDef<<"namespace "<<mNamespace<<"\n"
				<<"{\n"
				<<"	class "<<interfaceClassName<<":public virtual CRMIObject\n"
				<<"	{\n"
				<<"	public:\n"
				<<"		"<<interfaceClassName<<"();\n\n"
				<<"		virtual ERMIDispatchResult __onCall(const CSessionPtr&,const SRMICall&,CSerializeStream&);\n\n";

	for(int i=0;i<interfaceList.size();i++){
		CSGInterface tmp=interfaceList[i];
		std::string functionName=tmp.funcName;

		//class def
		std::string srvCB=srvCBprefix+functionName;  
		std::string srvCBPtr=srvCB+"_Ptr";
		std::string cliCB=cliCBprefix+functionName;
		std::string cliCBPtr=cliCB+"_Ptr";

		CSGStream functionDefStream;
		CSGStream cppClassProxyParam;


		functionDefStream<<"		ERMIDispatchResult __"<<functionName<<"_async("<<"const CSessionPtr&,const SRMICall&,CSerializeStream&);\n\n";
		functionDefStream<<"		virtual void "<<functionName<<"_async(const CSessionPtr& ,"<<mNamespace<<"::"<<srvCBPtr<<"&";

		cppClassInterface<<"csg::ERMIDispatchResult Message::"<<interfaceName<<"::__"<<functionName<<"_async(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)\n"
						<<"{\n";

		for(int j=0;j<tmp.paramList.size();j++){
			CSGInterfaceParam param=tmp.paramList[j];

			if(!param.isOut){
				if(isBaseType(param.type)){
					functionDefStream<<","<<getCsglType(param.type);
					cppClassInterface<<"	"<<getCsglType(param.type)<<" "<<param.identify<<";\n"
							<<"	__is.read("<<param.identify<<");\n";

				}else if(CSGStlTypeOne==param.stlTypeNum){

					functionDefStream<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&";

					cppClassInterface<<"	std::"<<param.type<<"<"<<getCsglType(param.stlType)<<"> "<<param.identify<<";\n";

					if(isBaseType(param.stlType)){
						cppClassInterface<<"	__is.read("<<param.identify<<");\n";

					}else{ //元素类型为自定义结构
						//命名规则=前缀+接口文件+接口名+类型+元素+identify
						std::string classWriteFunctionName="__STL_TYPE_ONE__Interface_CSrv__Read__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.identify;
						
						functionDefStlWrite<<"	class "<<classWriteFunctionName<<"{};\n"
											<<"	void __read(CSerializeStream&,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&,"<<classWriteFunctionName<<");\n\n";

						functionCppStlWrite<<"void Message::__read(CSerializeStream& __is,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& __data,"<<classWriteFunctionName<<")\n"
											<<"{\n"
											<<"	int size=0;\n"
											<<"	__is.readSize(size);\n"
											<<"	for(int i=0;i<size;i++)\n"
											<<"	{\n"
											<<"		"<<getCsglType(param.stlType)<<" val;\n"
											<<"		val._csg_read(__is);\n"
											<<"		__data.push_back(val);\n"
											<<"	}\n"
											<<"}\n\n";
						cppClassInterface<<"	Message::__read(__is,"<<param.identify<<","<<classWriteFunctionName<<"());\n";
					}
				}else if(CSGStlTypeDouble==param.stlTypeNum){
					functionDefStream<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&";
					cppClassInterface<<"	std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<"> "<<param.identify<<";\n";

					//map类均为自定义读函数
					//命名规则=前缀+接口文件+接口名+类型+元素1+元素2+identify
					std::string classWriteFunctionName="__STL_TYPE_DOUBLE__Interface_CSrv__Read__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;

					functionDefStlWrite<<"	class "<<classWriteFunctionName<<"{};\n"
											<<"	void __read(CSerializeStream&,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&,"<<classWriteFunctionName<<");\n\n";

					functionCppStlWrite<<"void Message::__read(CSerializeStream& __is,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& __data,"<<classWriteFunctionName<<")\n"
										<<"{\n"
										<<"	int size=0;\n"
										<<"	__is.readSize(size);\n"
										<<"	for(int i=0;i<size;i++)\n"
										<<"	{\n"
										<<"		"<<getCsglType(param.stlType)<<" key;\n";
					if(isBaseType(param.stlType)){
						functionCppStlWrite<<"		__is.read(key);\n";
					}else{
						functionCppStlWrite<<"		key._csg_read(__is);\n";
					}

					functionCppStlWrite<<"		"<<getCsglType(param.stlTypeEx)<<" val;\n";

					if(isBaseType(param.stlTypeEx)){
						functionCppStlWrite<<"		__is.read(val);\n";
					}else{
						functionCppStlWrite<<"		val._csg_read(__is);\n";
					}
					functionCppStlWrite<<"		__data[key]=val;\n"
										<<"	}\n"
										<<"}\n\n";

					cppClassInterface<<"	Message::__read(__is,"<<param.identify<<","<<classWriteFunctionName<<"());\n";

				}else{
					checkIsCsglType(param.type,"interface param error");
					functionDefStream<<",const "<<getCsglType(param.type)<<" &";
					cppClassInterface<<"	"<<getCsglType(param.type)<<" "<<param.identify<<";\n";
					cppClassInterface<<"	"<<param.identify<<"._csg_read(__is);\n";
				}

				cppClassProxyParam<<","<<param.identify;
			}
		}
		functionDefStream<<")=0;\n\n";

		classDef<<functionDefStream.content;


		cppClassInterface<<"	"<<srvCBPtr<<" cb=new "<<srvCB<<"();\n"
						<<"	cb->setSession(session,rmiCall);\n"
						<<"	"<<functionName<<"_async(session,cb"<<cppClassProxyParam.content<<");\n\n"
						<<"	return ERMIDispatchResultOk;\n\n"
						<<"}\n\n";
	}

	classDef<<"	};\n\n";
	classDef<<functionDefStlWrite.content;
	classDef<<"}\n";
	
	headInterfaceStream<<classDef.content<<"\n";


	cppInterfaceStream<<cppClassInterface.content;
	cppInterfaceStream<<functionCppStlWrite.content;


	//*************************Server interface class end******************************

	// 客户端部分使用代码
	//======================proxy callBack start============== //客户端回调对象

	CSGStream proxyCallBackDef;
	CSGStream cppProxyCallBack;

	
	proxyCallBackDef<<"namespace "<<proxyNamespace<<"\n"
					<<"{\n"
					<<"	using namespace Message;\n\n";

	for(int i=0;i<interfaceList.size();i++){
		CSGInterface tmp=interfaceList[i];
		std::string functionName=tmp.funcName;

		//class def
		std::string srvCB=srvCBprefix+functionName;
		std::string srvCBPtr=srvCB+"_Ptr";
		std::string cliCB=cliCBprefix+functionName;
		std::string cliCBPtr=cliCB+"_Ptr";

		CSGStream cppProxyCallBackParam;
		CSGStream cppProxyReturnParam;

		CSGStream functionDefStlRead; //额外的读函数
		CSGStream functionCppStlRead; //额外的读函数

		proxyCallBackDef<<"	class "<<cliCB<<":public virtual CRMIProxyCallBackObject\n"
						<<"	{\n"
						<<"	public:\n"
						<<"		virtual void response(";
		cppProxyCallBack<<"void csg_proxy::"<<cliCB<<"::__response(CSerializeStream& __is)\n"
						<<"{\n";


		bool isFirstOutParam=true;
		bool isFirstParam=true;
		
		for(int j=0;j<tmp.paramList.size();j++){
			CSGInterfaceParam param=tmp.paramList[j];

			if(param.isOut){
				if(!isFirstOutParam){
					proxyCallBackDef<<",";
					cppProxyReturnParam<<",";				
				}

				if(isBaseType(param.type)){
					proxyCallBackDef<<"const "<<getCsglType(param.type);

					cppProxyCallBackParam<<"	"<<getCsglType(param.type)<<" "<<param.identify<<";\n"
										<<"	__is.read("<<param.identify<<");\n";

				}else if(CSGStlTypeOne==param.stlTypeNum){
					proxyCallBackDef<<"const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& ";
					cppProxyCallBackParam<<"	std::"<<param.type<<"<"<<getCsglType(param.stlType)<<"> "<<param.identify<<";\n";
					if(isBaseType(param.stlType)){
						cppProxyCallBackParam<<"	__is.read("<<param.identify<<");\n";
					}else{
						//命名规则=前缀+接口文件+接口名+类型+元素+identify
						std::string classReadFunctionName="__STL_TYPE_ONE__Interface_CCli__Read__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.identify;

						functionDefStlRead<<"	class "<<classReadFunctionName<<" {};\n"
											<<"	void __read(CSerializeStream&,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&,"<<classReadFunctionName<<");\n\n";

						functionCppStlRead<<"void "<<proxyNamespace<<"::__read(CSerializeStream& __is,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& __data,"<<classReadFunctionName<<")\n"
											<<"{\n"
											<<"	int size=0;\n"
											<<"	__is.readSize(size);\n"
											<<"	for(int i=0;i<size;i++)\n"
											<<"	{\n"
											<<"		"<<getCsglType(param.stlType)<<" val;\n"
											<<"		val._csg_read(__is);\n"
											<<"		__data.push_back(val);\n"
											<<"	}\n"
											<<"}\n\n";

						cppProxyCallBackParam<<"	"<<proxyNamespace<<"::__read(__is,"<<param.identify<<","<<classReadFunctionName<<"());\n";
					}


					
				}else if(CSGStlTypeDouble==param.stlTypeNum){
					proxyCallBackDef<<"const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)
<<">&";
					cppProxyCallBackParam<<"	std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<"> "<<param.identify<<";\n";

					//命名规则=前缀+接口文件+接口名+类型+元素1+元素2+identify
					std::string classReadFunctionName="__STL_TYPE_DOUBLE__Interface_CCli__Read__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;

					functionDefStlRead<<"	class "<<classReadFunctionName<<" {};\n"
										<<"	void __read(CSerializeStream&,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&,"<<classReadFunctionName<<");\n\n";

					functionCppStlRead<<"void "<<proxyNamespace<<"::__read(CSerializeStream& __is,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& __data,"<<classReadFunctionName<<")\n"
										<<"{\n"
										<<"	int size=0;\n"
										<<"	__is.readSize(size);\n"
										<<"	for(int i=0;i<size;i++)\n"
										<<"	{\n"
										<<"		"<<getCsglType(param.stlType)<<" key;\n";
					
					if(isBaseType(param.stlType)){
						functionCppStlRead<<"		__is.read(key);\n";
					}else{
						functionCppStlRead<<"		key._csg_read(__is);\n";
					}
					functionCppStlRead<<"		"<<getCsglType(param.stlTypeEx)<<" val;\n";

					if(isBaseType(param.stlTypeEx)){
						functionCppStlRead<<"		__is.read(val);\n";
					}else{
						functionCppStlRead<<"		val._csg_read(__is);\n";
					}
					functionCppStlRead<<"		__data[key]=val;\n"
										<<"	}\n"
										<<"}\n\n";

					cppProxyCallBackParam<<"	"<<proxyNamespace<<"::__read(__is,"<<param.identify<<","<<classReadFunctionName<<"());\n";


				}else{ //自定义结构体
					checkIsCsglType(param.type,"client respond not define struct");
					proxyCallBackDef<<"const "<<getCsglType(param.type)<<"&";

					cppProxyCallBackParam<<"	"<<getCsglType(param.type)<<" "<<param.identify<<";\n"
										<<"	"<<param.identify<<"._csg_read(__is);\n";

				}
				isFirstOutParam=false;
				cppProxyReturnParam<<param.identify;
			}
		}
		proxyCallBackDef<<")=0;\n"
						<<"	protected:\n"
						<<"		virtual void __response(CSerializeStream& __is);\n"
						<<"	};\n"
						<<"	typedef CSmartPointShare<"<<cliCB<<"> "<<cliCBPtr<<";\n\n";

		proxyCallBackDef<<functionDefStlRead.content;

		cppProxyCallBack<<cppProxyCallBackParam.content
						<<"\n"
						<<"	response("<<cppProxyReturnParam.content<<");\n\n"
						<<"}\n\n";
		cppProxyCallBack<<functionCppStlRead.content;

	}

	proxyCallBackDef<<"}\n";
	
	headInterfaceStream<<proxyCallBackDef.content<<"\n";
	cppInterfaceStream<<cppProxyCallBack.content;
	//*************************proxy callBack end******************************


	//======================proxy class start============== //客户端调用接口

	CSGStream proxyClassDef;
	CSGStream cppProxyClass;
	CSGStream cppProxyFunction;

	
	proxyClassDef<<"namespace "<<proxyNamespace<<"\n"
					<<"{\n"
					<<"	using namespace Message;\n\n"
					<<"	class "<<interfaceClassName<<":public virtual CRMIProxyObject\n"
					<<"	{\n"
					<<"	public:\n"
					<<"		"<<interfaceClassName<<"();\n";
	cppProxyClass<<"csg_proxy::"<<interfaceClassName<<"::"<<interfaceClassName<<"()\n"
					<<"{\n"
					<<"}\n\n";

	CSGStream proxyWriteFunctionDef;
	CSGStream proxyWriteFunctionCpp;

	for(int i=0;i<interfaceList.size();i++){
		CSGInterface tmp=interfaceList[i];
		std::string functionName=tmp.funcName;

		//class def
		std::string srvCB=srvCBprefix+functionName;
		std::string srvCBPtr=srvCB+"_Ptr";
		std::string cliCB=cliCBprefix+functionName;
		std::string cliCBPtr=cliCB+"_Ptr";

		CSGStream cppProxyCallWrite;

		//proxy headfile code
		proxyClassDef<<"		void "<<functionName<<"_async(const CSessionPtr&,const "<<cliCBPtr<<"&";
		cppProxyFunction<<"void csg_proxy::"<<interfaceName<<"::"<<functionName<<"_async(const CSessionPtr& session,const "<<cliCBPtr<<"& cb";

		bool isFirstOutParam=true;
		bool isFirstParam=true;
		
		for(int j=0;j<tmp.paramList.size();j++){
			CSGInterfaceParam param=tmp.paramList[j];

			if(!param.isOut){
				if(isBaseType(param.type)){
					proxyClassDef<<",const "<<getCsglType(param.type);
					cppProxyFunction<<",const "<<getCsglType(param.type)<<" "<<param.identify;
					cppProxyCallWrite<<"	__os->write("<<param.identify<<");\n";
				}else if(CSGStlTypeOne==param.stlTypeNum){
					proxyClassDef<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&";
					cppProxyFunction<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& "<<param.identify;

					if(isBaseType(param.stlType)){
						cppProxyCallWrite<<"	__os->write("<<param.identify<<");\n";
					}else{
						//命名规则=前缀+接口文件+接口名+类型+元素+identify
						std::string classWriteFunctionName="__STL_TYPE_ONE__Interface_CCli__Write__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;

						proxyWriteFunctionDef<<"	class "<<classWriteFunctionName<<" {};\n"
												<<"	void __write(CSerializeStream&,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&,"<<classWriteFunctionName<<");\n\n";
						proxyWriteFunctionCpp<<"void csg_proxy::__write(CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& __data,"<<classWriteFunctionName<<")\n"
												<<"{\n"
												<<"	int size=__data.size();\n"
												<<"	__os.writeSize(size);\n"
												<<"	for(int i=0;i<size;i++)\n"
												<<"	{\n"
												<<"		__data[i]._csg_write(__os);\n"
												<<"	}\n"
												<<"}\n\n";

						cppProxyCallWrite<<"	csg_proxy::__write(*__os,"<<param.identify<<","<<classWriteFunctionName<<"());\n";
					}						


				}else if(CSGStlTypeDouble==param.stlTypeNum){
					proxyClassDef<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&";
					cppProxyFunction<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& "<<param.identify;

					//命名规则=前缀+接口文件+接口名+类型+元素1+元素2+identify
					std::string classWriteFunctionName="__STL_TYPE_DOUBLE__Interface_CCli__Write__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;

					proxyWriteFunctionDef<<"	class "<<classWriteFunctionName<<" {};\n"
												<<"	void __write(CSerializeStream&,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&,"<<classWriteFunctionName<<");\n\n";
					proxyWriteFunctionCpp<<"void csg_proxy::__write(CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& __data,"<<classWriteFunctionName<<")\n"
										<<"{\n"
										<<"	int size=__data.size();\n"
										<<"	__os.writeSize(size);\n"
										<<"	for(std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">::const_iterator it=__data.cbegin();it!=__data.end();++it)\n"
										<<"	{\n";
					if(isBaseType(param.stlType)){
						proxyWriteFunctionCpp<<"		__os.write(it->first);\n";
					}else{
						proxyWriteFunctionCpp<<"		it->first._csg_write(__os);\n";
					}

					if(isBaseType(param.stlTypeEx)){
						proxyWriteFunctionCpp<<"		__os.write(it->second);\n";
					}else{
						proxyWriteFunctionCpp<<"		it->second._csg_write(__os);\n";
					}

					proxyWriteFunctionCpp<<"	}\n"
											<<"}\n\n";


					cppProxyCallWrite<<"	csg_proxy::__write(*__os,"<<param.identify<<","<<classWriteFunctionName<<"());\n";
				}else{
					checkIsCsglType(param.type,"interface client call function param undefine");
					proxyClassDef<<",const "<<getCsglType(param.type)<<"&";
					cppProxyFunction<<",const "<<getCsglType(param.type)<<"& "<<param.identify;
					cppProxyCallWrite<<"	"<<param.identify<<"._csg_write(*__os);\n";
				}
			}
		}
		proxyClassDef<<");\n\n";
		cppProxyFunction<<")\n"
						<<"{\n"
						<<"	csg::SRMICall call;\n"
						<<"	call.rpcId="<<toStr(tmp.rpcId)<<";\n\n"
						<<"	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());\n"
						<<"	CRMIObjectBindPtr objectBind=NULL;\n"
						<<"	CRpcHelper::prepareToCall(session,__os,call,cb,objectBind);\n\n"
						<<"	__os->setUseBitMark(true);\n"
						<<cppProxyCallWrite.content<<"\n"
						<<"	CRpcHelper::toCall(session,__os,objectBind"<<");\n\n"
						<<"}\n\n";
	}

	proxyClassDef<<"	};\n\n"
				<<proxyWriteFunctionDef.content
				<<"}\n";
	
	
	headInterfaceStream<<proxyClassDef.content<<"\n";
	cppInterfaceStream<<cppProxyClass.content;
	cppInterfaceStream<<cppProxyFunction.content;
	cppInterfaceStream<<proxyWriteFunctionCpp.content;

	//**********************proxy class start end******************************

}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 872 "csgl.y"
    {
	headDefStream<<"#ifndef "<<(yyvsp[(2) - (3)].t_string)<<"\n";
}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 874 "csgl.y"
    {
	headDefStream<<"#define "<<(yyvsp[(2) - (3)].t_string)<<"\n";
}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 876 "csgl.y"
    {
	endDefStream<<(yyvsp[(1) - (1)].t_string)<<"\n";
}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 886 "csgl.y"
    {
	outputInfo<<"yacc match comment:"<<BOLDGREEN<<"//"<<(yyvsp[(2) - (3)].t_string)<<"\r"<<RESET<<"\n";
}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 888 "csgl.y"
    {
	outputInfo<<"yacc match commentex:"<<BOLDGREEN<<"/**"<<(yyvsp[(2) - (3)].t_string)<<"\r"<<RESET<<"\n";
}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 901 "csgl.y"
    {
	headIncludeStream<<"#include \""+(yyvsp[(3) - (4)].t_string)+"\"\n";
}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 911 "csgl.y"
    {
	
	std::string enumName=(yyvsp[(1) - (2)].t_string);
	int minEnumValue=999999;
	int maxEnumValue=-99999;
	int lastValue=-1;
	std::set<std::string> enumNameSet;
	//generated enum code
	CSGStream enumHeadfileStream;
	enumHeadfileStream<<"	enum "+enumName+" {\n";
	for(int i=0;i<(yyvsp[(2) - (2)].te_list).size();i++){
		CSGEnum tmp=(yyvsp[(2) - (2)].te_list)[i];
		if(enumNameSet.count(tmp.identify)>0){
			std::cerr<<"error enum value,duplicate enum identify:"<<enumName<<",identify:"<<tmp.identify<<std::endl;
			globalError=true;
			assert(false);
		}
		enumNameSet.insert(tmp.identify);

		enumHeadfileStream<<"		"<<tmp.identify;
		if(0!=tmp.value){
			enumHeadfileStream<<" = "<<toStr(tmp.value);
			if(lastValue>=tmp.value){
				std::cerr<<"error enum value,less than last one,enum name:"<<enumName<<",identify:"<<tmp.identify<<std::endl;
				globalError=true;
				assert(false);
			}
			lastValue=tmp.value;
		}else{
			lastValue++;
		}
		enumHeadfileStream<<",\n";
		minEnumValue=minEnumValue<lastValue?minEnumValue:lastValue;
		maxEnumValue=maxEnumValue>lastValue?maxEnumValue:lastValue;
	}
	enumHeadfileStream<<"	};\n\n";
	
	//generated serialize code
	enumHeadfileStream<<"	void _csg_write(CSerializeStream& __os,"<<enumName<<" __enumType);\n";
	enumHeadfileStream<<"	void _csg_read(CSerializeStream& __is,"<<enumName<<"& __enumType);\n";
	enumHeadfileStream<<"\n\n";
	
	headfileContentStream<<enumHeadfileStream.content;
	
	//generated cpp serialize code
	std::string typeName=maxEnumValue>255?"int":"byte_t";
	
	CSGStream enumCppStream;
	
	enumCppStream<<"void Message::_csg_write(CSerializeStream& __os,"<<enumName<<" __enumType){\n"
				<<"	__os.write(static_cast<"<<typeName<<">(__enumType));\n}\n\n";
	enumCppStream<<"void Message::_csg_read(CSerializeStream& __is,"<<enumName<<"& __enumType){\n"
				<<"	"<<typeName<<" value;\n"
				<<"	__is.read(value);\n"
				<<"	__enumType=static_cast<"<<enumName<<">(value);\n"
				<<"	if(__enumType>"<<toStr(maxEnumValue)<<"||__enumType<"<<toStr(minEnumValue)<<")\n"
				<<"	{\n"
				<<"		throw CException(\"ExceptionCodeSerialize\",ExceptionCodeSerialize);\n"
				<<"	}\n"
				<<"}\n\n";
	
	cppContentStream<<enumCppStream.content;

}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 987 "csgl.y"
    {
	std::string structName=(yyvsp[(5) - (6)].t_string);
	structVec.push_back(structName);
	int idNum=(yyvsp[(2) - (6)].id);

	//check
	MapStructId::iterator idIter=mapStructId.find(idNum);
	if(idIter!=mapStructId.end()){
		if(idIter->second.name!=structName||idIter->second.fileName!=nowInputFile){
			std::cout<<"struct id="<<idNum<<" had be used by "<<std::endl;
			globalError=true;
			assert(false);
		}
	}
	MapStructName::iterator nameIter=mapStructName.find(structName);
	if(nameIter!=mapStructName.end()){
		if(nameIter->second.id!=idNum||nameIter->second.fileName!=nowInputFile){
			std::cout<<"struct name="<<structName<<" had be used by "<<std::endl;
			globalError=true;
			assert(false);
		}
	}

	CSGStructKey tmpStructKey;
	tmpStructKey.id=idNum;
	tmpStructKey.name=structName;
	tmpStructKey.fileName=nowInputFile;
	mapStructId[idNum]=tmpStructKey;
	mapStructName[structName]=tmpStructKey;

	CSGStream structHeadfileStream;
	structHeadfileStream<<"	class "<<structName<<"\n"
						<<"		:public virtual csg::IMsgBase {\n"
						<<"	public:\n";

	//针对vector,map类型的成员变量,额外另生成方法读写
	CSGStream stlStructHeadStream;   //生成额外读写方法的头文件内容
	CSGStream stlStructCppStream;	//生成额外读写方法的cpp文件内容

	//每个结构体变量成员，都需要有 init,read,write,=,!=,< 这几个方法
	std::string initDef="	";		// _csg_init()函数内容
	std::string readDef;			// _csg_read()函数内容
	std::string writeDef;			// _csg_write()函数内容
	
	std::string operatorEq="	";
	std::string operatorEqEq;
	std::string operatorless;
	
	std::set<std::string> structNameSet; //判断结构体内同名的identify

	for(int i=0;i<(yyvsp[(6) - (6)].tstruct_list).size();i++){
		CSGStruct tmp=(yyvsp[(6) - (6)].tstruct_list)[i];
		if(structNameSet.count(tmp.identify)>0){
			std::cerr<<"error struct value,duplicate name:"<<structName<<",identify:"<<tmp.identify<<std::endl;
			globalError=true;
			assert(false);
		}
		structNameSet.insert(tmp.identify);

		if(isBaseType(tmp.type)){  //基础类型结构体成员变量

			structHeadfileStream<<"		"<<getCsglType(tmp.type)<<"  "<<tmp.identify<<";\n";  //类型显示处理  getCsglType

			initDef+=tmp.identify+"="+getInitTypeString(tmp.type)+";\n	"; //代码初始值根据类型初始化 getInitTypeString
			readDef+="	__is.read("+tmp.identify+");\n";
			writeDef+="	__os.write("+tmp.identify+");\n";

		}else if(CSGStlTypeOne==tmp.stlTypeNum){   // vector类结构体成员变量处理
			
			structHeadfileStream<<"		std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<"> "<<tmp.identify<<";\n";  //变量定义

			initDef+=tmp.identify+".clear();\n	"; 

			if(isBaseType(tmp.stlType)){
				readDef+="	__is.read("+tmp.identify+");\n";
				writeDef+="	__os.write("+tmp.identify+");\n";
			}else{ //vector类自定义结构体成员变量
				// vector<A> ai;
				// tmp.type=vector
				// tmp.stlType=A
				// tmp.identify=ai
				// check

				checkIsCsglType(tmp.stlType,"unknow csgl struct type from struct stl one");


				//函数命名规则= 前缀+结构体名+stl类型+stl内的元素类型+identify
				std::string classFunctionName="__STL_TYPE_ONE__Struct__"+structName+"__"+tmp.type+"__"+tmp.stlType+"__"+tmp.identify+"__Serialize";

				readDef+="	Message::__read(__is,"+tmp.identify+","+classFunctionName+"());\n";
				writeDef+="	Message::__write(__os,"+tmp.identify+","+classFunctionName+"());\n";

				stlStructHeadStream<<"	class "<<classFunctionName<<" {};\n"
								<<"	void __read(csg::CSerializeStream& __is,std::"<<tmp.type+"<"<<getCsglType(tmp.stlType)<<">"<<"&,"<<classFunctionName<<");\n"
								<<"	void __write(csg::CSerializeStream& __os,const std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<">&,"<<classFunctionName<<");\n\n";
				
				stlStructCppStream<<"void Message::__read(csg::CSerializeStream& __is,std::"<<tmp.type+"<"<<getCsglType(tmp.stlType)<<">"<<"& __data,"<<classFunctionName<<")\n"
									<<"{\n"
									<<"	int size=0;\n"
									<<"	__is.readSize(size);\n"
									<<"	for(int i=0;i<size;i++)\n"
									<<"	{\n"
									<<"		"<<tmp.stlType<<" val;\n"
									<<"		val._csg_read(__is);\n"
									<<"		__data.push_back(val);\n"
									<<"	}\n"
									<<"};\n\n"

									<<"void Message::__write(csg::CSerializeStream& __os,const std::"<<tmp.type<<"<"<<tmp.stlType<<">& __data,"<<classFunctionName<<")\n\n"
									<<"{\n"
									<<"	int size=__data.size();\n"
									<<"	__os.writeSize(size);\n"
									<<"	for(std::"<<tmp.type<<"<"<<tmp.stlType<<">::const_iterator it=__data.cbegin();it!=__data.cend();++it)\n"
									<<"	{\n"
									<<"		(*it)._csg_write(__os);\n"
									<<"	}\n"
									<<"};\n\n";				
			}


		}else if(CSGStlTypeDouble==tmp.stlTypeNum){ //map类结构体成员变量
			// map<A,B> ab;
			// tmp.type=map
			// tmp.stlType=A
			// tmp.stlTypeEx=B
			// tmp.identify=ab

			structHeadfileStream<<"		std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<"> "<<tmp.identify<<";\n";  //变量定义
			initDef+=tmp.identify+".clear();\n	"; 
			
			//函数命名规则= 前缀+结构体名+stl类型+stlEx类型+stl内的元素类型+identify
			std::string classFunctionName="__STL_TYPE_DOUBLE__Struct__"+structName+"__"+tmp.type+"__"+tmp.stlType+"__"+tmp.stlTypeEx+"__"+tmp.identify+"__Serialize";

			readDef+="	Message::__read(__is,"+tmp.identify+","+classFunctionName+"());\n";
			writeDef+="	Message::__write(__os,"+tmp.identify+","+classFunctionName+"());\n";


			stlStructHeadStream<<"	class "<<classFunctionName<<" {};\n"
								<<"	void __read(csg::CSerializeStream& __is,std::"<<tmp.type+"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<">"<<"&,"<<classFunctionName<<");\n"
								<<"	void __write(csg::CSerializeStream& __os,const std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<">&,"<<classFunctionName<<");\n\n";

			
			stlStructCppStream<<"void Message::__read(csg::CSerializeStream& __is,std::"<<tmp.type+"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<">"<<"& __data,"<<classFunctionName<<")\n"
								<<"{\n"
								<<"	int size=0;\n"
								<<"	__is.readSize(size);\n"
								<<"	for(int i=0;i<size;i++)\n"
								<<"	{\n"
								<<"		"<<getCsglType(tmp.stlType)<<" key;\n";

			//根据类型,使用不同的读方法
			if(isBaseType(tmp.stlType)){
				stlStructCppStream<<"		__is.read(key);\n";
			}else{
				//check
				checkIsCsglType(tmp.stlType,"unknow csgl struct type from struct stl double first key ");

				stlStructCppStream<<"		key._csg_read(__is);\n";
			}
					
			stlStructCppStream<<"		"<<getCsglType(tmp.stlTypeEx)<<" val;\n";

			//根据类型,使用不同的读方法
			if(isBaseType(tmp.stlTypeEx)){
				stlStructCppStream<<"		__is.read(val);\n";
			}else{
				//check
				checkIsCsglType(tmp.stlTypeEx,"unknow csgl struct type from struct stl double second key");

				stlStructCppStream<<"		val._csg_read(__is);\n";
			}

			stlStructCppStream<<"		__data[key]=val;\n"
								<<"	}\n"
								<<"};\n\n";

			stlStructCppStream<<"void Message::__write(csg::CSerializeStream& __os,const std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<">& __data,"<<classFunctionName<<")\n\n"
								<<"{\n"
								<<"	int size=__data.size();\n"
								<<"	__os.writeSize(size);\n"
								<<"	for(std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<">"<<"::const_iterator it=__data.cbegin();it!=__data.cend();++it)\n"
								<<"	{\n";
			//根据类型,使用不同的写方法
			if(isBaseType(tmp.stlType)){
				stlStructCppStream<<"		__os.write(it->first);\n";
			}else{
				stlStructCppStream<<"		it->first._csg_write(__os);\n";
			}
			//根据类型,使用不同的读方法
			if(isBaseType(tmp.stlTypeEx)){
				stlStructCppStream<<"		__os.write(it->second);\n";
			}else{
				stlStructCppStream<<"		it->second._csg_write(__os);\n";
			}
				
			stlStructCppStream<<"	}\n"
								<<"};\n\n";
		}
		else{ //自定义结构体成员变量
			checkIsCsglType(tmp.type,"unknow csgl struct type");

			structHeadfileStream<<"		"<<tmp.type<<"  "<<tmp.identify<<";\n";  //类型显示处理  getCsglType

			initDef+=tmp.identify+"._csg_init();\n	"; //代码初始值根据类型初始化 getInitTypeString

			readDef+="	"+tmp.identify+"._csg_read(__is);\n";
			writeDef+="	"+tmp.identify+"._csg_write(__os);\n";

		};

		//判断==的方法都是一样的
		operatorEq+=tmp.identify+" = "+"__other."+tmp.identify+";\n	";
		operatorEqEq+="	if("+tmp.identify+" !="+" __other."+tmp.identify+")\n"
						+"	{\n"
						+"		return true;\n"
						+"	}\n";
		operatorless+="	if("+tmp.identify+" <"+" __other."+tmp.identify+")\n"
						+"	{\n"
						+"		return true;\n"
						+"	}\n"
						+"	else if(__other."+tmp.identify+"<"+tmp.identify+")\n"
						+"	{\n"
						+"		return false;\n"
						+"	}\n";
	}
	
	structHeadfileStream<<"\n";
	structHeadfileStream<<"	public:\n"
						<<"		"<<structName<<"();\n"
						<<"		"<<structName<<"(const "<<structName<<" &);\n"
						<<"		"<<structName<<"& operator=(const "<<structName<<" &);\n";
	structHeadfileStream<<"\n";
	structHeadfileStream<<"	public:\n";
	structHeadfileStream<<"		bool operator==(const "<<structName<<" &)const;\n"
						<<"		bool operator!=(const "<<structName<<" &)const;\n"
						<<"		bool operator<(const "<<structName<<" &)const;\n\n"
						<<"		void _csg_init();\n"
						<<"		void _csg_read(CSerializeStream&);\n"
						<<"		void _csg_write(CSerializeStream&)const;\n\n"
						<<"		virtual IMsgBase* clone();\n"
						<<"		virtual int getType()const;\n";
	structHeadfileStream<<"	private:\n"
						<<"		static const int _msgType = "<<toStr(idNum)<<";\n";
						
	structHeadfileStream<<"	};\n\n";
	structHeadfileStream<<"	typedef csg::CSmartPointShare<"<<structName<<"> "<<structName<<"_Ptr;\n\n";
	
	headfileContentStream<<structHeadfileStream.content;
	headfileContentStream<<stlStructHeadStream.content;

	//generated cpp code
	CSGStream structCppStream;
	std::string constructioncpp="";

	//construcion
	structCppStream<<"Message::"<<structName<<"::"<<structName<<"()\n"
					<<"{\n"
					<<"	_csg_init();\n"
					<<"}\n\n";

	structCppStream<<"Message::"<<structName<<"::"<<structName<<"(const "<<structName<<"& __other)\n"
					<<"{\n"
					<<"	if(this==&__other)\n"
					<<"	{\n"
					<<"		return;\n"
					<<"	}\n"
					<<"	*this=__other;\n"
					<<"}\n\n";

	structCppStream<<"Message::"<<structName<<"& Message::"<<structName<<"::operator=(const "<<structName<<"& __other)\n"
					<<"{\n"
					<<"	if(this==&__other)\n"
					<<"	{\n"
					<<"		return *this;\n"
					<<"	}\n"
					<<"	IMsgBase::operator=(__other);\n"
					<<operatorEq
					<<"return *this;\n"
					<<"}\n\n";

	structCppStream<<"int Message::"<<structName<<"::getType()const{\n"
					<<"	return _msgType;\n"
					<<"}\n\n";
	
	structCppStream<<"csg::IMsgBase* Message::"<<structName<<"::clone()\n"
					<<"{\n"
					<<"	return new "<<structName<<"(*this);\n"
					<<"}\n\n";
				
	structCppStream<<"bool Message::"<<structName<<"::operator==(const "<<structName<<"& __other)const\n"
					<<"{\n"
					<<"	return !operator!=(__other);\n"
					<<"}\n\n";

	structCppStream<<"bool Message::"<<structName<<"::operator!=(const "<<structName<<"& __other)const\n"
					<<"{\n"
					<<"	if(this==&__other)\n"
					<<"	{\n"
					<<"		return false;\n"
					<<"	}\n"
					<<operatorEqEq
					<<"	return false;\n"
					<<"}\n\n";

	structCppStream<<"bool Message::"<<structName<<"::operator<(const "<<structName<<"& __other)const\n"
					<<"{\n"
					<<"	if(this==&__other)\n"
					<<"	{\n"
					<<"		return false;\n"
					<<"	}\n"
					<<operatorless
					<<"	return false;\n"
					<<"}\n\n";



	structCppStream<<"void Message::"<<structName<<"::_csg_init(){\n"
					<<initDef<<"\n};\n\n";	
	structCppStream<<"void Message::"<<structName<<"::_csg_read(CSerializeStream& __is){\n"
					<<readDef<<"};\n\n";
	structCppStream<<"void Message::"<<structName<<"::_csg_write(CSerializeStream& __os)const{\n"
					<<writeDef<<"};\n\n";
					
	structCppStream<<stlStructCppStream.content;

	cppContentStream<<structCppStream.content;
}
    break;


/* Line 1792 of yacc.c  */
#line 2679 "csgl.tab.c"
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2055 of yacc.c  */
#line 1316 "csgl.y"



std::string toStr(int i){
	std::stringstream ss;
	ss<<i;
	return ss.str();

};


void csgInfo(std::string type,std::string s){
	bool defineType=false;
	if(type=="ifndef"){
		//defineType=true ;
	}		
	
	bool unknowB=false;
	if("table"==type)
		unknowB=true;
	if("newline"==type)
		unknowB=true;
	if("blank"==type)
		unknowB=true;
	if("unknow"==type)
		unknowB=true;

	if(unknowB){
		//return ;
	
	}
	if(defineType){
		//return ;
	}
	
	//outputInfo<<YELLOW<<"csgl:"<<type<<","<<BOLDYELLOW<<"["<<s<<"]"<<RESET<<RESET<<"\n";
	std::cout<<YELLOW<<"csgl:"<<type<<","<<BOLDYELLOW<<"["<<s<<"]"<<RESET<<RESET<<"\n";
}

void csgOutputCppHead(std::string fileName){
	ofscpp<<"#include "<<"\""<<fileName+"\.h\"\n";
	ofscpp<<"#include \"engine/rpc/rpcHelper.h\"\n";
	ofscpp<<"using namespace csg;\n";
	ofscpp<<"using namespace Message;\n\n";
}


void csgOutputHead(){
	ofs<<csgDefStr<<"\n";
	ofs<<headDefStream.content<<"\n";
	ofs<<includeCsgFile<<"\n";
	ofs<<headIncludeStream.content<<"\n";
	ofs<<"using namespace csg;"<<"\n\n";
	ofs<<"namespace Message {"<<"\n\n";
	
}

void csgOutputEnd(std::string fileName){
	//regist struct
	std::string registClass="C"+fileName;
	ofs<<"	class "<<registClass<<"{\n"
		<<"	public:\n"
		<<"		static void regist();\n"
		<<"	};\n";
	ofs<<"\n}\n\n";//namespace

	//interface

	ofs<<headInterfaceStream.content<<"\n";

	ofs<<endDefStream.content<<"\n";

	CSGStream cppregistStream;
	cppregistStream<<"void Message::"<<registClass<<"::regist()\n"
					<<"{\n";
	for(int i=0;i<structVec.size();i++){
		cppregistStream<<"	csg::CMsgManager::instance()->regist(new "<<structVec[i]<<"());\n";
	}
	cppregistStream<<"}\n";
	cppContentStream<<cppregistStream.content;
}



void yyerror(const char* s){
	std::cerr<<"\033[31m"<<"get error:["<<s<<"]\033[0m"<<",line "<<yylineno<<std::endl;
	assert(false);
}

void csgReadJson(Json::Value& jsonInfo){
	
	for(Json::Value::iterator it=jsonInfo["struct"].begin();it!=jsonInfo["struct"].end();++it){
		CSGStructKey key;
		key.id=(*it)["id"].asInt();
		key.name=(*it)["name"].asString();
		key.fileName=(*it)["file"].asString();
		mapStructId[key.id]=key;
		mapStructName[key.name]=key;
	}
	for(Json::Value::iterator it=jsonInfo["interface"].begin();it!=jsonInfo["interface"].end();++it){
		CSGInterfaceKey key;
		key.rpcId=(*it)["rpcId"].asInt();
		key.interface=(*it)["name"].asString();
		key.interfaceFile=(*it)["file"].asString();
		mapInterfaceId[key.rpcId]=key;
		mapInterfaceFileName[key.interfaceFile][key.interface]=key;
	}
}


void rewriteJson(){
	jsonofs.open(jsonfile);
	if(!jsonofs.is_open()){
		std::cerr<<RED<<"can't open json_file by writer"<<jsonfile<<RESET<<std::endl;
		return ;
	}
	Json::Value rewriteJs;
	for(MapStructId::iterator it=mapStructId.begin();it!=mapStructId.end();++it){
		Json::Value tmpJs;
		tmpJs["id"]=it->second.id;
		tmpJs["name"]=it->second.name;
		tmpJs["file"]=it->second.fileName;
		rewriteJs["struct"].append(tmpJs);
	}
	for(MapInterfaceId::iterator it=mapInterfaceId.begin();it!=mapInterfaceId.end();++it){	
		Json::Value tmpJs;
		tmpJs["rpcId"]=it->second.rpcId;
		tmpJs["name"]=it->second.interface;
		tmpJs["file"]=it->second.interfaceFile;
		rewriteJs["interface"].append(tmpJs);
	}

	std::string rewriteStr=rewriteJs.toStyledString();
	jsonofs<<rewriteStr;
	jsonofs.flush();
	jsonofs.close();
	//std::cout<<"rewrite js="<<rewriteStr<<std::endl;
};


int main(int argc,char **argv){
	
	//get csl file
	if(argc<4){
		std::cerr<<RED<<"no enough param,first is csgl file ,next is outfile dir"<<RESET<<std::endl;
	}
	jsonfs.open(jsonfile);
	if(!jsonfs.is_open()){
		std::cerr<<RED<<"can't open json_file "<<jsonfile<<RESET<<std::endl;
		return 1;
	}
	std::string jsonStr,lineStr;
	Json::Value jsonInfo;
	while(getline(jsonfs,lineStr)){
		jsonStr.append(lineStr);
	}
	jsonfs.close();
	Json::Reader reader;
	if ( false == reader.parse(jsonStr ,jsonInfo) )
	{
		std::cerr<<RED<<"can't parse json_file "<<jsonfile<<RESET<<std::endl;
		return 1;
	}
	csgReadJson(jsonInfo);

	std::string inputfile(*(argv+3));
	nowInputFile=inputfile;
	std::cout<<"now inputfile is "<<nowInputFile<<std::endl;
	std::string inputfileName=inputfile+".csgl";
	std::string inputDir(*(argv+1));
	std::string outputDir(*(argv+2));
	std::string inputfileCsg=inputDir+inputfileName;
	std::string outputHeadFileName=outputDir+inputfile+".h";
	std::string outputCppFileName=outputDir+inputfile+".cpp";

	std::cout<<"input file is "<<YELLOW<<inputfileCsg<<RESET<<std::endl;
	std::cout<<"output dir is "<<YELLOW<<outputDir<<RESET<<std::endl;
	std::cout<<"output headfile is "<<GREEN<<outputHeadFileName<<RESET<<std::endl;
	std::cout<<"output cppfile is "<<GREEN<<outputCppFileName<<RESET<<std::endl;

	FILE *fp=fopen(inputfileCsg.c_str(),"r");
	if(NULL==fp){
		std::cerr<<RED<<"can't open file "<<inputfileCsg<<RESET<<std::endl;
		return 0;
	}
	
	ofs.open(outputHeadFileName);
	ofscpp.open(outputCppFileName);

	if(!ofs.is_open()){
		std::cerr<<RED<<"can't open file "<<outputHeadFileName<<RESET<<std::endl;
		return 0;
	}
	if(!ofscpp.is_open()){
		std::cerr<<RED<<"can't open file "<<outputCppFileName<<RESET<<std::endl;
		return 0;
	}

	yyin=fp;
	yyparse();
	fclose(fp);

	if(globalError){
		assert(false);
		return 1;
	}
	rewriteJson();

	std::cout<<GREEN<<"start generated head file "<<inputfileName<<RESET<<std::endl;
	//generated headfile
	csgOutputHead();
	ofs<<headfileContentStream.content<<std::endl;


	csgOutputEnd(inputfile);


	std::cout<<GREEN<<"start generated cpp file "<<inputfileName<<RESET<<std::endl;
	//generated cppfile
	csgOutputCppHead(inputfile);
	ofscpp<<cppContentStream.content<<std::endl;
	ofscpp<<cppInterfaceStream.content<<"\n";

	std::cout<<BOLDGREEN<<"build csgl file success!"<<RESET<<std::endl;
	
	ofs.close();
	ofscpp.close();
	return 0;
}



