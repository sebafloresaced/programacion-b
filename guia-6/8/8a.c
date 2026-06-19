#include <stdio.h>
#include <stdlib.h>
// Lista doblemente enlazada
typedef struct nodo {
  char dato;
  struct nodo *sig,*ant;
} nodo;
typedef nodo *Pnodo;
typedef struct {
  Pnodo pri,ult;
} TLista;
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
  Pnodo aux;
  L->pri = NULL;
  L->ult = NULL;
  printf("Ingresa un caracter (0 para terminar): ");
  scanf(" %c",&c);
  while (c != '0') {
    aux = (Pnodo)malloc(sizeof(nodo));
    aux->dato = c;
    aux->ant = NULL;
    if (L->pri == NULL) { // primera iteracion
      L->pri = L->ult = aux;
      aux->sig = NULL;
    }
    else {
      aux->sig = L->pri;
      L->pri->ant = aux;
      L->pri = aux;
    }
    printf("Ingresa un caracter (0 para terminar): ");
    scanf(" %c",&c);
  }
}
void Muestra(TLista L){
  Pnodo aux;
  aux = L.pri;
  while (aux != NULL){
    printf("%c ",aux->dato);
    aux = aux->sig;
  }
}
int ContVocales(TLista L){
  int cont=0;
  Pnodo aux;
  aux = L.pri;
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
  Pnodo act;
  act = L.pri;
  if (act != NULL)
    act = act->sig;
  while (act!=NULL && act->ant->dato <= act->dato)
    act = act->sig;
  return act == NULL;
}
void EliminaPos(TLista *L,int P){
  int i=1;
  Pnodo act;
  if (L->pri != NULL) //no esta vacia
    if (P == 1) {
      act = L->pri;
      L->pri = L->pri->sig;
      if (L->pri == NULL)
        L->ult = NULL;
      else
        L->pri->ant = NULL;
      free(act);
    }
    else {
      act = L->pri;
      while (act != NULL && i<P) {
        i++;
        act = act->sig;
      }
      if (act != NULL) {
        if (act == L->ult) {
          L->ult = L->ult->ant;
          L->ult->sig = NULL;
        }
        else {
          act->ant->sig = act->sig;
          act->sig->ant = act->ant;
        }
        free(act);
      }
    }
}

