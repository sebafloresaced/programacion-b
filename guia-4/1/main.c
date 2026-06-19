#include <stdio.h>
#include "ej1.h"

int main(){
  fraccion f1,f2,f3;

  f1 = crear(1,2);
  f2 = crear(3,4);

  printf("f1 = %d/%d",numerador(f1),denominador(f1));
  printf("\nf2 = %d/%d",numerador(f2),denominador(f2));

  f3 = sumar(f1,f2);
  printf("\n\nSuma: %d/%d",f3.numerador,f3.denominador);
  f3 = simplificar(f3);
  printf("\nSuma simplificada: %d/%d",f3.numerador,f3.denominador);

  f3 = restar(f1,f2);
  printf("\n\nResta: %d/%d",f3.numerador,f3.denominador);
  f3 = simplificar(f3);
  printf("\nResta simplificada: %d/%d",f3.numerador,f3.denominador);

  f3 = multiplicar(f1,f2);
  printf("\n\nMultiplicacion: %d/%d",f3.numerador,f3.denominador);
  f3 = simplificar(f3);
  printf("\nMultiplicacion simplificada: %d/%d",f3.numerador,f3.denominador);

  f3 = dividir(f1,f2);
  printf("\n\nDivision: %d/%d",f3.numerador,f3.denominador);
  f3 = simplificar(f3);
  printf("\nDivision simplificada: %d/%d",f3.numerador,f3.denominador);

  f3 = crear(8,12);
  printf("\n\nFraccion a simplificar: %d/%d",f3.numerador,f3.denominador);
  f3 = simplificar(f3);
  printf("\nFraccion simplificada: %d/%d",f3.numerador,f3.denominador);

  printf("\n\nComparacion de fracciones:");

  if (iguales(f1,f2))
    printf("\nSon iguales");
  else
    printf("\nNo son iguales");

  return 0;
}
