#include <stdio.h>
#include "Colas.h"
#include "Pilas.h"
void ParentensisBal(TCola *C,int *cumple);
void ParCorLlavBal(TCola *C,int *cumple);
int main(){
  TCola C;
  int cumple;
  IniciaC(&C);
  poneC(&C,'(');
  poneC(&C,'(');
  poneC(&C,')');
  poneC(&C,'(');
  poneC(&C,')');
  poneC(&C,')');
  ParentesisBal(&C,&cumple);
  if (cumple)
    printf("La secuencia esta balanceada");
  else
    printf("La secuencia no esta balanceada");
  IniciaC(&C);
  poneC(&C,'{');
  poneC(&C,'(');
  poneC(&C,')');
  poneC(&C,'[');
  poneC(&C,'(');
  poneC(&C,')');
  poneC(&C,']');
  poneC(&C,'}');
  poneC(&C,')');
  poneC(&C,';');
  poneC(&C,'(');
  poneC(&C,'{');
  poneC(&C,'}');
  poneC(&C,')');
  ParCorLlavBal(&C,&cumple);
  if (cumple)
    printf("\nLa secuencia esta balanceada");
  else
    printf("\nLa secuencia no esta balanceada");
  return 0;
}
void ParentensisBal(TCola *C,int *cumple){
  char n;
  int cont=0;
  *cumple = 1;
  while (!VaciaC(*C)){
    sacaC(C,&n);
    if (n == '(')
      cont++;
    if (n == ')')
      cont--;
    if (cont<0)
      *cumple = 0;
  }
  if (cont > 0)
    *cumple = 0;
}
void ParCorLlavBal(TCola *C,int *cumple){
  TPila P;
  char n,aux;
  IniciaP(&P);
  *cumple = 1;
  while (!VaciaC(*C) && *cumple){
    sacaC(C,&n);
    if (n == '(' || n == '[' || n == '{')
      poneP(&P,n);
    else if (n == ')' || n == ']' || n == '}'){
      if (VaciaP(P))
        *cumple = 0;
      else {
        sacaP(&P,&aux);
        if ((n == ')' && aux != '(') ||
            (n == ']' && aux != '[') ||
            (n == '}' && aux != '{'))
          *cumple = 0;
      }
    }
  }
  if (!VaciaP(P))
    *cumple = 0;
}

