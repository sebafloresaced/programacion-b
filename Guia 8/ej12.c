#include <stdio.h>
#include "Pilas.h"
#include "Colas.h"
#define MaxElem 20

typedef struct nodo {
  int dato;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;
typedef TLista TVecL[MaxElem];
typedef int TVec[MaxElem];

void CargaLista(TVecL VL, int *N);
void InicializaVec(TVec VV, int N);
int TodosVisitados(TVec VV,int N);
void RecorreProfundidad(TVecL VL,TVec VV,int N);
void RecorreAmplitud(TVecL VL,TVec VV,int N);
int CantCompConexas(TVecL VL,TVec VV,int N);

int main() {
  return 0;
}

void InicializaVec(TVec VV, int N){
  int i;
  for (i=0;i<N;i++)
    VV[i] = 0;
}
int TodosVisitados(TVec VV,int N){
  int i=0;
  while (i<N && VV[i] != 0)
    i++;
  if (i<N)
    return 1;
  else
    return 0;
}
void RecorreAmplitud(TVecL VL,TVec VV,int N) {
  int i, ccc=0, v=0, encontre;
  TCola C;
  InicializaVec(VV,N);
  IniciaC(&C);
  while (!TodosVisitados(VV,N)) {
    ccc++;
    i = 0;
    while (VV[i] != 0)
      i++;
    VV[i] = ccc;
    printf("%d\n",i);
    poneC(&C,i);
    while (!TodosVisitados(VV,N) && !VaciaC(C)){
      sacaC(&C,&v);
      aux = V[v];
      while (aux != NULL) {
        if (VV[aux->dato] == 0) {
          VV[aux->dato] = ccc;
          printf("%d\n",aux->dato);
          poneC(&C,aux->dato);
        }
        aux = aux->sig;
      }
    }
  }
}
void RecorreProfundidad(TVecL VL,TVec VV,int N){
  int i, ccc=0, v=0, encontre;
  TPila P;
  InicializaVec(VV,N);
  IniciaP(&P);
  while (!TodosVisitados(VV,N)) {
    ccc++;
    i = 0;
    while (VV[i] != 0)
      i++;
    VV[i] = ccc;
    printf("%d\n",i);
    poneP(&P,i);
    while (!VaciaP(P)) {
      v = consultaP(P);
        aux = V[v];
      encontre = 0;
      while (aux != NULL && !encontre) {
        if (VV[aux->dato] == 0)
          encontre = 1;
        else
          aux = aux->sig;
      }
      if (encontre) {
        VV[aux->dato] = ccc;
        printf("%d\n",aux->dato);
        poneP(&P,aux->dato);
      }
      else {
        sacaP(&P,&v);
      }
    }
  }
}
int CantCompConexas(TVecL VL, TVec VV,int N){
  int i, ccc=0, v=0, encontre;
  TPila P;
  InicializaVec(VV,N);
  IniciaP(&P);
  while (!TodosVisitados(VV,N)) {
    ccc++;
    i = 0;
    while (VV[i] != 0)
      i++;
    VV[i] = ccc;
    printf("%d\n",i);
    poneP(&P,i);
    while (!VaciaP(P)) {
      v = consultaP(P);
      aux = V[v];
      encontre = 0;
      while (aux != NULL && !encontre) {
        if (VV[aux->dato] == 0)
          encontre = 1;
        else
          aux = aux->sig;
      }
      if (encontre) {
        VV[aux->dato] = ccc;
        printf("%d\n",aux->dato);
        poneP(&P,aux->dato);
      }
      else {
        sacaP(&P,&v);
      }
    }
  }
  return ccc;
}
