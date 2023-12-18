#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "parser.h"
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
        case NODE_TYPE_FUNCTION_CALL:
            executeFunctionCall(node);
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



void executePrintStatement(ASTNode *node) {
    if (node->data.printStatement.argument->type == NODE_TYPE_EXPRESSION) {
        TokenType exprType = node->data.printStatement.argument->data.expression.expressionType;
        
        if (exprType == TOKEN_IDENTIFIER) {
        const char *varName = node->data.printStatement.argument->data.expression.value;
        for (int i = 0; i < 256; i++) {
            if (strcmp(variableNames[i], varName) == 0) {
                if (variableTypes[i] == TOKEN_INT) {
                    printf("%d\n", intVariables[i]);
                } else if (variableTypes[i] == TOKEN_LETTER) {
                    printf("%s\n", stringVariables[i]);
                }
                return;
            }
        }
        } else if (exprType == TOKEN_STRING_LITERAL) {
            printf("%s\n", node->data.printStatement.argument->data.expression.value);
        }
    }
}


void executeInputStatement(ASTNode *node) {
    char input[256];
    printf("%s", strlen(node->data.inputStatement.prompt) > 0 ? node->data.inputStatement.prompt : ": ");
    fflush(stdout);  // Ensure prompt is printed before input

    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;  // Remove newline character

        int varIndex = -1;
        for (int i = 0; i < 256; i++) {
            if (strcmp(variableNames[i], node->data.inputStatement.variableName) == 0) {
                varIndex = i;
                break;
            } else if (variableNames[i][0] == '\0') {
                strcpy(variableNames[i], node->data.inputStatement.variableName);
                varIndex = i;
                break;
            }
        }

        if (varIndex != -1) {
            // Check if the input is a number
            char *endPtr;
            long intVal = strtol(input, &endPtr, 10);

            if (*endPtr == '\0') {  // Input was a number
                intVariables[varIndex] = intVal;
                variableTypes[varIndex] = TOKEN_INT;
            } else {  // Input was not a number, so a string
                strcpy(stringVariables[varIndex], input);
                variableTypes[varIndex] = TOKEN_LETTER;
            }
        }
    }
}



void executeFunctionCall(ASTNode *node) {
    for (int i = 0; i < numFunctionDefinitions; i++) {
        if (strcmp(functionDefinitions[i]->data.function.name, node->data.functionCall.functionName) == 0) {
            executeAST(functionDefinitions[i]->data.function.body);
            break; // Ensure to break after finding and executing the function
        }
    }
}



