#include <stdio.h>
#include "Colas.h"
void LeerArch(TCola *C1,TCola *C2);
void Muestra(TCola *C);
void MuestraYMantiene(TCola *C);
int main(){
  TCola C1,C2;
  LeerArch(&C1,&C2);
  Muestra(&C1);
  MuestraYMantiene(&C2);
  return 0;
}
void LeerArch(TCola *C1,TCola *C2){
  FILE *arch;
  int n;
  IniciaC(C1);
  IniciaC(C2);
  if ((arch = fopen("Datos.txt","rt"))==NULL)
    printf("Error al abrir el archivo");
  else {
    while (fscanf(arch,"%d",&n) == 1) {
      poneC(C1,n);
      poneC(C2,n);
    }
    fclose(arch);
  }
}
void Muestra(TCola *C){
  int n;
  while (!VaciaC(*C)) {
    sacaC(C,&n);
    printf("\n%d",n);
  }
}
void MuestraYMantiene(TCola *C){
  int n;
  TCola Caux;
  IniciaC(&Caux);
  while (!VaciaC(*C)) {
    sacaC(C,&n);
    printf("\n%d",n);
    poneC(&Caux,n);
  }
  while (!VaciaC(Caux)) {
    sacaC(&Caux,&n);
    poneC(C,n);
  }
}
