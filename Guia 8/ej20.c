#include <stdio.h>
#define MaxElem 20
#define INF 9999
#include "Pilas.h"

typedef int TMat[MaxElem][MaxElem];
typedef int TVec[MaxElem];

void CargaMat(TMat Mat, int *N);
void CargaLista(TVec VecL,int *N);
int CantAristasMat(TMat Mat,int N,int origen,int destino);

int main(){
  return 0;
}

int CantAristasMat(TMat Mat,int N,int origen,int destino){
  TCola C;
  TVec Dist[MaxElem];
  int i,v;

  for (i=0;i<N;i++)
    Dist[i] = -1;

  IniciaC(&C);

  Dist[origen] = 0;
  poneC(&C,origen);

  while (!VaciaC(C) && Dist[destino] == -1) {
    sacaC(&C,&v);

    for (i=0;i<N;i++)
      if (Mat[v][i] != 0 && Dist[i] == -1) {
        Dist[i] = Dist[v] + 1;
        poneC(&C,i);
      }
  }

  return Dist[destino];
}
int CantAristasLista(TVec V,int N,int origen,int destino){
  TCola C;
  TLista aux;
  TVec Dist[MaxElem];
  int i,v;

  for (i=0;i<N;i++)
    Dist[i] = -1;

  IniciaC(&C);

  Dist[origen] = 0;
  poneC(&C,origen);

  while (!VaciaC(C) && Dist[destino] == -1) {
    sacaC(&C,&v);

    aux = V[v];

    while (aux != NULL) {
      if (Dist[aux->dato] == -1) {
        Dist[aux->dato] = Dist[v] + 1;
        poneC(&C,aux->dato);
      }

      aux = aux->sig;
    }
  }

  return Dist[destino];
}
