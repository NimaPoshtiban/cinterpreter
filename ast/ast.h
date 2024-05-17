#pragma once
#include "../token/tk_token.h"
#include <stdint.h>
#define AST_H

typedef struct ast_identifier 
{
	tk_token token;
	char* value;
}ast_identifier;

typedef struct ast_node {
	(char*)(*token_literal)(void);
	(char*)(*string)(void);
}ast_node;

typedef struct ast_expression {
	ast_node node;
	(void) (*expression_node)(void);
} ast_expression;

typedef struct ast_statement{
	ast_node node;
	(void)(*statement_node)(void);
}ast_statement;

typedef struct ast_program {
	ast_statement* statements;
};

typedef struct ast_let_statement{
	tk_token  token;
	ast_identifier name;
	ast_expression value;
}ast_let_statement;

typedef struct ast_return_statement{
	tk_token token;
	ast_expression return_value;
}ast_return_statement;

typedef struct ast_expression_statement{
	tk_token token;
	ast_expression expression;
}ast_expression_statement;

typedef struct ast_integer_literal {
	tk_token token;
	int64_t value;
}ast_integer_literal;

typedef struct ast_prefix_expression {
	tk_token token;
	char* op; // operator
	ast_expression right;

} ast_prefix_expression;

typedef struct ast_infix_expression {
	tk_token token;
	char* op; // operator
	ast_expression left;
	ast_expression right;
}ast_infix_expression;

typedef struct ast_index_expression {
	tk_token token;
	ast_expression left;
	ast_expression index;

}ast_index_expression;

typedef struct ast_boolean {
	tk_token token;
	bool value;
}ast_boolean;

typedef struct ast_block_statement {
	tk_token token;
	ast_statement* statements;
}ast_block_statement;

typedef struct ast_if_expression {
	tk_token token;
	ast_expression condition;
	ast_block_statement* consequence;
	ast_block_statement* alternative;
}ast_if_expression;

typedef struct ast_while_expression{
	tk_token token;
	ast_expression condition;
	ast_block_statement* body;
}ast_while_expression;

typedef struct ast_function_literal {
	tk_token token;
	ast_identifier* parameters;
	ast_block_statement* body;
}ast_function_literal;

typedef struct ast_call_expression {
	tk_token token;
	ast_expression function;
	ast_expression* arguments;
}ast_call_expression;

typedef struct ast_string_literal {
	tk_token token;
	char* value; 
}ast_string_literal;

typedef struct ast_array_literal {
	tk_token token;
	ast_expression* elements;
};

typedef struct ast_hash_literal{
	tk_token token;
	// implement a hashmap of ast_expression[ast_expression]
	// expressin_map pairs
}ast_hash_literal;