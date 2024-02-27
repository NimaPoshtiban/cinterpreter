#pragma once
#include "../token/tk_const.h"
#include "../token/tk_token.h"
#include "../utils/map.h"
#include <stdbool.h>
#ifndef AST_H
#define AST_H
#endif // !AST_Hj

typedef struct ast_node {
  char *(*ast_token_literal)(void);
  char *(*ast_string)(void);
} ast_node;

typedef struct ast_statement {
  ast_node *node;
  void (*ast_statement_node)(void);
} ast_statement;

typedef struct ast_expression {
  ast_node *node;
  void (*ast_expression_node)(void);
} ast_expression;

typedef struct ast_program {
  ast_statement *statements;
} ast_program;

char *ast_token_literal(ast_program *program);
char *ast_string(ast_program *program);

typedef struct ast_identifier {
  tk_token token;
  char *value;
} ast_identifier;

typedef struct ast_let_statement {
  tk_token token;
  ast_expression value;
  ast_identifier *name;
} ast_let_statement;

typedef struct ast_return_statement {
  tk_token token;
  ast_expression return_value;
} ast_return_statement;

typedef struct ast_expression_statement {
  tk_token tokenl;
  ast_expression expression;
} ast_expression_statement;

typedef struct ast_integeral_literal {
  tk_token tokenl;
  long long int value;
} ast_integeral_literal;

typedef struct ast_prefix_expression {
  tk_token token;
  char *_operator;
  ast_expression right;
} ast_prefix_expression;

typedef struct ast_infix_expression {
  tk_token token;
  char *_operator;
  ast_expression right;
  ast_expression left;
} ast_infix_expression;

typedef struct ast_index_expression {
  tk_token token;
  ast_expression left;
  ast_expression right;
} ast_index_expression;

typedef struct ast_boolean {
  tk_token token;
  bool value;
} ast_boolean;

typedef struct ast_block_statement {
  tk_token token;
  ast_statement *statements;
} ast_block_statement;

typedef struct ast_if_expression {
  tk_token token;
  ast_expression condition;
  ast_block_statement *Consequence;
  ast_block_statement *alternative;
} ast_if_expression;

typedef struct ast_function_literal {
  tk_token token;
  ast_expression function;
  ast_expression *arguments;
} ast_function_literal;

typedef struct ast_call_expression {
  tk_token token;
  ast_expression function;
  ast_expression *arguments;
} ast_call_expression;

typedef struct ast_string_literal {
  tk_token token;
  char *value;
} ast_string_literal;

typedef struct ast_array_literal {
  tk_token token;
  ast_expression *elements;
} ast_array_literal;

typedef struct ast_hash_literal {
  tk_token token;
  hashmap pairs;
} ast_hash_literal;
