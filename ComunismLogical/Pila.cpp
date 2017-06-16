#include "Pila.h"
#include <stdlib.h>


struct node {
	struct node* next;
	void* data;
};

typedef struct node nodo;

struct pilita {
	nodo* first;
};

typedef struct pilita pilita;

pilita* createStack() {
	pilita* l = (pilita*)malloc(sizeof(pilita));
	l->first = NULL;
	return l;
}

void* top(pilita* L) {
	if (L->first) {
		return L->first->data;
	}
	return NULL;
}


void push(pilita* list, void* dato) {
	nodo* node = _createNode(dato);
	if (list->first != NULL) {
		node->next = list->first;
	}
	list->first = node;
}
void pop(pilita* list) {
	if (list->first)list->first = list->first->next;
}
nodo* _createNode(void* data) {
	nodo* aux = (nodo*)malloc(sizeof(nodo));
	aux->next = NULL;
	aux->data = data;
	return aux;
}

