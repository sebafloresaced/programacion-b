#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "Colas.h"

typedef struct nodoC {
  char patente[8],vip,libre,radio[4];
  unsigned int cantmax;
  struct nodoC *sig;
} nodoC;
typedef nodoC *TListaC;

typedef struct nodoS {
  char patente[8];
  TCola C;
  struct nodoS *sig;
} nodoS;
typedef nodoS *TListaS;

 /*
 Cada elemento de la cola contiene:
  - cantidad de pasajeros
  - vip
  - radio
*/

typedef struct {
  unsigned int pasajeros;
  char vip,radio;
} Rviaje;

typedef struct {
  unsigned int cantviajes,cantpasajeros;
} RegVec;
typedef RegVec TVec[3];

// Inciso ii)
void CargaLS(TListaS *LS);
void CargaLC(TListaC *LC);
void ProcesaArchivo(TListaC LC,TListaS *LS);
void EliminaViajes(TListaS LS);
void EliminarAuto(TListaS *LS,TListaC *LC,char P[8],TVec V);
int main(){
  TListaS LS;
  TListaC LC;
  char P[8];
  TVec V = {0};
  CargaLC(&LC);
  CargaLS(&LS);
  ProcesaArchivo(LC,&LS);
  EliminaViajes(LS);
  printf("\nIngresa P: ");
  scanf("%s",P);
  EliminarAuto(&LS,&LC,P,V);
  return 0;
}

// Inciso i.a)
void ProcesaArchivo(TListaC LC,TListaS *LS){
  FILE *arch;
  TListaC auxC;
  TListaS antS,actS,nuevoS;
  Rviaje viaje;
  if ((arch = fopen("VIAJES.DAT","rb")) == NULL)
    printf("Error al abrir el archivo");
  else {
    while (fread(&viaje,sizeof(Rviaje),1,arch) == 1) {
      auxC = LC->sig; // principio de la lista
      while (auxC != LC && (auxC->libre == 'N' || (viaje.vip == 'S' && auxC->vip == 'N') || strchr(auxC->radio, viaje.radio) == NULL || auxC->cantmax < viaje.pasajeros))
        auxC = auxC->sig;
      if (auxC->libre == 'S' && auxC->vip == viaje.vip && strchr(auxC->radio, viaje.radio) != NULL && auxC->cantmax >= viaje.pasajeros) {
        printf("\nSe le asigno el viaje al auto %s",auxC->patente);
        auxC->libre = 'N';
        actS = *LS;
        antS = NULL;
        while (actS != NULL && strcmp(auxC->patente,actS->patente) > 0) {
          antS = actS;
          actS = actS->sig;
        }
        nuevoS = (TListaS)malloc(sizeof(nodoS));
        strcpy(nuevoS->patente,auxC->patente);
        if (actS == *LS || strcmp(auxC->patente,(*LS)->patente) < 0) {
          nuevoS->sig = *LS;
          *LS = nuevoS;
          IniciaC(&(nuevoS->C));
          PoneC(&(actS->C),viaje);
        }
        else {
          if (strcmp(auxC->patente,actS->patente) < 0) {
            nuevoS->sig = actS;
            antS->sig = nuevoS;
            IniciaC(&(nuevoS->C));
            PoneC(&(actS->C),viaje);
          }
          else {
            PoneC(&(actS->C),viaje);
            free(nuevoS);
          }
        }
      }
      else {
        printf("\nNo se pudo asignar el viaje");
      }
    }
  }
}

// Inciso i.b)
void EliminaViajes(TListaS LS) {
  unsigned int cont,maxElim=0;
  char maxPat[8];
  Rviaje viaje;
  TCola Caux;
  IniciaC(&Caux);
  while (LS != NULL) {
    cont=0;
    while (!VaciaC(LS->C)) {
      SacaC(&(LS->C),&viaje);
      if (viaje.pasajeros != 0)
        PoneC(*Caux,viaje);
      else
        cont++;
    }
    if (cont >= maxElim) {
      maxElim = cont;
      strcpy(maxPat,LS->patente);
    }
    while (!VaciaC(Caux)) {
      SacaC(&Caux,&viaje);
      PoneC(&(LS->C),viaje);
    }
    LS = LS->sig;
  }
  printf("\n%u fue la mayor cantidad de viajes no efectuados, realizados por el auto %s.",maxElim,maxPat);
}

// Inciso i.c)
void EliminarAuto(TListaS *LS,TListaC *LC,char P[8],TVec V){ // Inicializo vector en el main
  TListaS antS,actS;
  TListaC antC,actC;
  actS = *LS;
  antS = NULL;
  Rviaje viaje;
  unsigned int idx;
  while (strcmp(actS->patente,P) != 0) {
    antS = actS;
    actS = actS->sig;
  }
  if (actS == *LS)
    *LS = actS->sig;
  else
    antS->sig = actS->sig;
  while (!VaciaC(actS->C)) {
    SacaC(&(actS->C),&viaje);
    switch (viaje.radio) {
      case 'U': idx = 0;
                break;
      case 'R': idx = 1;
                break;
      case 'I': idx = 2;
                break;
    }
    V[idx].cantviajes++;
    V[idx].cantpasajeros += viaje.pasajeros;
  }
  free(actS);
  actC = (*LC)->sig;
  antC = *LC;
  while (strcmp(actC->patente,P) != 0) {
    antC = actC;
    actC = actC->sig;
  }
  if (actC == *LC) {
    antC->sig = actC->sig;
    *LC = antC;
  }
  else
    antC->sig = actC->sig;
  free(actC);
}

// Inciso iii)
"Colas.h"
#define MaxElem 20
typedef struct {
  unsigned int cant;
  char vip,radio;
} TElemC;
typedef struct {
  int pri,ult;
  TElemC datos[MaxElem];
} TCola;
void IniciaC(TCola *C);
int VaciaC(TCola C);
void SacaC(TCola *C,TElemC *dato);
void PoneC(TCola *C,TElemC dato);

"Colas.c"
void IniciaC(TCola *C){
  C->pri = C->ult = -1;
}
int VaciaC(TCola C) {
  return C.pri == -1;
}
void SacaC(TCola *C,TElemC *dato){
  if (!VaciaC(*C)) {
    *dato = C->datos[C->pri];
    if (C->pri == C->ult)
      IniciaC(C);
    else
      if (C->pri == MaxElem-1)
        C->pri = 0;
      else
        C->pri++;
  }
}
void PoneC(TCola *C,TElemC dato){
  if (!(C->pri - 1 == C->ult || (C->pri == 0 && C->ult == MaxElem-1))) {
    if (C->ult == MaxElem-1)
      C->ult = 0;
    else
      C->ult++;
    C->datos[C->ult] = dato;
  }
}

/*
Rubrica
i.a = 1.3
i.b = 2
i.c = 2.5
ii = 0,75
iii = 0,4
total = 7
*/
