#ifndef LEXER_H
#define LEXER_H

// Token types
typedef enum {
    TOKEN_INT, //0
    TOKEN_CHAR,
    TOKEN_IF,
    TOKEN_IF_ELSE,
    TOKEN_PRINTF,
    TOKEN_SCANF, //5
    TOKEN_DEF,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_UNKNOWN,
    TOKEN_COLON, //10
    TOKEN_NEWLINE,
    TOKEN_STRING_LITERAL,
    TOKEN_EQUALS,
    TOKEN_LETTER, //14
    // Add more token types as needed
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char lexeme[256]; // Assuming a maximum lexeme length
} Token;

// Lexer function prototypes
TokenType checkKeyword(char *str);
void lex(const char *source, Token *tokens, int *tokenCount);

#endif // LEXER_H
