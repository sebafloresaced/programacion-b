#include <stdio.h>
#include "Pilas.h"
void CargaVotantes(TPila *P);
void MuestraUltimosInversoRec(TPila *P,unsigned int N);
void MuestraUltimosOrdenRec(TPila *P,unsigned int N);
int main(){
  TPila P;
  unsigned int N;

  CargaVotantes(&P);

  printf("\nIngresa N: ");
  scanf("%u",&N);

  printf("\nUltimos N votantes en orden inverso:\n");
  MuestraUltimosInversoRec(&P,N);

  printf("\nUltimos N votantes en el orden que sufragaron:\n");
  MuestraUltimosOrdenRec(&P,N);

  return 0;
}
void CargaVotantes(TPila *P){
  unsigned int dni;

  IniciaP(P);

  printf("Ingresa el DNI del votante (0 para terminar): ");
  scanf("%u",&dni);

  while (dni != 0) {
    poneP(P,dni);
    printf("Ingresa el DNI del votante (0 para terminar): ");
    scanf("%u",&dni);
  }
}
void MuestraUltimosInversoRec(TPila *P,unsigned int N){
  unsigned int x;

  if (N > 0 && !VaciaP(*P)) {
    sacaP(P,&x);
    printf("%u\n",x);
    MuestraUltimosInversoRec(P,N-1);
    poneP(P,x);
  }
}
void MuestraUltimosOrdenRec(TPila *P,unsigned int N){
  unsigned int x;

  if (N > 0 && !VaciaP(*P)) {
    sacaP(P,&x);
    MuestraUltimosOrdenRec(P,N-1);
    printf("%u\n",x);
    poneP(P,x);
  }
}
