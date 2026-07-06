// Inciso 1 (2 pts)
"Indicar V o F."
a) "Si el valor de la arista (i,j) de G cambia cuando se esta ejecutando el algoritmo de Dijkstra sobre G, el valor de los caminos minimos ya calculados no cambiaran si i y j ya estan en S."
Respuesta:
Flaso. El algoritmo en ejecución puede no darse cuenta. Pero si recalculás desde cero con el nuevo grafo, los caminos mínimos pueden cambiar.

b) "Dado un grafo simple conexo G con |V| = |E| = N, existen sobre G al menos N arboles abarcadores"
Respuesta:
Falso. Un arbol abarcador tiene |V| - 1 aristas, por lo que hay una arista extra formando un ciclo. La unica forma de que haya N arboles abarcadores bajo esta condicion es que el grafo
simple conexo sea un ciclo de N vertices.

Ejemplo:
V = {A,B,C,D}
Aristas:
A->B
B->C
C->A
C->D
N = 4

Hay solo tres arboles abarcadores:
Opcion 1:
  A->B
  B->C
  C->D

Opcion 2:
  B->C
  C->A
  C->D

Opcion 3:
  A->B
  C->A
  C->D

// Inciso 2 (4.5 pts)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIT 21

typedef struct nodito {
    char id[MAX_ID];          // primeros 4 caracteres = interprete
    char titulo[MAX_TIT];
    unsigned int duracion;    // en segundos
    struct nodito *sig;
} TNodoCancion;
typedef TNodoCancion *TSubL;

typedef struct nodoD {
    unsigned int id;          // Id Playlist, ordenada
    TSubL canciones;
    struct nodoD *ant, *sig;
} TNodoD;

typedef TNodoD *PnodoD;

typedef struct {
    PnodoD pri, ult;
} TListaD;

int MismoElemento(TElementoC a, TElementoC b) {
    return a.idPlaylist == b.idPlaylist &&
           strcmp(a.idCancion, b.idCancion) == 0;
}
int EsDUKI(char idCancion[]) {
    return strncmp(idCancion, "DUKI", 4) == 0;
}
int DebeEliminar(TElementoC elem, unsigned int X) {
    return elem.idPlaylist == X && EsDUKI(elem.idCancion);
}
unsigned int BuscaDuracion(TListaD LP, unsigned int idPlaylist, char idCancion[]) {
    PnodoD auxD;
    TSubL auxS;
    auxD = LP.pri;
    while (auxD != NULL && auxD->id < idPlaylist)
        auxD = auxD->sig;
    if (auxD != NULL && auxD->id == idPlaylist) {
        auxS = auxD->canciones;
        while (auxS != NULL && strcmp(auxS->id, idCancion) != 0)
            auxS = auxS->sig;
        if (auxS != NULL)
            return auxS->duracion;
    }
    return 0;
}
void ProcesaCola(TCola *C, TListaD LP, unsigned int X, int *horas, int *minutos) {
    TElementoC primero, elem;
    unsigned int totalSegundos = 0;
    int eliminarPrimero;
    if (VaciaC(*C)) {
        *horas = 0;
        *minutos = 0;
    } else {
        /*
            Tomo el primer elemento como centinela.
            Lo proceso y lo vuelvo a poner al final.
        */
        SacaC(C, &primero);
        totalSegundos += BuscaDuracion(LP, primero.idPlaylist, primero.idCancion);
        eliminarPrimero = DebeEliminar(primero, X);
        PoneC(C, primero);
        /*
            Ahora proceso hasta volver a encontrar el primero.
        */
        while (!VaciaC(*C) && !MismoElemento(ConsultaC(*C), primero)) {
            SacaC(C, &elem);
            totalSegundos += BuscaDuracion(LP, elem.idPlaylist, elem.idCancion);
            if (!DebeEliminar(elem, X))
                PoneC(C, elem);
        }
        /*
            Cuando corto, el primero vuelve a estar al frente.
            Si debía eliminarse, lo saco.
            Si no, lo dejo donde está.
        */
        if (eliminarPrimero) {
            SacaC(C, &elem);
        }
        *horas = totalSegundos / 3600;
        *minutos = (totalSegundos % 3600) / 60;
    }
}

// Inciso b)
void EliminaListaCanciones(TSubL *L, char interprete[], unsigned int idPlaylist) {
    TSubL act, ant;
    int imprimioCabecera = 0;
    act = *L;
    ant = NULL;
    printf("PLAYLIST %u\n", idPlaylist);
    printf("%-15s %-20s\n", "Id Cancion", "Titulo Cancion");
    while (act != NULL) {
        if (strncmp(act->id, interprete, 4) == 0) {
            printf("%-15s %-20s\n", act->id, act->titulo);
            if (ant == NULL) {
                *L = act->sig;
                free(act);
                act = *L;
            } else {
                ant->sig = act->sig;
                free(act);
                act = ant->sig;
            }
        } else {
            ant = act;
            act = act->sig;
        }
    }
}
void EliminaInterpreteXY(TListaD *LP, char interprete[], unsigned int X, unsigned int Y) {
    PnodoD aux;
    unsigned int menor, mayor;
    int eliminoAlgo = 0;
    if (X < Y) {
        menor = X;
        mayor = Y;
    } else {
        menor = Y;
        mayor = X;
    }
    aux = LP->pri;
    while (aux != NULL && aux->id < menor)
        aux = aux->sig;
    printf("Interprete: %.4s\n", interprete);
    while (aux != NULL && aux->id <= mayor) {
        if (aux->id == X || aux->id == Y) {
            if (EliminaListaCanciones(&(aux->canciones), interprete, aux->id))
                eliminoAlgo = 1;
        }
        aux = aux->sig;
    }
    if (!eliminoAlgo)
        printf("No se encontraron canciones del interprete en las playlists indicadas.\n");
}

// Inciso c)
"Colas.h"
#define MAX_ID 16
#define MAXC 100
typedef struct {
    unsigned int idPlaylist;
    char idCancion[MAX_ID];
} TElementoC;

typedef struct {
    TElementoC datos[MAXC];
    int pri;
    int ult;
    int cant;
} TCola;

int VaciaC(TCola C);
int LlenaC(TCola C);
void PoneC(TCola *C, TElementoC x);

"Colas.c"
#include "Colas.h"
int VaciaC(TCola C) {
    return C.cant == 0;
}
int LlenaC(TCola C) {
    return C.cant == MAXC;
}
void PoneC(TCola *C, TElementoC x) {
    if (!LlenaC(*C)) {
        C->ult = (C->ult + 1) % MAXC;
        C->datos[C->ult] = x;
        C->cant++;
    }
}
// Inciso 3 (2 pts)
int CantGradoNivel(arbol A,pos p,int nivel) {
  pos c;
  int aux=0,grado=0;
  if (!Vacio(A)) {
    c = HijoMasIzq(p,A);
    while (!Nulo(c,A)) {
      aux += CantGradoNivel(A,c,nivel+1);
      c = HermanoDer(c,A);
      grado++;
    }
    return aux + (grado==nivel);
  }
  else
   return 0;
}
int VerificanK(arbol A,int K){
  return K == CantGradoNivel(A,Raiz(A),0);
}

// Inciso 4 (1.5 pts)
int Grado(TMat Mat,int K,int j,int N) {
  if (j==N)
    return 0;
  else
    return (Mat[K][j] != 0) + Grado(Mat,K,j+1,N);
}
int CumplenK(TMat Mat,int K,int N) {
  int GradoAnt;
  if (K == 0)
    return 1;
  else {
    GradoAnt = Grado(Mat,K+1,0,N);
    if (GradoAnt != Grado(Mat,K,0,N))
      return 0;
    else
      return CumplenK(Mat,K-1,N);
  }
}
// Invocacion: cumple = CumplenK(Mat,K,N);

// Puntaje:
Ejercicio 1: 2/2
Ejercicio 2: // Hecho con chatgpt
Ejercicio 3: 2/2
Ejercicio 4: 1.5/1.5
Total: 5.5/5.5
