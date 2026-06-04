#include <stdio.h>
#include "Pilas.h"
void CambiaSigno(TPila *P);
int main(){
  TPila P;
  int x;

  IniciaP(&P);

  poneP(&P,2);
  poneP(&P,-7);
  poneP(&P,3);

  CambiaSigno(&P);

  while (!VaciaP(P)) {
    sacaP(&P,&x);
    printf("%d\n",x);
  }

  return 0;
}
void CambiaSigno(TPila *P){
  int x;

  if (!VaciaP(*P)) {
    sacaP(P,&x);
    x = -x;
    CambiaSigno(P);
    poneP(P,x);
  }
}
