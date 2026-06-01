#include <stdio.h>
#define MaxElem 20
typedef int TMat[MaxElem][MaxElem];
void CargaMat(TMat M,int *N);
int GradoE(TMat M,int j,int N);
int GradoS(TMat M,int i,int N);
int Grado(TMat M,int N);
int main() {
  TMat M;
  int N,v;
  CargaMat(M,&N);
  printf("Ingrese vertice: ");
  scanf("%d",&v);
  printf("Grado de Entrada: %d\nGrado de Salida: %d\nGrado del nodo: %d",GradoE(M,v,N),GradoS(M,v,N),Grado(M,v,N));
  return 0;
}
int GradoE(TMat M,int j,int N) {
  int i,cant=0;
  for (i=0;i<N;i++)
    cant += M[i][j];
  return cant;
}
int GradoS(TMat M,int i,int N){
  int j,cant=0;
  for (j=0;j<N;j++)
    cant += M[i][j];
  return cant;
}
int Grado(TMat M,int i,int N) {
  return GradoE(M,i,N) + GradoS(M,i,N) - M[i][i];
}
