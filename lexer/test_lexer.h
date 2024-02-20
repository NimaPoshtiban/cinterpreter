#include "../token/tk_const.h"
#include "lex_lexer.h"
#define TEST_LEXER_H
typedef struct {
  tk_token_type expected_type;
  char *expected_literal;
} tests;
