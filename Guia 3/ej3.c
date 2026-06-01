#include <stdio.h>
#define MaxElem 20
void CargaVector(int V[],unsigned int *N);
float Promedio(int V[],unsigned int i,unsigned int N);
int main(){
  int V[MaxElem];
  unsigned int N;
  CargaVector(V,&N);
  printf("\nEl promedio de sus elementos es %.2f",Promedio(V,0,N-1));
  return 0;
}
void CargaVector(int V[],unsigned int *N){
  unsigned int i;
  printf("Ingrese N: ");
  scanf("%u",N);
  for (i=0;i<*N;i++)
    scanf("%d",&V[i]);
}
float Promedio(int V[],unsigned int i,unsigned int N){
  if (i==0)
    return (V[i] + Promedio(V,i+1,N)) / (N+1);
  else
    if (i==N)
      return V[N];
    else
      return V[N] + Promedio(V,i+1,N);
}
