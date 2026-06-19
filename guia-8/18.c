#include <stdio.h>
#define MaxElem 20
#define INF 9999

typedef int TMat[MaxElem][MaxElem];
typedef int TVec[MaxElem];

void CargaMat(TMat Mat, int *N);
void InicializaMat(TMat Mat, int N);
void Floyd(TMat Mat, TMat MatF, int N);
void AlcanceMat(TMat MatF,TMat MatR, int N);

int main(){
}

void Floyd(TMat Mat,TMat MatF, int N){
  int i,j,k;
  //Inicializo matriz
  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      if (i == j)
        MatF[i][j] = 0;
      else
        if (Mat[i][j] == 0)
          MatF[i][j] = INF;
        else
          MatF[i][j] = Mat[i][j];
  //Consigo costos minimos
  for (k=0;k<N;k++)
    for (i=0;i<N;i++)
      for (j=0;j<N;j++)
        if (MatF[i][k] != INF && MatF[k][j] != INF)
          if (MatF[i][k] + MatF[k][j] < MatF[i][j])
            MatF[i][j] = MatF[i][k] + MatF[k][j];
}
void AlcanceMat(TMat MatF,TMat MatR, int N){
  int i,j;
  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      MatR[i][j] = (MatF[i][j] < INF)? 1:0;
}
