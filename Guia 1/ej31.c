#include <stdio.h>
typedef struct {
  char Apellido[20],Nombre[20],Nacionalidad[20];
  unsigned int Puntaje;
} RJ;
void MostrarJugador(int Posicion);
int main(){
  int Posicion;
  printf("Ingresa la posicion del jugador (-1 para terminar): ");
  scanf("%d",&Posicion);
  while (Posicion > 0) {
    MostrarJugador(Posicion);
    printf("\nIngresa la posicion del jugador (-1 para terminar): ");
    scanf("%d",&Posicion);
  }
  return 0;
}
void MostrarJugador(int Posicion){
  RJ Jugador;
  FILE *arch;
  if ((arch = fopen("Tenistas.DAT","rb"))==NULL)
    printf("\nError al abrir el archivo");
  else {
    fseek(arch,(Posicion-1) * sizeof(RJ),0);
    fread(&Jugador,sizeof(RJ),1,arch);
    printf("\nApellido: %s\tNombre: %s\tNacionalidad: %s\tPuntaje: %u",Jugador.Apellido,Jugador.Nombre,Jugador.Nacionalidad,Jugador.Puntaje);
  }
  fclose(arch);
}
