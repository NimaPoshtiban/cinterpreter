#include "test_lexer.h"
#include <stdio.h>
#include <stdlib.h>
#define RED "\033[31m"   /* Red */
#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"

int errors = 0;
void Test_Next_Token() {
  char *input = "let five = 5;"
                "let ten = 10;"
                "	let add = func(x, y) {"
                "	x + y;"
                "	};"
                "	let result = add(five, ten);"
                "	!-/*5;"
                "	5 < 10 > 5;"
                "	if (5 < 10) {"
                "		return true;"
                "		} else {"
                "		return false;"
                "	}"
                "	10 == 10;"
                "	10 != 9;"
                "	\"foobar\""
                "	\"foo bar\"";

  tests tst[76] = {
      {TK_LET, "let"},      {TK_IDENT, "five"},    {TK_ASSIGN, "="},
      {TK_INT, "5"},        {TK_SEMICOLON, ";"},   {TK_LET, "let"},
      {TK_IDENT, "ten"},    {TK_ASSIGN, "="},      {TK_INT, "10"},
      {TK_SEMICOLON, ";"},  {TK_LET, "let"},       {TK_IDENT, "add"},
      {TK_ASSIGN, "="},     {TK_FUNCTION, "func"}, {TK_LPAREN, "("},
      {TK_IDENT, "x"},      {TK_COMMA, ","},       {TK_IDENT, "y"},
      {TK_RPAREN, ")"},     {TK_LBRACE, "{"},      {TK_IDENT, "x"},
      {TK_PLUS, "+"},       {TK_IDENT, "y"},       {TK_SEMICOLON, ";"},
      {TK_RBRACE, "}"},     {TK_SEMICOLON, ";"},   {TK_LET, "let"},
      {TK_IDENT, "result"}, {TK_ASSIGN, "="},      {TK_IDENT, "add"},
      {TK_LPAREN, "("},     {TK_IDENT, "five"},    {TK_COMMA, ","},
      {TK_IDENT, "ten"},    {TK_RPAREN, ")"},      {TK_SEMICOLON, ";"},
      {TK_BANG, "!"},       {TK_MINUS, "-"},       {TK_SLASH, "/"},
      {TK_ASTERISK, "*"},   {TK_INT, "5"},         {TK_SEMICOLON, ";"},
      {TK_INT, "5"},        {TK_LT, "<"},          {TK_INT, "10"},
      {TK_GT, ">"},         {TK_INT, "5"},         {TK_SEMICOLON, ";"},
      {TK_IF, "if"},        {TK_LPAREN, "("},      {TK_INT, "5"},
      {TK_LT, "<"},         {TK_INT, "10"},        {TK_RPAREN, ")"},
      {TK_LBRACE, "{"},     {TK_RETURN, "return"}, {TK_TRUE, "true"},
      {TK_SEMICOLON, ";"},  {TK_RBRACE, "}"},      {TK_ELSE, "else"},
      {TK_LBRACE, "{"},     {TK_RETURN, "return"}, {TK_FALSE, "false"},
      {TK_SEMICOLON, ";"},  {TK_RBRACE, "}"},      {TK_INT, "10"},
      {TK_EQ, "=="},        {TK_INT, "10"},        {TK_SEMICOLON, ";"},
      {TK_INT, "10"},       {TK_NOT_EQ, "!="},     {TK_INT, "9"},
      {TK_SEMICOLON, ";"},  {TK_STRING, "foobar"}, {TK_STRING, "foo bar"},
      {TK_EOF, ""},
  };
  lex_lexer *lexer = lex_lexer_new(input);
  for (int i = 0; i < 76; i++) {
    tk_token token = lex_next_token(lexer);
    if (token.tk_type != tst[i].expected_type) {
      printf(RED "Wrong token type. expected = %s but got = %s\n" RESET,
             tst[i].expected_type, token.tk_type);
      errors++;
    }

    if (token.literal != tst[i].expected_literal) {
      printf(RED "Wrong literal type. expected = %s but got = %s\n" RESET,
             tst[i].expected_literal, token.literal);
      errors++;
    }
  }
  free(lexer);
}

int main() {
  Test_Next_Token();
  if (errors != 0) {
    printf("%s", RED "Test Failed! :(\n" RESET);
  } else {
    printf("%s", GREEN "Test Successed! :)\n" RESET);
  }
  printf("%s", "Test Finished!");
}
