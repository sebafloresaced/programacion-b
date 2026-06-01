// Inciso ii
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colas.h"

typedef struct nodito {
  char fecha[11];
  float precio,cant;
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

typedef struct nodoS {
  char codigo[16];
  float precio,stock,ganancia;
  TSubL sub;
  struct nodoS *sig;
} nodoS;
typedef nodoS *TListaS;

typedef struct nodoD {
  char codigo[16];
  float stock;
  struct nodoD *sig,*ant;
} nodoD;
typedef nodoD *PnodoD;
typedef struct {
  PnodoD pri,ult;
} TListaD;

void CargaLS(TListaS *LS);
void CargaLD(TListaD *LD);
void CargaC(TCola *C);
void ProcesaCompra(TCola *C,TListaS LS,TListaD *LD);
void CompraProveedor(TListaS *LS,TListaD *LD);

int main(){
  TListaS LS;
  TListaD LD;
  TCola C;
  CargaLS(&LS);
  CargaLD(&LD);
  CargaC(&C);
  ProcesaCompra(&C,LS,&LD);
  CompraProveedor(&LS,&LD);
  return 0;
}

// Inciso i a)
void ProcesaCompra(TCola *C,TListaS LS,TListaD *LD) {
  float acum=0;
  unsigned int cont=0;
  int cantcomprada;
  TElemC producto;
  PnodoD nuevo;
  TListaS auxS;
  while (!VaciaC(*C)) {
    SacaC(C,&producto);
    cont++;
    auxS = LS;
    while (strcmp(producto.codigo,auxS->codigo)>0)
        auxS = auxS->sig;
    if (auxS->stock > 0) { // se compro minimo una unidad
        auxS->stock -= producto.cant;
        if (auxS->stock > 0) // se compraron todas las unidades deseadas
           acum += producto.cant * auxS->precio;
        else
           acum += (producto.cant + auxS->stock) * auxS->precio;
    }
    if (auxS->stock < 0) {
        nuevo = (PnodoD)malloc(sizeof(nodoD));
        strcpy(nuevo->codigo,producto.codigo);
        nuevo->stock = auxS->stock;
        nuevo->sig = NULL;
        if (LD->ult != NULL) {
          nuevo->ant = LD->ult;
          LD->ult->sig = nuevo;
          LD->ult = nuevo;
        }
        else {
          LD->pri = LD->ult = nuevo;
          nuevo->ant = NULL;
        }
    }
  }
  if (cont > 0)
    printf("El importe total es $%.2f.\nEl importe total promedio por producto es %.2f.",acum,acum/cont);
  else
    printf("No se registraron compras");
}

// inciso i b)
void CompraProveedor(TListaS *LS,TListaD *LD) {
  FILE *arch;
  PnodoD auxD,borraD;
  TListaS actS,antS,nuevoS;
  TSubL nuevoSub;
  char fecha[11],codigo[16];
  float precio,cant;
  if ((arch = fopen("PROVEEN.TXT","rt")) == NULL)
    printf("\nError al abrir el archivo.");
  else {
    while (fscanf(arch,"%s %s %f %f",fecha,codigo,&cant,&precio) == 4) {
        if ((fecha[0]=='2' && fecha[1]=='0' && fecha[2]=='2' && fecha[3]=='5' &&
             fecha[5]=='0' && fecha[6]=='4')) {
            actS = *LS;
            antS = NULL;
            while (actS != NULL && strcmp(codigo,actS->codigo)>0) {
                antS = actS;
                actS = actS->sig;
            }
            nuevoSub = (TSubL)malloc(sizeof(nodito));
            nuevoSub->precio = precio;
            nuevoSub->cant = cant;
            strcpy(nuevoSub->fecha,fecha);
            if (actS != NULL && strcmp(codigo,actS->codigo)==0) {
                actS->precio = precio + precio * actS->ganancia / 100;
                if (actS->stock < 0) {
                    actS->stock += cant;
                    if (actS->stock > 0) {
                       auxD = LD->pri;
                       while (auxD != NULL) {
                         if (strcmp(auxD->codigo,codigo) == 0) {
                             borraD = auxD;
                             if (borraD->ant == NULL) { // borro primero
                                if (borraD->sig == NULL) //borro unico
                                  LD->pri = LD->ult = NULL;
                                else {
                                  borraD->sig->ant = NULL;
                                  LD->pri = borraD->sig;
                                }
                             }
                             else
                               if (borraD->sig == NULL) { // borro ultimo
                                 borraD->ant->sig = NULL;
                                 LD->ult = borraD->ant;
                               }
                               else {
                                 auxD->sig->ant = auxD->ant;
                                 auxD->ant->sig = auxD->sig;
                               }
                             auxD = auxD->sig;
                             free(borraD);
                         }
                         else
                           auxD = auxD->sig;
                       }
                    }
                }
                else
                  actS->stock += cant;
                nuevoSub->sig = actS->sub;
                actS->sub = nuevoSub;
            }
            else {
                nuevoS = (TListaS)malloc(sizeof(nodoS));
                nuevoS->stock = cant;
                strcpy(nuevoS->codigo,codigo);
                nuevoS->precio = precio*1.5;
                nuevoS->ganancia = 50;
                nuevoS->sub = nuevoSub;
                nuevoSub->sig = NULL;
                if (actS == *LS) {
                    nuevoS->sig = *LS;
                    *LS = nuevoS;
                }
                else {
                    nuevoS->sig = actS;
                    antS->sig = nuevoS;
                }
            }
        }
    }
    fclose(arch);
  }
}

/*
"Colas.h"
#define MaxElem 50
typedef struct {
  char codigo[16];
  float cant;
} TElemC;
typedef struct {
  TElemC datos[MaxElem];
  int pri,ult;
} TCola;
void SacaC(TCola *C,TElemC *x);
int VaciaC(TCola C);

"Colas.c"
#include "Colas.h"
int VaciaC(TCola C){
  return C.pri == -1;
}
void SacaC(TCola *C,TElemC *x){
  if (!VaciaC(*C)) {
    *x = C->datos[C->pri];
    if (C->pri == C->ult)
      C->pri = C->ult = -1;
    else
      if (C->pri == MaxElem)
        C->pri = 0;
      else
        C->pri++;
  }
}
*/

