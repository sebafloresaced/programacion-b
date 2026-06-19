#include <stdio.h>
#include "Pilas.h"
void Orden(TPila *P,unsigned int N);
void OrdenInverso(TPila *P,unsigned int N);
void IngresarDatos(TPila *P1,TPila *P2);
int main(){
  TPila P1,P2;
  unsigned int N;
  IngresarDatos(&P1,&P2);
  printf("\nIngresa N: ");
  scanf("%u",&N);
  OrdenInverso(&P1,N);
  Orden(&P2,N);
  return 0;
}
void OrdenInverso(TPila *P,unsigned int N){
  unsigned int i,aux;
  for (i=0;i<N;i++) {
    sacaP(P,&aux);
    printf("\n%u",aux);
  }
}
void Orden(TPila *P,unsigned int N){
  TPila Paux;
  unsigned int i,aux;
  IniciaP(&Paux);
  for (i=0;i<N;i++) {
    sacaP(P,&aux);
    poneP(&Paux,aux);
  }
  for (i=0;i<N;i++) {
    sacaP(&Paux,&aux);
    printf("\n%u",aux);
  }
}
void IngresarDatos(TPila *P1,TPila *P2){
  unsigned int DNI;
  IniciaP(P1); IniciaP(P2);
  printf("Ingresa el DNI del votante (0 para terminar): ");
  scanf("%u",&DNI);
  while (DNI) { //DNI != 0
    poneP(P1,DNI); poneP(P2,DNI);
    printf("\nIngresa el DNI del votante (0 para terminar): ");
    scanf("%u",&DNI);
  }
}
