#ifndef NODES_H
#define NODES_H

#include <stdlib.h>
#include <stdio.h>

// Define types for your nodes
typedef enum {
    TYPE_INT,
    TYPE_CHAR,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_VOID
} Type;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
} Operator;


typedef struct Node Node;
typedef struct NumberTingNode NumberTingNode;
typedef struct DecimalTingNode DecimalTingNode;
typedef struct ArgumentListNode ArgumentListNode;
typedef struct ParameterNode ParameterNode;
typedef struct StatementNode StatementNode;
typedef struct StatementListNode StatementListNode;
typedef struct CaseNode CaseNode;
typedef struct VariableNode VariableNode;
typedef struct IfNode IfNode;
typedef struct IfElseNode IfElseNode;
typedef struct WhileNode WhileNode;
typedef struct DoWhileNode DoWhileNode;
typedef struct PrintNode PrintNode;
typedef struct ScanNode ScanNode;
typedef struct BreakNode BreakNode;
typedef struct ArrayNode ArrayNode;
typedef struct FunctionNode FunctionNode;
typedef struct SizeofNode SizeofNode;
typedef struct AssignmentNode AssignmentNode;
typedef struct BinaryOpNode BinaryOpNode;
typedef struct IntLiteralNode IntLiteralNode;
typedef struct FloatLiteralNode FloatLiteralNode;
typedef struct IdentifierNode IdentifierNode;
typedef struct ExpressionNode ExpressionNode;
typedef struct TypeNode TypeNode;
typedef struct Visitor Visitor;
typedef struct SwitchNode SwitchNode;

struct ArgumentListNode {
    ExpressionNode* expression;
    ArgumentListNode* next;
};

struct ParameterNode {
    Type type;
    char* identifier;
    ParameterNode* next;
};

typedef struct StatementListNode {
    StatementNode* statement;  // Assuming StatementNode is another struct you have defined
    struct StatementListNode* next;
} StatementListNode;

typedef struct CaseNode {
    int value;  // or the appropriate type for 'value'
    StatementNode* statement;  // Assuming StatementNode is a struct
    struct CaseNode* next;
} CaseNode;

typedef struct SwitchNode {
    ExpressionNode* switchExpression; // Expression the switch is based on
    CaseNode* cases; // Linked list of cases
} SwitchNode;

typedef struct VariableNode {
    Type type;  // Assuming Type is an enum or another type you have defined
    char* name;
    // Other members as needed
} VariableNode;

// Common Node structure for all AST nodes
typedef struct Node {
    void (*accept)(Node*, Visitor*);
}Node;

// NumberTingNode for integer values
struct NumberTingNode {
    Node base;
    int value;
};

// DecimalTingNode for floating-point values
struct DecimalTingNode {
    Node base;
    float value;
};

// IfNode for 'innit' construct
struct IfNode {
    Node base;
    ExpressionNode* condition;
    StatementNode* trueBranch;
    StatementNode* falseBranch;
};

struct IfElseNode {
    Node base;
    ExpressionNode* condition;
    StatementNode* trueBranch;
    StatementNode* falseBranch;
};

// WhileNode for 'whilengers' loop
struct WhileNode {
    Node base;
    ExpressionNode* condition;
    StatementNode* body;
};

// DoWhileNode for 'do-whilengers' loop
struct DoWhileNode {
    Node base;
    StatementNode* body;
    ExpressionNode* condition;
};

// PrintNode for 'waffle' function
struct PrintNode {
    Node base;
    ArgumentListNode* arguments;
};

// ScanNode for 'chat-to-man' function
struct ScanNode {
    Node base;
    ArgumentListNode* arguments;
};

// BreakNode for 'shush' statement
struct BreakNode {
    Node base;
};

// ArrayNode for 'mandem' arrays
struct ArrayNode {
    Node base;
    char* name;
    int size;
};

// FunctionNode for 'wagwan' function definitions
struct FunctionNode {
    Node base;
    char* name;
    ParameterNode* parameters;
    StatementListNode* statements;
};

// SizeofNode for 'chunker?' operation
struct SizeofNode {
    Node base;
    TypeNode* type;
};

// AssignmentNode for variable assignments
struct AssignmentNode {
    Node base;
    char* variableName;
    ExpressionNode* expression;
};

// BinaryOpNode for binary operations (like '+', '-', '*', '/')
struct BinaryOpNode {
    Node base;
    ExpressionNode* left;
    Operator op;
    ExpressionNode* right;
};

// IntLiteralNode for integer literals
struct IntLiteralNode {
    Node base;
    int value;
};

// FloatLiteralNode for float literals
struct FloatLiteralNode {
    Node base;
    float value;
};

// IdentifierNode for identifiers
struct IdentifierNode {
    Node base;
    char* name;
};



// ExpressionNode, StatementNode, ArgumentListNode, ParameterNode, StatementListNode, TypeNode
// These can be defined similarly based on their role in your language. 

// Function prototypes for node initializers and other functions
void initNumberTingNode(NumberTingNode* node, int value);
void acceptNumberTingNode(Node* base, Visitor* visitor);
void initDecimalTingNode(DecimalTingNode* node, float value);
void acceptDecimalTingNode(Node* base, Visitor* visitor);

// ... Prototypes for other node types and their functions
ArgumentListNode* createArgumentListNode(ExpressionNode* expression, ArgumentListNode* next);
ParameterNode* createParameterNode(Type type, char* identifier);
ParameterNode* appendParameterNode(ParameterNode* list, ParameterNode* newNode);
StatementListNode* createStatementListNode(StatementNode* statement, StatementListNode* next);
StatementListNode* appendStatementNode(StatementListNode* list, StatementNode* newNode);
CaseNode* createCaseNode(int value, StatementNode* statement, CaseNode* next);
CaseNode* appendCaseNode(CaseNode* list, CaseNode* newNode);
SwitchNode* createSwitchNode(ExpressionNode* switchExpression, CaseNode* cases);

Node* createVariableNode(char* name, Type type);
IfNode* createIfNode(ExpressionNode* condition, StatementNode* trueBranch, StatementNode* falseBranch);
IfElseNode* createIfElseNode(ExpressionNode* condition, StatementNode* trueBranch, StatementNode* falseBranch);
WhileNode* createWhileNode(ExpressionNode* condition, StatementNode* body);
DoWhileNode* createDoWhileNode(StatementNode* body, ExpressionNode* condition);
PrintNode* createPrintfNode(ArgumentListNode* arguments);
ScanNode* createScanfNode(ArgumentListNode* arguments);
BreakNode* createBreakNode(void);
ArrayNode* createArrayNode(char* name, int size);
FunctionNode* createFunctionNode(char* name, ParameterNode* parameters, StatementListNode* statements);
SizeofNode* createSizeofNode(TypeNode* type);
AssignmentNode* createAssignmentNode(char* variableName, ExpressionNode* expression);
BinaryOpNode* createBinaryOpNode(ExpressionNode* left, Operator op, ExpressionNode* right);
IntLiteralNode* createIntLiteralNode(int value);
FloatLiteralNode* createFloatLiteralNode(float value);
IdentifierNode* createIdentifierNode(char* name);
ArgumentListNode* createArgumentListNode(ExpressionNode* expression, ArgumentListNode* next);
ArgumentListNode* appendArgumentNode(ArgumentListNode* list, ArgumentListNode* newNode);

#endif // NODES_H
