#include <stdio.h>
#include "Pilas.h"
#include "Colas.h"

int EsPalindroma(TCola *C,unsigned int N);

int main(){
  TCola C;
  unsigned int N,i;
  char x;

  IniciaC(&C);

  printf("Ingresa la cantidad de letras: ");
  scanf("%u",&N);

  printf("Ingresa la palabra letra por letra:\n");
  for (i=0;i<N;i++) {
    scanf(" %c",&x);
    poneC(&C,x);
  }

  if (EsPalindroma(&C,N))
    printf("La palabra es palindroma");
  else
    printf("La palabra no es palindroma");

  return 0;
}
int EsPalindroma(TCola *C,unsigned int N){
  TPila P;
  unsigned int i;
  char x,y;
  int ok = 1;

  IniciaP(&P);

  for (i=0;i<N/2;i++) {
    sacaC(C,&x);
    poneP(&P,x);
  }

  if (N % 2 != 0)
    sacaC(C,&x);

  while (!VaciaP(P) && ok) {
    sacaP(&P,&x);
    sacaC(C,&y);
    if (x != y)
      ok = 0;
  }

  return ok;
}
