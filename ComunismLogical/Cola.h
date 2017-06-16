#pragma once
#ifndef COLA
#define COLA
#include <stdlib.h>
#include <stdio.h>


typedef struct nodoc{
	void* data;
	nodoc* prev;
}NodoC;


typedef struct {
	NodoC* top;
	NodoC* last;
}Cola;





/* Reserva memoria e inicializa una cola vacía y la retorna */
Cola* createQeue();

/* Retorna el dato del top de la cola 'q' */
void* topQ(Cola* q);

/* Inserta un nuevo dato 'dato' en la cola 'q' */
void pushQ(Cola* q, void* dato);

/* Elimina el dato en 'top' de la cola 'q' */
void popQ(Cola* q); 

/* Reserva e inicializa un nodo con dato 'data' y lo retorna */
NodoC* _createNodeQ(void* data);

/* Vacía la cola 'q' y luego libera la memoria reservada por esta */
void elimina_cola(Cola* q);
#endif
