/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     FLOAT_LITERAL = 259,
     INTEGER_LITERAL = 260,
     NUMBERTING = 261,
     LETTERTING = 262,
     DECIMALTING = 263,
     BAREDIGITS = 264,
     NUING = 265,
     INNIT = 266,
     INNIT_NAH = 267,
     MAINTING = 268,
     WHILENGERS = 269,
     DO_WHILENGERS = 270,
     WAFFLE = 271,
     CHAT_TO_MAN = 272,
     SHUSH = 273,
     MANDEM = 274,
     WAGWAN = 275,
     CHUNKER = 276,
     SIDETING = 277,
     integer = 278,
     floating = 279,
     RETURN = 280,
     AMPERSAND = 281,
     DEREFERENCE = 282,
     LINE_COMMENT = 283,
     BLOCK_COMMENT = 284,
     EQUALS = 285,
     PLUS = 286,
     MINUS = 287,
     MULT = 288,
     DIV = 289,
     SEMI = 290
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define FLOAT_LITERAL 259
#define INTEGER_LITERAL 260
#define NUMBERTING 261
#define LETTERTING 262
#define DECIMALTING 263
#define BAREDIGITS 264
#define NUING 265
#define INNIT 266
#define INNIT_NAH 267
#define MAINTING 268
#define WHILENGERS 269
#define DO_WHILENGERS 270
#define WAFFLE 271
#define CHAT_TO_MAN 272
#define SHUSH 273
#define MANDEM 274
#define WAGWAN 275
#define CHUNKER 276
#define SIDETING 277
#define integer 278
#define floating 279
#define RETURN 280
#define AMPERSAND 281
#define DEREFERENCE 282
#define LINE_COMMENT 283
#define BLOCK_COMMENT 284
#define EQUALS 285
#define PLUS 286
#define MINUS 287
#define MULT 288
#define DIV 289
#define SEMI 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 11 "parser.y"
{
    char* strval;   // For string values like identifiers
    int intval;     // For integer literals
    float floatval;
    Node* nodeval;  // For AST node pointers
}
/* Line 1529 of yacc.c.  */
#line 126 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

