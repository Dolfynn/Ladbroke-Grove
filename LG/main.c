#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#define MAX_SOURCE_CODE_LENGTH 65536

int main() {
    // Buffer to hold the source code
    char *sourceCode = malloc(MAX_SOURCE_CODE_LENGTH);
    if (sourceCode == NULL) {
        fprintf(stderr, "Failed to allocate memory for source code.\n");
        return 1;
    }

    // The source file is hardcoded in the program
    const char *filename = "source_code.lg";

    // Open the source code file
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening source code file");
        free(sourceCode);
        return 1;
    }

    size_t bytesRead = fread(sourceCode, sizeof(char), MAX_SOURCE_CODE_LENGTH - 1, file);
    sourceCode[bytesRead] = '\0'; // Ensure null-termination
    fclose(file);

    // Tokenize the source code
    Token tokens[256];
    int tokenCount = 0;
    lex(sourceCode, tokens, &tokenCount);

    // Parse the tokens into an AST
    ASTNode *root = parseProgram(tokens, tokenCount);

    //printf("Tokens:\n");
    //for (int i = 0; i < tokenCount; i++) {
    //    printf("Token %d: Type: %d, Lexeme: '%s'\n", i, tokens[i].type, tokens[i].lexeme);
    //}
    printf("\nExecuting source code:\n");

    executeAST(root);
    freeAST(root);

    printf("\n");
    return 0;
}
