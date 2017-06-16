#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Lista.h"
#include "Cola.h"
#define BUFFSIZE 3000


/*  To use this exported function of dll, include this header
*  in your project.
*/

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

typedef struct {
	long double exp_acu;
	long int muertes;
	long double puntaje;
	long int lineaA;
	long int lineaB;
	long int lineaC;
}Manager_partida;

typedef struct {
	Listilla* ptge;
	char logros[11];
}Manager_general;


typedef struct {
	char nombre[BUFFSIZE];
	char descripcion[BUFFSIZE];
}Habilidad;



typedef struct {

	Listilla* Padres;
	void* data;
	char key[30];
	Listilla* hijos;
	short int visitado;

}NodoG;


struct grafo{
	NodoG* raiz;
	NodoG* current;
	int corrupto;
};

typedef struct grafo Grafo;

typedef struct lista Listilla;

char save1[] = "save1.txt";
char save2[] = "save2.txt";
char save3[] = "save3.txt";
char LVLS[] = "LVLS.txt";
char hab_UW[] = "HAB_U.txt";
char hab_RW[] = "HAB_R.txt";
char hab_MW[] = "HAB_M.txt";

#ifdef __cplusplus
extern "C"
{
#endif

	DLL_EXPORT char* transformaString();

	DLL_EXPORT int AbraArchivo(int tipo);

	/* Crea un grafo, 'nombre' es nombre del archivo y 'es_save' es si es un grafo de nivel o grafo de habilidades */
	DLL_EXPORT Grafo* ArmaGrafo(int tipo);

	/* Crea un nodo para el grafo y crea listas vacías de padres e hijos */
	DLL_EXPORT NodoG* creaNodo(char* key, void* data);

	/* Busca un nodo en grafo 'graf' con key 'key' y cambia el current si 'cambiaCurrent' es 1 */
	DLL_EXPORT NodoG* buscarNodo(char* key, Grafo* graf, int cambiaCurrent);

	/* Llena lista de padres de 'graf' con string 'listaPadres' y une hijos con 'nodog' */
	DLL_EXPORT void unePadres(NodoG* nodog, Grafo* graf, char* listaPadres);

	/* Carga partida poblando los grafos de nivel, habilidades y manager de partida con los datos en archivo de nombre 'save' */
	DLL_EXPORT int CargaPartida(Grafo* graf_lv, Grafo* graf_UW, Grafo* graf_RW, Grafo* graf_MW, Manager_partida* man, int tipo);

	/* Carga grafo especifico con string (cambia nodoG->visitado) */
	DLL_EXPORT void C_Grafo(Grafo* graf_lv, char* linea, int cant_nodos);

	/* Comprueba que ls padres del nodo 'nodo' tiene los padres visitados */
	DLL_EXPORT int compruebaPadres(NodoG* nodo); 

	/* Guarda los nodoG->visitado de 'graf' en archivo 'f' */
	DLL_EXPORT void GuardarGrafo(FILE* f, Grafo* graf);

	/* Marca el nodo con key 'code' del grafo 'graf' con el valor de visitado = 'valor' */
	DLL_EXPORT void  marcaNodo(Grafo* graf, char* code, int valor);

	/* Guarda en archivo 'save' la partida */
	DLL_EXPORT int guardaPartida(Manager_partida* man, Grafo* graf_lv, Grafo* graf_uw, Grafo* graf_rw, Grafo* graf_mw, int tipo);

	/* Imprime las claves del grafo 'lv' con recorrido por anchura */
	DLL_EXPORT void imprimeGrafo(Grafo* lv);

	DLL_EXPORT char* transformaString();

	DLL_EXPORT void CargaTipo(char* str, int tipo);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
