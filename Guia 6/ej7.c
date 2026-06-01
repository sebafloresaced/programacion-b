#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxChar 20
#define letras 26
typedef struct nodito{
  char titulo[MaxChar],autor[MaxChar];
  unsigned int anio_de_edicion;
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

// Vector autores
typedef struct nodo {
  char autor[MaxChar];
  TSubL sub;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;

//Lista socios
typedef struct nodoS {
  char socio[MaxChar];
  TSubL sub;
  struct nodoS *sig;
} nodoS;
typedef nodoS *TListaS;

void CargaLista(TListaS *LS);
void CargaVector(TLista V[]);
void Prestar(TLista V[],TListaS *LS,nodito Libro,char socio[]);
void Devolver(TLista V[],TListaS *LS,nodito Libro,char socio[]);

int main(){
  TListaS LS;
  TLista V[letras];
  char opcion,socio[MaxChar];
  nodito Libro;

  CargaLista(&LS);
  CargaVector(V);
  printf("Ingresa una opcion:\n p : Prestamo \n d: Devolucion \n s: Salir");
  scanf(" %c",&opcion);
  while (opcion != 's') {
    if (opcion == 'p' || opcion == 'd') {
      printf("\nIngresa el Socio: ");
      scanf("%s",socio);
      printf("\nIngresa el titulo del libro: ");
      scanf("%s",Libro.titulo);
      printf("\nIngresa el autor del libro: ");
      scanf("%s",Libro.autor);
      printf("\nIngresa el anio de edicion del libro: ");
      scanf("%u",&Libro.anio_de_edicion);
      if (opcion == 'p')
        Prestar(V,&LS,Libro,socio);
      else
        Devolver(V,&LS,Libro,socio);
      printf("\nIngresa una opcion:\n p : Prestamo \n d: Devolucion \n s: Salir");
      scanf(" %c",&opcion);
    }
  }
  return 0;
}
void Prestar(TLista V[],TListaS *LS,nodito Libro,char socio[]){
  int pos;
  TLista auxA;
  TListaS auxS,nuevoS;
  TSubL act,ant,libro,ult;
  pos = Libro.autor[0] - 'A'; // indice en vector
  auxA = V[pos];
  while (auxA != NULL && strcmp(auxA->autor,Libro.autor) != 0) // recorro la lista de autores
    auxA = auxA->sig;
  if (auxA != NULL){
    act = auxA->sub;
    ant = NULL;
    while (act != NULL && strcmp(act->titulo,Libro.titulo) != 0){ // recorro la sublista de libros
      ant = act;
      act = act->sig;
    }
    if (act != NULL){ // si encontre el libro:
      libro = act;
      if (ant == NULL)
        auxA->sub = act->sig;
      else
        ant->sig = act->sig;
      libro->sig = NULL;
      auxS = *LS;
      while (auxS != NULL && strcmp(auxS->socio,socio) != 0) // recorro la lista de socios
        auxS = auxS->sig;
      if (auxS == NULL){ // si no existe lo creo
        nuevoS = (TListaS)malloc(sizeof(nodoS));
        strcpy(nuevoS->socio,socio);
        nuevoS->sub = NULL;
        nuevoS->sig = *LS;
        *LS = nuevoS;
        auxS = nuevoS;
      }
      if (auxS->sub == NULL) // si el socio no tiene libros prestados
        auxS->sub = libro;
      else {
        ult = auxS->sub;
        while (ult->sig != NULL) // recorro la sublista del socio
          ult = ult->sig;
        ult->sig = libro;
      }
    }
    else
      printf("\nEl libro no esta disponible");
  }
  else
    printf("\nNo existe el autor");
}
void Devolver(TLista V[],TListaS *LS,nodito Libro,char socio[]){
  int pos;
  TLista auxA;
  TListaS auxS;
  TSubL act,ant,libro,actL,antL;
  auxS = *LS;
  while (auxS != NULL && strcmp(auxS->socio,socio) != 0) // busco el socio
    auxS = auxS->sig;
  if (auxS != NULL){
    act = auxS->sub;
    ant = NULL;
    while (act != NULL && strcmp(act->titulo,Libro.titulo) != 0){ // busco el libro en su sublista
      ant = act;
      act = act->sig;
    }
    if (act != NULL){ // si encuentro el libro lo saco
      libro = act;
      if (ant == NULL)
        auxS->sub = act->sig;
      else
        ant->sig = act->sig;
      pos = Libro.autor[0] - 'A';
      auxA = V[pos];
      while (auxA != NULL && strcmp(auxA->autor,Libro.autor) != 0) // busco el autor
        auxA = auxA->sig;
      if (auxA != NULL){ // si encuentro el autor
        actL = auxA->sub;
        antL = NULL;
        while (actL != NULL && strcmp(libro->titulo,actL->titulo) > 0){ // busco donde va el libro y lo inserto ordenado
          antL = actL;
          actL = actL->sig;
        }
        libro->sig = actL;
        if (antL == NULL)
          auxA->sub = libro;
        else
          antL->sig = libro;
      }
    }
    else
      printf("\nEl socio no tiene ese libro");
  }
  else
    printf("\nNo existe el socio");
}
