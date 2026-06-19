#include <stdio.h>
#include <stdlib.h>
#include "Pilas.h"
#include <string.h>

typedef struct nodito { // Lista de codigos de materias correlativas
  char codigo[6];
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

typedef struct nodoS {
  char codigo[6],nombre[26]; // Ordenada ascendentemente por codigo, si empieza por 'O' es optativa
  unsigned int cantCreditos,cuatrimestre;
  TSubL sub;
  struct nodoS *sig;
} nodoS;
typedef nodoS *TListaS;

typedef struct nodoD {
  unsigned int cuatrimestre; // Ordenada por cuatrimestre
  TPila P;
  struct nodoD *ant,*sig;
} nodoD;
typedef nodoD *PnodoD;
typedef struct {
  PnodoD pri,ult;
} TListaD;

/*
Contenido Pila:
  char codigo[6];
  unsigned int creditos;
*/

void CargaListaS(TListaS *LS);
void GeneraArchivo(TListaS LS,char A[]);
void GeneraListaD(TListaD *LD,TListaS LS);
void EliminaAsignatura(TListaS *LS,TListaD *LD,char B[]);

int main(){
  TListaS LS;
  TListaD LD;
  char A[6],B[6];
  CargaListaS(&LS);
  printf("Ingresa el codigo A: ");
  scanf("%s",A);
  GeneraArchivo(LS,A);
  GeneraListaD(&LD,LS);
  printf("Ingresa el codigo B: ");
  scanf("%s",B);
  EliminaAsignatura(&LS,&LD,B);
  return 0;
}


// Inciso i.a)
void GeneraArchivo(TListaS LS,char A[]) { // A es codigo de materia validado
  FILE *arch;
  TListaS aux1S,aux2S;
  TSubL auxSub;
  char codigo[6];
  unsigned int contCorrelativas=0,acumCreditos=0;
  if (LS != NULL && ((arch = fopen(A + ".TXT","wt")) != NULL)) {
    aux1S = LS;
    while (aux1S != NULL && strcmp(A,aux1S->codigo) != 0) {
      aux1S = aux1S->sig;
    }
    if (aux1S != NULL) {
      if (strcmp(A,aux1S->codigo) == 0) {
        fprintf(arch,"%s del cuatrimestre %u",aux1S->nombre,aux1S->cuatrimestre);
        auxSub = aux1S->sub;
        while (auxSub != NULL) {
          contCorrelativas++;
          strcpy(codigo,auxSub->codigo);
          aux2S = LS;
          while (aux2S != NULL && strcmp(codigo,aux2S->codigo) != 0) {
            aux2S = aux2S->sig;
          }
          acumCreditos += aux2S->cantCreditos;
          fprintf(arch,"\n%s",aux2S->nombre);
          auxSub = auxSub->sig;
        }
        if (contCorrelativas != 0)
          fprintf(arch,"\nPromedio de creditos de correlativas: %.2f",(float)acumCreditos/contCorrelativas);
        else
          fprintf(arch,"\nNO TIENE CORRELATIVAS ANTERIORES");
      }
    }
    fclose(arch);
  }
  else {
    printf("Error");
  }
}

// Inciso i.b)
void GeneraListaD(TListaD *LD,TListaS LS){
  PnodoD auxD,nuevoD;
  TListaS auxS;
  auxS = LS;
  TElementoP nodo;
  LD->pri = LD->ult = NULL;
  while (auxS != NULL) {
    auxD = LD->pri;
    while (auxD != NULL && auxS->cuatrimestre > auxD->cuatrimestre)
      auxD = auxD->sig;
    if (LD->pri == NULL) { // primer nodo
      nuevoD = (PnodoD)malloc(sizeof(nodoD));
      nuevoD->sig = nuevoD->ant = NULL;
      LD->pri = LD->ult = nuevoD;
      nuevoD->cuatrimestre = auxS->cuatrimestre;
      IniciaP(&nuevoD->P);
      nodo.creditos = auxS->cantCreditos;
      strcpy(nodo.codigo,auxS->codigo);
      PoneP(&nuevoD->P,nodo);
    }
    else {
      if (auxD == NULL && auxS->cuatrimestre < LD->pri->cuatrimestre) { // va al principio
        nuevoD = (PnodoD)malloc(sizeof(nodoD));
        nuevoD->sig = LD->pri;
        nuevoD->ant = NULL;
        LD->pri = nuevoD;
        nuevoD->cuatrimestre = auxS->cuatrimestre;
        IniciaP(&nuevoD->P);
        nodo.creditos = auxS->cantCreditos;
        strcpy(nodo.codigo,auxS->codigo);
        PoneP(&nuevoD->P,nodo);
      }
      else {
        if (auxD == NULL && auxS->cuatrimestre > LD->pri->cuatrimestre) { // va al final
          nuevoD = (PnodoD)malloc(sizeof(nodoD));
          nuevoD->sig = NULL;
          nuevoD->ant = LD->ult;
          LD->ult = nuevoD;
          nuevoD->cuatrimestre = auxS->cuatrimestre;
          IniciaP(&nuevoD->P);
          nodo.creditos = auxS->cantCreditos;
          strcpy(nodo.codigo,auxS->codigo);
          PoneP(&nuevoD->P,nodo);
        }
        else { // va en el medio
          if (auxS->cuatrimestre < auxD->cuatrimestre) { // no existe el cuatrimestre
            nuevoD = (PnodoD)malloc(sizeof(nodoD));
            nuevoD->sig = auxD;
            nuevoD->ant = auxD->ant;
            auxD->ant = nuevoD;
            nuevoD->ant->sig = nuevoD;
            nuevoD->cuatrimestre = auxS->cuatrimestre;
            IniciaP(&nuevoD->P);
            nodo.creditos = auxS->cantCreditos;
            strcpy(nodo.codigo,auxS->codigo);
            PoneP(&nuevoD->P,nodo);
          }
          else { // ya existe el cuatrimestre
            nodo.creditos = auxS->cantCreditos;
            strcpy(nodo.codigo,auxS->codigo);
            PoneP(&(auxD->P),nodo);
          }
        }
      }
    }
    auxS = auxS->sig;
  }
}

// Inciso i.c)
void EliminaAsignaturaPila(TPila *P,char B[]){
  TElementoP dato;
  if (!VaciaP(*P)) {
    SacaP(P,&dato);
    if (strcmp(B,dato.codigo) != 0) {
      EliminaAsignaturaPila(P,B);
      PoneP(P,dato);
    }
  }
}
void EliminaAsignatura(TListaS *LS,TListaD *LD,char B[]){
  TListaS actS,antS;
  TSubL actSub,antSub;
  PnodoD auxD;
  unsigned int cuatrimestreB;
  actS = *LS;
  while (actS != NULL && strcmp(B,actS->codigo) > 0) {
    antS = actS;
    actS = actS->sig;
  }
  if (actS != NULL && strcmp(B,actS->codigo) == 0) {
    // elimino nodo de LS
    cuatrimestreB = actS->cuatrimestre;
    antS->sig = actS->sig;
    free(actS);
    // elimino apariciones en correlativas
    actS = *LS;
    antS = NULL;
    while (actS != NULL) {
      actSub = actS->sub;
      antSub = NULL;
      while (actSub != NULL) {
        if (strcmp(actSub->codigo,B) == 0) {
          if (actSub == actS->sub) {
            actS->sub = actS->sub->sig;
            free(actSub);
            actSub = actS->sub;
          }
          else {
            antSub->sig = actSub->sig;
            free(actSub);
            actSub = antSub->sig;
          }
        }
        else {
          antSub = actSub;
          actSub = actSub->sig;
        }
      }
      actS = actS->sig;
    }
    // elimino la pila correspondiente en la lista doble
    auxD = LD->pri;
    while (auxD != NULL && cuatrimestreB > auxD->cuatrimestre)
      auxD = auxD->sig;
    if (auxD != NULL && cuatrimestreB == auxD->cuatrimestre)
      EliminaAsignaturaPila(&(auxD->P),B);
  }
  else
    printf("\nNo se encontro la asignatura buscada");
}

// Inciso iii)
"Pilas.h"
typedef struct {
  char codigo[6];
  unsigned int creditos;
} TElementoP;
typedef struct nodo {
  TElementoP dato;
  struct nodo *sig;
} nodo;
typedef nodo *TPila;

void IniciaP(TPila *P);
int VaciaP(TPila P);
TElementoP ConsultaP(TPila P);
void SacaP(TPila *P,TElementoP *dato);
void PoneP(TPila *P,TElementoP dato);

"Pilas.c"
#include <stdlib.h>
#include "Pilas.h"
void IniciaP(TPila *P){
  *P = NULL;
}
int VaciaP(TPila P){
  return P == NULL;
}
TElementoP ConsultaP(TPila P){
  return P->dato;
}
void SacaP(TPila *P,TElementoP *dato){
  TPila elimina;
  if (*P != NULL) {
    *dato = (*P)->dato;
    elimina = *P;
    *P = elimina->sig;
    free(elimina);
  }
}
void PoneP(TPila *P,TElementoP dato){
  TPila nuevo;
  nuevo = (TPila)malloc(sizeof(nodo));
  nuevo->dato = dato;
  nuevo->sig = *P;
  *P = nuevo;
}

/* Correcciones:
inciso i.a)
  - No se puede concatenar un string con +, deberia haber hecho strcpy(nomArch,A) y despues strcat(nomArch,".TXT")
  - fprintf deben recibir el archivo
Puntaje: 2.5/3

inciso i.b)
  - Cuando agrego un nuevo nodo no inicializo la pila ni apilo la materia
  - Cuando inserto al principio no actualizo el LD->pri->ant = nuevoD
  - Cuando inserto al final no actualizo el LD->ult->sig = nuevoD
Puntaje: 1.8/3

inciso i.c)
  - No chequeo si estoy eliminando el primer nodo en LS
  - La funcion recursiva elimina solo la aprimera aparicion
Puntaje: 2/2.5

inciso ii + iii)
Puntaje: 1.5/1.5

Puntaje i: 6.3
Puntaje Total: 7.8
