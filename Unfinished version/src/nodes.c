#include "nodes.h"
#include "visitor.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void initNumberTingNode(NumberTingNode* node, int value) {
    if (node != NULL) {
        node->base.accept = &acceptNumberTingNode; // Assume this function is defined elsewhere
        node->value = value;
    }
}

void acceptNumberTingNode(Node* base, Visitor* visitor) {
    if (base != NULL && visitor != NULL) {
        NumberTingNode* node = (NumberTingNode*)base;
        if (visitor->visitNumberTing != NULL) {
            visitor->visitNumberTing(visitor, node);
        }
    }
}   

// Implementations for other node types
void initDecimalTingNode(DecimalTingNode* node, float value) {
    node->base.accept = &acceptDecimalTingNode; // Define this function
    node->value = value;
}

void acceptDecimalTingNode(Node* base, Visitor* visitor) {
    DecimalTingNode* node = (DecimalTingNode*)base;
    if (visitor->visitDecimalTing != NULL) {
        visitor->visitDecimalTing(visitor, node);
    }
}


ArgumentListNode* createArgumentListNode(ExpressionNode* expression, ArgumentListNode* next) {
    ArgumentListNode* node = malloc(sizeof(ArgumentListNode));
    if (!node) { /* handle error */ }
    node->expression = expression;
    node->next = next;
    return node;
}

ParameterNode* createParameterNode(Type type, char* identifier) {
    ParameterNode* node = malloc(sizeof(ParameterNode));
    if (!node) { /* handle error */ }
    node->type = type;
    node->identifier = strdup(identifier); // remember to free later
    return node;
}

ParameterNode* appendParameterNode(ParameterNode* list, ParameterNode* newNode) {
    if (!list) return newNode;
    ParameterNode* current = list;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
    return list;
}

StatementListNode* createStatementListNode(StatementNode* statement, StatementListNode* next) {
    StatementListNode* node = malloc(sizeof(StatementListNode));
    if (node != NULL) {
        node->statement = statement;
        node->next = next;
    }
    return node;
}

#include "nodes.h"

// Function to append an ArgumentNode to an ArgumentListNode
ArgumentListNode* appendArgumentNode(ArgumentListNode* list, ArgumentListNode* newNode) {
    if (list == NULL) return newNode;

    ArgumentListNode* current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return list;
}

// Function to append a CaseNode to a CaseNode list
CaseNode* appendCaseNode(CaseNode* list, CaseNode* newNode) {
    if (list == NULL) return newNode;

    CaseNode* current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return list;
}

// Function to append a StatementNode to a StatementListNode
StatementListNode* appendStatementNode(StatementListNode* list, StatementNode* newNode) {
    if (list == NULL) {
        list = (StatementListNode*)malloc(sizeof(StatementListNode));
        list->statement = newNode;
        list->next = NULL;
        return list;
    }

    StatementListNode* current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (StatementListNode*)malloc(sizeof(StatementListNode));
    current->next->statement = newNode;
    current->next->next = NULL;
    return list;
}

// Function to create a new SwitchNode
SwitchNode* createSwitchNode(ExpressionNode* switchExpression, CaseNode* cases) {
    SwitchNode* node = (SwitchNode*)malloc(sizeof(SwitchNode));
    if (node == NULL) {
        // Handle the memory allocation failure
        fprintf(stderr, "Error allocating memory for SwitchNode\n");
        exit(EXIT_FAILURE);
    }
    node->switchExpression = switchExpression;
    node->cases = cases;
    return node;
}


CaseNode* createCaseNode(int value, StatementNode* statement, CaseNode* next) {
    CaseNode* node = malloc(sizeof(CaseNode));
    if (node != NULL) {
        node->value = value;
        node->statement = statement;
        node->next = next;
    }
    return node;
}

Node* createVariableNode(char* name, Type type) {
    VariableNode* node = malloc(sizeof(VariableNode));
    if (node != NULL) {
        node->name = strdup(name); // Copy the string
        node->type = type;
        // Initialize other members as needed
    }
    return node;
}

// Create a new If Node
IfNode* createIfNode(ExpressionNode* condition, StatementNode* trueBranch, StatementNode* falseBranch) {
    IfNode* node = (IfNode*)malloc(sizeof(IfNode));
    if (!node) {
        return NULL;
    }
    node->condition = condition;
    node->trueBranch = trueBranch;
    node->falseBranch = falseBranch;
    return node;
}

// Create a new If-Else Node
IfElseNode* createIfElseNode(ExpressionNode* condition, StatementNode* trueBranch, StatementNode* falseBranch) {
    IfElseNode* node = malloc(sizeof(IfElseNode));
    if (node != NULL) {
        node->condition = condition;
        node->trueBranch = trueBranch;
        node->falseBranch = falseBranch;
        // Additional initialization as required
    }
    return node;
}

// Create a new While Node
WhileNode* createWhileNode(ExpressionNode* condition, StatementNode* body) {
    WhileNode* node = (WhileNode*)malloc(sizeof(WhileNode));
    if (!node) {
        return NULL;
    }
    node->condition = condition;
    node->body = body;
    return node;
}

// Create a new Do-While Node
DoWhileNode* createDoWhileNode(StatementNode* body, ExpressionNode* condition) {
    DoWhileNode* node = (DoWhileNode*)malloc(sizeof(DoWhileNode));
    if (!node) {
        return NULL;
    }
    node->body = body;
    node->condition = condition;
    return node;
}

// Create a new Print Node
PrintNode* createPrintfNode(ArgumentListNode* arguments) {
    PrintNode* node = (PrintNode*)malloc(sizeof(PrintNode));
    if (!node) {
        return NULL;
    }
    node->arguments = arguments;
    return node;
}

// Create a new Scan Node
ScanNode* createScanfNode(ArgumentListNode* arguments) {
    ScanNode* node = (ScanNode*)malloc(sizeof(ScanNode));
    if (!node) {
        return NULL;
    }
    node->arguments = arguments;
    return node;
}

// Create a new Break Node
BreakNode* createBreakNode(void) {
    BreakNode* node = (BreakNode*)malloc(sizeof(BreakNode));
    if (!node) {
        return NULL;
    }
    return node;
}

// Create a new Array Node
ArrayNode* createArrayNode(char* name, int size) {
    ArrayNode* node = (ArrayNode*)malloc(sizeof(ArrayNode));
    if (!node) {
        return NULL;
    }
    node->name = strdup(name);
    node->size = size;
    return node;
}

// Create a new Function Node
FunctionNode* createFunctionNode(char* name, ParameterNode* parameters, StatementListNode* statements) {
    FunctionNode* node = (FunctionNode*)malloc(sizeof(FunctionNode));
    if (!node) {
        return NULL;
    }
    node->name = strdup(name);
    node->parameters = parameters;
    node->statements = statements;
    return node;
}

// Create a new Sizeof Node
SizeofNode* createSizeofNode(TypeNode* type) {
    SizeofNode* node = (SizeofNode*)malloc(sizeof(SizeofNode));
    if (!node) {
        return NULL;
    }
    node->type = type;
    return node;
}

// Create a new Assignment Node
AssignmentNode* createAssignmentNode(char* variableName, ExpressionNode* expression) {
    AssignmentNode* node = (AssignmentNode*)malloc(sizeof(AssignmentNode));
    if (!node) {
        return NULL;
    }
    node->variableName = strdup(variableName);
    node->expression = expression;
    return node;
}

// Create a new Binary Operation Node
BinaryOpNode* createBinaryOpNode(ExpressionNode* left, Operator op, ExpressionNode* right) {
    BinaryOpNode* node = (BinaryOpNode*)malloc(sizeof(BinaryOpNode));
    if (!node) {
        return NULL;
    }
    node->left = left;
    node->op = op;
    node->right = right;
    return node;
}

// Create a new Integer Literal Node
IntLiteralNode* createIntLiteralNode(int value) {
    IntLiteralNode* node = (IntLiteralNode*)malloc(sizeof(IntLiteralNode));
    if (!node) {
        return NULL;
    }
    node->value = value;
    return node;
}

// Create a new Float Literal Node
FloatLiteralNode* createFloatLiteralNode(float value) {
    FloatLiteralNode* node = (FloatLiteralNode*)malloc(sizeof(FloatLiteralNode));
    if (!node) {
        return NULL;
    }
    node->value = value;
    return node;
}

// Create a new Identifier Node
IdentifierNode* createIdentifierNode(char* name) {
    IdentifierNode* node = (IdentifierNode*)malloc(sizeof(IdentifierNode));
    if (!node) {
        return NULL;
    }
    node->name = strdup(name);
    return node;
}
