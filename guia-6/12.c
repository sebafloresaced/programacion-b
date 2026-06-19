#include <stdio.h>
#include <stdlib.h>

// Sublista
typedef struct nodito {
  int dato;
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

// Lista Doble
typedef struct {
  int A,B;
} Rrango;
typedef struct nodoD {
  Rrango rango;
  TSubL sub;
  struct nodoD *sig,*ant;
} nodoD;
typedef nodoD *PnodoD;
typedef struct {
  PnodoD pri,ult;
} TListaD;

// Lista Simple
typedef struct nodo {
  float promedio;
  unsigned int fuera_rango;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;

void CargaListaD(TListaD *LD);
void GeneraLista(TLista *L,TListaD LD);

int main(){
  TListaD LD;
  TLista L;
  CargaListaD(&LD);
  GeneraLista(&L,LD);
  return 0;
}

void CargaListaD(TListaD *LD){
}
void GeneraLista(TLista *L,TListaD LD){
  TSubL auxS; // Recorre la sublista
  TLista nuevo; // Genera la lista
  unsigned int cont;
  int acum;

  *L = NULL;
  while (LD.ult != NULL) {
    nuevo = (TLista)malloc(sizeof(nodo));
    nuevo->fuera_rango = 0;
    cont = acum = 0;
    auxS = LD.ult->sub;
    while (auxS != NULL) {
      cont++;
      acum += auxS->dato;
      if (auxS->dato < LD.ult->rango.A || auxS->dato > LD.ult->rango.B)
        nuevo->fuera_rango += 1;
      auxS = auxS->sig;
    }
    if (cont > 0)
      nuevo->promedio = (float)acum/cont;
    else
      nuevo->promedio = 0;
    nuevo->sig = *L;
    *L = nuevo;
    LD.ult = LD.ult->ant;
  }
}
