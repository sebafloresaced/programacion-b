#include <stdio.h>
#include <stdlib.h>
void CreaVariablesDinamicas(int **pint1,int **pint2,int **pint3);
void Operaciones(int *pint1,int *pint2,int *pint3,int *suma,int *producto);
int main(){
  int *pint1,*pint2,*pint3,suma,producto;
  CreaVariablesDinamicas(&pint1,&pint2,&pint3);
  Operaciones(pint1,pint2,pint3,&suma,&producto);
  printf("\nEntero 1: %d\nEntero 2: %d\nEntero 3: %d\nSuma: %d\tProducto: %d",*pint1,*pint2,*pint3,suma,producto);
  free(pint1); free(pint2); free(pint3);
  return 0;
}
void CreaVariablesDinamicas(int **pint1,int **pint2,int **pint3){
  /*
  Estoy cambiando la direccion del puntero, por lo tanto:
    **p = entero
    *p = puntero a entero
    p = puntero a puntero a entero
  */
  *pint1 = (int *)malloc(sizeof(int));
  *pint2 = (int *)malloc(sizeof(int));
  *pint3 = (int *)malloc(sizeof(int));
  printf("Ingresa tres numeros enteros: ");
  scanf("%d %d %d",*pint1,*pint2,*pint3);
}
void Operaciones(int *pint1,int *pint2,int *pint3,int *suma,int *producto){
  *suma = *pint1 + *pint2 + *pint3;
  *producto = *pint1 * *pint2 * *pint3;
}
