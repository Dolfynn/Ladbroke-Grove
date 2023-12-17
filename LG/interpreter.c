#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
// Include other headers as needed

int intVariables[256];  // Array to store integer values of variables
char stringVariables[256][256];  // Array to store string values of variables
char variableNames[256][256];  // Array to store names of variables
TokenType variableTypes[256];  // Array to store the type of each variable


void executeAST(ASTNode *node) {
    if (node == NULL) return;

    switch (node->type) {
        case NODE_TYPE_VARIABLE_DECLARATION:
            executeVariableDeclaration(node);
            break;
        case NODE_TYPE_PRINT_STATEMENT:
            executePrintStatement(node);
            break;
        case NODE_TYPE_INPUT_STATEMENT:
            executeInputStatement(node);
            break;
        // Add cases for other node types as needed
        default:
            // Handle other types or error
            break;
    }

    // Recursively execute the next node
    if (node->next != NULL) {
        executeAST(node->next);
    }
}

void executeVariableDeclaration(ASTNode *node) {
    int varIndex = -1;
    for (int i = 0; i < 256; i++) {
        if (strcmp(variableNames[i], node->data.variableDeclaration.name) == 0) {
            varIndex = i;
            break;
        } else if (variableNames[i][0] == '\0') {
            strcpy(variableNames[i], node->data.variableDeclaration.name);
            varIndex = i;
            break;
        }
    }

    if (varIndex != -1) {
        if (node->data.variableDeclaration.initializer->data.expression.expressionType == TOKEN_NUMBER) {
            intVariables[varIndex] = atoi(node->data.variableDeclaration.initializer->data.expression.value);
            variableTypes[varIndex] = TOKEN_INT; // Set type to integer
        } else if (node->data.variableDeclaration.initializer->data.expression.expressionType == TOKEN_STRING_LITERAL) {
            strcpy(stringVariables[varIndex], node->data.variableDeclaration.initializer->data.expression.value);
            variableTypes[varIndex] = TOKEN_LETTER; // Set type to string for 'letterting'
        }
    }
}



void executeInputStatement(ASTNode *node) {
    char inputBuffer[256];
    printf("Enter input: "); // Prompt for input
    fgets(inputBuffer, sizeof(inputBuffer), stdin);

    // Removing newline character from fgets input
    inputBuffer[strcspn(inputBuffer, "\n")] = 0;

    // Find the variable in the variable array and store the input
    for (int i = 0; i < 256; i++) {
        if (strcmp(variableNames[i], node->data.inputStatement.variableName) == 0) {
            if (variableTypes[i] == TOKEN_STRING_LITERAL) {
                strncpy(stringVariables[i], inputBuffer, sizeof(stringVariables[i]));
            } else if (variableTypes[i] == TOKEN_INT) {
                intVariables[i] = atoi(inputBuffer);  // Convert string to int if the variable is an integer
            }
            return;
        }
    }

    fprintf(stderr, "Runtime error: Variable '%s' not found\n", node->data.inputStatement.variableName);
}




void executePrintStatement(ASTNode *node) {
    // Check if the argument of the print statement is an expression
    if (node->data.printStatement.argument->type == NODE_TYPE_EXPRESSION) {
        // Determine the type of the expression
        TokenType exprType = node->data.printStatement.argument->data.expression.expressionType;

        // Handle the case where the expression is an identifier (variable)
        if (exprType == TOKEN_IDENTIFIER) {
            // Retrieve the name of the variable
            const char *varName = node->data.printStatement.argument->data.expression.value;

            // Search for the variable in the array of variable names
            for (int i = 0; i < 256; i++) {
                // Check if the current variable name matches
                if (strcmp(variableNames[i], varName) == 0) {
                    // Print the value of the variable based on its type
                    switch (variableTypes[i]) {
                        case TOKEN_INT:
                            // Print integer value
                            printf("%d", intVariables[i]);
                            break;
                        case TOKEN_STRING_LITERAL:
                            // Print string value
                            printf("%s", stringVariables[i]);
                            break;
                        // Add other cases for different token types if necessary
                    }
                    return; // Exit after printing
                }
            }
            // If the variable is not found, print an error message
            printf("Variable '%s' not found\n", varName);
        } 
        // Handle the case where the expression is a string literal
        else if (exprType == TOKEN_STRING_LITERAL) {
            // Print the string literal directly
            printf("%s", node->data.printStatement.argument->data.expression.value);
        }
        // Add cases to handle other expression types if necessary
    }
}







