#include <stdio.h>
#define MaxElem 20
void CargaMat(float V[][MaxElem],unsigned int *N,unsigned int *M);
unsigned int EncuentraCantXInt(float V[][MaxElem],unsigned int i,unsigned int j,unsigned int M,float X);
void EncuentraCantXVoid(float V[][MaxElem],unsigned int i,unsigned int j,unsigned int M,float X,unsigned int *cantX);
int main(){
  float Mat[MaxElem][MaxElem],X;
  unsigned int N,M,cantX;
  CargaMat(Mat,&N,&M);
  printf("Ingresa X: ");
  scanf("%f",&X);
  cantX = EncuentraCantXInt(Mat,N-1,M-1,M-1,X);
  if (cantX>0)
    printf("\nSe encontro el numero %f, %u veces",X,cantX);
  else
    printf("\nNo se encontro el numero %f",X);
  cantX=0;
  EncuentraCantXVoid(Mat,N-1,M-1,M-1,X,&cantX);
  if (cantX>0)
    printf("\nSe encontro el numero %f, %u veces",X,cantX);
  else
    printf("\nNo se encontro el numero %f",X);
  return 0;
}
void CargaMat(float V[][MaxElem],unsigned int *N,unsigned int *M){
  unsigned int i,j;
  printf("\nIngresa N y M: ");
  scanf("%u %u",N,M);
  for (i=0;i<*N;i++)
    for (j=0;j<*M;j++)
      scanf("%f",&V[i][j]);
}
unsigned int EncuentraCantXInt(float V[][MaxElem],unsigned int i,unsigned int j,unsigned int M,float X){
  if (j==0) {
    if (i==0)
      return V[i][j]==X;
    else
      return (V[i][j]==X)? EncuentraCantXInt(V,i-1,M,M,X)+1:EncuentraCantXInt(V,i-1,M,M,X);
  }
  else
    return (V[i][j]==X)? EncuentraCantXInt(V,i,j-1,M,X)+1:EncuentraCantXInt(V,i,j-1,M,X);
}
void EncuentraCantXVoid(float V[][MaxElem],unsigned int i,unsigned int j,unsigned int M,float X,unsigned int *cantX){
  if (j=0) {
    if (i>0)
      EncuentraCantXVoid(V,i-1,M,M,X,cantX);
    if (V[i][j]==X)
      (*cantX)++;
    }
  else {
    EncuentraCantXVoid(V,i,j-1,M,X,cantX);
    if (V[i][j]==X)
      (*cantX)++;
  }
}
