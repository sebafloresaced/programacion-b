// Inciso 1 (2 pts)
Indicar V o F:
  a) "A partir de la matriz final An de Floyd sobre un digrafo G, se puede hallas la matriz de clausura transitiva sin necesidad de volver a acceder a la matriz de adyacencia de G"
  Verdadero. La matriz de clausura transitiva se puede construir a partir de la matriz final de Floyd.
  En (i,j) de matriz de clausura transitiva ira un 1 si en (i,j) de la matriz final de Floyd hay un valor distinto de INF y de 0, o un 0 en caso contrario

  b) "Dado un grafo de N vertices conexo, existen sobre el N-1 arboles abarcadores"
  Falso.
  Contraejemplo:
    V = {A, B, C, D}
    N = 4
    E = {
      A - B
      A - C
      A - D
      B - C
      B - D
      C - D
    }

  Posibles arboles abarcadores:
    E = {
      A - B
      A - C
      A - D
    }

    E = {
      A - B
      B - C
      B - D
    }

    E = {
      A - B
      B - C
      C - D
    }

    E = {
      A - C
      C - B
      C - D
    }

  Di cuatro ejemplos, no son los unicos, de arboles abarcadores del grafo conexo. Por lo tanto, ya queda demostrado el contraejemplo.

// Inciso 2 (4 pts)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxTitulo 20
typedef struct nodito {
  int idCancion; // se puede repetir
  char titulo[MaxTitulo];
  float duracion; // en segundos
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

typedef struct nodo {
  char idInterprete[11]; // ordenada
  TSubL canciones;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;

typedef struct nodoC {
  int idCancion;
  char idInterprete[11];
  struct nodoC *sig;
} nodoC;
typedef nodoC *TListaC;
// No esta ordenada bajo ningun criterio

// Dado un id interprete, listar todas las canciones disponibles de el, eliminando las que esten, de la lista de reproduccion (LC).
// Al final del listado, mostrar cantEliminadas y duracionTotal en minutos

void Listado(TLista L,TListaC *LC,char idInterprete[]) {
  int cantEliminadas = 0;
  float duracionTotal = 0;
  TLista auxL;
  TSubL auxSub;
  TListaC actC,antC;
  char eliminada;
  printf("Interprete: %s",idInterprete);
  // Recorro L hasta encontrar mi idInterprete
  auxL = L;
  while (auxL != NULL && strcmp(auxL->idInterprete,idInterprete) < 0) {
    auxL = auxL->sig;
  }
  if (auxL == NULL || strcmp(auxL->idInterprete,idInterprete) != 0)
    printf("\nNo se encontraron canciones disponibles del interprete ingresado");
  else {
    printf("\nId Cancion        Titulo Cancion       Eliminada");
    // Recorro el bloque de mi idInterprete
    auxSub = auxL->canciones;
    while (auxSub != NULL) {
      eliminada = 'N';
      // Por cada cancion disponible, verifico si esta en la lista de reproduccion
      actC = (*LC)->sig;
      antC = *LC;
      do {
        antC = actC;
        actC = actC->sig;
      } while (actC != (*LC)->sig && (strcmp(idInterprete,actC->idInterprete) != 0 || actC->idCancion != auxSub->idCancion));
      if (strcmp(idInterprete,actC->idInterprete) == 0 && actC->idCancion == auxSub->idCancion) {
        // Si esta, la elimino
        eliminada = 'S';
        cantEliminadas++;
        duracionTotal += auxSub->duracion;
        if (actC == *LC) // elimino cabeza
          if (actC == actC->sig) // es unico
            *LC = NULL;
          else
            *LC = actC->sig;
        else
          antC->sig = actC->sig;
        free(actC);
      }
      printf("%d     %s    %c",auxSub->idCancion,auxSub->titulo,eliminada);
      auxSub = auxSub->sig;
    }
    printf("%d Canciones eliminadas (%.2f minutos)",cantEliminadas,duracionTotal/60);
  }
}

// Inciso 3 (2.5 pts)
int BuscaCar(arbolN A,pos p,char x){
  pos c;
  int encontre = 0;
  if (Nulo(p))
    return 0;
  else {
    c = HijoMasIzq(p,A);
    if (Info(p,A) == x)
      return 1;
    else {
      while (!Nulo(c) && !encontre) {
        encontre = BuscaCar(A,c,x);
        c = HermanoDer(c,A);
      }
      return encontre;
    }
  }
}
int CumpleElem(TElementoP aux, arbol A) {
  return strlen(aux) % 2 == 0 && BuscaCar(A,Raiz(A),aux[0]) && BuscaCar(A,Raiz(A),aux[strlen(aux) - 1]);
}
void ProcesaPila(TPila *P, arbolN A) {
  TElementoP aux;
  if (!VaciaP(*P)) {
    SacaP(P,&aux);
    ProcesaPila(P,A);
    if (CumpleElem(aux, A))
      PoneP(P,aux);
  }
}

"Pilas.h"
#define MaxLen 20
typedef char TElementoP[MaxLen];
typedef struct nodo {
  TElementoP cadena;
  struct nodo *sig;
} nodo;
typedef nodo *TPila;

void SacaP(TPila *P,TElementoP *x);

"Pilas.c"
#include <stdlib.h>
#include "Pilas.h"
void SacaP(TPila *P,TElementoP *x){
  TPila borra;
  if (*P != NULL) {
    *x = (*P)->cadena;
    borra = *P;
    *P = (*P)->sig;
    free(borra);
  }
}

// Inciso 4 (1.5 pts)
typedef struct nodo {
  int clave;
  struct nodo *izq,*der;
} nodo;
typedef nodo *arbol;

int GradoNodo(arbol A) {
  int grado=0;
  if (A != NULL)
    A = A->izq;
  while (A != NULL) {
    grado++;
    A = A->der;
  }
  return grado;
}
int CantGradoPar(arbol A) {
  if (A == NULL)
    return 0;
  else
    return (GradoNodo(A) % 2 == 0) + CantGradoPar(A->izq) + CantGradoPar(A->der);
}

// Correcciones:
Ejercicio 2:
  No contemplo LC = NULL
Ejercicio 3:
  TElementoP es un string, lo puedo asignarlo con =

// Puntaje:
Ejercicio 1: 2/2
Ejercicio 2: 2.9/4
Ejercicio 3: 2.1/2.5
Ejercicio 4: 1.5/1.5
Total: 8.5/10
