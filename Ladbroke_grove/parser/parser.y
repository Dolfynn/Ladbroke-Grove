%{
#include "nodes.h"  // Includes the prototypes for node creation functions

extern int yylex();  // Lexer function
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);  // Error handling function
}
%}

%union {
    char* strval;   // For string values like identifiers
    int intval;     // For integer literals
    float floatval;
    Node* nodeval;  // For AST node pointers
}

%token <strval> IDENTIFIER
%token <floatval> FLOAT_LITERAL
%token <intval> INTEGER_LITERAL
%token NUMBERTING LETTERTING DECIMALTING BAREDIGITS NUING
%token INNIT INNIT_NAH MAINTING WHILENGERS DO_WHILENGERS WAFFLE CHAT_TO_MAN SHUSH MANDEM WAGWAN CHUNKER SIDETING
%token <intval> integer floating  // Tokens for number literals

%token RETURN AMPERSAND DEREFERENCE LINE_COMMENT BLOCK_COMMENT
%token EQUALS PLUS MINUS MULT DIV SEMI

%type <nodeval> program statement expression argument_list parameter_list statement_list case_statements
%type <intval> type_name

%%

program:
    statement { $$ = appendStatementNode($1, NULL); }
    ;


statement:
      NUMBERTING IDENTIFIER { $$ = createVariableNode($2, TYPE_INT); }
    | LETTERTING IDENTIFIER { $$ = createVariableNode($2, TYPE_CHAR); }
    | DECIMALTING IDENTIFIER { $$ = createVariableNode($2, TYPE_FLOAT); }
    | BAREDIGITS IDENTIFIER { $$ = createVariableNode($2, TYPE_DOUBLE); }
    | NUING IDENTIFIER { $$ = createVariableNode($2, TYPE_VOID); }
    | INNIT '(' expression ')' statement { $$ = createIfNode($3, $5, NULL); }
    | INNIT '(' expression ')' statement INNIT_NAH statement { $$ = createIfElseNode($3, $5, $7); }
    | MAINTING '(' expression ')' '{' case_statements '}' { $$ = createSwitchNode($3, $6); }
    | WHILENGERS '(' expression ')' statement { $$ = createWhileNode($3, $5); }
    | DO_WHILENGERS statement WHILENGERS '(' expression ')' { $$ = createDoWhileNode($2, $5); }
    | WAFFLE '(' argument_list ')' { $$ = createPrintfNode($3); }
    | CHAT_TO_MAN '(' argument_list ')' { $$ = createScanfNode($3); }
    | SHUSH { $$ = createBreakNode(); }
    | MANDEM IDENTIFIER '[' INTEGER_LITERAL ']' { $$ = createArrayNode($2, $4); }
    | WAGWAN IDENTIFIER '(' parameter_list ')' '{' statement_list '}' { $$ = createFunctionNode($2, $4, $7); }
    | CHUNKER '(' type_name ')' { $$ = createSizeofNode($3); }
    | IDENTIFIER '=' expression { $$ = createAssignmentNode($1, $3); }
    ;

expression:
      INTEGER_LITERAL { $$ = createIntLiteralNode($1); }
    | floating { $$ = createFloatLiteralNode($1); }
    | IDENTIFIER { $$ = createIdentifierNode($1); }
    | expression '+' expression { $$ = createBinaryOpNode($1, OP_ADD, $3); }
    | expression '-' expression { $$ = createBinaryOpNode($1, OP_SUB, $3); }
    | expression '*' expression { $$ = createBinaryOpNode($1, OP_MUL, $3); }
    | expression '/' expression { $$ = createBinaryOpNode($1, OP_DIV, $3); }
    | '(' expression ')' { $$ = $2; }
    ;

argument_list:
    expression { $$ = createArgumentListNode($1, NULL); }
    | argument_list ',' expression {
        ArgumentListNode* newArg = createArgumentListNode($3, NULL);
        $$ = appendArgumentNode($1, newArg);
        }
    ;

parameter_list:
    type_name IDENTIFIER { $$ = createParameterNode($1, $2); }
    | parameter_list ',' type_name IDENTIFIER { $$ = appendParameterNode($1, createParameterNode($3, $4)); }
    ;

statement_list:
    statement { $$ = createStatementListNode($1, NULL); }
    | statement_list statement { $$ = appendStatementNode((StatementListNode*)$1, (StatementNode*)$2); }
    ;

case_statements:
    SIDETING INTEGER_LITERAL ':' statement
    {
        $$ = createCaseNode($2, $4, NULL);  // Assuming no subsequent case node
    }
    | case_statements SIDETING INTEGER_LITERAL ':' statement
    {
        $$ = appendCaseNode($1, createCaseNode($3, $5, NULL)); // Again, assuming no subsequent case node
    }
    ;


type_name:
    NUMBERTING { $$ = TYPE_INT; }
   
