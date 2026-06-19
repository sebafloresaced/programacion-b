#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colas.h"

typedef struct nodito {
  unsigned int numero;
  char DNI[9]; // cadena vacia si la habitacion esta libre
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

typedef struct nodoS {
  unsigned int numero; // ordenada por numero de habitacion
  char tipo;
  TSubL sub;
  struct nodoS *sig;
} nodoS;
typedef nodoS *TListaS;

typedef struct nodoD {
  char DNI[9],tipo,individual,ingreso;  // ordenada por DNI
  struct nodoD *sig,*ant;
 } nodoD;
 typedef nodoD *PnodoD;
 typedef struct {
   PnodoD pri,ult;
 } TListaD;


 // Elementos de la cola CP:
 // char DNI[9],tipo,individual,ingreso;

void CargaListaS(TListaS *LH);
void CargaListaD(TListaD *LDP);
void CargaCola(TCola *CP);
void ProcesarPedidos(TCola *CP,TListaS LH,TListaD *LDP);
void EliminaHabitaciones(TListaS *LH, TListaD *LDP, unsigned int Pacientes[]);
unsigned int MaxTipo(unsigned int Pacientes[],unsigned int idx);

int main(){
  TCola CP;
  TListaS LH;
  TListaD LDP;
  unsigned int Pacientes[5] = {0};
  char TipoMax;
  CargaListaS(&LH);
  CargaListaD(&LDP);
  CargaCola(&CP);
  ProcesarPedidos(&CP,LH,&LDP);
  EliminaHabitaciones(&LH,&LDP,Pacientes);
  switch (MaxTipo(Pacientes,4)) {
  case 0: TipoMax = 'P';
            break;
  case 1: TipoMax = 'C';
            break;
  case 2: TipoMax = 'T';
            break;
  case 3: TipoMax = 'E';
            break;
  case 4: TipoMax = 'M';
            break;
  }
  printf("El tipo %c es el que mas pacientes tiene para trasladar",TipoMax);
 return 0;
}

// inciso i.a)
void ProcesarPedidos(TCola *CP,TListaS LH,TListaD *LDP) {
  TListaS auxS;
  TSubL auxSub;
  PnodoD auxD,nuevoD;
  TElementoC pedido;
  int encontrada;
  while (!VaciaC(*CP)) {
    SacaC(CP,&pedido);
    auxS = LH;
    encontrada = 0;
    while (auxS != NULL && !encontrada) {
      auxSub = auxS->sub;
      while (auxSub != NULL && !encontrada) {
        if (strcmp(auxSub->DNI,"") == 0  && auxS->tipo == pedido.tipo && (pedido.individual == 'S' || (pedido.individual == 'N' && auxSub->individual == 'N'))) {
          encontrada = 1;
          strcpy(auxSub->DNI,pedido.DNI);
          if (pedido.ingreso == 'N') {
            auxS = LH;
            encontrada = 0;
            while (!encontrada) {
              auxSub = auxS->sub;
              while (!encontrada) {
                if (!strcmp(auxSub->DNI,pedido.DNI)) {
                  encontrada = 1;
                  strcpy(auxSub->DNI,"")l
                }
                auxSub = auxSub -> sig;
              }
              auxS = auxS->sig;
            }
          }
        }
        else
          auxSub = auxSub->sig;
      }
      auxS = auxS->sig;
    }
    if (!encontrada) {
      nuevoD = (PnodoD)malloc(sizeof(nodoD));
      nuevoD->tipo = pedido.tipo;
      nuevoD->individual = pedido.individual;
      nuevoD->ingreso = pedido.ingreso;
      strcpy(nuevoD->DNI,pedido.DNI);
      auxD = LDP->pri;
      while (auxD != NULL && strcmp(nuevoD->DNI,auxD->DNI) > 0)
        auxD = auxD -> sig;
      if (auxD != NULL && strcmp(nuevoD->DNI,auxD->DNI) < 0) {
        nuevoD->sig = auxD;
        nuevoD->ant = auxD->ant;
        if (auxD != LDP->pri) {
          auxD->ant->sig = nuevoD;
          auxD->ant = nuevoD;
        }
        else {
          nuevoD->ant = NULL;
          nuevoD->sig = LDP->pri;
          LDP->pri->ant = nuevoD;
          LDP->pri = nuevoD;
        }
      }
      else {
        if (LDP->pri == LDP ->ult) {
          LDP->pri = LDP->ult = nuevoD;
          nuevoD->sig = nuevoD->ant = NULL;
        }
        else {
          LDP->ult->sig = nuevoD;
          nuevoD->ant = LDP->ult;
          LDP->ult = nuevoD;
          nuevoD->sig = NULL;
        }
      }
    }
  }
}

// inciso i.b)
void EliminaHabitaciones(TListaS *LH, TListaD *LDP, unsigned int Pacientes[]) { // el orden de indices es P,C,T,E,M, inicializada en main
  PnodoD auxD,nuevoD;
  TListaS auxS,antS,borraS;
  TSubL borraSub,auxSub;
  auxS = *LH;
  while (auxS != NULL && auxS->numero / 100 < 1) {
    antS = auxS;
    auxS = auxS->sig;
  }
  while (auxS != NULL && auxS->numero / 100 == 1) {
    auxSub = auxS->sub;
    while (auxSub != NULL) {
      if (strcmp(auxSub->DNI,"") == 0) {
        nuevoD = (PnodoD)malloc(sizeof(nodoD));
        nuevoD->tipo = auxS->tipo;
        nuevoD->individual = 'N';
        nuevoD->ingreso = 'S';
        strcpy(nuevoD->DNI,auxSub->DNI);
        switch (nuevoD->tipo) {
          case 'P': Pacientes[0]++;
                    break;
          case 'C': Pacientes[1]++;
                    break;
          case 'T': Pacientes[2]++;
                    break;
          case 'E': Pacientes[3]++;
                    break;
          case 'M': Pacientes[4]++;
                    break;
        }
        auxD = LDP->pri;
        while (auxD != NULL && strcmp(nuevoD->DNI,auxD->DNI) > 0)
          auxD = auxD->sig;
        if (auxD == LDP->pri)
          if (LDP->pri == NULL) {
            LDP->pri = LDP->ult = nuevoD;
            nuevoD->ant = nuevoD->sig = NULL;
          }
          else {
            nuevoD->sig = LDP->pri;
            LDP->pri->ant = nuevoD;
            nuevoD->ant = NULL;
            LDP->pri = nuevoD;
          }
        else
          if (strcmp(nuevoD->DNI,LDP->ult->DNI) > 0) {
            nuevoD->sig = NULL;
            nuevoD->ant = LDP->ult;
            LDP->ult->sig = nuevoD;
            LDP->ult = nuevoD;
          }
          else {
            nuevoD->sig = auxD;
            nuevoD->ant = auxD->ant;
            auxD->ant->sig = nuevoD;
            auxD->ant = nuevoD;
          }
      }
      borraSub = auxSub;
      auxSub = auxSub->sig;
      free(borraSub);
    }
    borraS = auxS;
    auxS = auxS->sig;
    free(borraS);
  }
  if (antS == NULL)
    *LH = auxS;
  else
    antS->sig = auxS;

}

// inciso i.c)
unsigned int MaxTipo(unsigned int Pacientes[],unsigned int idx) { // Llamo con idx = 4
  unsigned int Maxant;
  if (idx == 0)
    return 0;
  else {
    Maxant = MaxTipo(Pacientes,idx - 1);
    return (Pacientes[Maxant] >= Pacientes[idx])? Maxant:idx;
  }
}

// Inciso iii)
"Colas.h"
#define MaxElem 50
typedef struct {
  char DNI[9],tipo,individual,ingreso;
} TElementoC;
typedef struct {
  TElementoC datos[MaxElem];
  int pri,ult;
} TCola;
int VaciaC(TCola C);
void SacaC(TCola *C,TElementoC *dato);

"Colas.c"
#include "Colas.h"
int VaciaC(TCola C){
  return C.pri == -1;
}
void SacaC(TCola *C,TElementoC *dato){
  if (!VaciaC(*C)) {
    *dato = C->datos[C->pri];
    if (C->pri == C->ult)
      C->pri = C->ult = -1;
    else
      if (C->pri == MaxElem-1)
        C->pri = 0;
      else
        C->pri++;
  }
}

/*
Correciones:
Inciso i.a)
- no existe el campo individual, tengo que chequear que haya mas de una cama en la habitacion:
int EsIndividual(TSubL sub){
  return sub != NULL && sub->sig == NULL;
}
- si no es un ingreso, asigno la cama nueva y luego busco para liberar, deberia primero liberar y despues asignar la nueva ya
que podria borrar la cama nueva
- Pide mostrar el porcentaje de pedidos que pudieron concretarse. Usar un cont de concretados y otro de pedidos totales
Puntaje: 1.8/4

Inciso i.b)
Puntaje: 1,7/3,5

Inciso i.c)
Puntaje: 1/1

Inciso ii)
Puntaje 0,75/0,75

Inciso iii)
Puntaje 0,75/0,75

Puntaje inciso i: 4,5
Total: 6

*/
