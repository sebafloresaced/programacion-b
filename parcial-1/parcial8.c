#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colas.h"

typedef struct nodito { // productos
  char codigo[8];
  unsigned int destinatario,cantSolicitados,cantEnviados;
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

typedef struct nodoC { // puestos
  char nombre[31];
  unsigned int id, cantproductos; // ordenado por id, no se repite
  TSubL sub;
  struct nodoC *sig;
} nodoC;
typedef nodoC *TListaC;

typedef struct nodoS { // robots
  unsigned int idRobot,idPuesto;
  TCola Cola;
  struct nodoS *sig;
} nodoS;
typedef nodoS *TListaS;

/*
Contenido Cola:
  char codigo[8];
  unsigned int disponible;
*/

void CargaLS(TListaS *LS);
void CargaLC(TListaC *LC);
void ActualizaPuestos(TListaC *LC);
void SimularPreparacion(TListaC LC,TListaS LS);
void EliminaProducto(char codigo[8],unsigned int X,TListaC LC);

int main(){
  TListaS LS;
  TListaC LC;
  unsigned int X;
  char codigo[8];
  CargaLS(&LS);
  CargaLC(&LC);
  ActualizaPuestos(&LC);
  SimularPreparacion(LC,LS);
  printf("Ingresa el codigo y el id X: ");
  scanf("%s %u",codigo,&X);
  EliminaProducto(codigo,X,LC);
  return 0;
}

// Inciso i.a)
void ActualizaPuestos(TListaC *LC) {
  FILE *arch;
  TListaC actC,antC,nuevoC;
  TSubL actSub,antSub,nuevoSub;
  char nombre[31],codigo[8];
  unsigned int i,puesto,cantproductos,cant,destinatario;

  if ((arch = fopen("PEDIDOS.TXT","rt")) == NULL)
    printf("Error al abrir el archivo");
  else {
    while (fscanf(arch,"%u %s %u",&puesto,nombre,&cantproductos) == 3) {
      // Busco el puesto o lo creo
      if (*LC == NULL) { // lista vacia
        nuevoC = (TListaC)malloc(sizeof(nodoC));
        nuevoC->sig = nuevoC;
        *LC = nuevoC;
        nuevoC->id = puesto;
        nuevoC->sub = NULL;
        nuevoC->cantproductos = 0;
        strcpy(nuevoC->nombre,nombre);
      }
      else {
        actC = (*LC)->sig;
        antC = *LC;
        while (actC != *LC && puesto > actC->id) {
          antC = actC;
          actC = actC->sig;
        }
        if (actC == *LC && puesto > (*LC)->id) { // modifico cabeza
          nuevoC = (TListaC)malloc(sizeof(nodoC));
          nuevoC->sig = (*LC)->sig;
          (*LC)->sig = nuevoC;
          *LC = nuevoC;
          nuevoC->id = puesto;
          nuevoC->sub = NULL;
          nuevoC->cantproductos = 0;
          strcpy(nuevoC->nombre,nombre);
        }
        else {
          if (actC != *LC && puesto < actC->id) { // no modifico cabeza
            nuevoC = (TListaC)malloc(sizeof(nodoC));
            nuevoC->sig = actC;
            antC->sig = nuevoC;
            nuevoC->id = puesto;
            nuevoC->sub = NULL;
            nuevoC->cantproductos = 0;
            strcpy(nuevoC->nombre,nombre);
          }
          else // ya existe
            nuevoC = actC;
        }
      }
      for (i=0;i<cantproductos;i++) {
        fscanf(arch,"%u %s %u",&destinatario,codigo,&cant);
        // Busco o creo el producto
        actSub = nuevoC->sub;
        antSub = NULL;
        if (actSub == NULL) { // sublista vacia
          nuevoSub = (TSubL)malloc(sizeof(nodito));
          nuevoSub->cantEnviados = 0;
          nuevoSub->cantSolicitados = cant;
          strcpy(nuevoSub->codigo,codigo);
          nuevoSub->destinatario = destinatario;
          nuevoSub->sig = NULL;
          actSub = nuevoSub;
        }
        else {
          while (actSub != NULL && strcmp(codigo,actSub->codigo) != 0 && destinatario != actSub->destinatario) {
            antSub = actSub;
            actSub = actSub->sig;
          }
          if (actSub != NULL && strcmp(codigo,actSub->codigo) == 0 && destinatario == actSub->destinatario) { // ya existe
            actSub->cantSolicitados += cant;
          }
          else { // lo inserto al final
            nuevoSub = (TSubL)malloc(sizeof(nodito));
            nuevoSub->cantEnviados = 0;
            nuevoSub->cantSolicitados = cant;
            strcpy(nuevoSub->codigo,codigo);
            nuevoSub->destinatario = destinatario;
            nuevoSub->sig = actSub;
            antSub->sig = nuevoSub;
          }
        }
      }
    }
    fclose(arch);
  }
}

// Inciso i.b)
void SimularPreparacion(TListaC LC,TListaS LS) {
  TElementoC producto;
  TListaC auxC;
  TListaS auxS;
  TSubL auxSub;
  unsigned int faltantes;
  TCola ColaAux;
  IniciaC(&ColaAux);
  auxS = LS;
  while (auxS != NULL) { // recorro la lista simple
    auxC = LC->sig;
    while (auxS->idPuesto > auxC->id) // busco el puesto
      auxC = auxC->sig;
    auxSub = auxC->sub;
    while (!VaciaC(auxS->Cola)) { // proceso la cola
      SacaC(&(auxS->Cola),&producto);
      while (auxSub != NULL && producto.disponible > 0) {
        if (strcmp(producto.codigo,auxSub->codigo) == 0 && auxSub->cantEnviados < auxSub->cantSolicitados) {
          faltantes = auxSub->cantSolicitados - auxSub->cantEnviados;
          if (faltantes > producto.disponible) {
            auxSub->cantEnviados += producto.disponible;
            producto.disponible = 0;
          }
          else {
            auxSub->cantEnviados = auxSub->cantEnviados;
            producto.disponible -= faltantes;
          }
        }
        auxSub = auxSub->sig;
      }
      if (producto.disponible > 0)
        PoneC(&ColaAux,producto);
    }
    while (!VaciaC(ColaAux)) {
    SacaC(&ColaAux,&producto);
    PoneC(&(auxS->Cola),producto);
    }
    auxS = auxS->sig;
  }
}

// Inciso i.c)
void EliminaProducto(char codigo[8],unsigned int X,TListaC LC) {
  TListaC auxC;
  TSubL actSub,antSub;
  if (LC != NULL) {
    auxC = LC->sig;
    do {
      actSub = auxC->sub;
      antSub = NULL;
      while (actSub != NULL) {
        if (strcmp(codigo,actSub->codigo) == 0) {
          if (actSub != auxC->sub) {
            antSub->sig = actSub->sig;
            free(actSub);
            actSub = antSub->sig;
          }
          else {
            auxC->sub = auxC->sub->sig;
            free(actSub);
            actSub = auxC->sub;
          }
        }
        else {
          antSub = actSub;
          actSub = actSub->sig;
        }
      }
      auxC = auxC->sig;
    } while (auxC == LC || X >= auxC->id);
}

// Inciso iii)
"Colas.h"
typedef struct {
  char codigo[8];
  unsigned int disponible;
} TElementoC;
typedef struct nodo{
  TElementoC dato;
  struct nodo *sig;
} nodo;
typedef struct {
  nodo *pri,*ult;
} TCola;

int VaciaC(TCola C);
void SacaC(TCola *C,TElementoC *dato);

"Colas.c"
#include <stdlib.h>
#include "Colas.h"
int VaciaC(TCola C){
  return TCola.pri == NULL;
}
void SacaC(TCola *C,TElementoC *dato){
  nodo *aux;
  aux = C->pri;
  C->pri = aux->sig;
  *dato = aux->dato;
}

/* Correcciones:
inciso i.a)
  - No asigno el nodo nuevo a la sublista del puesto
  - el while deberia ser mientras no nulo y (no destinatario o no codigo)
  - No actualizo nuevoC->cantproductos
Puntaje: 1.5/2.5

inciso i.b)
  - auxSub no se reinicia, la Cola esta ordenada por codigo pero la sublista no, tengo que recorrerla toda
Puntaje: 3/4

inciso i.c)
  - Esta mal la condicion del do while
Puntaje: 2.1/2.5

inciso ii + iii)
 - SacaC no libera el nodo
 - Si la cola tenia un solo nodo deberia quedar C->pri = C->ult = NULL;
 - No controlo que la cola este vacia al sacar
Puntaje: 0.6/1.5

Puntaje i: 6.6
Puntaje Total: 7.2
