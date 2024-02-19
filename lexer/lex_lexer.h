#ifndef LEX_LEXER_H
#define LEX_LEXER_H

#endif // !LEX_LEXER_Hj
#include "../token/tk_token.h"
#include <stdbool.h>
typedef struct {
  char *input;
  int position;      // current position in input (points to current char)
  int read_position; // current reading position in input (after current char)
  char ch;           // current char under examination
} lex_lexer;

// isLetter checks if identifier has a valid name
bool lex_is_letter(char ch);
bool lex_is_digit(char ch);
tk_token lex_new_token(tk_token_type token_type, char ch);
char *lex_read_string(lex_lexer *lexer);
char *lex_read_number(lex_lexer *lexer);
void lex_skip_whitespace(lex_lexer *lexer);
char lex_peek_char(lex_lexer *lexer);
void lex_read_char(lex_lexer *lexer);
char *lex_read_identifier(lex_lexer *lexer);

// lex_next_token returns the next token from the lexer.
//
// It skips whitespace characters and then checks the value of the current
// character to determine the token type. It handles various cases, such as
// assignment, comparison, arithmetic operations, punctuation, and literals
// like strings and numbers. The function returns the token and moves the
// lexer's position to the next character.
//
// The function does not take any parameters.
// It returns a tk_token struct representing the next token.
tk_token lex_next_token(lex_lexer *lexer);
lex_lexer *lex_lexer_new(char *input);
