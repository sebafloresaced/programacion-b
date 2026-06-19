#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
  int dato;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;

typedef struct nodoD {
  int dato;
  struct nodoD *sig,*ant;
} nodoD;
typedef nodoD *PnodoD;
typedef struct {
  PnodoD pri,ult;
} TListaD;

void CargaLista(TLista *LS);
void CopiaLista(TLista LS,TLista *LC,TListaD *LD);
int main(){
  TLista LS,LC;
  TListaD LD;
  CargaLista(&LS);
  CopiaLista(LS,&LC,&LD);
  return 0;
}
void CopiaLista(TLista LS,TLista *LC,TListaD *LD){
  PnodoD nuevoD;
  TLista nuevoC;
  *LC = NULL;
  LD->pri = LD->ult = NULL;
  while (LS != NULL) {
    nuevoD = (PnodoD)malloc(sizeof(nodoD));
    nuevoC = (TLista)malloc(sizeof(nodo));
    nuevoD->dato = nuevoC->dato = LS->dato;
    if (*LC == NULL) { // primera iteracion
      *LC = nuevoC;
      nuevoC->sig = nuevoC;

      LD->pri = LD->ult = nuevoD;
      nuevoD->ant = nuevoD->sig = NULL;
    }
    else {
      nuevoC->sig = (*LC)->sig;
      (*LC)->sig = nuevoC;
      *LC = nuevoC;

      nuevoD->sig = NULL;
      nuevoD->ant = LD->ult;
      LD->ult->sig = nuevoD;
      LD->ult = nuevoD;
    }
    LS = LS->sig;
  }
}

void CargaLista(TLista *LS) {
}
