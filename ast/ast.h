#pragma once
#include "../token/tk_token.h"
#include <stdint.h>
#include <stdbool.h>
#define AST_H
#define AST_MAX_BUFFER_SIZE  1024
typedef struct ast_node {
	char*(*token_literal)(void*);
	char*(*string)(void*);
}ast_node;

typedef struct ast_expression {
	ast_node node;
	void (*expression_node)(void*);
} ast_expression;

typedef struct ast_statement{
	ast_node node;
	void(*statement_node)(void*);

}ast_statement;

typedef struct ast_program {
	ast_statement* statements;
};

typedef struct ast_identifier
{
	tk_token token;
	char* value;
	char*(*token_literal)(struct ast_identifier*);
	char*(*string)(struct ast_identifier*);
}ast_identifier;

typedef struct ast_let_statement{
	tk_token  token;
	ast_identifier name;
	ast_expression value;
	char*(*token_literal)(struct ast_let_statement*);
	char*(*string)(struct ast_let_statement*);
}ast_let_statement;

typedef struct ast_return_statement{
	tk_token token;
	ast_expression return_value;
	char*(*token_literal)(struct ast_return_statement*);
	char*(*string)(struct ast_return_statement*);
}ast_return_statement;

typedef struct ast_expression_statement{
	tk_token token;
	ast_expression expression;
	char*(*token_literal)(struct ast_expression_statement*);
	char*(*string)(struct ast_expression_statement*);
}ast_expression_statement;

typedef struct ast_integer_literal {
	tk_token token;
	int64_t value;
	char*(*token_literal)(struct ast_integer_literal*);
	char*(*string)(struct ast_integer_literal*);
}ast_integer_literal;

typedef struct ast_prefix_expression {
	tk_token token;
	char* op; // operator
	ast_expression right;
	void(*expressionNode)(struct ast_prefix_expression*);
	char*(*token_literal)(struct ast_prefix_expression*);
	char*(*string)(struct ast_prefix_expression*);
} ast_prefix_expression;

typedef struct ast_infix_expression {
	tk_token token;
	char* op; // operator
	ast_expression left;
	ast_expression right;
	char*(*token_literal)(struct ast_infix_expression*);
	char*(*string)(struct ast_infix_expression*);
}ast_infix_expression;

typedef struct ast_index_expression {
	tk_token token;
	ast_expression left;
	ast_expression index;
	char*(*token_literal)(struct ast_index_expression*);
	char*(*string)(struct ast_index_expression*);
}ast_index_expression;

typedef struct ast_boolean {
	tk_token token;
	bool value;
	char*(*token_literal)(struct ast_boolean*);
	char*(*string)(struct ast_boolean*);
}ast_boolean;

typedef struct ast_block_statement {
	tk_token token;
	ast_statement* statements;
	char*(*token_literal)(struct ast_block_statement*);
	char*(*string)(struct ast_block_statement*);
}ast_block_statement;

typedef struct ast_if_expression {
	tk_token token;
	ast_expression condition;
	ast_block_statement* consequence;
	ast_block_statement* alternative;
	
	char*(*token_literal)(struct ast_if_expression*);
	char*(*string)(struct ast_if_expression*);
}ast_if_expression;

typedef struct ast_while_expression{
	tk_token token;
	ast_expression condition;
	ast_block_statement* body;
	char*(*token_literal)(struct ast_while_expression*);
	char*(*string)(struct ast_while_expression*);
}ast_while_expression;

typedef struct ast_function_literal {
	tk_token token;
	ast_identifier* parameters;
	ast_block_statement* body;
	char*(*token_literal)(struct ast_function_literal*);
	char*(*string)(struct ast_function_literal*);
}ast_function_literal;

typedef struct ast_call_expression {
	tk_token token;
	ast_expression function;
	ast_expression* arguments;
	char*(*token_literal)(struct ast_call_expression*);
	char*(*string)(struct ast_call_expression*);
}ast_call_expression;

typedef struct ast_string_literal {
	tk_token token;
	char* value; 
	char*(*token_literal)(struct ast_string_literal*);
	char*(*string)(struct ast_string_literal*);
}ast_string_literal;

typedef struct ast_array_literal {
	tk_token token;
	ast_expression* elements;
	char*(*token_literal)(struct ast_array_literal*);
	char*(*string)(struct ast_array_literal*);
}ast_array_literal;

typedef struct ast_hash_literal{
	tk_token token;
	hashmap pairs;
	char*(*token_literal)(struct ast_hash_literal*);
	char*(*string)(struct ast_hash_literal*);
}ast_hash_literal;

char* ast_identifier_token_literal(ast_identifier* ident);
char* ast_identifier_string(ast_identifier* ident);
ast_identifier ast_identifier_init(tk_token token, char* value);

char* ast_let_statement_token_literal(ast_let_statement* statement);
char* ast_let_statement_string (ast_let_statement* statement);
ast_let_statement ast_let_statement_init(tk_token token, ast_identifier name, ast_expression value);

char* ast_return_statement_token_literal(ast_return_statement* statement);
char* ast_return_statement_string(ast_return_statement* statement);
ast_return_statement ast_return_statement_init(tk_token token,ast_expression return_value);

char* ast_expression_statement_token_literal(ast_expression_statement* expr);
char* ast_expression_statement_string(ast_expression_statement* expr);
ast_expression_statement ast_expression_statement_init(tk_token token, ast_expression expr);

char* ast_integer_literal_token_literal(ast_integer_literal* il);
char* ast_integer_literal_string(ast_integer_literal* il);
ast_integer_literal  ast_integer_literal_init(tk_token token, int64_t value);