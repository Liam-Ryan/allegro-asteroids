#ifndef AST_VECTOR_H
#define AST_VECTOR_H
#include <malloc.h>

typedef struct ast_vector {
	float x;
	float y;
} ast_vector;

ast_vector *ast_create_vector(float x, float y);

void ast_add_vector(ast_vector *add_this, ast_vector *to_this);

#endif