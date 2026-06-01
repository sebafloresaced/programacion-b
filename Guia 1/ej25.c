#include <stdio.h>
#define MaxElem 50
typedef struct {
  char nombre[20];
  unsigned int edad;
}  Persona;
void CargaVector(Persona Vec[],unsigned int *N);
void Listado(Persona Vec[],unsigned int N,unsigned int X);
float Porcentaje(Persona Vec[],unsigned int N);
int main(){
  unsigned int N,X;
  Persona Vec[MaxElem];
  float PorcMayores;
  CargaVector(Vec,&N);
  printf("\nIngresa X: ");
  scanf("%u",&X);
  Listado(Vec,N,X);
  PorcMayores = Porcentaje(Vec,N);
  printf("\nEl porcentaje de mayores de edad es: %%%5.2f",PorcMayores);
  return 0;
}
void CargaVector(Persona Vec[],unsigned int *N){
  unsigned int i;
  printf("\nIngresa N: ");
  scanf("%u",N);
  for (i=0;i<*N;i++){
    printf("\nIngresa Nombre y despues Edad: ");
    scanf("%s",Vec[i].nombre);
    scanf("%u",&Vec[i].edad);
  }
}
void Listado(Persona Vec[],unsigned int N,unsigned int X){
  unsigned int i;
  for (i=0;i<N;i++)
    if (Vec[i].edad > X)
      printf("\n%s",Vec[i].nombre);
}
float Porcentaje(Persona Vec[],unsigned int N){
  unsigned int Cont=0,i;
  for (i=0;i<N;i++)
    if (Vec[i].edad >= 18)
      Cont++;
  return (float)Cont/N*100;
}
