#include <stdio.h>
#include <string.h>
#include "Pilas.h"
#include "Colas.h"
#define CantLetras 26
void CargarCola(TCola *C);
void GenerarPilas(TCola *C,TPila VP[]);
void MostrarPilaLetra(TPila *P);
int main(){
  TCola C;
  TPila VP[CantLetras];
  char letra;
  int i,pos;
  IniciaC(&C);
  for (i=0;i<CantLetras;i++)
    IniciaP(&VP[i]);
  CargarCola(&C);
  GenerarPilas(&C,VP);
  printf("\nIngresa una letra: ");
  scanf(" %c",&letra);
  // pasar a mayúscula
  if (letra >= 'a' && letra <= 'z')
    letra = letra - 'a' + 'A';
  if (letra >= 'A' && letra <= 'Z') {
    pos = letra - 'A';
    MostrarPilaLetra(&VP[pos]);
  }
  else
    printf("Letra invalida");
  return 0;
}
void CargarCola(TCola *C){
  TElementoC x;
  printf("Apellido (FIN para terminar): ");
  scanf("%s",x.apellido);
  while (strcmp(x.apellido,"FIN") != 0) {
    printf("Nombre: ");
    scanf("%s",x.nombre);
    poneC(C,x);
    printf("\nApellido (FIN para terminar): ");
    scanf("%s",x.apellido);
  }
}
void GenerarPilas(TCola *C,TPila VP[]){
  TElementoC x;
  int pos;
  char inicial;
  while (!VaciaC(*C)) {
    sacaC(C,&x);
    inicial = x.apellido[0];
    // pasar a mayúscula
    if (inicial >= 'a' && inicial <= 'z')
      inicial = inicial - 'a' + 'A';
    pos = inicial - 'A';
    if (pos >= 0 && pos < CantLetras)
      poneP(&VP[pos],x);
  }
}

void MostrarPilaLetra(TPila *P){
  TPila Paux;
  TElementoP x;
  IniciaP(&Paux);
  if (VaciaP(*P))
    printf("\nNo hay competidores con esa inicial");
  else {
    printf("\nCompetidores:\n");
    while (!VaciaP(*P)) {
      sacaP(P,&x);
      printf("%s %s\n",x.apellido,x.nombre);
      poneP(&Paux,x);
    }
    while (!VaciaP(Paux)) {
      sacaP(&Paux,&x);
      poneP(P,x);
    }
  }
}
