cmake_minimum_required(VERSION 3.28.1)

project(INTERPRETER)

file(GLOB_RECURSE token token/*.c)
file(GLOB_RECURSE map map/*.c)
file(GLOB_RECURSE lexer lexer/lex_lexer.c)
file(GLOB_RECURSE repl repl/*.c)


set(SOURCES utils/map.c token/tk_token.c lexer/lex_lexer.c repl/repl.h)

add_executable(${PROJECT_NAME} main.c ${lexer} ${token} ${map} ${repl})
# enable_testing()

target_compile_options(${PROJECT_NAME} PUBLIC -Wall )

