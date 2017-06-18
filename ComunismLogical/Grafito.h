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
#define DLL_EXPORT __declspec(dllexport)

/*  To use this exported function of dll, include this header
*  in your project.
*/





typedef struct {

	Listilla* Padres;
	void* data;
	char key[30];
	Listilla* hijos;
	int visitado;

}NodoG;


struct grafo{
	NodoG* raiz;
	NodoG* current;
	int corrupto;
};

typedef struct grafo Grafo;

typedef struct lista Listilla;

typedef struct {
	double exp_acu;
	int muertes;
	double puntaje;
	int lineaA;
	int lineaB;
	int lineaC;
}Manager_partida;

typedef struct {
	Listilla* ptge;
	char logros[11];
	Grafo* HAB_UW;
	Grafo* HAB_RW;
	Grafo*  HAB_MW;
}Manager_general;


typedef struct {
	char nombre[BUFFSIZE];
	char descripcion[BUFFSIZE];
}Habilidad;




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

	DLL_EXPORT int AbraArchivo(char* str);

	/* Crea un grafo, 'nombre' es nombre del archivo y 'es_save' es si es un grafo de nivel o grafo de habilidades */
	DLL_EXPORT Grafo* ArmaGrafo(int tipo);

	/* Crea un nodo para el grafo y crea listas vacías de padres e hijos */
	DLL_EXPORT NodoG* CreaNodo(char* key, void* data);

	/* Busca un nodo en grafo 'graf' con key 'key' y cambia el current si 'cambiaCurrent' es 1 */
	DLL_EXPORT NodoG* BuscarNodo(char* key, Grafo* graf, int cambiaCurrent);

	/* Llena lista de padres de 'graf' con string 'listaPadres' y une hijos con 'nodog' */
	DLL_EXPORT void UnePadres(NodoG* nodog, Grafo* graf, char* listaPadres);

	/* Carga partida poblando el grafo de nivel y el manager de partida con los datos en archivo de nombre 'save' */
	DLL_EXPORT int CargaPartida(Grafo* graf_lv, Manager_partida* man,  int saveN);

	/* Carga los grafos y el manager general para el inicio del juego, lueg pobla los grafos de habilidad y los une al manager general */
	DLL_EXPORT int CargaJuego(Grafo* graf_lv, Manager_general* manG);

	/* Carga grafo especifico con string (cambia nodoG->visitado) */
	DLL_EXPORT void C_Grafo(Grafo* graf_lv, char* linea, int cant_nodos);

	/* Comprueba que ls padres del nodo 'nodo' tiene los padres visitados */
	DLL_EXPORT int CompruebaPadres(NodoG* nodo); 

	/* Guarda los nodoG->visitado de 'graf' en archivo 'f' */
	DLL_EXPORT void GuardarGrafo(FILE* f, Grafo* graf);

	/* Marca el nodo con key 'code' del grafo 'graf' con el valor de visitado = 'valor' */
	DLL_EXPORT void  MarcaNodo(Grafo* graf, char* code, int valor);

	/* Guarda en archivo 'save' la partida */
	DLL_EXPORT int GuardaPartida(Manager_partida* man, Grafo* graf_lv, int tipo);

	/* Guarda el manager general */
	DLL_EXPORT int GuardaManagerG(Manager_general* man);

	/* Imprime las claves del grafo 'lv' con recorrido por anchura */
	DLL_EXPORT void ImprimeGrafo(Grafo* lv);

	DLL_EXPORT void CargaTipo(char* str, int tipo);

	DLL_EXPORT void C_Puntaje(char* linea, Listilla* puntajes);

	DLL_EXPORT void GuardaPuntajes(Listilla* L,FILE* f);

	DLL_EXPORT Listilla* NodosDisponibles(Grafo* graf);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
