#include "Cola.h"

Cola* createQeue() {
	Cola* queque = (Cola*)malloc(sizeof(Cola));
	queque->top = NULL;
	queque->last = NULL;
	return queque;
}

void* topQ(Cola* q) {
	if (!q->top) return NULL;

	return q->top->data;
}

void pushQ(Cola* q, void* dato) {
	NodoC* nodo = _createNodeQ(dato);
	if (q->top) {
		q->last->prev =nodo;
		q->last = nodo;
		return;
	}
	else {
		q->last = nodo;
		q->top = nodo;
	}
	
	
}

void popQ(Cola* q) {
	NodoC* aux = q->top;
	q->top = aux->prev;
	free(aux);
}


NodoC* _createNodeQ(void* data) {
	NodoC* nodo = (NodoC*)malloc(sizeof(NodoC));
	nodo->data = data;
	nodo->prev = NULL;
	return nodo;
}

void elimina_cola(Cola* q) {
	while (topQ(q)) {
		popQ(q);
	}
	free(q);
}