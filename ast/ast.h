#pragma once
#include "../token/tk_token.h"
#include <stdint.h>
#define AST_H

typedef struct ast_node {
	(char*)(*token_literal)(void*);
	(char*)(*string)(void*);
}ast_node;

typedef struct ast_expression {
	ast_node node;
	(void) (*expression_node)(void*);
} ast_expression;

typedef struct ast_statement{
	ast_node node;
	(void)(*statement_node)(void*);

}ast_statement;

typedef struct ast_program {
	ast_statement* statements;
};

typedef struct ast_identifier
{
	tk_token token;
	char* value;
	(char*)(*token_literal)(ast_identifier*);
	(char*)(*string)(ast_identifier*);
	(void)(*expression_node)(ast_identifier*);
}ast_identifier;

typedef struct ast_let_statement{
	tk_token  token;
	ast_identifier name;
	ast_expression value;
	(void)(*statement_node)(ast_let_statement*);
	(char*)(*token_literal)(ast_let_statement*);
	(char*)(*string)(ast_let_statement*);
}ast_let_statement;

typedef struct ast_return_statement{
	tk_token token;
	ast_expression return_value;
	(void)(*statement_node)(ast_return_statement*);
	(char*)(*token_literal)(ast_return_statement*);
	(char*)(*string)(ast_return_statement*);
}ast_return_statement;

typedef struct ast_expression_statement{
	tk_token token;
	ast_expression expression;
	(void)(*statement_node)(ast_expression_statement*);
	(char*)(*token_literal)(ast_expression_statement*);
	(char*)(*string)(ast_expression_statement*);
}ast_expression_statement;

typedef struct ast_integer_literal {
	tk_token token;
	int64_t value;
	(void)(*expressionNode)(ast_integer_literal*);
	(char*)(*token_literal)(ast_integer_literal*);
	(char*)(*string)(ast_integer_literal*);
}ast_integer_literal;

typedef struct ast_prefix_expression {
	tk_token token;
	char* op; // operator
	ast_expression right;
	(void)(*expressionNode)(ast_prefix_expression*);
	(char*)(*token_literal)(ast_prefix_expression*);
	(char*)(*string)(ast_prefix_expression*);
} ast_prefix_expression;

typedef struct ast_infix_expression {
	tk_token token;
	char* op; // operator
	ast_expression left;
	ast_expression right;
	(void)(*expressionNode)(ast_infix_expression*);
	(char*)(*token_literal)(ast_infix_expression*);
	(char*)(*string)(ast_infix_expression*);
}ast_infix_expression;

typedef struct ast_index_expression {
	tk_token token;
	ast_expression left;
	ast_expression index;
	(void)(*expressionNode)(ast_index_expression*);
	(char*)(*token_literal)(ast_index_expression*);
	(char*)(*string)(ast_index_expression*);
}ast_index_expression;

typedef struct ast_boolean {
	tk_token token;
	bool value;
	(void)(*expressionNode)(ast_boolean*);
	(char*)(*token_literal)(ast_boolean*);
	(char*)(*string)(ast_boolean*);
}ast_boolean;

typedef struct ast_block_statement {
	tk_token token;
	ast_statement* statements;
	(void)(*statement_node)(ast_block_statement*);
	(char*)(*token_literal)(ast_block_statement*);
	(char*)(*string)(ast_block_statement*);
}ast_block_statement;

typedef struct ast_if_expression {
	tk_token token;
	ast_expression condition;
	ast_block_statement* consequence;
	ast_block_statement* alternative;
	(void)(*expressionNode)(ast_if_expression*);
	(char*)(*token_literal)(ast_if_expression*);
	(char*)(*string)(ast_if_expression*);
}ast_if_expression;

typedef struct ast_while_expression{
	tk_token token;
	ast_expression condition;
	ast_block_statement* body;
	(void)(*expressionNode)(ast_while_expression*);
	(char*)(*token_literal)(ast_while_expression*);
	(char*)(*string)(ast_while_expression*);
}ast_while_expression;

typedef struct ast_function_literal {
	tk_token token;
	ast_identifier* parameters;
	ast_block_statement* body;
	(void)(*expressionNode)(ast_function_literal*);
	(char*)(*token_literal)(ast_function_literal*);
	(char*)(*string)(ast_function_literal*);
}ast_function_literal;

typedef struct ast_call_expression {
	tk_token token;
	ast_expression function;
	ast_expression* arguments;
	(void)(*expressionNode)(ast_call_expression*);
	(char*)(*token_literal)(ast_call_expression*);
	(char*)(*string)(ast_call_expression*);
}ast_call_expression;

typedef struct ast_string_literal {
	tk_token token;
	char* value; 
	(void)(*expressionNode)(ast_string_literal*);
	(char*)(*token_literal)(ast_string_literal*);
	(char*)(*string)(ast_string_literal*);
}ast_string_literal;

typedef struct ast_array_literal {
	tk_token token;
	ast_expression* elements;
	(void)(*expressionNode)(ast_array_literal*);
	(char*)(*token_literal)(ast_array_literal*);
	(char*)(*string)(ast_array_literal*);
};

typedef struct ast_hash_literal{
	tk_token token;
	hashmap pairs;
	(void)(*expressionNode)(ast_hash_literal*);
	(char*)(*token_literal)(ast_hash_literal*);
	(char*)(*string)(ast_hash_literal*);
}ast_hash_literal;