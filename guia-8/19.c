#include <stdio.h>
#define MaxElem 20
#define INF 9999
#include "Pilas.h"

typedef int TMat[MaxElem][MaxElem];
typedef int TVec[MaxElem];

void CargaMat(TMat Mat, int *N);
void CargaLista(TVec VecL,int *N);
int AlcanzableMat(TMat Mat, int N, int origen, int destino);
int AlcanzableLis(TVec VecL, int N, int origen, int destino);

int main(){
  return 0;
}

int AlcanzableMat(TMat Mat, int N, int origen, int destino){
  TPila P;
  TVec VV;
  int v, i;

  InicializaVec(VV,N);
  IniciaP(&P);

  VV[origen] = 1;
  poneP(&P,origen);

  while (!VaciaP(P) && VV[destino] == 0) {
    sacaP(&P,&v);

    for (i=0;i<N;i++)
      if (Mat[v][i] != 0 && VV[i] == 0) {
        VV[i] = 1;
        poneP(&P,i);
      }
  }

  return VV[destino];
}
int AlcanzableLista(TVec V, int N, int origen, int destino){
  TPila P;
  TVec VV;
  TLista aux;
  int v;

  InicializaVec(VV,N);
  IniciaP(&P);

  VV[origen] = 1;
  poneP(&P,origen);

  while (!VaciaP(P) && VV[destino] == 0) {
    sacaP(&P,&v);

    aux = V[v];

    while (aux != NULL) {
      if (VV[aux->dato] == 0) {
        VV[aux->dato] = 1;
        poneP(&P,aux->dato);
      }

      aux = aux->sig;
    }
  }

  return VV[destino];
}
