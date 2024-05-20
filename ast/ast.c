#include "ast.h"
#include <stdlib.h>
#include <string.h>
char *ast_identifier_token_literal(ast_identifier *ident) {
  return ident->token.literal;
}
char *ast_identifier_string(ast_identifier *ident) { return ident->value; }

ast_identifier ast_identifier_init(tk_token token, char *value) {
  ast_identifier identifier = {token, value, ast_identifier_token_literal,
                               ast_identifier_string};

  return identifier;
}

char *ast_let_statement_token_literal(ast_let_statement *statement) {
  return statement->token.literal;
}

char *ast_let_statement_string(ast_let_statement *statement) {
  char *str = (char *)malloc(AST_MAX_BUFFER_SIZE * sizeof(char));
  strcat_s(str, sizeof(statement->token_literal(statement)),
           statement->token_literal(statement));
  strcat_s(str, sizeof(char) * 1, " ");
  strcat_s(str, sizeof(statement->name->string(statement->name)),
           statement->name->string(statement->name));
  strcat_s(str, sizeof(char) * 3, " = ");
  if (statement->value != NULL) {
    strcat_s(str, sizeof(statement->value->node.string(statement->value)),
             statement->value->node.string(statement->value));
  }
  strcat_s(str, sizeof(char) * 2, ";\0");
  return str;
}

ast_let_statement ast_let_statement_init(tk_token token, ast_identifier *name,
                                         ast_expression *value) {
  ast_let_statement let = {token, name, value, ast_let_statement_token_literal,
                           ast_let_statement_string};
  return let;
}

char *ast_return_statement_token_literal(ast_return_statement *statement) {
  return statement->token.literal;
}

char *ast_return_statement_string(ast_return_statement *statement) {
  char *str = (char *)malloc(sizeof(char) * AST_MAX_BUFFER_SIZE);
  strcat_s(str, sizeof(statement->token_literal(statement)),
           statement->token_literal(statement));
  strcat_s(str, sizeof(char), " ");
  if (statement->return_value != NULL) {
    strcat_s(
        str,
        sizeof(statement->return_value->node.string(statement->return_value)),
        statement->return_value->node.string(statement->return_value));
  }
  strcat_s(str, sizeof(char) * 2, ";\0");
  return str;
}

ast_return_statement ast_return_statement_init(tk_token token,
                                               ast_expression *return_value) {
  ast_return_statement rt = {token, return_value,
                             ast_return_statement_token_literal,
                             ast_return_statement_string};
  return rt;
}

char *ast_expression_statement_token_literal(ast_expression_statement *expr) {
  return expr->token.literal;
}
char *ast_expression_statement_string(ast_expression_statement *expr) {
  if (expr->expression != NULL) {
    return (char *)expr->expression->node.string(expr->expression);
  }
  return "\0";
}

ast_expression_statement ast_expression_statement_init(tk_token token,
                                                       ast_expression *expr) {
  ast_expression_statement expression = {token, expr,
                                         ast_expression_statement_token_literal,
                                         ast_expression_statement_string};
  return expression;
}

char *ast_integer_literal_token_literal(ast_integer_literal *il) {
  return il->token.literal;
}

char *ast_integer_literal_string(ast_integer_literal *il) {
  return il->token.literal;
}

ast_integer_literal ast_integer_literal_init(tk_token token, int64_t value) {
  ast_integer_literal il = {token, value, ast_integer_literal_token_literal,
                            ast_integer_literal_string};
  return il;
}

char *ast_prefix_expression_token_literal(ast_prefix_expression *expr) {
  return expr->token.literal;
}

char *ast_prefix_expression_string(ast_prefix_expression *expr) {
  char *str = (char *)malloc(sizeof(char) * AST_MAX_BUFFER_SIZE);
  strcat_s(str, sizeof(char), "(");
  strcat_s(str, sizeof(expr->op), expr->op);
  strcat_s(str, sizeof(expr->right->node.string(expr->right)),
           expr->right->node.string(expr->right));
  strcat_s(str, sizeof(char) * 2, ")\0");
  return str;
}

ast_prefix_expression ast_prefix_expression_init(tk_token token, char *op,
                                                 ast_expression *right) {
  ast_prefix_expression prefix = {token, op, right,
                                  ast_prefix_expression_token_literal,
                                  ast_prefix_expression_string};
  return prefix;
}

char *ast_infix_expression_token_literal(ast_infix_expression *expr) {
  return expr->token.literal;
}

char *ast_infix_expression_string(ast_infix_expression *expr) {
  char *str = (char *)malloc(sizeof(char) * AST_MAX_BUFFER_SIZE);
  strcat_s(str, sizeof(char), "(");
  strcat_s(str, sizeof(expr->left->node.string(expr->left)),
           expr->left->node.string(expr->left));
  strcat_s(str, sizeof(char), " ");
  strcat_s(str, sizeof(expr->op), expr->op);
  strcat_s(str, sizeof(char), " ");
  strcat_s(str, sizeof(expr->right->node.string(expr->right)),
           expr->right->node.string(expr->right));
  strcat_s(str, sizeof(char) * 2, ")\0");
  return str;
}
ast_infix_expression ast_infix_expression_init(tk_token token, char *op,
                                               ast_expression *left,
                                               ast_expression *right) {
  ast_infix_expression infix = {token,
                                op,
                                left,
                                right,
                                ast_infix_expression_token_literal,
                                ast_infix_expression_string};
  return infix;
}
char *ast_index_expression_token_literal(ast_index_expression *expr) {
  return expr->token.literal;
}
char *ast_index_expression_string(ast_index_expression *expr) {
  char *str = (char *)malloc(sizeof(char) * AST_MAX_BUFFER_SIZE);
  strcat_s(str, sizeof(char), "(");
  strcat_s(str, sizeof(expr->left->node.string(expr->left)),
           expr->left->node.string(expr->left));
  strcat_s(str, sizeof(char), "[");
  strcat_s(str, sizeof(expr->index->node.string(expr->index)),
           expr->index->node.string(expr->index));
  strcat_s(str, sizeof(char) * 2, "]\0");
  return str;
}

ast_index_expression ast_index_expression_init(tk_token token,
                                               ast_expression *left,
                                               ast_expression *index) {
  ast_index_expression index_expr = {token, left, index,
                                     ast_index_expression_token_literal,
                                     ast_index_expression_string};
  return index_expr;
}

char *ast_boolean_token_literal(ast_boolean *b) { return b->token.literal; }

char *ast_boolean_string(ast_boolean *b) { return b->token.literal; }

ast_boolean ast_boolean_init(tk_token token, bool value) {
  ast_boolean bl = {token, value, ast_boolean_token_literal,
                    ast_boolean_string};
  return bl;
}

char *ast_block_statement_literal(ast_block_statement *statement) {
  return statement->token.literal;
}

char *ast_block_statement_string(ast_block_statement *statement) {
  char *str = (char *)malloc(sizeof(char) * AST_MAX_BUFFER_SIZE);
  for (int i = 0; i < AST_STATEMENT_LIMIT; i++) {
    strcat_s(
        str,
        sizeof(statement->statements[i].node.string(&statement->statements[i])),
        statement->statements[i].node.string(&statement->statements[i]));
  }
  strcat_s(str, sizeof(char), "\0");
  return str;
}

ast_block_statement ast_block_statement_init(tk_token token,
                                             ast_statement *statements) {
  ast_block_statement stmt = {token, statements, ast_block_statement_literal,
                              ast_block_statement_string};
  return stmt;
}
char *ast_if_expression_token_literal(ast_if_expression *expr) {
  return expr->token.literal;
}
char *ast_if_expression_string(ast_if_expression *expr) {
  char *str = (char *)malloc(sizeof(char) * AST_MAX_BUFFER_SIZE);
  strcat_s(str, sizeof(char) * 2, "if");
  strcat_s(str, sizeof(expr->condition->node.string(expr->condition)),
           expr->condition->node.string(expr->condition));
  strcat_s(str, sizeof(char), " ");
  strcat_s(str, sizeof(expr->consequence->string(expr->consequence)),
           expr->consequence->string(expr->consequence));
  if (expr->alternative != NULL) {
    strcat_s(str, sizeof(char) * 5, "else ");
    strcat_s(str, sizeof(expr->alternative->string(expr->alternative)),
             expr->alternative->string(expr->alternative));
  }
  strcat_s(str, sizeof(char), "\0");
  return str;
}

ast_if_expression ast_if_expression_init(tk_token token,
                                         ast_expression *condition,
                                         ast_block_statement *consequence,
                                         ast_block_statement *alternative) {
  ast_if_expression expr = {token,
                            condition,
                            consequence,
                            alternative,
                            ast_if_expression_token_literal,
                            ast_if_expression_string};
  return expr;
}

char *ast_while_expression_token_literal(ast_while_expression *expr) {
  return expr->token.literal;
}

char *ast_while_expression_string(ast_while_expression *expr) {
  char *str = (char *)malloc(sizeof(char) * AST_MAX_BUFFER_SIZE);
  strcat_s(str, sizeof(expr->token_literal(expr)), expr->token_literal(expr));
  strcat_s(str, sizeof(char), "(");
  strcat_s(str, sizeof(expr->condition->node.string(expr->condition)),
           expr->condition->node.string(expr->condition));
  strcat_s(str, sizeof(char), ")");
  strcat_s(str, sizeof(expr->body->string(expr->body)),
           expr->body->string(expr->body));
  strcat_s(str, sizeof(char), "\0");
  return str;
}

ast_while_expression ast_while_expression_init(tk_token token,
                                               ast_expression *condition,
                                               ast_block_statement *body) {
  ast_while_expression expr = {token, condition, body,
                               ast_while_expression_token_literal,
                               ast_while_expression_string};
  return expr;
}

char *ast_function_literal_token_literal(ast_function_literal *fn) {
  return fn->token.literal;
}

char *ast_function_literal_string(ast_function_literal *fn) {
  char *str = (char *)malloc(sizeof(char) * AST_MAX_BUFFER_SIZE);
  char *params = (char *)malloc(sizeof(char));
  int i = 0;
  while (&fn->parameters[i] != NULL) {
    params = (char *)realloc(
        params,
        sizeof(params) + sizeof(fn->parameters->string(&fn->parameters[i])));
    strcpy_s(params, sizeof(fn->parameters->string(&fn->parameters[i])),
             fn->parameters[i].string(&fn->parameters[i]));
    i++;
  }
  strcat_s(str, sizeof(fn->token_literal(fn)), fn->token_literal(fn));
  strcat_s(str, sizeof(char), "(");
  strcat_s(str, sizeof(params), params);
  strcat_s(str, sizeof(char), ")");
  strcat_s(str, sizeof(fn->body->string(fn->body)), fn->body->string(fn->body));
  strcat_s(str, sizeof(char), "\0");
  return str;
}

ast_function_literal ast_function_literal_init(tk_token token,
                                               ast_identifier *parameters,
                                               ast_block_statement *body) {
  ast_function_literal fn = {token, parameters, body,
                             ast_function_literal_token_literal,
                             ast_function_literal_string};
  return fn;
}

char *ast_call_expression_token_literal(ast_call_expression *expr) {
  return expr->token.literal;
}

char *ast_call_expression_string(ast_call_expression *expr) {
  char *str = (char *)malloc(sizeof(char) * AST_MAX_BUFFER_SIZE);
  char *args = (char *)malloc(sizeof(char));
  int i = 0;
  while (&expr->arguments[i] != NULL) {
    args = (char *)realloc(
        args, sizeof(args) +
                  sizeof(expr->arguments->node.string(&expr->arguments[i])));
    strcpy_s(args, sizeof(expr->arguments->node.string(&expr->arguments[i])),
             expr->arguments[i].node.string(&expr->arguments[i]));
    i++;
  }
  strcat_s(str, sizeof(expr->function->node.string(expr->function)),
           expr->function->node.string(expr->function));
  strcat_s(str, sizeof(char), "(");
  strcat_s(str, sizeof(args), args);
  strcat_s(str, sizeof(char), ")");
  strcat_s(str, sizeof(char), "\0");
  return str;
}

ast_call_expression ast_call_expression_init(tk_token token,
                                             ast_expression *function,
                                             ast_expression *arguments) {
  ast_call_expression expr = {token, function, arguments,
                              ast_call_expression_token_literal,
                              ast_call_expression_string};
  return expr;
}

char *ast_string_literal_token_literal(ast_string_literal *li) {
  return li->token.literal;
}

char *ast_string_literal_string(ast_string_literal *li) {
  return li->token.literal;
}

ast_string_literal ast_string_literal_init(tk_token token, char *value) {
  ast_string_literal str = {token, value, ast_string_literal_token_literal,
                            ast_string_literal_string};
  return str;
}

char *ast_array_literal_token_literal(ast_array_literal *li) {
  return li->token.literal;
}

char *ast_array_literal_string(ast_array_literal *li) {
  char *str = (char *)malloc(sizeof(char) * AST_MAX_BUFFER_SIZE);
  char *el = (char *)malloc(sizeof(char));
  int i = 0;
  while (&li->elements[i] != NULL) {
    el = (char *)realloc(
        el, sizeof(el) + sizeof(li->elements[i].node.string(&li->elements[i])));
    strcpy_s(el, sizeof(li->elements[i].node.string(&li->elements[i])),
             li->elements[i].node.string(&li->elements[i]));
    i++;
  }

  strcat_s(str, sizeof(char), "[");
  strcat_s(str, sizeof(el), el);
  strcat_s(str, sizeof(char), "]");
  strcat_s(str, sizeof(char), "\0");
  return str;
}

ast_array_literal ast_array_literal_init(tk_token token,
                                         ast_expression *elements) {
  ast_array_literal arr = {token, elements, ast_array_literal_token_literal,
                           ast_array_literal_string};
  return arr;
}

char *ast_hash_literal_token_literal(ast_hash_literal *hl) {
  return hl->token.literal;
}

// implemnent this
// need to iterate over hashmap
// hashmap only suppor CRUD operations
char *ast_hash_literal_string(ast_hash_literal *hl) {
  return hl->token.literal;
}

ast_hash_literal ast_hash_literal_init(tk_token token, hashmap *pairs) {
  ast_hash_literal hash = {token, pairs, ast_hash_literal_token_literal,
                           ast_hash_literal_string};
  return hash;
}
