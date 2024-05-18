#include "ast.h"
#include <string.h>
char* ast_identifier_token_literal(ast_identifier* ident) {
	return ident->token.literal;
}
char* ast_identifier_string(ast_identifier* ident) {
	return ident->value;
}

ast_identifier ast_identifier_init(tk_token token, char* value)
{
	ast_identifier identifier = {token,value,ast_identifier_token_literal,ast_identifier_string};
	
	return identifier;
}

char* ast_let_statement_token_literal(ast_let_statement* statement)
{
	return statement->token.literal;
}


char* ast_let_statement_string(ast_let_statement* statement)
{
	char str[AST_MAX_BUFFER_SIZE];
	strcat(str,statement->token_literal(statement));
	strcat(str, " ");
	strcat(str, statement->name.string(&statement->name));
	strcat(str, " = ");
	if (&statement->value != NULL)
	{
		strcat(str,statement->value.node.string(&statement->value));
	}
	strcat(str, ";\0");
	return str;
}

ast_let_statement ast_let_statement_init(tk_token token, ast_identifier name, ast_expression value)
{
	ast_let_statement let = { token,name,value,ast_let_statement_token_literal,ast_let_statement_string };
}

char* ast_return_statement_token_literal(ast_return_statement* statement)
{
	return statement->token_literal;
}

char* ast_return_statement_string(ast_return_statement* statement)
{
	char str[AST_MAX_BUFFER_SIZE];
	strcat(str, statement->token_literal(statement));
	strcat(str, " ");
	if (&statement->return_value != NULL)
	{
		strcat(str, statement->return_value.node.string(&statement->return_value));
	}
	strcat(str, ";");
	return str;
}

ast_return_statement ast_return_statement_init(tk_token token, ast_expression return_value)
{
	ast_return_statement rt = { token,return_value,ast_return_statement_token_literal,ast_return_statement_string };
	return rt;
}

char* ast_expression_statement_token_literal(ast_expression_statement* expr)
{
	return expr->token_literal;
}

char* ast_expression_statement_string(ast_expression_statement* expr)
{
	if (&expr->expression != NULL) {
		return (char*)expr->expression.node.string(&expr->expression);
	}
	return "\0";
}

ast_expression_statement ast_expression_statement_init(tk_token token, ast_expression expr)
{
	ast_expression_statement expression = { token,expr,ast_expression_statement_token_literal,ast_expression_statement_string };
	return expression;
}

char* ast_integer_literal_token_literal(ast_integer_literal* il)
{
	return il->token_literal;
}

char* ast_integer_literal_string(ast_integer_literal* il)
{
	return il->token_literal;
}

ast_integer_literal ast_integer_literal_init(tk_token token, int64_t value)
{
	ast_integer_literal il = { token,value,ast_integer_literal_token_literal,ast_integer_literal_string };
	return il;
}



