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
	int key;
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
	char* logros;
	Grafo* HAB_UW;
	Grafo* HAB_RW;
	Grafo*  HAB_MW;
}Manager_general;


typedef struct {
	char* nombre;
	char* descripcion;
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

	/* Función que comprueba el correcto funcionamiento de la funcion fopen */
	DLL_EXPORT int AbraArchivo(char* str);

	/* Crea un grafo, de acuerdo a 'tipo' se abrie cierto archivo y se arma un grafo específico de acuerdo a 'tipo'*/
	DLL_EXPORT Grafo* ArmaGrafo(int tipo);

	/* Crea un nodo para el grafo y crea listas vacías de padres e hijos */
	DLL_EXPORT NodoG* CreaNodo(int key, void* data);

	/* Busca un nodo en grafo 'graf' con key 'key' y cambia el current si 'cambiaCurrent' es 1 */
	DLL_EXPORT NodoG* BuscarNodo(int key, Grafo* graf, int cambiaCurrent);

	/* Llena lista de padres de 'nodoG' con string 'listaPadres' y los une hacia ambos lados */
	DLL_EXPORT void UnePadres(NodoG* nodog, Grafo* graf, char* listaPadres);

	/* Carga partida poblando el grafo de nivel y el manager de partida con los datos en archivo de nombre 'save' */
	DLL_EXPORT int CargaPartida(int saveN);

	/* llena el manager general con los datos necesarios */
	DLL_EXPORT Manager_general* ArmaManagerG();

	/* crea y llena el manager de partida con los datos necesarios */
	DLL_EXPORT Manager_partida* ArmaManagerP();
	/* Carga los grafos y el manager general para el inicio del juego, lueg pobla los grafos de habilidad y los une al manager general */
	DLL_EXPORT int CargaJuego();

	/* Carga grafo especifico con string (cambia nodoG->visitado) */
	DLL_EXPORT void C_Grafo(Grafo* graf_lv, char* linea, int cant_nodos);

	/* Comprueba que los padres del nodo 'nodo' tiene todos sus padres "visitados" */
	DLL_EXPORT int CompruebaPadres(NodoG* nodo); 

	/* Crea y arga el Manager general con los datos necesrios para iniciar el juego*/
	DLL_EXPORT int CargaManager();

	/* Guarda en archivo 'save' la partida */
	DLL_EXPORT int GuardaPartida(int tipo);

	/* Guarda los nodoG->visitado de 'graf' en archivo 'f' */
	DLL_EXPORT void GuardarGrafo(FILE* f, Grafo* graf);

	/* Marca el nodo con key 'code' del grafo 'graf' con el valor de visitado = 'valor' */
	DLL_EXPORT void  MarcaNodo(int tipo,int code, int valor);

	/* Guarda el manager general */
	DLL_EXPORT int GuardaManagerG();

	/* Imprime las claves del grafo 'lv' con recorrido por anchura */
	DLL_EXPORT void ImprimeGrafo(int tipo);

	/*Carga str con nombre de archivo a buscar a través de 'tipo'*/
	DLL_EXPORT void CargaTipo(char* str, int tipo);

	/*llena la lista puntjes a partir de el string linea*/
	DLL_EXPORT void C_Puntaje(char* linea, Listilla* puntajes);

	/* Guarfa los puntajes de la lista L en una linea en el archivo f */
	DLL_EXPORT void GuardaPuntajes(Listilla* L,FILE* f);	

	/* Retorna un grafo a partir de 'tipo' */
	DLL_EXPORT Grafo* RetornaGrafo(int tipo);

	/* Retorna el manager general para su uso fuera del dll */
	DLL_EXPORT Manager_general* RetornaManG();

	/*Retorna el manager de partida para su uso fuera del dll*/
	DLL_EXPORT Manager_partida* RetornaManP();

	/* Retorna una lista con los niveles disponibles a partir de graf_lvl */
	DLL_EXPORT Listilla* NodosDisponibles();

	/* Aumenta la cantidad de muertes del jugador */
	DLL_EXPORT void AumentaMuertes();

	/* Aumenta la cantidad de veces que se ha asado una línea */
	DLL_EXPORT void AumentaLinea(int nL);


#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
