#include "ast_vector.h";

ast_vector *ast_create_vector(float x, float y)
{
	ast_vector *a = malloc(sizeof(ast_vector));
	ast_vector->x = x;
	ast_vector->y = y;
	return a;
}

void ast_add_vector(ast_vector *add_this, ast_vector *to_this)
{
	to_this->x += add_this->x;
	to_this->y += add_this->y;
}

void ast_destroy_vector(vector *v)
{
	free(v);
}
