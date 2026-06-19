#include <stdio.h>
#include <string.h>
typedef struct {
  char Ciudad[20];
  unsigned int Dia;
  float TempMax,TempMin;
} RM;
void Listado();
int main(){
  Listado();
  return 0;
}
void Listado(){
  FILE *arch;
  RM Medicion;
  char CiudadAct[20],MinCiudad[20];
  unsigned int MinDia;
  float MinTempC,MinTemp,MaxTempC;
  if ((arch = fopen("Temperaturas.DAT","rb"))==NULL)
    printf("Error al abrir el archivo");
  else {
    printf("\nCiudad\tTempMax\tTempMin");
    fread(&Medicion,sizeof(RM),1,arch);
    MinTemp = Medicion.TempMin;
    strcpy(MinCiudad,Medicion.Ciudad);
    MinDia = Medicion.Dia;
    while (!feof(arch)){
      strcpy(CiudadAct,Medicion.Ciudad);
      MinTempC = Medicion.TempMin;
      MaxTempC = Medicion.TempMax;
      while ((!feof(arch))&&(strcmp(CiudadAct,Medicion.Ciudad)==0)) {
        if (Medicion.TempMax>MaxTempC)
          MaxTempC = Medicion.TempMax;
        if (Medicion.TempMin<MinTempC) {
          MinTempC = Medicion.TempMin;
          if (Medicion.TempMin<MinTemp) {
            MinTemp = Medicion.TempMin;
            MinDia = Medicion.Dia;
            strcpy(MinCiudad,Medicion.Ciudad);
          }
        }
        fread(&Medicion,sizeof(RM),1,arch);
      }
      printf("\n%s\t%f\t%f",CiudadAct,MaxTempC,MinTempC);
    }
    printf("\nEl dia mas frio fue el dia %u en %s. Hicieron %.2f grados.",MinDia,MinCiudad,MinTemp);
    fclose(arch);
  }
}

