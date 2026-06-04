#include <stdio.h>
#include <stdlib.h>
#define MaxElem 20

typedef struct nodo {
  int dato;
  struct nodo *sig;
} nodo;

typedef nodo *TLista;
typedef TLista TVec[MaxElem];

void CargaVec(TVec V,int *N);
int GradoE(TVec V,int ver,int N);
int MayorGradoE(TVec V,int N);

int main() {
  TVec V;
  int N, pos;
  CargaVec(V,&N);
  pos = MayorGradoE(V,N);
  printf("El vertice con mayor grado de entrada es: %d",pos);
  return 0;
}

int GradoE(TVec V,int ver,int N) {
  int i,cant=0;
  TLista aux;
  for (i=0;i<N;i++) {
    aux = V[i];
    while (aux != NULL) {
      if (aux->dato == ver)
        cant++;
      aux = aux->sig;
    }
  }
  return cant;
}
int MayorGradoE(TVec V,int N) {
  int i,posMax=0;
  for (i=1;i<N;i++)
    if (GradoE(V,i,N) > GradoE(V,posMax,N))
      posMax = i;
  return posMax;
}
