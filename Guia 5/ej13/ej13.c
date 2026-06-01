#include "Cola.h"

void IniciaC (TCola *C){
  C->inicio = 0;
  C->fin = -1;
  C->cant = 0;
}

int VaciaC (TCola C){
  return C.cant == 0;
}

TElementoC consultaC (TCola C){
  return C.datos[C.inicio];
}

void sacaC (TCola *C, TElementoC *x){
  *x = C->datos[C->inicio];
  C->inicio = (C->inicio + 1) % MaxElem;
  C->cant--;
}

void poneC (TCola *C, TElementoC x){
  C->fin = (C->fin + 1) % MaxElem;
  C->datos[C->fin] = x;
  C->cant++;
}
