#include <stdio.h>
#include <stdlib.h>
typedef struct nodo {
  char dato;
  struct nodo *sig,*ant;
} nodo;
typedef nodo *Pnodo;
typedef struct {
  Pnodo pri,ult;
} TLista;
void CargaLista(TLista *L);
int Cumple(TLista L);
int main(){
  TLista L;
  CargaLista(&L);
  if (Cumple(L))
    printf("La cadena es palindroma");
  else
    printf("La cadena no es palindroma");
  return 0;
}
void CargaLista(TLista *L){
}
int Cumple(TLista L){
  if (L.pri != L.ult) {
    while (L.pri->dato == L.ult->dato && L.pri != L.ult && L.pri != L.ult->ant) {
      L.pri = L.pri->sig;
      L.ult = L.ult->ant;
    }
    return L.pri->dato == L.ult->dato;
  }
  else // Lista vacia o con un caracter
    return 1;
}
