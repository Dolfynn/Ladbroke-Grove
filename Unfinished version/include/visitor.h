#ifndef VISITOR_H
#define VISITOR_H

#include "nodes.h" // Assuming this is where your node structures are defined
#include <stdio.h>

// Forward declarations of node structures
struct NumberTingNode;
struct DecimalTingNode;
struct IfNode;
struct IfElseNode;
struct WhileNode;
struct DoWhileNode;
struct PrintNode;
struct ScanNode;
struct BreakNode;
struct ArrayNode;
struct FunctionNode;
struct SizeofNode;
struct AssignmentNode;
struct BinaryOpNode;
struct IntLiteralNode;
struct FloatLiteralNode;
struct IdentifierNode;

// Function pointer types for visitor methods
typedef void (*VisitNumberTing)(struct Visitor*, struct NumberTingNode*);
typedef void (*VisitDecimalTing)(struct Visitor*, struct DecimalTingNode*);
typedef void (*VisitIfNode)(struct Visitor*, struct IfNode*);
typedef void (*VisitIfElseNode)(struct Visitor*, struct IfElseNode*);
typedef void (*VisitWhileNode)(struct Visitor*, struct WhileNode*);
typedef void (*VisitDoWhileNode)(struct Visitor*, struct DoWhileNode*);
typedef void (*VisitPrintNode)(struct Visitor*, struct PrintNode*);
typedef void (*VisitScanNode)(struct Visitor*, struct ScanNode*);
typedef void (*VisitBreakNode)(struct Visitor*, struct BreakNode*);
typedef void (*VisitArrayNode)(struct Visitor*, struct ArrayNode*);
typedef void (*VisitFunctionNode)(struct Visitor*, struct FunctionNode*);
typedef void (*VisitSizeofNode)(struct Visitor*, struct SizeofNode*);
typedef void (*VisitAssignmentNode)(struct Visitor*, struct AssignmentNode*);
typedef void (*VisitBinaryOpNode)(struct Visitor*, struct BinaryOpNode*);
typedef void (*VisitIntLiteralNode)(struct Visitor*, struct IntLiteralNode*);
typedef void (*VisitFloatLiteralNode)(struct Visitor*, struct FloatLiteralNode*);
typedef void (*VisitIdentifierNode)(struct Visitor*, struct IdentifierNode*);

// Visitor structure and function pointers for different node types
typedef struct Visitor {
    void (*visitNumberTing)(Visitor*, NumberTingNode*);
    void (*visitDecimalTing)(Visitor*, DecimalTingNode*);
    void (*visitIfNode)(Visitor*, IfNode*);
    void (*visitIfElseNode)(Visitor*, IfElseNode*);
    void (*visitWhileNode)(Visitor*, WhileNode*);
    void (*visitDoWhileNode)(Visitor*, DoWhileNode*);
    void (*visitPrintNode)(Visitor*, PrintNode*);
    void (*visitScanNode)(Visitor*, ScanNode*);
    void (*visitBreakNode)(Visitor*, BreakNode*);
    void (*visitArrayNode)(Visitor*, ArrayNode*);
    void (*visitFunctionNode)(Visitor*, FunctionNode*);
    void (*visitSizeofNode)(Visitor*, SizeofNode*);
    void (*visitAssignmentNode)(Visitor*, AssignmentNode*);
    void (*visitBinaryOpNode)(Visitor*, BinaryOpNode*);
    void (*visitIntLiteralNode)(Visitor*, IntLiteralNode*);
    void (*visitFloatLiteralNode)(Visitor*, FloatLiteralNode*);
    void (*visitIdentifierNode)(Visitor*, IdentifierNode*);
} Visitor; 

#endif // VISITOR_H

