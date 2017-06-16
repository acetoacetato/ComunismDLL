#ifndef LISTA
#define LISTA

typedef struct node nodo;

typedef struct pilita pilita;


pilita* createStack(); //crea y retorna una nueva lista
void* top(pilita* p); // Retorna un puntero al primer dato de la lista
void push(pilita* p, void* dato);  //Inserta al final
void pop(pilita* p);  //Elimina el dato apuntado por current

nodo* _createNode(void* data); //crea un nodo vacio

#endif
