#include <stdio.h>
#include <stdlib.h>
typedef struct nodo {
  int dato;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;
void CargaVector(int V[],int *N);
void CargaListaOrdenInverso(TLista *L,int V[],int N);
void CargaListaOrden(TLista *L,int V[],int N);
void CargaListaOrdenada(TLista *L,int V[],int N);
int main(){
  return 0;
}
void CargaVector(int V[],int *N){
  int i;
  printf("Ingresa N: ");
  scanf("%d",N);
  for (i=0;i<*N;i++)
    scanf("%d",&V[i]);
}
void CargaListaOrdenInverso(TLista *L,int V[],int N){
  int i;
  TLista aux;
  *L = NULL;
  for (i=0;i<N;i++){
    aux = (TLista)malloc(sizeof(nodo));
    aux->dato = V[i];
    aux ->sig = *L;
    *L = aux;
  }
}
void CargaListaOrden(TLista *L,int V[],int N){
  int i;
  TLista aux,ult;
  *L = NULL;
  for (i=0;i<N;i++){
    aux = (TLista)malloc(sizeof(nodo));
    aux->dato = V[i];
    aux ->sig = NULL;
    if (i==0)
      *L = ult = aux;
    else {
      ult->sig = aux;
      ult = aux;
    }
  }
}
void CargaListaOrdenada(TLista *L,int V[],int N){
  int i;
  TLista act,ant,aux;
  *L = NULL;
  for (i=0;i<N;i++) {
     aux = (TLista)malloc(sizeof(nodo));
     aux->dato = V[i];
     if (*L == NULL || V[i] < (*L)->dato) { //modifico el primero
      aux->sig=*L;
      *L = aux;
     }
     else {
      ant = NULL;
      act = *L;
      while (act != NULL && V[i] > act->dato) {
        ant = act;
        act = act->sig;
      }
      aux->sig = act;
      ant->sig = aux;
     }
  }
}
