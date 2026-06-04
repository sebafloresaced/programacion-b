#include <stdio.h>
#include "Pilas.h"
void LeeArchivo(TPila *P);
void MuestraPilaRec(TPila *P);
int main(){
  TPila P;

  LeeArchivo(&P);

  printf("Contenido de la pila:\n");
  MuestraPilaRec(&P);

  return 0;
}
void LeeArchivo(TPila *P){
  FILE *arch;
  char x;

  IniciaP(P);

  if ((arch = fopen("Datos.txt","rt")) == NULL)
    printf("Error al abrir el archivo");
  else {
    while (fscanf(arch,"%c\n",&x) == 1)
      poneP(P,x);
    fclose(arch);
  }
}
void MuestraPilaRec(TPila *P){
  char x;

  if (!VaciaP(*P)) {
    sacaP(P,&x);
    printf("%c\n",x);
    MuestraPilaRec(P);
    poneP(P,x);
  }
}
