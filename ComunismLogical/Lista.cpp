#include "Lista.h"



int retornaI(int i) {
	return i + 1;

}
// a sample exported function
void  SomeFunction(const LPCSTR sometext)
{
	MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}


Listilla*  createList() {
	Listilla* L = (Listilla*)malloc(sizeof(Listilla));
	L->first = NULL;
	L->last = NULL;
	L->current = NULL;

	return L;
}

Node*  createNode(void* data) {

	Node* nodo = (Node*)malloc(sizeof(Node));
	nodo->data = data;
	nodo->prev = NULL;
	nodo->next = NULL;

	return nodo;
}



Node*  nextL(Listilla* L) {
	if (!L->current) return NULL;

	if (L->current->next) {
		L->current = L->current->next;
		return L->current;
	}
	return NULL;
}



void*  currentL(Listilla* L) {
	if (!L || !L->first || !L->current) return NULL;
	return L->current->data;

}


Node*  currentN(Listilla* L) {
	if (!L || !L->first) return NULL;
	return L->current;
}


Node*  prev(Listilla* L) {
	if (!L->current) return NULL;

	if (L->current->prev) {
		L->current = L->current->prev;
		return L->current;
	}

	return NULL;



}


void*  firstL(Listilla* L) {

	if (!L || !L->first) return NULL;

	L->current = L->first;
	return L->current->data;

}


void*  last(Listilla* L) {

	if (!L || !L->first) return NULL;

	L->current = L->last;
	return L->current->data;

}


Listilla*  push_back(Listilla* L, void* data) {
	Node* nuevo = createNode(data);

	if (!L->last) {
		L->current = nuevo;
		L->first = nuevo;
		L->last = nuevo;
		return L;
	}
	L->last->next = nuevo;
	nuevo->prev = L->last;
	L->last = nuevo;
	return L;

}



Listilla*  push_front(Listilla* L, void* data) {
	Node* nuevo = createNode(data);
	if (!L->first) {
		L->first = nuevo;
		L->current = nuevo;
		L->last = nuevo;
		return L;
	}

	L->first->prev = nuevo;
	nuevo->next = L->first;
	L->first = nuevo;

	return L;
}


Listilla*  push_current(Listilla* L, void* data) {
	Node* nuevo = createNode(data);

	if (!L->current) {
		L->first = nuevo;
		L->current = nuevo;
		L->last = nuevo;

		return L;
	}
	if (L->current == L->first) {
		L->first->prev = nuevo;
		nuevo->next = L->first;
		L->first = nuevo;

		return L;
	}

	if (L->current == L->last) {
		L->last->next = nuevo;
		nuevo->prev = L->last;
		L->last = nuevo;

		return L;
	}

	nuevo->next = L->current->next;
	nuevo->prev = L->current->prev;
	L->current->next = nuevo;
	nuevo->next->prev = nuevo;

	return L;
}



Listilla*  pop_back(Listilla* L) {

	if (!L->last) return L;

	if (L->first == L->last) {
		free(L->last);
		L->last = NULL;
		L->first = NULL;
		L->current = NULL;
		return L;
	}

	Node* aux = L->last;

	L->last = L->last->prev;
	L->last->next = NULL;
	free(aux);

	return L;


}
Listilla*  pop_front(Listilla* L) {

	if (!L->first) return L;

	if (L->first == L->last) {
		free(L->first);
		L->last = NULL;
		L->first = NULL;
		L->current = NULL;
		return L;
	}

	Node* aux = L->first;

	L->first = L->first->next;
	L->first->prev = NULL;
	free(aux);
	return L;




}


Listilla*  pop_current(Listilla* L) {
	Node* nodo;
	if (L->current) {
		nodo = L->current;
		if (L->current == L->first) {
			if (L->last != L->current) { //es el primero pero no el único de la Listillaa
				L->first = nodo->next;
				L->current = nodo->next;
				L->current->prev = NULL;
				free(nodo);
				return L;
			}
			else { // es el primero y el único de la Listillaa
				L->current = NULL;
				L->first = NULL;
				L->last = NULL;
				free(nodo);
				return L;
			}
		}
		else {
			if (L->current != L->last) {
				L->current = nodo->next;
				L->current->prev = nodo->prev;
				L->current->prev->next = nodo->next;
				free(nodo);
				return L;
			}
			else {
				L->current = nodo->prev;
				L->last = nodo->prev;
				L->last->next = NULL;
				free(nodo);
				return L;
			}
		}
	}
	return L;
}



int is_empty(Listilla* L) {
	if (!L->first || !L->current) return 1;
	return 0;
}

























extern "C"  BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// attach to process
		// return FALSE to fail DLL load
		break;

	case DLL_PROCESS_DETACH:
		// detach from process
		break;

	case DLL_THREAD_ATTACH:
		// attach to thread
		break;

	case DLL_THREAD_DETACH:
		// detach from thread
		break;
	}
	return TRUE; // succesful
}


DLL_EXPORT int searchL(Listilla* L, void* data) {

	if (is_empty(L)) return 0;
	Node* nodo = L->current;
	firstL(L);
	do {
		if (currentN(L)->data == data) {
			L->current = nodo;
			return 1;
		}
	} while (nextL(L));
	L->current = nodo;
	return 0;

}



DLL_EXPORT void elimina_lista(Listilla* L) {
	while (firstL(L)) {
		pop_front(L);
	}
	free(L);
}