#include <stdio.h>
#include "Pilas.h"
void CargarNumero(TPila *P);
void SumarPilas(TPila *P1,TPila *P2,TPila *Pres);
void MuestraPilaRec(TPila *P);
int main(){
  TPila P1,P2,Pres;
  printf("Ingresa el primer numero digito por digito (termina con x):\n");
  CargarNumero(&P1);
  printf("Ingresa el segundo numero digito por digito (termina con x):\n");
  CargarNumero(&P2);
  SumarPilas(&P1,&P2,&Pres);
  printf("Resultado: ");
  MuestraPilaRec(&Pres);
  return 0;
}
void CargarNumero(TPila *P){
  char d;
  IniciaP(P);
  scanf(" %c",&d);
  while (d != 'x') {
    poneP(P,d);
    scanf(" %c",&d);
  }
}
void SumarPilas(TPila *P1,TPila *P2,TPila *Pres){
  int n1,n2,suma,acarreo;
  char d1,d2;
  IniciaP(Pres);
  acarreo = 0;
  while (!VaciaP(*P1) || !VaciaP(*P2)) {
    if (!VaciaP(*P1)) {
      sacaP(P1,&d1);
      n1 = d1 - '0'; // - '0' pasa de char a int
    }
    else
      n1 = 0;
    if (!VaciaP(*P2)) {
      sacaP(P2,&d2);
      n2 = d2 - '0'; // + '0' pasa de int a char
    }
    else
      n2 = 0;
    suma = n1 + n2 + acarreo;
    acarreo = suma / 10;
    poneP(Pres,(suma % 10) + '0');
  }
  if (acarreo > 0)
    poneP(Pres,acarreo + '0');
}
void MuestraPilaRec(TPila *P){
  char x;
  if (!VaciaP(*P)) {
    sacaP(P,&x);
    printf("%c",x);
    MuestraPilaRec(P);
    poneP(P,x);
  }
}
