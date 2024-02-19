#include "lex_lexer.h"
#include "../token/tk_const.h"
#include <stdlib.h>
#include <string.h>

bool lex_is_letter(char ch) {
  return ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_' ||
          ch == '$');
}

bool lex_is_digit(char ch) { return ('0' <= ch && ch <= '9'); }

tk_token lex_new_token(tk_token_type token_type, char* ch) {
  tk_token token;
  token.tk_type = token_type;
  
  token.literal = ch;
  return token;
}

void lex_read_char(lex_lexer *lexer) {
  if (lexer->read_position >= strlen(lexer->input)) {
    lexer->ch = 0;
  } else {
    lexer->ch = lexer->input[lexer->read_position];
  }
  lexer->position = lexer->read_position;
  lexer->read_position++;
}

char *lex_read_string(lex_lexer *lexer) {
  int position = lexer->position + 1;
  int size = 0;
  while (!(lexer->ch == '"' || lexer->ch == 0)) {
    lex_read_char(lexer);
    size++;
  }
  char* result = malloc((sizeof(char) * size) + 1);
  memcpy(result, lexer->input + position, lexer->position);
  result[strlen(lexer->input) - 1] = '\0';
  return result;
}

char *lex_read_number(lex_lexer *lexer) {
  int position = lexer->position;
  int size = 0;
  while (lex_is_digit(lexer->ch)) {
    lex_read_char(lexer);
    size++;
  }

  char* result = malloc((sizeof(char) * size) + 1);
  memcpy(result, lexer->input + position, lexer->position);
  result[strlen(lexer->input) - 1] = '\0';
  return result;
}

void lex_skip_whitespace(lex_lexer *lexer) {
  while ((lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' ||
          lexer->ch == '\r'))
    lex_read_char(lexer);
}

char lex_peek_char(lex_lexer *lexer) {
  if (lexer->read_position >= strlen(lexer->input)) {
    return 0;
  } else {
    return lexer->input[lexer->read_position];
  }
}

char *lex_read_identifier(lex_lexer *lexer) {
  int position = lexer->position;
  int size = 0;
  while (lex_is_letter(lexer->ch)) {
      lex_read_char(lexer);
      size++;
  }
  char *result = malloc((sizeof(char) *size)+1);
  memcpy(result, lexer->input + position, lexer->position);
  result[size] = '\0';
  return result;
}

lex_lexer *lex_lexer_new(char *input) {
  lex_lexer *lexer = malloc(sizeof(lex_lexer));
  lexer->input = malloc(sizeof(input));
  lexer->input = input;
  lexer->position = NULL;
  lexer->read_position = NULL;
  lex_read_char(lexer);
  return lexer;
}

tk_token lex_next_token(lex_lexer *lexer) {
  tk_token token ;

  lex_skip_whitespace(lexer);

  switch (lexer->ch) {
  case '=':
    if (lex_peek_char(lexer) == '=') {
      char ch = lexer->ch;
      lex_read_char(lexer);
      char literal[3] = {ch, lexer->ch, '\0'};
      token.tk_type = TK_EQ;
      token.literal = literal;
    } else {
        char literal[2] = { lexer->ch,'\0' };
      token = lex_new_token(TK_ASSIGN, literal);
    }
    break;
  case '-':
    token = lex_new_token(TK_MINUS, lexer->ch);
    break;
  case '!':
    if (lex_peek_char(lexer) == '=') {
      char ch = lexer->ch;
      lex_read_char(lexer);
      char literal[3] = {ch, lexer->ch, '\0'};
      token.tk_type = TK_NOT_EQ;
      token.literal = literal;
    } else {
      token = lex_new_token(TK_BANG, lexer->ch);
    }
    break;
  case '*':
    token = lex_new_token(TK_ASTERISK, lexer->ch);
    break;
  case '/':
    token = lex_new_token(TK_SLASH, lexer->ch);
    break;
  case '<':
    token = lex_new_token(TK_LT, lexer->ch);
    break;
  case '>':
    token = lex_new_token(TK_GT, lexer->ch);
    break;
  case ';':
    token = lex_new_token(TK_SEMICOLON, lexer->ch);
    break;
  case '(':
    token = lex_new_token(TK_LPAREN, lexer->ch);
    break;
  case ')':
    token = lex_new_token(TK_RPAREN, lexer->ch);
    break;
  case ',':
    token = lex_new_token(TK_COMMA, lexer->ch);
    break;
  case '+':
    token = lex_new_token(TK_PLUS, lexer->ch);
    break;
  case '{':
    token = lex_new_token(TK_LBRACE, lexer->ch);
    break;
  case '}':
    token = lex_new_token(TK_RBRACE, lexer->ch);
    break;
  case '[':
    token = lex_new_token(TK_LBRACKET, lexer->ch);
    break;
  case ']':
    token = lex_new_token(TK_RBRACKET, lexer->ch);
    break;
  case '"':
    token.tk_type = TK_STRING;
    token.literal = lex_read_string(lexer);
    break;
  case ':':
    token = lex_new_token(TK_COLON, lexer->ch);
    break;
  case 0:
    token.tk_type = TK_EOF;
    token.literal = "";
    break;
  default:
    if (lex_is_letter(lexer->ch)) {
      token.literal = lex_read_identifier(lexer);
      token.tk_type = tk_lookup_ident(tk_keywords(), token.literal);
      return token;
    } else if (lex_is_digit(lexer->ch)) {
      token.tk_type = TK_INT;
      token.literal = lex_read_number(lexer);
      return token;
    } else {
      token = lex_new_token(TK_ILLEGAL, lexer->ch);
    }
  }
  lex_read_char(lexer);
  return token;
}
