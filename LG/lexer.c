#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// Function to check if a string matches a keyword
TokenType checkKeyword(char *str) {
    if (strcmp(str, "numberting") == 0) return TOKEN_INT;
    if (strcmp(str, "letterting") == 0) return TOKEN_CHAR;
    if (strcmp(str, "innit") == 0) return TOKEN_IF;
    if (strcmp(str, "innit-nah") == 0) return TOKEN_IF_ELSE;
    if (strcmp(str, "waffle") == 0) return TOKEN_PRINTF;
    if (strcmp(str, "chat-to-man") == 0) return TOKEN_SCANF;
    if (strcmp(str, "wagwan") == 0) return TOKEN_DEF;
    return TOKEN_IDENTIFIER;
}

Token tokens[256];  // Definition of the tokens array

// Lexical analysis function
void lex(const char *source, Token *tokens, int *tokenCount) {
    int i = 0, j = 0;
    while (source[i] != '\0') {
        if (isspace(source[i])) {
            i++; // Skip whitespace
        } else if (isalpha(source[i]) || (source[i] == '-' && isalpha(source[i+1]))) {
            // Handle keywords, identifiers, and hyphenated words
            int start = i;
            while (isalpha(source[i]) || (source[i] == '-' && isalpha(source[i+1]))) {
                i++;
            }
            strncpy(tokens[j].lexeme, source + start, i - start);
            tokens[j].lexeme[i - start] = '\0';
            tokens[j].type = checkKeyword(tokens[j].lexeme);
            j++;
        } else if (isdigit(source[i])) {
            // Handle numbers
            int start = i;
            while (isdigit(source[i])) i++;
            strncpy(tokens[j].lexeme, source + start, i - start);
            tokens[j].lexeme[i - start] = '\0';
            tokens[j].type = TOKEN_NUMBER;
            j++;
        } else if (source[i] == '\'') {
            // Handle string literals
            int start = ++i;
            while (source[i] != '\'' && source[i] != '\0') i++;
            if (source[i] == '\'') {
                strncpy(tokens[j].lexeme, source + start, i - start);
                tokens[j].lexeme[i - start] = '\0';
                tokens[j].type = TOKEN_STRING_LITERAL;
                i++;
            } else {
                fprintf(stderr, "Error: Unclosed string literal.\n");
            }
            j++;
        } else {
            // Handle single character tokens like '=', ':'
            switch (source[i]) {
                case '=':
                    tokens[j++] = (Token){TOKEN_EQUALS, "="};
                    break;
                case '{':
                    tokens[j++] = (Token){TOKEN_OPEN_BRACE, "{"};
                    break;
                case '}':
                    tokens[j++] = (Token){TOKEN_CLOSE_BRACE, "}"};
                    break;
                // Additional cases for other single character tokens
                default:
                    // Handle unrecognized characters
                    break;
            }
            i++;
        }
    }
    *tokenCount = j;
}

