#include <stdio.h>
#define MaxElem 20
void AlcanceMat(TMat MatF,TMat MatR, int N);

typedef int TMat[MaxElem][MaxElem];

void CargaMat(TMat Mat,int *N);
void AlcanceMat(TMat MatF,TMat MatR, int N);
int SumaColumna(TMat R,int fila,int col,int N);
int MayorAlcanzado(TMat MatR,int N);

int main(){
  return 0;
}

void AlcanceMat(TMat MatF,TMat MatR, int N){
  int i,j;
  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      MatR[i][j] = (MatF[i][j] < INF)? 1:0;
}
int SumaColumna(TMat R,int fila,int col,int N) {
  if (fila == N)
    return 0;
  else
    return R[fila][col] + SumaColumna(R,fila+1,col,N);
}
int MayorAlcanzado(TMat MatR,int j,int N){
  int posMaxAnt, sumaMaxAnt, sumaJ;
  if (j == 0)
    return 0;
  else {
    posMaxAnt = MayorAlcanzado(MatR,j-1,N);
    sumaMaxAnt = SumaColumna(MatR,0,posMaxAnt,N);
    sumaJ = SumaColumna(MatR,0,j,N);
    return (sumaJ > sumaMaxAnt)? j:posMaxAnt;
  }
}
