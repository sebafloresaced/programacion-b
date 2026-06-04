#include <stdio.h>
#include "Pilas.h"
#include "Colas.h"
#define MaxElem 20

typedef int TMat[MaxElem][MaxElem];
typedef int TVec[MaxElem];

void CargaMat(TMat Mat, int *N);
void InicializaMat(TMat Mat, int N);
void Kruskal(TMat Mat,TMat AAM,int N);
void Prim(TMat Mat,TMat AAM,int N);

int main(){
  return 0;
}

void Kruskal(TMat Mat,TMat AAM,int N) {
  TVec CC;
  int i,j,k;
  int ori,dest,min;
  int cantAristas=0;

  // Inicializo Matriz de AAM
  InicializaMat(AAM,N);

  // Inicializo Vector de CC
  for (i=0;i<N;i++)
    CC[i] = i;

  // Mientras no haya guardado todos los vertices
  while (cantAristas < N-1) {
    // Inicializo variables
    min = 9999;
    ori = -1;
    dest = -1;

    for (i=0;i<N;i++)
      for (j=i+1;j<N;j++)
        if (Mat[i][j] != 0 && CC[i] != CC[j]) // Si existe camino entre i y j y sus componentes en el vector son distintas
          if (Mat[i][j] < min) { // Me sirve esa arista
            min = Mat[i][j];
            ori = i;
            dest = j;
          }

    if (ori != -1) { // Si acepte alguna arista
      AAM[ori][dest] = min;
      AAM[dest][ori] = min;

      cantAristas++;

      for (k=0;k<N;k++) // Actualizo las componentes en CC
        if (CC[k] == CC[dest])
          CC[k] = CC[ori];
    }
  }
}

void Prim(TMat Mat,TMat AAM,int N) {
  TVec Visitado;
  int i,j;
  int ori,dest,min;
  int cantVisitados=1;

  InicializaMat(AAM,N);

  // Inicializo Vector de Visitados
  for (i=1;i<N;i++)
    Visitado[i] = 0;
  Visitado[0] = 1;

  // Mientras no haya guardado todos los vertices
  while (cantVisitados < N) {
    min = 9999;
    ori = -1;
    dest = -1;

    for (i=0;i<N;i++)
      if (Visitado[i] != 0)
        for (j=0;j<N;j++)
          if (Visitado[j] == 0 && Mat[i][j] != 0) // Si existe camino entre i y j y no lo visite
            if (Mat[i][j] < min) { // me sirve el camino
              min = Mat[i][j];
              ori = i;
              dest = j;
            }

    if (ori != -1) { // Si acepte alguna arista
      AAM[ori][dest] = min;
      AAM[dest][ori] = min;

      Visitado[dest] = 1; // Actualizo los visitados
      cantVisitados++;
    }
  }
}
