#include <stdio.h>
#define MaxElem 20
typedef int TMat[MaxElem][MaxElem];
void CargaMat(TMat M,int *N);
void CambiaMat(TMat M,int N);
int main(){
  TMat M;
  int N;
  CargaMat(M,&N);
  CambiaMat(M,N);
  return 0;
}
void CambiaMat(TMat M,int N) {
  int i,j;
  for (i=0;i<N;i++)
    for (j=0;j<i;j++)
      if (M[i][j] == 1 || M[j][i] == 1)
        M[i][j] = M[j][i] = 1;
}
