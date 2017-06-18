#pragma once
#ifndef COLA
#define COLA
#include <stdlib.h>
#include <stdio.h>
#define DLL_EXPORT __declspec(dllexport)

typedef struct nodoc{
	void* data;
	nodoc* prev;
}NodoC;


typedef struct {
	NodoC* top;
	NodoC* last;
}Cola;




#ifdef __cplusplus
extern "C"
{
#endif
	/* Reserva memoria e inicializa una cola vacía y la retorna */
	DLL_EXPORT Cola* createQeue();

	/* Retorna el dato del top de la cola 'q' */
	DLL_EXPORT void* topQ(Cola* q);

	/* Inserta un nuevo dato 'dato' en la cola 'q' */
	DLL_EXPORT void pushQ(Cola* q, void* dato);

	/* Elimina el dato en 'top' de la cola 'q' */
	DLL_EXPORT void popQ(Cola* q);

	/* Reserva e inicializa un nodo con dato 'data' y lo retorna */
	DLL_EXPORT NodoC* _createNodeQ(void* data);

	/* Vacía la cola 'q' y luego libera la memoria reservada por esta */
	DLL_EXPORT void elimina_cola(Cola* q);

#ifdef __cplusplus
}
#endif


#endif
