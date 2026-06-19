#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilas.h"

typedef struct nodoC { // Cada nodo representa un call center
  char razonSocial[41],provincia[31]; // razon social no se repide, no ordenado
  float porcentajeComision;
  struct nodoC *sig;
} nodoC;
typedef nodoC *TListaC;

/*
Contenido Pila:
  char CodigoMP[11];
  float coefComision; // 0.2 representa 20%
*/

typedef struct {
  char razonSocial[41];
  float recaudacionBruta,recaudacionNeta;
} Rresumen;

void CargaPila(TPila *P);
void CargaListaC(TListaC *LC);
float BuscaComision(TPila *P,char CodigoMP[]);
void ProcesaVentas(TListaC *LC,TPila *P);
void EliminaCallCenters(TListaC *LC,char Q[]);

int main() {
  TPila P;
  TListaC LC;
  char Q[31];
  CargaPila(&P);
  CargaListaC(&LC);
  ProcesaVentas(&LC,&P);
  printf("Ingresa la provincia Q: ");
  scanf("%s",Q);
  EliminaCallCenters(&LC,Q);
  return 0;
}

// Inciso i.a)
float BuscaComision(TPila *P,char CodigoMP[]) {
  TElementoP dato;
  float comision;
  if (VaciaP(*P))
    return 0;
  else {
    SacaP(P,&dato);
    if (strcmp(dato.CodigoMP,CodigoMP) == 0) {
      PoneP(P,dato);
      return dato.coefComision;
    }
    else
      comision = BuscaComision(P,CodigoMP);
    PoneP(P,dato);
    return comision;
  }
}

void ProcesaVentas(TListaC *LC,TPila *P) {
  FILE *archT,*archB;
  TListaC antC,actC,nuevoC;
  char razonSocial[41],provincia[31],CodigoMP[11],fecha[20],CUIT[14];
  float importe,comisionC,comisionP;
  Rresumen resumen;
  if ((archT = fopen("Ventas.TXT","rt")) == NULL) {
    printf("Error al abrir el archivo de texto");
  }
  else {
    if ((archB = fopen("COMXCC202505.DAT","wb")) == NULL) {
      printf("Error al crear el archivo binario");
    }
    else {
      while (fscanf(archT,"%s %s %s %s %s %f",razonSocial,provincia,CodigoMP,fecha,CUIT,&importe) == 6) {
        if (razonSocial[strlen(razonSocial) - 1] == 'A' && razonSocial[strlen(razonSocial) - 2] == 'R' && fecha[3] == '0' && fecha[4] == '5' && fecha[6] == '2' && fecha[7] == '0' &&
            fecha[8] == '2' && fecha[9] == '5') {
              strcpy(resumen.razonSocial,razonSocial);
              resumen.recaudacionBruta = importe;
              antC = *LC;
              actC = antC->sig;
              while (actC != *LC && strcmp(actC->razonSocial,razonSocial) != 0) {
                antC = actC;
                actC = actC->sig;
              }
              if (strcmp(actC->razonSocial,razonSocial) == 0)
                comisionC = actC->porcentajeComision/100;
              else {
                comisionC = 4.5/100;
                nuevoC = (TListaC)malloc(sizeof(nodoC));
                nuevoC->sig = actC;
                antC->sig = nuevoC;
                strcpy(nuevoC->razonSocial,razonSocial);
                strcpy(nuevoC->provincia,provincia);
                nuevoC->porcentajeComision = 4.5;
              }
              comisionP = BuscaComision(P,CodigoMP);
              resumen.recaudacionNeta = importe - importe*comisionC - importe*comisionP;
              fwrite(&resumen,sizeof(resumen),1,archB);
            }
      }
      fclose(archB);
    }
    fclose(archT);
  }
}

// Inciso i.b)
void EliminaCallCenters(TListaC *LC,char Q[]){
  TLista antC,actC;
  if (*LC != NULL) {
    antC = *LC;
    actC = antC->sig;
    while (actC != *LC) {
      if (strcmp(act->provincia,Q) == 0) {
        antC->sig = actC->sig;
        free(actC);
        actC = antC->sig;
      }
      else {
        antC = actC;
        actC = actC->sig;
      }
    }
    if (strcmp((*LC)->provincia,Q) == 0) {
      *LC = antC;
      antC->sig = actC->sig;
      free(actC);
    }
  }
}

// Inciso iii
"Pilas.h"
typedef struct {
  char CodigoMP[11];
  float coefComision; // 0.2 representa 20%
} TElementoP;
typedef struct nodoP {
  TElementoP dato;
  struct nodoP *sig;
} nodoP;
typedef nodoP *TPila;

void SacaP(TPila *P,TElementoC *dato);
void IniciaP(TPila *P);

"Pilas.c"
#include "Pilas.h"
#include <stdlib.h>
void SacaP(TPila *P,TElementoC *dato){
  TPila aux;
  if (*P != NULL) {
    aux = *P;
    *P = aux->sig;
    *dato = aux->dato;
    free(aux);
  }
}
void IniciaP(TPila *P){
  *P = NULL;
}

/* Correcciones:
inciso i.a)
 - No controlo que *LC pueda ser coincidencia, en el while tendria que ser actC != (*LC)->sig
 - No controlo *LC == NULL
 Puntaje 3/5
inciso i.b)
 - No contemplo bien casos borde:
   - Lista con un solo nodo
   - Borrar todos los nodos
   - Borrar el ultimo nodo
   - Actualizar correctamente LC
Puntaje 2/3.5
inciso ii + iii)
Puntaje 1.5/1.5

Total inciso i) 5
Total 6.5
