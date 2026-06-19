#include <stdio.h>
#include <stdlib.h>
#define MaxElem 20
void CreaVector(float **pvec,unsigned int *N);
void MuestraVector(float *pvec,unsigned int N);
int main(){
  unsigned int N;
  float *pvec;
  CreaVector(&pvec,&N);
  MuestraVector(pvec,N);
  free(pvec);
  return 0;
}
void CreaVector(float **pvec,unsigned int *N){
  unsigned int i;
  printf("Ingresa N: ");
  scanf("%u",N);
  *pvec = (float *)malloc(*N * sizeof(float));
  for (i=0;i<*N;i++)
    scanf("%f",*pvec + i);
}
void MuestraVector(float *pvec,unsigned int N){
  unsigned int i;
  printf("\nElementos Positivos:\n");
  for (i=0;i<N;i++)
    if (*(pvec+i)>0)
      printf("%.2f\t",*(pvec+i));
}
