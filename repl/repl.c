#include "repl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void repl_start(void *in, void *out) {

  char *buffer;
  size_t bufsize = 100;
  buffer = malloc(sizeof(char) * bufsize);
  if (buffer == NULL)
    exit(EXIT_FAILURE);
  hashmap *keywords = tk_keywords();
  while (fgets(buffer, bufsize, in)) {
    printf("%s", REPL_PROMPT);
    lex_lexer *lexer = lex_lexer_new(buffer);
    for (tk_token token = lex_next_token(lexer, keywords);
         strcmp(token.tk_type, TK_EOF) != 0;
         token = lex_next_token(lexer, keywords)) {
      printf("{type:%s literal:%s}\n", token.tk_type, token.literal);
    }
  }
}
