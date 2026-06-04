#include <stdio.h>
int SumaEnteros();
int main(){
  printf("La suma de enteros del archivo es: %d",SumaEnteros());
  return 0;
}
int SumaEnteros(){
  FILE *arch;
  unsigned int Suma=0,N;
  if ((arch = fopen("Numeros.TXT","rt"))== NULL)
    printf("Error al abrir el archivo");
  else {
    fscanf(arch,"%d",&N);
    while (!feof(arch)){
      Suma+=N;
      fscanf(arch,"%d",&N);
      //Si hubiese un numero por linea no habria que modificarlo ya que %d ya consume espacios y saltos de linea
    }
    fclose(arch);
  }

  return Suma;
}
