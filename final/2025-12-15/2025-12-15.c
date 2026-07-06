// Inciso 1 (6 pts)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilas.h"
#define MaxChar 11

typedef struct nodito {
  char nadador[MaxChar];
  float tiempo; // descendente
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

typedef struct nodoD{
  unsigned int Prueba;
  float tiempoRecord;
  TSubL nadadores;
  struct nodoD *ant,*sig;
} nodoD;
typedef nodoD *PnodoD;
typedef struct {
  PnodoD pri,ult;
} TListaD;

void CargaPila(TPila *P);
void CargaLN(TListaD *LN);
void CargaNadador(TLista *LN, TElementoP Rnadador, int *cargado);
void ProcesaP(TPila *P,TListaD *LN);

// Inciso 1.a
int main() {
  TPila P;
  TListaD LN;
  IniciaP(&P);
  CargaPila(&P);
  CargaLN(&LN);
  ProcesaP(&P,&LN);
  return 0;
}

void CargaNadador(TListaD *LN, TElementoP Rnadador, int *cargado) {
  PnodoD auxD,nuevoD;
  TSubL actSub,antSub,nuevoSub;
  auxD = LN->pri;
  while (auxD != NULL && auxD->Prueba < Rnadador.TipoPrueba)
    auxD = auxD->sig;
  if (auxD != NULL && auxD->Prueba == Rnadador.TipoPrueba) { // encontre la prueba
    actSub = auxD->nadadores;
    antSub = NULL;
    while (actSub != NULL && strcmp(actSub->nadador,Rnadador.nadador) != 0) {
      antSub = actSub;
      actSub = actSub->sig;
    }
    if (actSub != NULL && strcmp(actSub->nadador,Rnadador.nadador) == 0) { // encontre el nadador
      if (actSub->tiempo > Rnadador.tiempo) { // tengo que actualizar el tiempo
        antSub->sig = actSub->sig;
        free(actSub);
      }
      else { // no tengo que actualizar nada
        *cargado = 0;
      }
    }
    if (*cargado == 1) {
      nuevoSub = (TSubL)malloc(sizeof(nodito));
      strcpy(nuevoSub->nadador,Rnadador.nadador);
      nuevoSub->tiempo = Rnadador.tiempo;
      actSub = auxD->nadadores;
      antSub = NULL;
      while (actSub != NULL && actSub->tiempo > Rnadador.tiempo) {
        antSub = actSub;
        actSub = actSub->sig;
      }
      if (actSub == auxD->nadadores) { // Actualizo la cabecera
        nuevoSub->sig = auxD->nadadores;
        auxD->nadadores = nuevoSub;
      }
      else { // Inserto en el medio
        nuevoSub->sig = actSub;
        antSub->sig = nuevoSub;
      }
    }
    // Actualizo el mejor tiempo de la prueba
    if (auxD->tiempoRecord > Rnadador.tiempo)
      auxD->tiempoRecord = Rnadador.tiempo;
  }
  else { // Tengo que crear la prueba
    nuevoD = (PnodoD)malloc(sizeof(nodoD));
    nuevoSub = (TSubL)malloc(sizeof(nodito));
    nuevoSub->sig = NULL;
    nuevoD->tiempoRecord = nuevoSub->tiempo = Rnadador.tiempo;
    strcpy(nuevoSub->nadador,Rnadador.nadador);
    nuevoD->nadadores = nuevoSub;
    nuevoD->Prueba = Rnadador.TipoPrueba;
    *cargado = 1;
    if (auxD == LN->pri) { // Inserto al principio
      nuevoD->ant = NULL;
      nuevoD->sig = LN->pri;
      LN->pri = nuevoD;
      if (auxD == NULL) { // estaba vacia
        LN->ult = nuevoD;
      }
      else {
        auxD->ant = nuevoD;
      }
    }
    else {
      if (auxD == NULL) { // Inserto al final
        nuevoD->ant = LN->ult;
        nuevoD->sig = NULL;
        LN->ult->sig = nuevoD;
        LN->ult = nuevoD;
      }
      else { // Inserto en el medio
        nuevoD->sig = auxD;
        nuevoD->ant = auxD->ant;
        auxD->ant->sig = nuevoD;
        auxD->ant = nuevoD;
      }
    }
  }
}

void ProcesaP(TPila *P,TListaD *LN) {
  int cargado = 1;
  TElementoP Rnadador;
  if (!VaciaP(*P)) {
    SacaP(P,&Rnadador);
    CargaNadador(LN,Rnadador,&cargado);
    ProcesaP(P,LN);
    if (!cargado)
    PoneP(P,Rnadador);
  }
}

// Inciso 1.b
// "Pilas.h"
#define MaxElem 30

typedef struct {
  char nadador[11];
  unsigned int TipoPrueba;
  float tiempo;
} TElementoP;
typedef struct {
  TElementoP datos[MaxElem];
  int tope;
} TPila;

void PoneP(TPila P,TElementoP x);

// "Pilas.c"
#include "Pilas.h"
void PoneP(TPilaP *P,TElementoP x){
  if (P->tope != MaxElem-1) { // si no esta llena
    P->tope += 1;
    P->datos[P->tope] = x;
  }
}

// Inciso 2 (3 pts)
#include <stdio.h>
#include <stdlib.h>
#define MaxElem 30

typedef unsigned int TMat[MaxElem][MaxElem];
typedef struct nodo {
  int vertice;
  struct nodo *izq,*der;
} nodo;
typedef nodo *ABB;

void CargaMat(TMat Mat,int *N);
void CargaArbol(ABB *A);
int EstaEnABB(ABB A,int x);
int CantCumplen(TMat Mat,int N,ABB A);

int main() {
  ABB A;
  TMat Mat;
  int N;
  CargaMat(Mat,&N);
  CargaArbol(&A);
  printf("%d vertices cumplen la condicion",CantCumplen(Mat,N,A));
  return 0;
}

int EstaEnABB(ABB A,int x){
  if (A == NULL)
    return 0;
  else {
    if (A->vertice == x)
      return 1;
    else {
      if (A->vertice < x)
        return EstaEnABB(A->der,x);
      else
        return EstaEnABB(A->izq,x);
    }
  }
}

int CantCumplen(TMat Mat,int N,ABB A){
  int i, j, sumaCostos, cumplen=0;
  for (i=0;i<N;i++) {
    sumaCostos=0;
    for (j=i;j<N;j++)
      if (i != j)
        sumaCostos += Mat[i][j];
      else
        sumaCostos += Mat[i][j] + Mat[j][i];
    if (!EstaEnABB(A,sumaCostos))
      cumplen++;
  }
  return cumplen;
}

// Inciso 3 (1 pts)
"Indicar V o F: Dado un AAM sobre un grafo G, el costo de ir del vertice i al v'ertice j considerando las aristas del AAm es menor que el costo de hacerlo a traves de G"
Falso. El AAM busca un grafo conexo de costos minimos (totales), lo cual no asegura costos minimos entre todos los pares de vertices.
Ejemplo:
V = {A, B, C, D}
Costos:
  A->B = 3;
  A->C = 1;
  C->D = 2;
  D->B = 1;

El AAM conservaria las aristas:
  A->C = 1;
  C->D = 2;
  D->B = 1;

Vemos que en el AAM, el costo de ir del vertice A al B es 4, pero en el grafo original G era 3.

// Correcciones:
Ejercicio 1:
  Si tengo que actualizar el tiempo del nadador, no contemplo que este actualizando el primer nodo. (antSub == NULL)

// Puntajes:
Ejercicio 1: 4.5/6
Ejercicio 2: 3/3
Ejercicio 3: 1/1
Total: 8.5/10
