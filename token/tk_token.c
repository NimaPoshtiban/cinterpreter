
#include "tk_token.h"
#include "tk_const.h"
// TODO implement this function
tk_token_type tk_lookup_ident(hashmap *map, char *ident) {
  if (hashmap_find(map , ident) != 0) {
    return ident;
  }
  return TK_IDENT;
}

// TODO add tk_keywords hashmap
hashmap *tk_keywords(void) {
  hashmap *map = hashmap_create();
  hashmap_add(map, "func", TK_FUNCTION);
  hashmap_add(map, "let", TK_LET);
  hashmap_add(map, "true", TK_TRUE);
  hashmap_add(map, "false", TK_FALSE);
  hashmap_add(map, "if", TK_IF);
  hashmap_add(map, "else", TK_ELSE);
  hashmap_add(map, "return", TK_RETURN);
  return map;
}
