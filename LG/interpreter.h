#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "parser.h" // Include this for ASTNode definitions

void executeAST(ASTNode *node);
void executePrintStatement(ASTNode *node);
void executeVariableDeclaration(ASTNode *node);
void executeInputStatement(ASTNode *node);
void executeFunctionCall(ASTNode *node);


#endif // EXECUTOR_H
