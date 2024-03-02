#pragma once
#ifndef PARSER_H
#define PARSER_H

#endif // !PARSER_H
#include "../ast/ast.h"
#include "../lexer/lex_lexer.h"
#include "../utils/map.h"
typedef ast_expression prefix_parse_fn(void);
typedef ast_expression infix_parse_fn(ast_expression);

enum {
  LOWEST = 1,
  EQUALS,      // ==
  LESSGREATER, // < or >
  SUM,         // +
  PRODUCT,     // *
  PREFIX,      // -X or !X
  CALL,        // myFunc(X)
  INDEX
};

hashmap *precedences(void);

typedef struct parser {
  lex_lexer *lexer;
  tk_token current_token;
  tk_token peek_token;
  char **errors;
  hashmap *prefix_parse_fns;
  hashmap *infix_parse_fns;
} parser;
parser* parser_new(lex_lexer* lexer);

char **parser_errors(parser *p);
void parser_next_token(parser *p);
ast_program *parser_parse_program(parser *p);
ast_expression parser_parse_identifier(parser *p);
ast_return_statement *parser_parse_return_statement(parser *p);
ast_statement parser_parse_let_statement(parser *p);
ast_expression *parser_parse_expression_statement(parser *p);
ast_expression pasrser_parse_expression(parser *p, int precedence);
ast_expression parser_parse_integeral_literal(parser *p);
ast_expression parser_parse_boolean(parser *p);
ast_expression parser_parse_prefix_expression(parser *p);
ast_expression parser_parse_infix_expression(parser *p, ast_expression left);

ast_expression parser_parse_grouped_expression(parser *p);
ast_expression parser_parse_if_expression(parser *p);
ast_block_statement *parser_parse_block_statement(parser *p);
ast_expression parser_parse_function_literal(parser *p);
ast_identifier **parser_parse_function_parameters(parser *p);
ast_expression parser_parse_call_expression(parser *p, ast_expression function);
ast_expression *parser_parse_call_arguments(parser *p);
ast_expression parser_parse_string_literal(parser *p);
ast_expression parser_parse_array_literal(parser *p);
ast_expression *parser_parse_expression_list(parser *p, tk_token_type end);

ast_expression parser_parse_index_expression(parser *p, ast_expression left);

ast_expression parser_parse_hash_literal(parser *p);

bool parser_current_token_is(parser *p, tk_token_type t);
bool parser_peek_token_is(parser *p, tk_token_type t);
void parser_peek_error(parser *p, tk_token_type t);
bool parser_expect_peek(parser *p, tk_token_type t);
void parser_register_prefix(parser *p, tk_token_type t, prefix_parse_fn fn);
void parser_register_infix(parser *p, tk_token_type t, infix_parse_fn fn);
void parser_no_prefix_parse_fn_error(parser* p,tk_token_type t);
int parser_peek_precedence(parser* p);
int parser_current_precedence(parser* p);
