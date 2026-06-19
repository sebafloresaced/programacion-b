#include <stdio.h>
#include "Pilas.h"

unsigned int CuentaCeros(TPila *P);
float PromedioPila(TPila *P);
void MaxMinPila(TPila *P,int *max,int *min);
void QuitaMayoresAlUltimo(TPila *P);
int main(){
  TPila P;
  int x,max,min;
  IniciaP(&P);
  poneP(&P,4);
  poneP(&P,0);
  poneP(&P,7);
  poneP(&P,2);
  poneP(&P,0);
  poneP(&P,5);
  printf("\nCantidad de ceros: %u",CuentaCeros(&P));
  printf("\nPromedio: %.2f",PromedioPila(&P));
  MaxMinPila(&P,&max,&min);
  printf("\nMaximo: %d",max);
  printf("\nMinimo: %d",min);
  QuitaMayoresAlUltimo(&P);
  printf("\nPila luego de quitar mayores al ultimo:\n");
  while (!VaciaP(P)) {
    sacaP(&P,&x);
    printf("%d\n",x);
  }
  return 0;
}
unsigned int CuentaCeros(TPila *P){
  TPila Paux;
  int x;
  unsigned int cant = 0;

  IniciaP(&Paux);

  while (!VaciaP(*P)) {
    sacaP(P,&x);
    if (x == 0)
      cant++;
    poneP(&Paux,x);
  }

  while (!VaciaP(Paux)) {
    sacaP(&Paux,&x);
    poneP(P,x);
  }

  return cant;
}
float PromedioPila(TPila *P){
  TPila Paux;
  int x;
  int suma = 0;
  unsigned int cant = 0;

  IniciaP(&Paux);

  while (!VaciaP(*P)) {
    sacaP(P,&x);
    suma += x;
    cant++;
    poneP(&Paux,x);
  }

  while (!VaciaP(Paux)) {
    sacaP(&Paux,&x);
    poneP(P,x);
  }

  if (cant == 0)
    return 0;

  return (float)suma / cant;
}
void MaxMinPila(TPila *P,int *max,int *min){
  TPila Paux;
  int x;

  IniciaP(&Paux);

  if (!VaciaP(*P)) {
    sacaP(P,&x);
    *max = x;
    *min = x;
    poneP(&Paux,x);

    while (!VaciaP(*P)) {
      sacaP(P,&x);

      if (x > *max)
        *max = x;
      if (x < *min)
        *min = x;

      poneP(&Paux,x);
    }

    while (!VaciaP(Paux)) {
      sacaP(&Paux,&x);
      poneP(P,x);
    }
  }
}
void QuitaMayoresAlUltimo(TPila *P){
  TPila Paux;
  int x, ult;

  if (!VaciaP(*P)) {
    IniciaP(&Paux);
    ult = consultaP(*P);

    while (!VaciaP(*P)) {
      sacaP(P,&x);
      if (x <= ult)
        poneP(&Paux,x);
    }

    while (!VaciaP(Paux)) {
      sacaP(&Paux,&x);
      poneP(P,x);
    }
  }
}
