#include <stdio.h>
#include <stdlib.h>
// Lista circular
typedef struct nodo {
  char dato;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;
void CargaLista(TLista *L);
void Muestra(TLista L);
int EsVocal(char c);
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
  TLista aux;
  *L = NULL;
  printf("Ingresa un caracter (0 para terminar): ");
  scanf(" %c",&c);
  while (c != '0') {
    aux = (TLista)malloc(sizeof(nodo));
    aux->dato = c;
    aux->sig = NULL;
    if (*L == NULL) // primera iteracion
      *L = aux->sig = aux;
    else {
      aux->sig = (*L)->sig;
      (*L)->sig  = aux;
      *L = aux;
    }
    printf("Ingresa un caracter (0 para terminar): ");
    scanf(" %c",&c);
  }
}
void Muestra(TLista L){
  TLista aux;
  if (L != NULL) {
    aux = L->sig;
    while (aux != L){
      printf("%c ",aux->dato);
      aux = aux->sig;
    }
    printf("%c ",L->dato);
  }
}
int EsVocal(char c){
  return (c == 'a' ||
          c == 'A' ||
          c == 'e' ||
          c == 'E' ||
          c == 'i' ||
          c == 'I' ||
          c == 'o' ||
          c == 'O' ||
          c == 'u' ||
          c == 'U');
}
int ContVocales(TLista L){
  int cont=0;
  TLista aux;
  if (L != NULL) {
    if (EsVocal(L->dato))
      cont++;
    aux = L->sig;
    while (aux != L){
      if (EsVocal(aux->dato))
        cont++;
      aux = aux->sig;
    }
  }
  return cont;
}
int Ordenada(TLista L){
  TLista act;
  if (L != NULL) {
    act = L->sig;
    while (act != L && act->dato <= act->sig->dato)
      act = act->sig;
    return act == L;
  }
  else
    return 0;
}
void EliminaPos(TLista *L,int P){
  int i=1;
  TLista ant,act;
  if ((*L) != NULL && P>=1) {
    ant = *L;
    act = (*L)->sig;
    while (act != (*L)->sig && i<P) {
      i++;
      ant = act;
      act = act->sig;
    }
    if (i==P) {
      if (act == *L) {
        if (act == (*L)->sig)
          *L = NULL;
        else {
          *L = ant;
          ant->sig = act->sig;
        }
      }
      else
        ant->sig = act->sig;
      free(act);
    }
  }
}
