#include "parser.h"
#include <cstdlib>
//TODO: implement all parser functions
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

int parser_peek_precedence(parser *p) {
  hashmap *precedence = precedences();
  char *value = hashmap_find(precedence, p->peek_token.tk_type);
  if (value != 0) {
    return atoi(value);
  }
  return LOWEST;
}


