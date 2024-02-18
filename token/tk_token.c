
#include "tk_token.h"
#include "tk_const.h"
#include <stdint.h>
// TODO implement this function
tk_token_type tk_lookup_ident(hashmap *map, char *ident) {
  if (hashmap_get(map, ident, sizeof(*ident), 0)) {
    return ident;
  }
  return TK_IDENT;
}

// TODO add tk_keywords hashmap
hashmap *tk_keywords(void) {
  hashmap *map = hashmap_create();
  hashmap_set(map, hashmap_str_lit("func"), (uintptr_t)TK_FUNCTION);
  hashmap_set(map, hashmap_str_lit("let"), (uintptr_t)TK_LET);
  hashmap_set(map, hashmap_str_lit("true"), (uintptr_t)TK_TRUE);
  hashmap_set(map, hashmap_str_lit("false"), (uintptr_t)TK_FALSE);
  hashmap_set(map, hashmap_str_lit("if"), (uintptr_t)TK_IF);
  hashmap_set(map, hashmap_str_lit("else"), (uintptr_t)TK_ELSE);
  hashmap_set(map, hashmap_str_lit("return"), (uintptr_t)TK_RETURN);
  return map;
}
