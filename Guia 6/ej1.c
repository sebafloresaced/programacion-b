#include <stdio.h>
#include <stdlib.h>
typedef struct nodo {
  char dato;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;
void CargaLista(TLista *L);
void Muestra(TLista L);
int ContVocales(TLista L);
int Ordenada(TLista L);
void EliminaPos(TLista *L,int P);
int main(){
  TLista L;
  int P;
  CargaLista(&L);
  Muestra(L);
  printf("\n%d nodos tienen una vocal",ContVocales(L));
  if (Ordenada(L))
    printf("\nLa lista esta ordenada");
  else
    printf("\nLa lista esta desordenada");
  printf("\nIngresa P: ");
  scanf("%d",&P);
  EliminaPos(&L,P);
  Muestra(L);
  return 0;
}
void CargaLista(TLista *L){
  char c;
  TLista aux,ult;
  *L = NULL;
  printf("Ingresa un caracter (0 para terminar): ");
  scanf(" %c",&c);
  while (c != '0') {
    aux = (TLista)malloc(sizeof(nodo));
    aux->dato = c;
    aux->sig = NULL;
    if (*L == NULL) // primera iteracion
      *L = ult = aux;
    else {
      ult->sig = aux;
      ult = aux;
    }
    printf("Ingresa un caracter (0 para terminar): ");
    scanf(" %c",&c);
  }
}
void Muestra(TLista L){
  TLista aux;
  aux = L;
  while (aux != NULL){
    printf("%c ",aux->dato);
    aux = aux->sig;
  }
}
int ContVocales(TLista L){
  int cont=0;
  TLista aux;
  aux = L;
  while (aux != NULL){
    if (aux->dato == 'a' ||
        aux->dato == 'A' ||
        aux->dato == 'e' ||
        aux->dato == 'E' ||
        aux->dato == 'i' ||
        aux->dato == 'I' ||
        aux->dato == 'o' ||
        aux->dato == 'O' ||
        aux->dato == 'u' ||
        aux->dato == 'U')
      cont++;
    aux = aux->sig;
  }
  return cont;
}
int Ordenada(TLista L){
  TLista ant,act;
  act = L;
  if (act != NULL) {
    ant = act;
    act = act->sig;
  }
  while (act!=NULL && ant->dato <= act->dato){
    ant = act;
    act = act->sig;
  }
  return act == NULL;
}
void EliminaPos(TLista *L,int P){
  int i=1;
  TLista ant,act;
  if ((*L) != NULL) //no esta vacia
    if (P == 1) {
      act = *L;
      *L = (*L)->sig;
      free(act);
    }
    else {
      act = *L;
      while (act != NULL && i<P) {
        i++;
        ant = act;
        act = act->sig;
      }
      if (act != NULL)
        ant->sig = act->sig;
      free(act);
    }
}
