#include <stdio.h>
#include "Pilas.h"
#include "Colas.h"
#define MaxJug 20

void CargarMazo(TPila *M);
void CargarJugadores(TCola *C,unsigned int N);
void Jugar(TPila *M,TCola *C,int Puntaje[]);
void MostrarPuntajes(int Puntaje[],unsigned int N);

int main(){
  TPila M;
  TCola C;
  unsigned int N,i;
  int Puntaje[MaxJug];
  printf("Ingresa la cantidad de jugadores: ");
  scanf("%u",&N);
  IniciaP(&M);
  IniciaC(&C);
  for (i=0;i<N;i++)
    Puntaje[i] = 0;
  CargarMazo(&M);
  CargarJugadores(&C,N);
  Jugar(&M,&C,Puntaje);
  MostrarPuntajes(Puntaje,N);
  return 0;
}
void CargarMazo(TPila *M){
  TElementoP x;
  printf("Numero del naipe (0 para terminar): ");
  scanf("%d",&x.numero);
  while (x.numero != 0) {
    printf("Palo: ");
    scanf(" %c",&x.palo);
    poneP(M,x);
    printf("\nNumero del naipe (0 para terminar): ");
    scanf("%d",&x.numero);
  }
}
void CargarJugadores(TCola *C,unsigned int N){
  unsigned int i;
  for (i=1;i<=N;i++)
    poneC(C,i);
}
void Jugar(TPila *M,TCola *C,int Puntaje[]){
  TElementoP x,anterior;
  int jug,valor;
  int hayAnterior = 0;
  while (!VaciaP(*M)) {
    sacaP(M,&x);
    sacaC(C,&jug);
    valor = x.numero;
    if (hayAnterior && x.palo == anterior.palo)
      valor *= 2;
    Puntaje[jug-1] += valor;
    anterior = x;
    hayAnterior = 1;
    poneC(C,jug);
  }
}
void MostrarPuntajes(int Puntaje[],unsigned int N){
  unsigned int i;
  printf("\nPuntajes finales:\n");
  for (i=0;i<N;i++)
    printf("Jugador %u: %d\n",i+1,Puntaje[i]);
}
