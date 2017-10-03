typedef stuct ast_vector {
	float x;
	float y;
} ast_vector;

ast_vector *ast_create_vector(float x, float y);

void ast_vector_add(ast_vector *add_this, ast_vector *to_this);
