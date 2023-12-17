#include "visitor.h"
#include <stdio.h>


// Implementation of the visitNumberTing function
void visitNumberTingNode(Visitor* visitor, NumberTingNode* node) {
    printf("Visited NumberTingNode with value: %d\n", node->value);
}


// Implementation of the visitDecimalTing function
void visitDecimalTingNode(Visitor* visitor, DecimalTingNode* node) {
    // Example operation on DecimalTingNode
    printf("Visited DecimalTingNode with value: %f\n", node->value);
}

// ... Implementations for other visit functions
