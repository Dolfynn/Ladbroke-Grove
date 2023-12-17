#ifndef PARSER_H
#define PARSER_H

#include "lexer.h" // Include the lexer header


// AST Node Types
typedef enum {
    NODE_TYPE_FUNCTION,
    NODE_TYPE_EXPRESSION,
    NODE_TYPE_VARIABLE_DECLARATION,
    NODE_TYPE_PRINT_STATEMENT,
    NODE_TYPE_INPUT_STATEMENT,
    // Add more AST node types as needed
} NodeType;

// AST Node structure
typedef struct ASTNode {
    NodeType type;
    union {
        struct {
            char name[256]; // Function name
            struct ASTNode *body; // Function body
        } function;
        struct {
            char name[256]; // Variable name
            struct ASTNode *initializer; // Initializer expression
        } variableDeclaration;
        struct {
            struct ASTNode *argument; // Argument of the print statement
        } printStatement;
        struct {
            TokenType expressionType;
            char value[256]; // Value of the expression (number, identifier, or string literal)
        } expression;
        struct {
            char variableName[256];  // Variable to store the input
        } inputStatement;
    } data;
    struct ASTNode *next;
} ASTNode;

// Parser function prototypes
ASTNode *parseExpression(Token *tokens);
ASTNode *parseStatement();
ASTNode *parseFunctionDefinition();
ASTNode *parseProgram(Token *tokens, int tokenCount);
void printAST(ASTNode *node);
void freeAST(ASTNode *node);

extern int currentToken;
extern Token tokens[256];

#endif // PARSER_H
