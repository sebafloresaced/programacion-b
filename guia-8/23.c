#include <stdio.h>
#define MaxElem 20
#define INF 9999

typedef int TMat[MaxElem][MaxElem];

void CargaMat(TMat Mat,int *N);
void Floyd(TMat Mat,TMat D,TMat P,int N);
void MuestraCamino(TMat P,int origen,int destino);

int main(){
  return 0;
}

// D: Matriz de distancias mínimas.
// P: Matriz de caminos.
void MuestraCamino(TMat P,int origen,int destino){
  int k;
  k = P[origen][destino];
  if (k == -1)
    printf(" -> %d",destino);
  else {
    MuestraCamino(P,origen,k);
    MuestraCamino(P,k,destino);
  }
}
