#include <stdio.h>
#define MaxElem 10
typedef struct{
  unsigned int fila;
  unsigned int columna;
  int numero;
} RNumero;
void GeneraVector(int Mat[][3],unsigned int N,unsigned int M,RNumero Vec[],unsigned int *K);
void MuestraVector(RNumero Vec[],unsigned int K);
int main(){
  int Mat[3][3] = {
  {2,6,9},
  {12,5,18},
  {7,3,24}
  };
  unsigned int N = 3,M = 3,K;
  RNumero Vec[MaxElem];
  GeneraVector(Mat,N,M,Vec,&K);
  MuestraVector(Vec,K);
  return 0;
}
void GeneraVector(int Mat[][3],unsigned int N,unsigned int M,RNumero Vec[],unsigned int *K){
  unsigned int suma=N+M,i,j;
  *K=0;
  for (i=0;i<N;i++)
    for (j=0;j<M;j++)
      if (Mat[i][j] % suma == 0) {
        Vec[*K].fila = i;
        Vec[*K].columna = j;
        Vec[*K].numero = Mat[i][j];
        (*K)++;
      }
}
void MuestraVector(RNumero Vec[],unsigned int K){
  unsigned int i;
  printf("Fila\tColumna\tNumero");
  for (i=0;i<K;i++)
    printf("\n%u\t%u\t%d",Vec[i].fila,Vec[i].columna,Vec[i].numero);
}
