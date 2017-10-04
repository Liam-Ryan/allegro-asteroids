#include "ast_vector.h"

ast_vector *ast_create_vector(float x, float y)
{
	ast_vector *a = malloc(sizeof(ast_vector));
	a->x = x;
	a->y = y;
	return a;
}

void ast_add_vector(ast_vector *add_this, ast_vector *to_this)
{
	to_this->x += add_this->x;
	to_this->y += add_this->y;
}

void ast_destroy_vector(ast_vector *v)
{
	free(v);
}
