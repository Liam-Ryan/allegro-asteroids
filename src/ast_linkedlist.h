#ifndef ALLEGRO_ASTEROIDS_AST_LINKEDLIST_H
#define ALLEGRO_ASTEROIDS_AST_LINKEDLIST_H
#include <malloc.h>
typedef struct ast_listnode {
	void *item;
	struct ast_listnode *next;
	struct ast_listnode *prev;
} ast_listnode;

typedef struct ast_linkedlist {
	ast_listnode *head;
	ast_listnode *tail;
} ast_linkedlist;

void ast_linkedlist_remove(ast_linkedlist *list, ast_listnode *node);

void ast_linkedlist_push(ast_linkedlist *list, ast_listnode *node);

ast_linkedlist *create_ast_linkedlist();

ast_listnode *create_ast_listnode( void *obj);

#endif //ALLEGRO_ASTEROIDS_AST_LINKEDLIST_H
