#include <stdio.h>
#include "Pilas.h"
#include "Colas.h"
#define MaxElem 20

typedef int TMat[MaxElem][MaxElem];
typedef int TVec[MaxElem];

void CargaMat(TMat Mat, int *N);
void InicializaVec(TVec VV, int N);
int TodosVisitados(TVec VV,int N);
void RecorreProfundidad(TMat Mat,TVec VV,int N);
void RecorreAmplitud(TMat Mat,TVec VV,int N);
int CantCompConexas(TMat Mat,TVec VV,int N);

int main() {
  return 0;
}

void InicializaVec(TVec VV, int N){
  int i;
  for (i=0;i<N;i++)
    VV[i] = 0;
}
int TodosVisitados(TVec VV,int N){
  int i=0;
  while (i<N && VV[i] != 0)
    i++;
  if (i<N)
    return 1;
  else
    return 0;
}
void RecorreAmplitud(TMat Mat,TVec VV,int N) {
  int i, ccc=0, v=0;
  TCola C;
  InicializaVec(VV,N);
  IniciaC(&C);
  while (!TodosVisitados(VV,N)) {
    ccc++;
    i = 0;
    while (VV[i] != 0)
      i++;
    VV[i] = ccc;
    printf("%d\n",i);
    poneC(&C,i);
    while (!TodosVisitados(VV,N) && !VaciaC(C)){
      sacaC(&C,&v);
      for (i=0;i<N;i++)
        if (Mat[v][i] == 1 && VV[i] == 0) {
          VV[i] = ccc;
          printf("%d\n",i);
          poneC(&C,i);
        }
    }
  }
}
void RecorreProfundidad(TMat Mat,TVec VV,int N){
  int i, ccc=0, v=0;
  TPila P;
  InicializaVec(VV,N);
  IniciaP(&P);
  while (!TodosVisitados(VV,N)) {
    ccc++;
    i = 0;
    while (VV[i] != 0)
      i++;
    VV[i] = ccc;
    printf("%d\n",i);
    poneP(&P,i);
    while (!TodosVisitados(VV,N) && !VaciaP(P)){
      v = consultaP(P);
      i = 0;
      while (i < N && (VV[i] != 0 || Mat[v][i] == 0))
        i++;
      if (i < N) {
        VV[i] = ccc;
        printf("%d\n",i);
        poneP(&P,i);
      }
      else {
        sacaP(&P,&v);
      }
    }
  }
}
int CantCompConexas(TMat Mat, TVec VV,int N){
  int i, ccc=0, v=0;
  TCola C;
  InicializaVec(VV,N);
  IniciaC(&C);
  while (!TodosVisitados(VV,N)) {
    ccc++;
    i = 0;
    while (VV[i] != 0)
      i++;
    VV[i] = ccc;
    poneC(&C,i);
    while (!TodosVisitados(VV,N) && !VaciaC(C)){
      sacaC(&C,&v);
      for (i=0;i<N;i++)
        if (Mat[v][i] == 1 && VV[i] == 0) {
          VV[i] = ccc;
          poneC(&C,i);
        }
    }
  }
  return ccc;
}
