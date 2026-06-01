#include <stdio.h>
#include <stdlib.h>
#include "Pilas.h"
#include "Colas.h"
typedef struct nodo {
  TCola dato;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;
void CargaLista(TLista *L);
void MaxCola(TCola *C,int *max);
void GeneraPila(TPila *P,TLista L);
int main(){
  TPila P;
  TLista L;
  CargaLista(&L);
  GeneraPila(&P,L);
  return 0;
}
void MaxCola(TCola *C,int *max){
  int num;
  if (VaciaC(*C))
    return 0;
  else {
    sacaC(C,&num);
    *max = num;
    while (!VaciaC(*C)) {
      sacaC(C,&num);
      if (*max < num)
        *max = num;
    }
  }
}
void GeneraPila(TPila *P,TLista L){
  TLista aux;
  int max;
  aux = L;
  IniciaP(P);
  while (aux != NULL) {
    MaxCola(&(aux->dato),&max);
    PoneP(P,max);
    aux = aux->sig;
  }
}
