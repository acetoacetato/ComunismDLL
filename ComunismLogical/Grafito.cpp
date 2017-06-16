#include "Grafito.h"



char* transformaString() {
	char* a = (char*)malloc(sizeof(char)*30);
	strcpy(a, "theGame");
	return a;
}

void quitaCaracteres(char* str, char c) {
	str[strlen(str) - 1] = '\0';
}


int AbraArchivo(int tipo) {
	FILE* p;
	int i=0;

	p = fopen("ts.txt", "r");
	if (p) {
		i = 2;
		fclose(p);
	}

	return i;


}


Grafo* ArmaGrafo(int tipo) {


	NodoG* aux;
	Grafo* donGraph = (Grafo*)malloc(sizeof(Grafo));
	char line[BUFFSIZE];
	char nombre[BUFFSIZE];
	donGraph->corrupto = 0;
	char* level = NULL;
	Habilidad* skill = NULL;
	char* sep;
	char* str;
	int es_raiz=1;
	int cont;

	CargaTipo(nombre, tipo);

	if (!nombre) return NULL; //tipo es invalido

	FILE* f = fopen(nombre, "r");
	if (!f) return NULL; //archivo no exise

	/* El archivo de niveles consta de Codigo;visitado o completado;Lista de padres */
	if (tipo == 1) { //si es un grafo de nivel
		do {
			level = (char*)malloc(sizeof(char)* BUFFSIZE);
			fgets(line, BUFFSIZE, f); //cada linea es un nodo del grafo
			//printf("%s\n", line);
			sep = strtok(line, ";");
			cont = 1;
			do {
				//printf("%i", cont);
				switch (cont) {
					
					case 1: //codigo
						str = (char*)malloc(sizeof(char)*BUFFSIZE);
						strcpy(str, sep);
						aux = creaNodo(str, level);
						//printf("%s\n", aux->key);
						if (es_raiz) {
							donGraph->raiz = aux;
							donGraph->current = aux;
							es_raiz = 0;
						}
						
						break;
					case 2: //nivel completado
						aux->visitado = atoi(sep);
						break;
					case 3: //padres
						quitaCaracteres(sep, '\n');
						unePadres(aux, donGraph, sep);
						break;

				}
				sep = strtok(NULL, ";");
				cont++;
			} while (sep);


		} while (!feof(f));
		fclose(f);
		return donGraph;
	}
	/*En caso de que sea un 'arbol' de habilidades*/
	/* En el caso de habilidades, se separa codigo;nombre;visitado o activo;descripcion;efecto u orden al juego;lista de padres */
	do {
		skill = (Habilidad*)malloc(sizeof(Habilidad));

		fgets(line, BUFFSIZE, f); //cada linea es un nodo del grafo
		sep = strtok(line, ";");
		cont = 1;
		do {
			switch (cont) {
			case 1: //code/key

				str = (char*)malloc(sizeof(char)*BUFFSIZE);
				strcpy(str, sep);
				aux = creaNodo(str, level);
				if (es_raiz) {
					donGraph->raiz = aux;
					donGraph->current = aux;
					es_raiz = 0;
				}
				
				break;
			case 2: //nombre
				strcpy(skill->nombre, sep);
				break;
			case 3: //habilidad activa
				aux->visitado = atoi(sep);
				break;
			case 4: //descripcion
				strcpy(skill->descripcion, sep);
				break;
			case 5: //padres
				quitaCaracteres(sep, '\n');
				unePadres(aux, donGraph, sep);
				break;
			}
			sep = strtok(NULL, ";");
			cont++;
		} while (sep);


	} while (!feof(f));
	fclose(f);
	return donGraph;

}

NodoG* creaNodo(char* key, void* data) {
	NodoG* Nod32 = (NodoG*)malloc(sizeof(NodoG));
	Nod32->data = data;
	Nod32->hijos = createList();
	Nod32->Padres = createList();
	strcpy(Nod32->key, key);
	Nod32->visitado = 0;
	return Nod32;
}

void unePadres(NodoG* nodog, Grafo* graf, char* listaPadres) {
	char* sep = strtok(listaPadres, ",");
	NodoG* padre = NULL;

	//printf("padres = %s\n", listaPadres);
	if (!strcmp(listaPadres, "NULL\n") || !strcmp(listaPadres, "NULL")) return;
	do {
		//printf("sep=%s \n", sep);
		padre = buscarNodo(sep, graf, 0);
		




		if (!padre) {

			sep = strtok(NULL,",");
			if(sep) continue;
			else break;
		}

	

		push_back(nodog->Padres, padre);
		push_back(padre->hijos, nodog);
		sep = strtok(NULL, ",");
	} while (sep);

	return;
}




NodoG* buscarNodo(char* key, Grafo* graf, int cambiaCurrent) {
	NodoG* nodo = graf->raiz; //nodo* auxiliar para ir recorriendo el grafo
	Cola* queque = createQeue(); //cola para hacer recorrido por anchura
	Listilla* list = createList(); //lista de visitados
	pushQ(queque, nodo);

	push_back(list, topQ(queque));

	while ( (nodo = (NodoG*)topQ(queque)) ) {

		if (!strcmp(nodo->key, key)) {
			

			return nodo;

		}
		firstL(nodo->hijos); 
		popQ(queque);
		if (is_empty(nodo->hijos)) continue;
		do {


				pushQ(queque, currentL(nodo->hijos));
				push_back(list, currentL(nodo->hijos));
			
		} while (nextL(nodo->hijos));

		pushQ(queque, last(nodo->hijos));
		


	}

	return NULL;
}



int CargaPartida(Grafo* graf_lv, Grafo* graf_UW, Grafo* graf_RW, Grafo* graf_MW, Manager_partida* man, int tipo) {
	
	char linea[BUFFSIZE];
	int Nlinea = 0;
	char save[BUFFSIZE];
	CargaTipo(save, tipo);
	FILE* f = fopen(save, "r");
	if (!f) return 0;
	Nlinea++;
	fgets(linea, BUFFSIZE, f);
	linea[strlen(linea)-1] = '\0';
	do {
		switch(Nlinea){
			case 1:
				C_Grafo(graf_lv, linea, 18);
				break;
			case 2:
				C_Grafo(graf_UW, linea, 8);
				break;
			case 3:
				C_Grafo(graf_RW, linea, 15);
				break;
			case 4:
				C_Grafo(graf_MW, linea, 9);
				break;
			case 5:
				man->lineaA = atoi(linea);
				break;
			case 6:
				man->lineaB = atoi(linea);
				break;
			case 7:
				man->lineaC = atoi(linea);
				break;
			case 8:
				man->muertes = atoi(linea);
				break;

		}


		fgets(linea, BUFFSIZE, f);
	} while (!feof(f));
	fclose(f);
	return 1;
}




void C_Grafo(Grafo* graf_lv, char* linea, int cant_nodos) {
	if ((int)strlen(linea) < cant_nodos || (int)strlen(linea) > cant_nodos) {
		graf_lv->corrupto = 1;
		return;
	}

	Cola* q = createQeue();
	NodoG* nodo = graf_lv->raiz;
	pushQ(q, nodo);
	Listilla* visitados= createList();
	int i = 0;
	while (nodo = (NodoG*)topQ(q)) {

		if (!compruebaPadres(nodo)) {
			graf_lv->corrupto = 1;
			return;
		}
		nodo->visitado = linea[i];
		i++;
		firstL(nodo->hijos);
		popQ(q);
		if (is_empty(nodo->hijos)) continue;
		do {
			if (!searchL(visitados, currentL(nodo->hijos))) {
				pushQ(q, currentL(nodo->hijos));
				push_back(visitados, nodo->hijos);
			}
		} while (nextL(nodo->hijos));
	}
}


int compruebaPadres(NodoG* nodo) {

	if (is_empty(nodo->Padres)) return 1;

	firstL(nodo->Padres);
	do {

		if (!((NodoG*)currentL(nodo->Padres))->visitado) return 0;

	} while (nextL(nodo->Padres));

	return 1;

}


int CargaManager(Manager_general* man, int tipo) {
	FILE* f = NULL;
	char archivo[BUFFSIZE];
	CargaTipo(archivo, tipo);

	f = fopen(archivo, "r");
	char linea[BUFFSIZE];
	char* puntaje;
	fgets(linea, BUFFSIZE, f);
	char* ptge = strtok(linea, ";");
	do {
		puntaje = (char*)malloc(sizeof(char)* strlen(ptge));
		strcpy(puntaje, ptge);
		push_back(man->ptge, puntaje);
		ptge = strtok(NULL, ";");
	} while (ptge);
	fgets(linea, BUFFSIZE, f);
	strcpy_s(man->logros, linea);
	fclose(f);
	return 1;
}



int guardaPartida(Manager_partida* man, Grafo* graf_lv, Grafo* graf_uw, Grafo* graf_rw, Grafo* graf_mw, int tipo) {
	char save[BUFFSIZE];
	CargaTipo(save, tipo);
	if (!save) return 0;
	FILE* f = fopen(save, "w");
	if (!f) return 0;
	GuardarGrafo(f, graf_lv);
	fputc('\n', f); 
	GuardarGrafo(f, graf_uw);
	fputc('\n', f);
	GuardarGrafo(f, graf_rw);
	fputc('\n', f);
	GuardarGrafo(f, graf_mw);
	fputc('\n', f);
	fprintf(f, "%ld\n", man->lineaA);
	fprintf(f, "%ld\n", man->lineaB);
	fprintf(f, "%ld\n", man->lineaC);
	fprintf(f, "%ld\n", man->muertes);
	fclose(f);
	return 1;

}

void GuardarGrafo(FILE* f, Grafo* graf) {
	Listilla* visitados = createList();
	Cola* q = createQeue();
	NodoG* nodo = graf->raiz;
	pushQ(q, nodo);
	while ((nodo = (NodoG*)topQ(q))) {
		fprintf(f, "%i", nodo->visitado);
		firstL(nodo->hijos);
		popQ(q);
		do {
			if (!searchL(visitados, currentL(nodo->hijos))) {
				pushQ(q, currentL(nodo->hijos));
				push_back(visitados, currentL(nodo->hijos));
			}
			
		} while (nextL(nodo->hijos));
	}
}



void  marcaNodo(Grafo* graf, char* code, int valor) {
	NodoG* nodo = buscarNodo(code, graf, 0);
	if (!nodo) return;
	nodo->visitado = valor;

}


void imprimeGrafo(Grafo* lv) {
	Cola* q = createQeue();
	Listilla* vis = createList();
	pushQ(q, lv->raiz);
	if (!topQ(q)) printf("no entra la wea");
	NodoG* nodo = (NodoG*)topQ(q);
	while (nodo) {
		printf("\"%s\"\n", nodo->key);
		popQ(q);
		firstL(nodo->hijos);
		do {
			if (!searchL(vis, currentL(nodo->hijos))) {
				push_back(vis, currentL(nodo->hijos));
				pushQ(q, currentL(nodo->hijos));
			}
		} while (nextL(nodo->hijos));
		nodo = (NodoG*) topQ(q);
	}
	


}


void CargaTipo(char* str, int tipo) {
	switch (tipo) {

	case 1:
		strcpy(str, LVLS);
		return;
	case 2:
		strcpy(str, hab_UW);
		return;
	case 3:
		strcpy(str, hab_RW);
		return;
	case 4:
		strcpy(str, hab_MW);
		return;
	default:
		str = NULL;
		return;
	}
}