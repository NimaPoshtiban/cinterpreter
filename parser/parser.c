#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
hashmap *precedences(void) {
  hashmap *map = hashmap_create();
  hashmap_add(map, TK_EQ, (char *)EQUALS);
  hashmap_add(map, TK_NOT_EQ, (char *)EQUALS);
  hashmap_add(map, TK_LT, (char *)LESSGREATER);
  hashmap_add(map, TK_GT, (char *)LESSGREATER);
  hashmap_add(map, TK_PLUS, (char *)SUM);
  hashmap_add(map, TK_MINUS, (char *)SUM);
  hashmap_add(map, TK_SLASH, (char *)PRODUCT);
  hashmap_add(map, TK_ASTERISK, (char *)PRODUCT);
  hashmap_add(map, TK_LPAREN, (char *)CALL);
  hashmap_add(map, TK_LBRACKET, (char *)INDEX);
  return map;
}

int parser_current_precedence(parser *p) {
  hashmap *precedence = precedences();
  char *value = hashmap_find(precedence, p->current_token.tk_type);
  if (value != 0) {
    return atoi(value);
  }
  return LOWEST;
}

char **parser_errors(parser *p) { return p->errors; }
void parser_next_token(parser *p) {
  p->current_token = p->peek_token;
  p->peek_token = lex_next_token(p->lexer, tk_keywords());
}
int parser_peek_precedence(parser *p) {
  hashmap *precedence = precedences();
  char *value = hashmap_find(precedence, p->peek_token.tk_type);
  if (value != 0) {
    return atoi(value);
  }
  return LOWEST;
}

void parser_no_prefix_parse_fn_error(parser *p, tk_token_type t) {
  char *message = malloc(sizeof(char) * ERROR_MESSAGE_LENGTH);
  int val = sprintf_s(message, ERROR_MESSAGE_LENGTH,
                      "no prefix parse function for %s found.\n", t);
  if (val < 0) {
    exit(EXIT_FAILURE);
  }
  strcpy_s(p->errors[p->error_counts++], sizeof(*message), message);
}

void parser_register_infix(parser *p, tk_token_type t, infix_parse_fn fn) {
  hashmap_add(p->infix_parse_fns, t, FUNCTION_NAME_STRINGify(fn));
}
void parser_register_prefix(parser *p, tk_token_type t, prefix_parse_fn fn) {
  hashmap_add(p->prefix_parse_fns, t, FUNCTION_NAME_STRINGify(fn));
}

bool parser_current_token_is(parser *p, tk_token_type t) {
  return p->current_token.tk_type == t;
}
bool parser_peek_token_is(parser *p, tk_token_type t) {
  return p->peek_token.tk_type == t;
}
void parser_peek_error(parser *p, tk_token_type t) {
  char *message = malloc(sizeof(char) * ERROR_MESSAGE_LENGTH);
  sprintf_s(message, ERROR_MESSAGE_LENGTH,
            "expected next token to be %s, got %s instead\n", t);
  strcpy_s(p->errors[p->error_counts++], ERROR_MESSAGE_LENGTH, message);
}
bool parser_expect_peek(parser *p, tk_token_type t) {
  if (parser_peek_token_is(p, t)) {
    parser_next_token(p);
    return true;
  } else {
    parser_peek_error(p, t);
    return false;
  }
}

// parsing functions
//TODO: Implement parsing functions
