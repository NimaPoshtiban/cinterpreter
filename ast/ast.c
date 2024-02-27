#include "ast.h"
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 256
size_t strlcpy(char *dest, const char *src, size_t n) {
  size_t len = strlen(src);

  if (len < n)
    memcpy(dest, src, len + 1);
  else {
    memcpy(dest, src, n - 1);
    dest[n - 1] = '\0';
  }

  return len;
}

char *ast_token_literal(ast_program *program) {
  if (_countof(program->statements) > 0) {
    return program->statements->node->ast_token_literal();
  }
  return "";
}

char *ast_string(ast_program *program) {
  char *buf = malloc(sizeof(char) * BUFSIZE);
  for (size_t i = 0; i < _countof(program->statements); i++) {
    strlcpy(buf, program->statements[i].node->ast_string(), sizeof(buf));
  }
  return buf;
}
