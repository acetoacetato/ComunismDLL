#pragma once
#ifndef Lista_h
#define Lista_h

#include <windows.h>

/*  To use this exported function of dll, include this header
*  in your project.
*/

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllexport)
#endif
struct Nodo {
	void* data;
	struct Nodo* prev;
	struct Nodo* next;

};

typedef struct Nodo Node;

struct lista {
	Node* first;
	Node* last;
	Node* current;
};

typedef struct lista Listilla;

#ifdef __cplusplus
extern "C"
{
#endif

	 DLL_EXPORT int retornaI(int i);

	 DLL_EXPORT void  SomeFunction(const LPCSTR sometext);


	/* crea una lista vacía y la retorna */
	 DLL_EXPORT Listilla* createList();

	/* crea un nodo, lo llena y devuelve */
	 DLL_EXPORT Node* createNode(void* data);

	/* retorna el dato del nodo actual */
	 DLL_EXPORT void* currentL(Listilla* L);

	/* retorna el nodo actual */
	 DLL_EXPORT Node* currentN(Listilla* L);

	/* avanza el puntero 'current' de la lista hacia el siguiente */
	 DLL_EXPORT void* nextL(Listilla* L);

	/* retrocede el puntero 'current' de la lista haceia el anterior */
	 DLL_EXPORT Node* prev(Listilla* L);

	/* posiciona 'current' en el primer elemento de la lista y lo retorna */
	 DLL_EXPORT void* firstL(Listilla* L);

	/* posiciona 'current' en el último dato de la lista y lo retorna */
	 DLL_EXPORT void* last(Listilla* L);


	/* inserta un nuevo dato al final de la lista */
	 DLL_EXPORT Listilla* push_back(Listilla* L, void* data);

	/* inserta un nuevo dato al principio de la lista */
	 DLL_EXPORT Listilla* push_front(Listilla* L, void* data);

	/* inserta un nuevo dato a la derecha de la posición 'current' */
	 DLL_EXPORT Listilla* push_current(Listilla* L, void* data);



	/* elimina el último elemento de la lista */
	 DLL_EXPORT Listilla* pop_back(Listilla* L);

	/* elimina el último elemento de la lista */
	 DLL_EXPORT Listilla* pop_front(Listilla* L);

	/* elimina el elemento en la posición 'current' de la lista */
	 DLL_EXPORT Listilla* pop_current(Listilla* L);

	 /* Comprueba si la lista esta vacia */
	 DLL_EXPORT int is_empty(Listilla* L);

	 /* Comprueba si el dato 'data' está en la lista */
	 DLL_EXPORT int searchL(Listilla* L, void* data);

	 /* vacia la lista y liver la memoria */
	 DLL_EXPORT void elimina_lista(Listilla* L);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
