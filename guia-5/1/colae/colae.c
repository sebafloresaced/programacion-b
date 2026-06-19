#include "ColaE.h"
void IniciaC (TCola * C){
  C->inicio=0;
  C->fin=-1;
}
int VaciaC (TCola C){
  return C.fin < C.inicio;
}
TElementoC consultaC (TCola C){
  return C.datos[C.inicio];
}
void sacaC (TCola *C, TElementoC* x){
  *x = (C->datos)[C->inicio];
  C->inicio++;
}
void poneC (TCola *C, TElementoC x){
  C->fin++;
  (C->datos)[C->fin] = x;
}
