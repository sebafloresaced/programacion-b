#include <stdio.h>
#define MaxElem 20
#define INF 9999

typedef int TMat[MaxElem][MaxElem];
typedef int TVec[MaxElem];

void CargaMat(TMat Mat,int *N);
void Dijkstra(TMat Mat,TVec D,TVec P,int N,int origen);
void MuestraCamino(TVec P,int origen,int v);

int main(){
  return 0;
}

// S: vector de vertices visitados.
// D: vector de distancias mínimas.
// P: vector de predecesores.
void MuestraCamino(TVec P,int origen,int v) {
  if (v == origen)
    printf("%d",origen);
  else {
    MuestraCamino(P,origen,P[v]);
    printf(" -> %d",v);
  }
}
