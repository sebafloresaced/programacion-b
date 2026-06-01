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
int GradoS(TVec V,int ver,int N);
int Grado(TVec V,int ver,int N);
int main() {
  TVec V;
  int N,ver;
  CargaVec(V,&N);
  printf("Ingrese vertice: ");
  scanf("%d",&ver);
  printf("Grado de Entrada: %d\nGrado de Salida: %d\nGrado del nodo: %d",GradoE(V,ver,N),GradoS(V,ver,N),Grado(V,ver,N));
  return 0;
}
int GradoE(TVec V,int ver,int N){
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
int GradoS(TVec V,int ver,int N){
  TLista aux;
  int cont = 0;
  aux = V[ver];
  while (aux != NULL) {
    cont++;
    aux = aux->sig;
  }
  return cont;
}
int Grado(TVec V,int ver,int N) {
  return GradoE(V,ver,N) + GradoS(V,ver,N);
}
