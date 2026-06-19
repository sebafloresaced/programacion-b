#include <stdio.h>
#define MaxElem 20
typedef int TMat[MaxElem][MaxElem];
typedef int TVec[MaxElem];

void CargaMat(TMat M,int *N);

int Grado(TMat M,int N);
void GeneraVec(TMat M,TVec V,int N);

int GradoEntrada(TMat M,int ver,int i,int N);
int MayorGradoEntrada(TMat M,int i,int N,int posMax);

int main() {
  TMat M;
  int N;
  TVec V;
  CargaMat(M,&N);
  GeneraVec(M,V,0,N);
  printf("Vertice con mayor grado de entrada: %d",MayorGradoEntrada(M,1,N,0));
  return 0;
}
int GradoVertice(TMat M,int ver,int j,int N) {
  if (j == N)
    return 0;
  else
    return M[ver][j] + GradoVertice(M,ver,j+1,N);
}
void GeneraVec(TMat M,TVec V,int i,int N) {
  if (i < N) {
    V[i] = GradoVertice(M,i,0,N);
    GeneraVec(M,V,i+1,N);
  }
}

int GradoEntrada(TMat M,int ver,int i,int N) {
  if (i == N)
    return 0;
  else
    return M[i][ver] + GradoEntrada(M,ver,i+1,N);
}

int MayorGradoEntrada(TMat M,int i,int N,int posMax) {
  if (i == N)
    return posMax;
  else {
    if (GradoEntrada(M,i,0,N) > GradoEntrada(M,posMax,0,N))
      posMax = i;

    return MayorGradoEntrada(M,i+1,N,posMax);
  }
}
