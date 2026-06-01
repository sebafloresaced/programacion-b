#include <stdio.h>
#define MaxAlumnos 20
typedef struct {
  char nombre[20];
  unsigned int matricula;
  float promedio;
} Alumno;
void CargaVector(Alumno Vec[],unsigned int *N);
void MuestraVector(Alumno Vec[],unsigned int N);
int main(){
  unsigned int N;
  Alumno Vec[MaxAlumnos];
  CargaVector(Vec,&N);
  MuestraVector(Vec,N);
  return 0;
}
void CargaVector(Alumno Vec[],unsigned int *N){
  unsigned int i;
  printf("Ingresa N: ");
  scanf("%u",N);
  for (i=0;i<*N;i++){
  printf("\nIngresa los datos del alumno nro %u\n",i+1);
  printf("Nombre: ");
  scanf(" %[^\n]", Vec[i].nombre);
  printf("Matricula y Promedio: ");
  scanf("%u %f", &Vec[i].matricula, &Vec[i].promedio);
}
}
void MuestraVector(Alumno Vec[],unsigned int N){
  unsigned int i;
  printf("\nNombre\tMatricula\tPromedio");
  for (i=0;i<N;i++)
    printf("\n%s\t%u\t%4.2f",Vec[i].nombre,Vec[i].matricula,Vec[i].promedio);
}
