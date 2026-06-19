#include <stdio.h>
#define MaxElem 20

void CargaMat(int V[][MaxElem],unsigned int *N,unsigned int *M);
int SumaFila(int V[][MaxElem],unsigned int i,unsigned int j);
int CumpleCondicion(int V[][MaxElem],unsigned int i,unsigned int N,unsigned int M);

int main(){
  int Mat[MaxElem][MaxElem];
  unsigned int N,M;
  CargaMat(Mat,&N,&M);
  if (CumpleCondicion(Mat,0,N-1,M-1)==1)
    printf("\nLa matriz cumple la condicion");
  else
    printf("\nLa matriz no cumple la condicion");
  return 0;
}
void CargaMat(int V[][MaxElem],unsigned int *N,unsigned int *M){
  unsigned int i,j;
  printf("\nIngresa N y M: ");
  scanf("%u %u",N,M);
  for (i=0;i<*N;i++)
    for (j=0;j<*M;j++)
      scanf("%d",&V[i][j]);
}
int SumaFila(int V[][MaxElem],unsigned int i,unsigned int j){
  if (j==0)
    return V[i][j];
  else
    return V[i][j] + SumaFila(V,i,j-1);
}
int CumpleCondicion(int V[][MaxElem],unsigned int i,unsigned int N,unsigned int M){
  if (i==0)
    return (SumaFila(V,0,M) % 2 == 0);
  else
    if (SumaFila(V,i,M) > SumaFila(V,i-1,M))
      return CumpleCondicion(V,i-1,N,M);
    else
      return 0;
}
