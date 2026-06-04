#include <stdio.h>
#include "ej1.h"
fraccion crear(int numerador,int denominador){
  fraccion f;
  f.numerador = numerador;
  f.denominador = denominador;
  return f;
}
int numerador(fraccion f){
  return f.numerador;
}
int denominador(fraccion f){
  return f.denominador;
}
fraccion sumar(fraccion f1,fraccion f2){
  f1.numerador = f1.numerador*f2.denominador + f2.numerador*f1.denominador;
  f1.denominador *= f2.denominador;
  return f1;
}
fraccion restar(fraccion f1,fraccion f2){
  f1.numerador = f1.numerador*f2.denominador - f2.numerador*f1.denominador;
  f1.denominador *= f2.denominador;
  return f1;
}
fraccion multiplicar(fraccion f1,fraccion f2){
  f1.numerador *= f2.numerador;
  f1.denominador *= f2.denominador;
  return f1;
}
fraccion dividir(fraccion f1,fraccion f2){
  f1.numerador *= f2.denominador;
  f1.denominador *= f2.numerador;
  return f1;
}
int MCD(int a,int b){
  if (b==0)
    return (a<0)? -a:a;
  return MCD(b,a%b);
}
fraccion simplificar(fraccion f){
  int mcd;
  mcd = MCD(f.numerador,f.denominador);
  f.numerador = f.numerador / mcd;
  f.denominador = f.denominador / mcd;
  if (f.denominador<0){
    f.numerador = -f.numerador;
    f.denominador = -f.denominador;
  }
  return f;
}
int iguales(fraccion f1,fraccion f2){
  f1 = simplificar(f1);
  f2 = simplificar(f2);
  return ((f1.numerador==f2.numerador)&&(f1.denominador==f2.denominador))? 1:0;
}
