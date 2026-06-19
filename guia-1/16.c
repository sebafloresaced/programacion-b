#include <stdio.h>

void FormatoHoras(unsigned int);

void main(){
  unsigned int segundos;
  printf("Ingresa la cantidad de segundos: ");
  scanf("%u",&segundos);
  FormatoHoras(segundos);
}

void FormatoHoras(unsigned int segundos) {
  int horas,minutos;
  minutos = segundos/60;
  segundos -= (minutos*60);
  horas = minutos/60;
  minutos -= (horas*60);
  horas %= 24;
  printf("%02d:%02d:%02d",horas,minutos,segundos);
}
