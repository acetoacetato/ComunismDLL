#include "Grafito.h"
Grafo* graf_lvl;
Grafo* graf_UWG;
Grafo* graf_MWG;
Grafo* graf_RWG;
Manager_partida* manP;
Manager_general* manG;


void quitaCaracteres(char* str, char c) {
	str[strlen(str) - 1] = '\0';
}


int AbraArchivo(char* str) {
	printf("%s", str);
	FILE* p;
	int i=0;

	p = fopen(str, "r");
	if (p) {
		i = 2;
		fclose(p);
	}

	return i;


}

/* Crea un grafo, de acuerdo a 'tipo' se abrie cierto archivo y se arma un grafo específico de acuerdo a 'tipo'*/
Grafo* ArmaGrafo(int tipo) {


	NodoG* aux;
	Grafo* donGraph = (Grafo*)malloc(sizeof(Grafo));
	switch (tipo) {
		case 1:
			graf_lvl = donGraph;
			break;
		case 2:
			graf_UWG = donGraph;
		case 3:
			graf_RWG = donGraph;
			break;
		case 4:
			graf_MWG = donGraph;
	
	}
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
						aux = CreaNodo(atoi(str), level);
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
						UnePadres(aux, donGraph, sep);
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
		skill->descripcion = (char*)malloc(sizeof(char) * 3000);
		skill->nombre = (char*) malloc(sizeof(char) * 300);
		fgets(line, BUFFSIZE, f); //cada linea es un nodo del grafo
		if (!strcmp(line, "NULL")) break;
		sep = strtok(line, ";");
		cont = 1;
		do {
			
			switch (cont) {
			case 1: //code/key

				str = (char*)malloc(sizeof(char)*BUFFSIZE);
				strcpy(str, sep);
				aux = CreaNodo(atoi(str), skill);
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
				UnePadres(aux, donGraph, sep);
				break;
			}
			sep = strtok(NULL, ";");
			cont++;
		} while (sep);


	} while (!feof(f));
	fclose(f);
	return donGraph;

}

/* Crea un nodo para el grafo y crea listas vacías de padres e hijos */
NodoG* CreaNodo(int key, void* data) {
	NodoG* Nod32 = (NodoG*)malloc(sizeof(NodoG));
	Nod32->data = data;
	Nod32->hijos = createList();
	Nod32->Padres = createList();
	Nod32->key = key;
	Nod32->visitado = 0;
	return Nod32;
}

/* Llena lista de padres de 'nodoG' con string 'listaPadres' y los une hacia ambos lados */
void UnePadres(NodoG* nodog, Grafo* graf, char* listaPadres) {
	printf("Llamada:%s\n", listaPadres);
	char* sep = strtok(listaPadres, ",");
	NodoG* padre = NULL;

	if (!strcmp(listaPadres, "NULL\n") || !strcmp(listaPadres, "NULL")) return;
	
	do { 
		printf("sep=%s \n", sep); 
		padre = BuscarNodo(atoi(sep), graf, 0);
		




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



/* Busca un nodo en grafo 'graf' con key 'key' y cambia el current si 'cambiaCurrent' es 1 */
NodoG* BuscarNodo(int key, Grafo* graf, int cambiaCurrent) {
	NodoG* nodo = graf->raiz; //nodo* auxiliar para ir recorriendo el grafo
	Cola* queque = createQeue(); //cola para hacer recorrido por anchura
	Listilla* list = createList(); //lista de visitados
	pushQ(queque, nodo);

	push_back(list, topQ(queque));

	while ( (nodo = (NodoG*)topQ(queque)) ) {

		if (nodo->key == key) {
			

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


/* Carga partida poblando el grafo de nivel y el manager de partida con los datos en archivo de acuerdo a 'saveN', que es el numero de archivo (archivo de guardado 1, 2 o 3) */
int CargaPartida(int saveN) {
	
	char linea[BUFFSIZE];
	int Nlinea = 0;
	char save[BUFFSIZE];
	
	Grafo* graf_lv = graf_lvl;
	Manager_partida* man = manP;

	switch (saveN) {
		case 1:
			strcpy(save, "sv1.caballo");
			break;
		case 2:
			strcpy(save, "sv2.caballo");
			break;
		case 3:
			strcpy(save, "sv3.caballo");
			break;
		default:
			return 0;
	
	}

	FILE* f = fopen(save, "r");
	if (!f) return 0;
	
	fgets(linea, BUFFSIZE, f);
	
	do {
		Nlinea++;
		linea[strlen(linea) - 1] = '\0';
		switch(Nlinea){
			case 1:
				C_Grafo(graf_lv, linea, 18);
				break;
			case 2:
				man->lineaA = atoi(linea);
				break;
			case 3:
				man->lineaB = atoi(linea);
				break;
			case 4:
				man->lineaC = atoi(linea);
				break;
			case 5:
				man->muertes = atoi(linea);
				break;
			case 6:
				man->puntaje = atoi(linea);

		}


		fgets(linea, BUFFSIZE, f);
	} while (!feof(f));
	fclose(f);
	return 1;
}

Manager_general* ArmaManagerG() {
	Manager_general* man = (Manager_general*)malloc(sizeof(Manager_general));
	manG = man;
	man->HAB_MW = ArmaGrafo(4);
	man->HAB_RW = ArmaGrafo(3);
	man->HAB_UW = ArmaGrafo(2);
	man->logros = (char*)malloc(sizeof(char) * 12);
	man->ptge = createList();
	return man;

	FILE* f = fopen("Manager.txt", "r");
	int lineC = 0;
	char linea[BUFFSIZE];
	if (!f) return 0;
	fgets(linea, BUFFSIZE, f);
	if (linea[strlen(linea) - 1] == '\n') linea[strlen(linea) - 1] = '\0';
	do {
		lineC++;
		switch (lineC) {
		case 1:
			C_Puntaje(linea, man->ptge);
			break;
		case 2:
			strcpy(man->logros, linea);
			break;
		case 3:
			C_Grafo(man->HAB_UW, linea, 8);
			break;
		case 4:
			C_Grafo(man->HAB_RW, linea, 15);
		case 5:
			C_Grafo(man->HAB_MW, linea, 9);
		}
	} while (!feof(f));

	return man;
}



int CargaJuego() {
	Manager_general* manGeneral = manG;
	FILE* f = fopen("Manager.txt", "r");
	int lineC = 0;
	char linea[BUFFSIZE];
	if (!f) return 0;
	fgets(linea, BUFFSIZE, f);
	if (linea[strlen(linea) - 1] == '\n') linea[strlen(linea) - 1] = '\0';
	do {
		lineC++;
		switch (lineC) {
			case 1:
				C_Puntaje(linea, manGeneral->ptge);
				break;
			case 2:
				strcpy(manGeneral->logros, linea);
				break;
			case 3:
				C_Grafo(manGeneral->HAB_UW, linea, 8);
				break;
			case 4:
				C_Grafo(manGeneral->HAB_RW, linea, 15);
			case 5:
				C_Grafo(manGeneral->HAB_MW, linea, 9);
		}
	} while (!feof(f));
	
	return 1;
}



/* Carga grafo especifico con string (cambia nodoG->visitado) */
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

		if (!CompruebaPadres(nodo)) {
			graf_lv->corrupto = 1;
			return;
		}
		nodo->visitado = linea[i]; ///revisar esta wea
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

/* Comprueba que los padres del nodo 'nodo' tiene todos sus padres "visitados" */
int CompruebaPadres(NodoG* nodo) {

	if (is_empty(nodo->Padres)) return 1;

	firstL(nodo->Padres);
	do {

		if (!((NodoG*)currentL(nodo->Padres))->visitado) return 0;

	} while (nextL(nodo->Padres));

	return 1;

}

/* Crea y arga el Manager general con los datos necesrios para iniciar el juego*/
int CargaManager() {
	Manager_general* man = manG;
	man->HAB_UW = graf_UWG;
	man->HAB_RW = graf_RWG;
	man->HAB_MW = graf_MWG;
	man->HAB_UW = ArmaGrafo(2);
	man->HAB_RW = ArmaGrafo(3);
	man->HAB_MW = ArmaGrafo(4);

	FILE* f = NULL;
	f = fopen("Manager.txt", "r");
	if (!f) return 0;
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
	strcpy(man->logros, linea);
	fclose(f);
	return 1;
}


/* Guarda en archivo "sv" + tipo + ".txt" la partida */
int GuardaPartida(int tipo) {
	char save[BUFFSIZE];
	Manager_partida* man = manP;
	Grafo* graf_lv = graf_lvl;
	CargaTipo(save, tipo);
	if (!save) return 0;
	FILE* f = fopen(save, "w");
	if (!f) return 0;
	GuardarGrafo(f, graf_lv);
	fputc('\n', f);
	fprintf(f, "%ld\n", man->lineaA);
	fprintf(f, "%ld\n", man->lineaB);
	fprintf(f, "%ld\n", man->lineaC);
	fprintf(f, "%ld\n", man->muertes);
	fprintf(f, "%ld\n", man->puntaje);
	fclose(f);
	return 1;

}

int GuardaManagerG() {
	Manager_general* man = manG;
	FILE* f = fopen("Manager.caballo", "w");
	if (!f) return 0;
	GuardaPuntajes(man->ptge, f);

	fprintf(f, "\n%s", man->logros);
	fputc((int)"\n", f);
	GuardarGrafo(f, man->HAB_UW);
	fputc((int)"\n", f);
	GuardarGrafo(f, man->HAB_RW);
	fputc((int)"\n", f);
	GuardarGrafo(f, man->HAB_MW);
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


/* Marca el nodo con key 'code' del grafo 'graf' con el valor de visitado = 'valor' */
void MarcaNodo(int tipo, int code, int valor) {
	Grafo* graf;
	switch (tipo) {
		case 1:
			graf = graf_lvl;
			break;
		case 2:
			graf = graf_UWG;
			break;
		case 3:
			graf = graf_RWG;
			break;
		case 4:
			graf = graf_MWG;
			break;
	}

	NodoG* nodo = BuscarNodo(code, graf, 0);
	if (!nodo) return;
	nodo->visitado = valor;

}

/* Imprime las claves del grafo asociado con 'tipo' con recorrido por anchura */
void ImprimeGrafo(int tipo) {
	Grafo* lv;
	switch (tipo) {
	case 1:
		lv = graf_lvl;
		break;
	case 2:
		lv = graf_UWG;
		break;
	case 3:
		lv = graf_RWG;
		break;
	case 4:
		lv = graf_MWG;
		break;
	}
	Cola* q = createQeue();
	Listilla* vis = createList();
	pushQ(q, lv->raiz);
	if (!topQ(q)) printf("Grafo vacio");
	NodoG* nodo = (NodoG*)topQ(q);
	while (nodo) {
		printf("\nkey = \"%i\"\nHijos = ", nodo->key);
		popQ(q);
		if (!firstL(nodo->hijos)) {
			nodo = (NodoG*)topQ(q);
			continue;
		}
		do {
			printf("%i\n", ((NodoG*)currentL(nodo->hijos))->key);
			if (!searchL(vis, currentL(nodo->hijos))) {
				push_back(vis, currentL(nodo->hijos));
				pushQ(q, currentL(nodo->hijos));
			}
		} while (nextL(nodo->hijos));
		nodo = (NodoG*) topQ(q);
	}
	


}

/*Carga str con nombre de archivo a buscar a través de 'tipo'*/
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

/*llena la lista puntjes a partir de el string linea*/
void C_Puntaje(char* linea, Listilla* puntajes) {
	char* line;
	char* tok = strtok(linea, ";");
	while(tok) {
		line = (char*)malloc(sizeof(char)*BUFFSIZE);
		strcpy(line, tok);
		push_back(puntajes, line);
		strtok(NULL, ";");
	};


}

/* Guarfa los puntajes de la lista L en una linea en el archivo f */
void GuardaPuntajes(Listilla* L, FILE* f) {
	
	if (firstL(L)) {
		do {
			fprintf(f, (char*)currentL(L));
		} while (nextL(L));
	
	}
	else {
		fprintf(f, "NULL");
	}
	


}

Manager_partida* ArmaManagerP() {
	manP = (Manager_partida*)malloc(sizeof(Manager_partida));
	return manP;
}



Grafo* RetornaGrafo(int tipo) {
	switch (tipo) {
	case 1:
		return graf_lvl;
		break;
	case 2:
		return graf_UWG;
		break;
	case 3:
		return graf_RWG;
		break;
	case 4:
		return graf_MWG;
		break;
	}
	return NULL;
}



Manager_general* RetornaManG() {
	return manG;
}
Manager_partida* RetornaManP() {
	return manP;
}






Listilla* NodosDisponibles() {
	Grafo* graf = graf_lvl;
	NodoG* aux = graf->raiz;
	Cola* q = createQeue();
	Listilla* L = createList();
	pushQ(q, aux);
	firstL(aux->hijos);
	

	if (((NodoG*)firstL(aux->hijos))->visitado) {
		aux = (NodoG*)currentL(aux->hijos);
	}
	else if (((NodoG*)nextL(aux->hijos))->visitado) {
		aux = (NodoG*)currentL(aux->hijos);
	
	}
	else  if (((NodoG*)nextL(aux->hijos))->visitado) {
		aux = (NodoG*)currentL(aux->hijos);
	}

	if (!firstL(aux->hijos)) return NULL;
	do {
		if (((NodoG*)currentL(aux->hijos))->visitado == 0) push_back(L, currentL(aux->hijos));
	} while (nextL(aux->hijos));

	if (is_empty(L)) {
		push_back(L, ((NodoG*)currentL(aux->hijos))->Padres->first);
	}

	return L;



}