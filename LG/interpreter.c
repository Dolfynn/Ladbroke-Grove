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
    printf("Starting executeAST\n");
    switch (node->type) {
        printf("Node type: %d\n", node->type);
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
            if (node->next != NULL) {
                printf("Next node type after function call: %d\n", node->next->type);
            } else {
                printf("No next node after function call\n");
            }
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
    printf("Finishing executeAST\n");
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
                    printf("%d", intVariables[i]);
                } else if (variableTypes[i] == TOKEN_LETTER) {
                    printf("%s", stringVariables[i]);
                }
                return;
            }
        }
        } else if (exprType == TOKEN_STRING_LITERAL) {
            printf("%s", node->data.printStatement.argument->data.expression.value);
        }
    }
}


void executeInputStatement(ASTNode *node) {
    char input[256];
    printf("%s", node->data.inputStatement.variableName);
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;

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
            strcpy(stringVariables[varIndex], input);
            variableTypes[varIndex] = TOKEN_STRING_LITERAL; // Or appropriate type
        }
    }
}


void executeFunctionCall(ASTNode *node) {
    printf("Starting Function Call: %s\n", node->data.functionCall.functionName);
    for (int i = 0; i < numFunctionDefinitions; i++) {
        if (strcmp(functionDefinitions[i]->data.function.name, node->data.functionCall.functionName) == 0) {
            executeAST(functionDefinitions[i]->data.function.body);
            break; // Ensure to break after finding and executing the function
        }
    }
    printf("Ending Function Call: %s\n", node->data.functionCall.functionName);
}



