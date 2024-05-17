#pragma once
#include "../utils/map.h"
#ifndef tk_token_h
#define tk_token_h
#endif // !token_h
// using tk prefix for token.h and token.c
typedef char *tk_token_type;

typedef struct {
  tk_token_type tk_type;
  char *literal;
} tk_token;

tk_token_type tk_lookup_ident(hashmap *map, char *ident);

hashmap *tk_keywords(void);
