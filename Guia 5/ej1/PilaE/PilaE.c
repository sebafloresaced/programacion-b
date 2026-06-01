#include "PilaE.h"
void IniciaP (TPila * P){
  P->tope=-1;
}
void poneP (TPila * P, TElementoP x){
  (P->tope)++;
  (P->datos)[P->tope]=x;
}
void sacaP (TPila * P, TElementoP * x){
  *x=(P->datos)[P->tope];
  (P->tope)--;
}
TElementoP consultaP(TPila P){
  return P.datos[P.tope];
}
int VaciaP (TPila P){
  return P.tope == -1;
}
