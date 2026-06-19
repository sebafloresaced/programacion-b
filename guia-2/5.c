#include <stdio.h>
#include <stdlib.h>
#define MaxElem 20
int main(){
  int *V[MaxElem],Num,N=0;
  unsigned int i;
  FILE *arch;
  if ((arch = fopen("Numeros.TXT","rt"))==NULL)
    printf("Error al abrir el archivo");
  else {
    while (fscanf(arch,"%d",&Num) == 1) {
      V[N] = (int *)malloc(sizeof(int));
      *V[N] = Num;
      N++;
    }
    printf("Enteros positivos: \n");
    for (i=0;i<N;i++)
      if (*V[i] > 0)
        printf("%d ",*V[i]);
    for (i=0;i<N;i++)
      free(V[i]);
    fclose(arch);
  }
  return 0;
}
