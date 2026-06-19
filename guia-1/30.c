#include <stdio.h>
#include <string.h>
typedef struct {
  char Patente[8];
  unsigned int Vel,VelMax;
  char Fecha[17];
} RM;
void Proceso();
int main(){
  Proceso();
  return 0;
}
void Proceso(){
  FILE *archt,*archb;
  unsigned int CantProcesada=0,CantRegistrada=0;
  RM Medicion;
  if ((archt = fopen("Mediciones.TXT","rt"))==NULL)
    printf("Error al abrir el archivo de texto");
  else {
    if ((archb = fopen("Mediciones.DAT","wb"))==NULL)
      printf("Error al crear el archivo binario");
    else {
      while (fscanf(archt,"%s %u %u %s",Medicion.Patente,&Medicion.Vel,&Medicion.VelMax,Medicion.Fecha) == 4) {
        CantProcesada++;
        if (Medicion.Vel > Medicion.VelMax * 1.2) {
          CantRegistrada++;
          fwrite(&Medicion,sizeof(RM),1,archb);
        }
      }
      fclose(archb); fclose(archt);
      printf("Se procesaron %u mediciones del archivo de texto, de las cuales se cargaron %u en el archivo binario",CantProcesada,CantRegistrada);
    }
  }
}
