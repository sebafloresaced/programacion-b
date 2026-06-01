#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colas.h"
#define DiasMeses[12] = {31,28,31,30,31,30,31,31,30,31,30,31}

typedef struct {
  unsigned int horas,minutos;
} tiempo;

typedef struct nodito {
  char patente[8],hora[6]; // ordenada por patente
  unsigned int fecha;
  tiempo Tabonado,Tocupacion;
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

typedef struct nodoD {
  char codigo[6],nombre[31],estudiante; // ordenada por codigo desc
  TSubL sub;
  struct nodoD *sig,*ant;
} nodoD;
typedef nodoD *PnodoD;
typedef struct {
  PnodoD pri,ult;
} TListaD;

/*
Cada elemento de C contiene:
    - Codigo
    - Patente
    - Fecha (en nro)
    - Hora
    - Tabonado
    - Tocupacion
*/

void CargaLista(TListaD *LD);
void CargaCola(TCola *C);
int MultaDeMesX(unsigned int fecha,unsigned int mes);
void ProcesaC(TCola *C,TListaD *LD);
void GeneraArchivo (TListaD LD, char AG[6], unsigned int K);
void EliminaMultas(TListaD *LD,char X[6]);

/*
inciso ii
Crear el main()
*/

int main() {
  TListaD LD;
  TCola C;
  char AG[6],X[6];
  unsigned int K;
  CargaLista(&LD);
  CargaCola(&C);
  ProcesaC(&C,&LD);
  printf("Ingresa AG y K:");
  scanf("%s %u",AG,&K);
  GeneraArchivo(LD,AG,K);
  printf("Ingresa X:");
  scanf("%s",X);
  EliminaMultas(&LD,X);
  return 0;
}

/*
inciso i a)
Procesar C y actualizar LD (si el Tabonado es menor a Tocupacion) para infracciones
cometidas en septiembre (el resto deben permaneces en la cola en el mismo orden).
*/

int MesDeMulta(unsigned int fecha){
  unsigned int i=0;
  while (i < 12 && fecha > DiasMeses[i]) {
    fecha -= DiasMeses[i];
    i++;
  }
  return i;
}
void ProcesaC(TCola *C,TListaD *LD) {
  TCola auxC;
  TElemC multa;
  PnodoD auxD,nuevoD;
  TSubL actS,antS,nuevoS;
  IniciaC(*auxC);
  while (!VaciaC(*C)) {
    SacaC(C,&multa);
    if (multa.Tabonado < multa.Tocupacion && MesDeMulta(multa.fecha) == 9) { // multa correcta
      nuevoS = (TSubL)malloc(sizeof(nodito));
      nuevoS->fecha = multa.fecha;
      strcpy(nuevoS->patente,multa.patente);
      strcpy(nuevoS->hora,multa.hora);
      nuevoS->Tabonado.horas = multa.Tabonado / 60;
      nuevoS->Tabonado.minutos = multa.Tabonado % 60;
      nuevoS->Tocupacion.horas = multa.Tocupacion / 60;
      nuevoS->Tocupacion.minutos = multa.Tocupacion % 60;
      auxD = LD->pri;
      while (strcmp(multa.codigo,auxD->codigo) < 0) {
        auxD = auxD->sig;
      }
      actS = auxD->sub;
      antS = NULL;
      while (actS != NULL && strcmp(multa.patente,actS->patente) > 0) {
        antS = actS;
        actS = actS->sig;
      }
      if (actS != auxD->sub) {
        nuevoS->sig = actS;
        antS->sig = nuevoS;
      }
      else {
        nuevoS->sig = auxD->sub;
        auxD->sub = nuevoS;
      }
    else
      PoneC(*auxC,multa);
    }
  }
  while (!VaciaC(auxC)) {
    SacaC(&auxC,&multa);
    PoneC(C,multa);
  }
}

/*
inciso i b)
Procesar C y actualizar LD (si el Tabonado es menor a Tocupacion) para infracciones
cometidas en septiembre (el resto deben permaneces en la cola en el mismo orden).
*/

void GeneraArchivo (TListaD LD, char AG[6], unsigned int K) {
  TSubL auxS;
  PnodoD auxD;
  FILE *arch;
  unsigned int cont=0;
  if ((arch = fopen("MULTAS.DAT","wb")) == NULL) {
    printf("Error al crear el archivo");
  }
  else {
    auxD = LD.pri;
    while (strcmp(AG,auxD->codigo) < 0)
      auxD = auxD->sig;
    auxS = auxD->sub;
    while (auxS != NULL) {
      cont++;
      if (MesDeMulta(auxS->fecha) % 2 == 0 && (strcmp(auxS->hora,"12:00") < 0 || strcmp(auxS->hora,"18:00")) > 0) {
        fwrite(auxD,sizeof(nodito),1,arch);
      }
      auxS = auxS->sig;
    }
    if (cont > K && auxD->estudiante == 'S')
      printf("\nAl agente con codigo %s le correspone la bonificacion.",AG);
    fclose(arch);
  }
}

/*
inciso i c)
Eliminar de LD las multas realizadas por el agente X, de las patentes que empiecen con "AF", eliminar el agente si se queda sin multas. X podria no existir.
*/

void EliminaMultas(TListaD *LD,char X[6]) {
  PnodoD auxD;
  TSubL actS,antS;
  auxD = LD->pri;
  while (auxD != NULL && strcmp(X,auxD->codigo) < 0)
    auxD=auxD->sig;
  if (auxD!= NULL && strcmp(X,auxD->codigo) == 0) {
    actS = auxD->sub;
    antS = NULL;
    while (actS != NULL) {
      if (actS->patente[0] == 'A' && actS->patente[1] == 'F') {
        if (actS == auxD->sub) {
          auxD->sub = actS->sig;
          free(actS);
          actS = auxD->sub;
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
    if (auxD->sub == NULL) {
      if (auxD->ant != NULL)
        auxD->ant->sig = auxD->sig;
      else
        LD->pri = auxD->sig;
      if (auxD->sig != NULL)
        auxD->sig->ant = auxD->ant;
      else
        LD->ult = auxD->ant;

      free(auxD);
    }
  }
}

/* Inciso iii

Crear el TDA de cola dinamica. Desarrolar SacaC()

"Colas.h"
typedef struct {
  char codigo[6],patente[8],hora[6];
  unsigned int fecha,Tabonado,Tocupacion;
} TElementoC;
typedef struct nodo {
  TElementoC dato;
  struct nodo *sig;
} nodo;
typedef struct {
  nodo *pri,*ult;
} TCola;

SacaC(TCola *C,TElementoC *dato);

"Colas.c"
#include "Colas.h"
SacaC(TCola *C,TElementoC *dato){
  nodo *aux;
  if (C->pri != NULL) {
    *dato = C->pri->dato;
    aux = C->pri;
    if (C->pri != C->ult) {
      C->pri = C->pri->sig;
    }
    else {
      C->pri = C->ult = NULL;
    }
    free(aux);
  }
}
