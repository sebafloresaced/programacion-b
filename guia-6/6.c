#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxChar 20
typedef struct nodito {
  char nombre[MaxChar];
  unsigned int edad;
  char estado;
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;
typedef struct nodo {
  char nombre[MaxChar];
  unsigned int puntos;
  TSubL sub;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;
void CargaLista(TLista *L);
void ListarJugadores(TLista L,char k);
void ListarClubes(TLista L,unsigned int x);
int Verifica(TLista L,char E[],unsigned int P);
void EliminaJugadores(TLista L);
int main(){
  TLista L;
  char k,E[MaxChar];
  unsigned int x,P;
  CargaLista(&L);
  printf("Ingresa k: ");
  scanf(" %c",&k);
  ListarJugadores(L,k);
  printf("\nIngresa x: ");
  scanf("%u",&x);
  ListarClubes(L,x);
  printf("\nIngresa E: ");
  scanf("%s",E);
  printf("\nIngresa P: ");
  scanf("%u",&P);
  if (Verifica(L,E,P))
    printf("El equipo %s tiene %u puntos",E,P);
  else
    printf("El equipo %s no tiene %u puntos",E,P);
  EliminaJugadores(L);
  return 0;
}
void ListarJugadores(TLista L,char k){
  TLista aux;
  TSubL auxS;
  unsigned int cont,maxcont=0,contTot=0;
  char maxClub[MaxChar] = "Ninguno";
  aux = L;
  while (aux != NULL) {
      auxS=aux->sub;
      printf("\nEquipo %s:",aux->nombre);
      cont = 0;
      while (auxS != NULL) {
        if (auxS->nombre[0] == k) {
          printf("\n%s",auxS->nombre);
          cont++;
        }
        auxS = auxS->sig;
      }
      contTot += cont;
      if (cont > maxcont) {
        maxcont = cont;
        strcpy(maxClub,aux->nombre);
      }
    aux = aux->sig;
  }
  if (strcmp(maxClub,"Ninguno") == 0)
    printf("\nNo hay jugadores que empiecen con la letra %c",k);
  else {
    printf("\nEl total de jugadores listados fue %u",contTot);
    printf("\nEl club con mas jugadores listados fue %s",maxClub);
  }
}
void ListarClubes(TLista L,unsigned int x){
  TLista aux;
  TSubL auxS;
  unsigned int cont,acum;
  aux = L;
  while (aux != NULL) {
    if (aux->puntos >= x) {
      auxS=aux->sub;
      printf("\nEquipo %s:",aux->nombre);
      cont = 0; acum=0;
      while (auxS != NULL) {
        printf("\n%s",auxS->nombre);
        cont++;
        acum += auxS->edad;
        auxS = auxS->sig;
      }
     if (cont != 0)
       printf("\nEdad promedio del equipo: %.2f",(float)acum/cont);
     else
       printf("\nEl equipo no tiene jugadores");
    }
    aux = aux->sig;
  }
}
int Verifica(TLista L,char E[],unsigned int P){
  TLista aux;
  aux = L;
  while (aux != NULL && aux->puntos >= P && strcmp(aux->nombre,E))
    aux = aux->sig;
  return (aux != NULL && aux->puntos == P && strcmp(aux->nombre,E) == 0);
}
void EliminaJugadores(TLista L){
  TLista aux;
  TSubL actS,antS;
  aux = L;
  while (aux != NULL) {
    actS=aux->sub; antS = NULL;
    while (actS != NULL) {
      if (actS->estado == 'S') {
        if (actS == aux->sub) {
          aux->sub = actS->sig;
          free(actS);
          actS = aux->sub;
        }
        else {
          antS->sig = actS->sig;
          free(actS);
          actS = antS->sig;
        }
      }
      else {
      antS = actS;
      actS = actS->sig;
      }
    }
    aux = aux->sig;
  }
}
