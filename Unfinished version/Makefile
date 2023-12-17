CC = gcc
CFLAGS = -I./include
BISON = bison
FLEX = flex
SRC_DIR = src
INC_DIR = include
PARSER_DIR = parser
OBJ_DIR = obj

# Define the parser and lexer outputs for dependencies
PARSER_C = $(SRC_DIR)/parser.c
PARSER_H = $(INC_DIR)/parser.tab.h
LEXER_C = $(SRC_DIR)/lexer.c

# Targets
all: $(OBJ_DIR) ladbroke_grove

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

ladbroke_grove: $(OBJ_DIR)/main.o $(OBJ_DIR)/nodes.o $(OBJ_DIR)/visitor.o $(OBJ_DIR)/parser.o $(OBJ_DIR)/lexer.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/nodes.o: $(SRC_DIR)/nodes.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/visitor.o: $(SRC_DIR)/visitor.c
	$(CC) $(CFLAGS) -c $< -o $@

# Parser target
$(OBJ_DIR)/parser.o: $(PARSER_C)
	$(CC) $(CFLAGS) -c $< -o $@

$(PARSER_C): $(PARSER_DIR)/parser.y
	$(BISON) --yacc --defines=$(PARSER_H) --output=$@ $^

# Lexer target depends on the parser
$(OBJ_DIR)/lexer.o: $(LEXER_C)
	$(CC) $(CFLAGS) -c $< -o $@

$(LEXER_C): $(PARSER_DIR)/lexer.l $(PARSER_H)
	$(FLEX) --outfile=$@ $<

clean:
	rm -rf $(OBJ_DIR)/*.o $(LEXER_C) $(PARSER_C) ladbroke_grove $(PARSER_H)






