#pragma once
#include "../token/tk_token.h"
#include <stdbool.h>
#include <stdint.h>
#define AST_H
#define AST_MAX_BUFFER_SIZE 1024
#define AST_STATEMENT_LIMIT 25
typedef struct ast_node {
  char *(*token_literal)(void *);
  char *(*string)(void *);
} ast_node;

typedef struct ast_expression {
  ast_node node;
} ast_expression;

typedef struct ast_statement {
  ast_node node;
} ast_statement;

typedef struct ast_program {
  ast_statement *statements;
} ast_program;

typedef struct ast_identifier {
  tk_token token;
  char *value;
  char *(*token_literal)(struct ast_identifier *);
  char *(*string)(struct ast_identifier *);
} ast_identifier;

typedef struct ast_let_statement {
  tk_token token;
  ast_identifier *name;
  ast_expression *value;
  char *(*token_literal)(struct ast_let_statement *);
  char *(*string)(struct ast_let_statement *);
} ast_let_statement;

typedef struct ast_return_statement {
  tk_token token;
  ast_expression *return_value;
  char *(*token_literal)(struct ast_return_statement *);
  char *(*string)(struct ast_return_statement *);
} ast_return_statement;

typedef struct ast_expression_statement {
  tk_token token;
  ast_expression *expression;
  char *(*token_literal)(struct ast_expression_statement *);
  char *(*string)(struct ast_expression_statement *);
} ast_expression_statement;

typedef struct ast_integer_literal {
  tk_token token;
  int64_t value;
  char *(*token_literal)(struct ast_integer_literal *);
  char *(*string)(struct ast_integer_literal *);
} ast_integer_literal;

typedef struct ast_prefix_expression {
  tk_token token;
  char *op; // operator
  ast_expression *right;
  char *(*token_literal)(struct ast_prefix_expression *);
  char *(*string)(struct ast_prefix_expression *);
} ast_prefix_expression;

typedef struct ast_infix_expression {
  tk_token token;
  char *op; // operator
  ast_expression *left;
  ast_expression *right;
  char *(*token_literal)(struct ast_infix_expression *);
  char *(*string)(struct ast_infix_expression *);
} ast_infix_expression;

typedef struct ast_index_expression {
  tk_token token;
  ast_expression *left;
  ast_expression *index;
  char *(*token_literal)(struct ast_index_expression *);
  char *(*string)(struct ast_index_expression *);
} ast_index_expression;

typedef struct ast_boolean {
  tk_token token;
  bool value;
  char *(*token_literal)(struct ast_boolean *);
  char *(*string)(struct ast_boolean *);
} ast_boolean;

typedef struct ast_block_statement {
  tk_token token;
  ast_statement *statements;
  char *(*token_literal)(struct ast_block_statement *);
  char *(*string)(struct ast_block_statement *);
} ast_block_statement;

typedef struct ast_if_expression {
  tk_token token;
  ast_expression *condition;
  ast_block_statement *consequence;
  ast_block_statement *alternative;

  char *(*token_literal)(struct ast_if_expression *);
  char *(*string)(struct ast_if_expression *);
} ast_if_expression;

typedef struct ast_while_expression {
  tk_token token;
  ast_expression *condition;
  ast_block_statement *body;
  char *(*token_literal)(struct ast_while_expression *);
  char *(*string)(struct ast_while_expression *);
} ast_while_expression;

typedef struct ast_function_literal {
  tk_token token;
  ast_identifier *parameters;
  ast_block_statement *body;
  char *(*token_literal)(struct ast_function_literal *);
  char *(*string)(struct ast_function_literal *);
} ast_function_literal;

typedef struct ast_call_expression {
  tk_token token;
  ast_expression *function;
  ast_expression *arguments;
  char *(*token_literal)(struct ast_call_expression *);
  char *(*string)(struct ast_call_expression *);
} ast_call_expression;

typedef struct ast_string_literal {
  tk_token token;
  char *value;
  char *(*token_literal)(struct ast_string_literal *);
  char *(*string)(struct ast_string_literal *);
} ast_string_literal;

typedef struct ast_array_literal {
  tk_token token;
  ast_expression *elements;
  char *(*token_literal)(struct ast_array_literal *);
  char *(*string)(struct ast_array_literal *);
} ast_array_literal;

typedef struct ast_hash_literal {
  tk_token token;
  hashmap *pairs;
  char *(*token_literal)(struct ast_hash_literal *);
  char *(*string)(struct ast_hash_literal *);
} ast_hash_literal;

char *ast_identifier_token_literal(ast_identifier *ident);
char *ast_identifier_string(ast_identifier *ident);
ast_identifier ast_identifier_init(tk_token token, char *value);

char *ast_let_statement_token_literal(ast_let_statement *statement);
char *ast_let_statement_string(ast_let_statement *statement);
ast_let_statement ast_let_statement_init(tk_token token, ast_identifier *name,
                                         ast_expression *value);

char *ast_return_statement_token_literal(ast_return_statement *statement);
char *ast_return_statement_string(ast_return_statement *statement);
ast_return_statement ast_return_statement_init(tk_token token,
                                               ast_expression *return_value);

char *ast_expression_statement_token_literal(ast_expression_statement *expr);
char *ast_expression_statement_string(ast_expression_statement *expr);
ast_expression_statement ast_expression_statement_init(tk_token token,
                                                       ast_expression *expr);

char *ast_integer_literal_token_literal(ast_integer_literal *il);
char *ast_integer_literal_string(ast_integer_literal *il);
ast_integer_literal ast_integer_literal_init(tk_token token, int64_t value);

char *ast_prefix_expression_token_literal(ast_prefix_expression *expr);
char *ast_prefix_expression_string(ast_prefix_expression *expr);
ast_prefix_expression ast_prefix_expression_init(tk_token token, char *op,
                                                 ast_expression *right);
char *ast_infix_expression_token_literal(ast_infix_expression *expr);
char *ast_infix_expression_string(ast_infix_expression *expr);
ast_infix_expression ast_infix_expression_init(tk_token token, char *op,
                                               ast_expression *left,
                                               ast_expression *right);
char *ast_index_expression_token_literal(ast_index_expression *expr);
char *ast_index_expression_string(ast_index_expression *expr);
ast_index_expression ast_index_expression_init(tk_token token,
                                               ast_expression *left,
                                               ast_expression *index);

char *ast_boolean_token_literal(ast_boolean *b);
char *ast_boolean_string(ast_boolean *b);
ast_boolean ast_boolean_init(tk_token token, bool value);

char *ast_block_statement_literal(ast_block_statement *statement);
char *ast_block_statement_string(ast_block_statement *statement);
ast_block_statement ast_block_statement_init(tk_token token,
                                             ast_statement *statements);
char *ast_if_expression_token_literal(ast_if_expression *expr);
char *ast_if_expression_string(ast_if_expression *expr);
ast_if_expression ast_if_expression_init(tk_token token,
                                         ast_expression *condition,
                                         ast_block_statement *consequence,
                                         ast_block_statement *alternative);

char *ast_while_expression_token_literal(ast_while_expression *expr);
char *ast_while_expression_string(ast_while_expression *expr);
ast_while_expression ast_while_expression_init(tk_token token,
                                               ast_expression *condition,
                                               ast_block_statement *body);
char *ast_function_literal_token_literal(ast_function_literal *fn);
char *ast_function_literal_string(ast_function_literal *fn);
ast_function_literal ast_function_literal_init(tk_token token,
                                               ast_identifier *parameters,
                                               ast_block_statement *body);

char *ast_call_expression_token_literal(ast_call_expression *expr);
char *ast_call_expression_string(ast_call_expression *expr);
ast_call_expression ast_call_expression_init(tk_token token,
                                             ast_expression *function,
                                             ast_expression *arguments);
char *ast_string_literal_token_literal(ast_string_literal *li);
char *ast_string_literal_string(ast_string_literal *li);
ast_string_literal ast_string_literal_init(tk_token token, char *value);

char *ast_array_literal_token_literal(ast_array_literal *li);
char *ast_array_literal_string(ast_array_literal *li);
ast_array_literal ast_array_literal_init(tk_token token,
                                         ast_expression *elements);

char *ast_hash_literal_token_literal(ast_hash_literal *hl);
char *ast_hash_literal_string(ast_hash_literal *hl);
ast_hash_literal ast_hash_literal_init(tk_token token, hashmap *pairs);

// implement these functions
char *ast_node_token_literal(void *expr);
char *ast_node_string(void *expr);
ast_expression ast_expression_init(void);
ast_statement ast_statement_init(void);

char *ast_program_token_literal(ast_program *program);
char *ast_program_string(ast_program *program);
ast_program ast_program_init(ast_statement *statements);
