#include "repl/repl.h"
#include "stdio.h"
#include <stdlib.h>
int main(int argc, char **argv, char **env) {
  char *username = getenv("USERPROFILE");
  printf("Hello %s! This is the C-- programming language!\n", username);
  printf("%s", "Feel free to type in commands\n");
  repl_start(stdin, stdout);
}
