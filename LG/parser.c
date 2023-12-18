#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#define MAX_FUNCTIONS 256

int currentToken = 0; 
ASTNode *functionDefinitions[MAX_FUNCTIONS];
int numFunctionDefinitions = 0;


// Function to create a new AST node
ASTNode *createNode(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    memset(node, 0, sizeof(ASTNode));
    node->type = type;
    return node;
}

// Function to check if the current token matches an expected type
int match(TokenType expected) {
    if (tokens[currentToken].type == expected) {
        return 1;
    }
    return 0;
}

// Parsing functions

// Parse an expression (currently just numbers and identifiers for simplicity)
ASTNode *parseExpression(Token *tokens) {
    ASTNode *node = createNode(NODE_TYPE_EXPRESSION);
    if (tokens[currentToken].type == TOKEN_NUMBER || tokens[currentToken].type == TOKEN_IDENTIFIER || tokens[currentToken].type == TOKEN_STRING_LITERAL) {
        node->data.expression.expressionType = tokens[currentToken].type;
        strncpy(node->data.expression.value, tokens[currentToken].lexeme, sizeof(node->data.expression.value));
    }
    return node;
}

// Parse a variable declaration (e.g., "numberting x = 10")
ASTNode *parseVariableDeclaration(Token *tokens) {
    ASTNode *node = createNode(NODE_TYPE_VARIABLE_DECLARATION);
    currentToken++;  // Skip 'numberting'
    if (tokens[currentToken].type == TOKEN_IDENTIFIER) {
        strncpy(node->data.variableDeclaration.name, tokens[currentToken].lexeme, sizeof(node->data.variableDeclaration.name));
        currentToken++;  // Move to the next token
        if (tokens[currentToken].type == TOKEN_EQUALS) {
            currentToken++;  // Skip '='
            node->data.variableDeclaration.initializer = parseExpression(tokens);
        }
    }
    return node;
}

// Parse a print statement (e.g., "waffle 'message'")
ASTNode *parsePrintStatement(Token *tokens) {
    ASTNode *node = createNode(NODE_TYPE_PRINT_STATEMENT);
    currentToken++; // To skip the 'waffle'

    node->data.printStatement.argument = parseExpression(tokens);
    return node;
}

ASTNode *parseInputStatement(Token *tokens) {
    ASTNode *node = createNode(NODE_TYPE_INPUT_STATEMENT);
    currentToken++;  // Skip 'chat-to-man'

    // Check if next token is a string literal (prompt)
    if (tokens[currentToken].type == TOKEN_STRING_LITERAL) {
        strncpy(node->data.inputStatement.prompt, tokens[currentToken].lexeme, sizeof(node->data.inputStatement.prompt));
    } else {
        strcpy(node->data.inputStatement.prompt, "");  // No prompt provided
    }

    // Check for the variable name
    currentToken++;
    if (tokens[currentToken].type == TOKEN_IDENTIFIER) {
        strncpy(node->data.inputStatement.variableName, tokens[currentToken].lexeme, sizeof(node->data.inputStatement.variableName));
    }

    return node;
}


// Parse a function definition (e.g., "wagwan main():")
ASTNode *parseFunctionDefinition(Token *tokens) {
    ASTNode *node = createNode(NODE_TYPE_FUNCTION);
    currentToken++;  // Skip 'wagwan'

    if (tokens[currentToken].type == TOKEN_IDENTIFIER) {
        strncpy(node->data.function.name, tokens[currentToken].lexeme, sizeof(node->data.function.name));
        currentToken++;  // Move to the next token

        if (tokens[currentToken].type == TOKEN_OPEN_BRACE) {
            currentToken++;  // Skip '{'

            ASTNode *firstStatement = NULL;
            ASTNode *lastStatement = NULL;

            while (tokens[currentToken].type != TOKEN_CLOSE_BRACE) {
                ASTNode *statement = parseStatement(tokens);
                if (statement != NULL) {
                    if (firstStatement == NULL) {
                        firstStatement = statement;  // This is the first statement in the function body
                    } else {
                        lastStatement->next = statement;  // Link this statement to the previous one
                    }
                    lastStatement = statement;  // Update the last statement to the current one
                }
                currentToken++;
            }
            node->data.function.body = firstStatement;  // Set the body of the function
        }
    }

    // Store the function definition in the global list
    if (numFunctionDefinitions < MAX_FUNCTIONS) {
        functionDefinitions[numFunctionDefinitions++] = node;
    }

    return node;
}




ASTNode *parseFunctionCall(Token *tokens) {
    ASTNode *node = createNode(NODE_TYPE_FUNCTION_CALL);
    strncpy(node->data.functionCall.functionName, tokens[currentToken].lexeme, sizeof(node->data.functionCall.functionName));
    return node;
}



// Parse a general statement (could be a variable declaration, print statement, etc.)
ASTNode *parseStatement(Token *tokens) {
    if (tokens[currentToken].type == TOKEN_INT) {
        return parseVariableDeclaration(tokens);
    }if (tokens[currentToken].type == TOKEN_SCANF) {
        return parseInputStatement(tokens);
    }if (tokens[currentToken].type == TOKEN_PRINTF) {
        return parsePrintStatement(tokens);
    }if (tokens[currentToken].type == TOKEN_IDENTIFIER && tokens[currentToken+1].type == TOKEN_OPEN_BRACE) {
        return parseFunctionDefinition(tokens);
    } else if (tokens[currentToken].type == TOKEN_IDENTIFIER) {
        return parseFunctionCall(tokens);
    }
    // Add more cases as needed
    return NULL;
}

// Main parsing function (to be called from your main program)
ASTNode *parseProgram(Token *tokens, int tokenCount) {
    ASTNode *root = NULL;
    ASTNode *lastNode = NULL; // Keep track of the last node added to the AST

    while (currentToken < tokenCount && tokens[currentToken].type != TOKEN_UNKNOWN) {
        ASTNode *newNode = NULL;
        switch (tokens[currentToken].type) {
            case TOKEN_DEF:
                newNode = parseFunctionDefinition(tokens);
                break;
            case TOKEN_PRINTF:
                newNode = parsePrintStatement(tokens);
                break;
            case TOKEN_INT:
                newNode = parseVariableDeclaration(tokens);
                break;
            case TOKEN_CHAR:
                newNode = parseVariableDeclaration(tokens);
                break;
            case TOKEN_IF:
            case TOKEN_IF_ELSE:
            case TOKEN_SCANF:
                newNode = parseInputStatement(tokens);
                break;
            case TOKEN_NUMBER:
            case TOKEN_IDENTIFIER:
                newNode = parseFunctionCall(tokens);
                break;
            case TOKEN_NEWLINE:
            case TOKEN_STRING_LITERAL:
            case TOKEN_EQUALS:
            case TOKEN_LETTER:
            case TOKEN_OPEN_BRACE:
            case TOKEN_CLOSE_BRACE:
            case TOKEN_UNKNOWN:
                break;
            // Add more cases for other statements
        }

        if (newNode != NULL) {
            if (root == NULL) {
                root = newNode; // First node becomes the root
            } else {
                lastNode->next = newNode; // Link the new node to the last node in the AST
            }
            lastNode = newNode; // Update the last node to the new node
        }
        currentToken ++;
    }

    return root;
}


void freeAST(ASTNode *node) {
    if (node == NULL) return;

    // Recursively free child nodes depending on the node type
    switch (node->type) {
        case NODE_TYPE_FUNCTION:
            freeAST(node->data.function.body);
            break;
        case NODE_TYPE_VARIABLE_DECLARATION:
            freeAST(node->data.variableDeclaration.initializer);
            break;
        case NODE_TYPE_PRINT_STATEMENT:
            freeAST(node->data.printStatement.argument);
            break;
        case NODE_TYPE_EXPRESSION:
            break;
        case NODE_TYPE_INPUT_STATEMENT:
            break;
        case NODE_TYPE_FUNCTION_CALL:
            break;
        // ... other cases as needed ...
    }

    if (node->next) {
        freeAST(node->next);
    }

    free(node); // Free the node itself
}


