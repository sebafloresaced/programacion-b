  #include <stdio.h>
void LeeArch();
void GeneraArch();
int main(){
  GeneraArch();
  LeeArch();
  return 0;
}
void GeneraArch(){
  float medicion;
  FILE *arch;
  if ((arch = fopen("Mediciones.DAT","wb"))==NULL)
    printf("Error al crear el archivo");
  else {
    printf("Ingresa el valor de la medicion (0 para terminar): ");
    scanf("%f",&medicion);
    while (medicion != 0) {
      fwrite(&medicion,sizeof(medicion),1,arch);
      printf("\nIngresa el valor de la medicion (0 para terminar): ");
      scanf("%f",&medicion);
    }
    fclose(arch);
  }
}
void LeeArch(){
  float medicion,max=0,min=100,acum=0,prom;
  unsigned int cont=0;
  FILE *arch;
  if ((arch = fopen("Mediciones.DAT","rb"))==NULL)
    printf("\nError al intentar abrir el archivo");
  else {
    while (fread(&medicion,sizeof(medicion),1,arch) == 1) {
      acum += medicion;
      cont++;
      if (medicion<min)
        min = medicion;
      if (medicion>max)
        max = medicion;
    }
    fclose(arch);
    prom = (cont>0)? acum/cont:0;
    printf("\nMedicion maxima: %.2f\nMedicion minima: %.2f\nMedicion promedio: %.2f",max,min,prom);
  }
}
