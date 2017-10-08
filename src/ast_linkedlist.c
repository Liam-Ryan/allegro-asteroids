#include "ast_linkedlist.h"

void ast_linkedlist_remove(ast_linkedlist *list, ast_listnode *node)
{
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if(list->head == node)
		list->head = node->next;
	if(list->tail == node)
		list->tail = node->prev;
}

void ast_linkedlist_push(ast_linkedlist *list, ast_listnode *node)
{
	if (list->tail) {
		list->tail->next = node;
		node->prev = list->tail;
		node->next = NULL;
		list->tail = node;
	} else {
		list->tail = node;
		list->head = node;
		node->next = NULL;
		node->prev = NULL;
	}
}

ast_linkedlist *create_ast_linkedlist()
{
	ast_linkedlist *l = malloc(sizeof(ast_linkedlist));
	l->head = NULL;
	l->tail = NULL;
	return l;
}

ast_listnode *create_ast_listnode( void *obj)
{
	ast_listnode *n = malloc(sizeof(ast_listnode));
	n->item = obj;
	n->prev = NULL;
	n->next = NULL;
}