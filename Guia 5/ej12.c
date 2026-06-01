#include <stdio.h>
#include "Pilas.h"
int main(){
 TPila P;
  char c,n1,n2;
   IniciaP(&P);
    //Ingreso de datos
     printf("Ingresa una expresion: ");
      scanf("%c",&c);
       while (c != '.') {
        if (c =< '9' && c >= '0'){
         poneP(&P,c);
         scanf(" %c",&c);
        }
        else {
         switch (c) {
          case '+': sacaP(&P,&n1);
                    sacaP(&P,&n2);
                    n1 = n2 - '0' + n1 - '0' + '0';
                    poneP(&P,n1);
                    break;
          case '-': sacaP(&P,&n1);
                    sacaP(&P,&n2);
                    n1 = n2 - '0' - n1 - '0' + '0';
                    poneP(&P,n1);
                    break;
          case '*': sacaP(&P,&n1);
                    sacaP(&P,&n2);
                    n1 = (n2 - '0') * (n1 - '0') + '0';
                    poneP(&P,n1); break; case '/':
                    sacaP(&P,&n1);
                    sacaP(&P,&n2);
                    n1 = (n2 - '0') / (n1 - '0') + '0';
                    poneP(&P,n1);
                    break;
          }
        scanf(" %c",&c);
        }
      }
      printf("\nEl resultado es %d",n1 - '0');
  return 0;
}
