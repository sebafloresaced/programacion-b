#include <stdio.h>
#include "Pilas.h"
void LeeArchivo(TPila *P);
void MuestraPila(TPila *P);
void MuestraYMantienePila(TPila *P);
int main(){
  TPila P;
  LeeArchivo(&P);
  MuestraPila(&P);
  LeeArchivo(&P);
  MuestraYMantienePila(&P);
  return 0;
}
void LeeArchivo(TPila *P){
  FILE *arch;
  char n;
  if ((arch=fopen("Datos.TXT","rt"))==NULL)
    printf("Error al abrir el archivo");
  else {
    IniciaP(P);
    while (fscanf(arch,"%c\n",&n)==1)
      poneP(P,n);
    fclose(arch);
  }
}
void MuestraPila(TPila *P){
  char n;
  while(!VaciaP(*P)) {
    sacaP(P,&n);
    printf("%c ",n);
  }
}
void MuestraYMantienePila(TPila *P){
  TPila Paux;
  char n;
  IniciaP(&Paux);
  while(!VaciaP(*P)) {
    sacaP(P,&n);
    printf("%c ",n);
    poneP(&Paux,n);
  }
  while(!VaciaP(Paux)) {
    sacaP(&Paux,&n);
    poneP(P,n);
  }
}
