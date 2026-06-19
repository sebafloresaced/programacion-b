#include <stdio.h>
#define MaxElem 20
void CargaMat(int V[][MaxElem],unsigned int *N);
int EsSimetrica(int V[][MaxElem],unsigned int i,unsigned int j,unsigned int N); // 0 falso - 1 verdadero
int main(){
  int Mat[MaxElem][MaxElem];
  unsigned int N;
  CargaMat(Mat,&N);
  if (EsSimetrica(Mat,N-2,N-1,N-1)==0)
    printf("\nLa matriz no es simetrica");
  else
    printf("La matriz es simetrica");
  return 0;
}
void CargaMat(int V[][MaxElem],unsigned int *N){
  unsigned int i,j;
  printf("\nIngresa N: ");
  scanf("%u",N);
  for (i=0;i<*N;i++)
    for (j=0;j<*N;j++)
      scanf("%d",&V[i][j]);
}
int EsSimetrica(int V[][MaxElem],unsigned int i,unsigned int j,unsigned int N){
  if ((i==0)&&(j==1))
    return V[i][j]==V[j][i];
  else
    if (j == i + 1)
      return (V[i][j]==V[j][i])? EsSimetrica(V,i-1,N,N):0;
    else
      return (V[i][j]==V[j][i])? EsSimetrica(V,i,j-1,N):0;
}
