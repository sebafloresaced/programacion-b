// Inciso 1 (1.5pts)
Indicar V o F:
  a) "Al finalizar la ejecuci'on del algoritmo de Floyd sobre un digrafo, si el mismo es no conexo, en la diagonal habra posiciones con valor 0 y otras con valor INF"
  Falso. Al finalizar el algoritmo de Floyd, la diagonal de la matriz siempre tendra valor 0.

  b) "Al insertar una clave en un arbol AVL, se deben calcular los FE desde la raiz hasta la clave insertada (a la ida) en el proceso de insercion"
  Falso. Al insertar una clave, se deben calcular los FE desde la clave insertada hasta la raiz (a la vuelta).

// Inciso 2 (4 pts)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Normas 21
#define Empresas 40

typedef struct nodito {
  int nroEmpresa;
  char fechaCertificacion[7]; // ordenada por este campo,  formato aaaamm
  struct nodito *sig;
} nodito
typedef nodito *TSubL;

typedef struct nodoC {
  int norma; // ordenada, no se repite
  char nombreNorma[9];
  TSubL empresasCertificadas;
  struct nodoC *sig;
}
typedef nodoC *TListaC;
// Una empresa puede haber certificado una o mas normas

typedef struct {
  int nroEmpresa,norma;
  char fechaCertificacion[7];
} TRegArch;

// Inciso a: Generar una matriz de 21x40 caracteres, tal que en (i,j) haya un S o N segun si la norma i fue certificada o no por la empresa j. Hallar de forma recursiva mediante una funcion
// int, la cantidad de empresas que han certificado todas las normas
void InicializaMat(TMat Mat) {
    int i, j
    for (i = 0; i < Normas; i++)
        for (j = 0; j < Empresas; j++)
            Mat[i][j] = 'N';
}
void GeneraMatriz(TMat Mat,TListaC LC) {
  TListaC auxC;
  TSubL auxSub;
  InicializaMat(Mat);
  if (LC != NULL) {
    auxC = LC;
    do {
      auxSub = auxC->empresasCertificadas;
      while (auxSub != NULL) {
        Mat[auxC->norma][auxSub->nroEmpresa] = 'S';
        auxSub = auxSub->sig;
      }
      auxC = auxC->sig;
    } while (auxC != LC);
  }
}
int CumpleEmpresa(TMat Mat,int i,int j){
  if (i == Normas)
    return 1;
  else
    return Mat[i][j] == 'S' && CumpleEmpresa(Mat,i+1,j);
}
int CantEmpresasCumplen(TMat Mat,int j){
  if (j == Empresas)
    return 0;
  else
    return CumpleEmpresa(Mat,0,j) + CantEmpresasCumplen(Mat,j+1);
}

// Inciso b: Dados un mes MM (cadena) y una norma N, eliminar todas las empresas que hayan certificado N en el mes MM. Si la norma quedara sin empresas certificadas, eliminarla tambien.
// Generar un archivo binario ELIM.DAT de registros que contentan: nroEmpresa, norma, fechaCertificacion para cada empresa eliminada
void EliminaEmpresas(TListaC *LC,char MM[3],int N) {
  TListaC actC,antC;
  TSubL antSub,actSub;
  TRegArch regArch;
  FILE *arch;
  if ((arch = fopen("ELIM.DAT","wb")) == NULL)
    printf("Error al abrir el archivo");
  else {
    if (*LC != NULL) {
      antC = *LC;
      actC = antC->sig;
      do {
        antC = actC;
        actC = actC->sig;
      } while (actC != (*LC)->sig && actC->norma != N);
      while (actC != NULL && actC->norma == N) {
        actSub = actC->empresasCertificadas;
        antSub = NULL;
        while (actSub != NULL) {
          if (actSub->fechaCertificacion[4] == MM[0] && actSub->fechaCertificacion[5] == MM[1]) { // tengo que eliminar
            regArch.norma = actC->norma;
            regArch.nroEmpresa = actSub->nroEmpresa;
            strcpy(regArch.fechaCertificacion,actSub->fechaCertificacion);
            fwrite(&regArch,sizeof(refArch),1,arch);
            if (actSub == actC->empresasCertificadas) {
              actC->empresasCertificadas = actSub->sig;
            }
            else {
              antSub->sig = actSub->sig;
            }
            free(actSub);
            actSub = antSub->sig;
          }
          else {
            antSub = actSub;
            actSub = actSub->sig;
          }
        }
        if (actC->empresasCertificadas == NULL) { // quedo vacia
          if (actC == *LC) // elimino la cabeza
            if (actC == actC->sig)) // es unico
              *LC = NULL;
            else
              *LC = antC;
          else
            antC->sig = actC->sig;
          free(actC);
          actC = antC->sig;
        }
        else {
          antC = actC;
          actC = actC->sig;
        }
      }
    }
    fclose(arch);
  }
}

// Inciso 3 (2 pts)
int ClaveMenorNivelK(arbol A,pos p,int K,int nivel) {
  int claveAnt,claveMenor = -1;
  pos c;
  if (Nulo(p))
    return -1;
  else {
    c = HijoMasIzq(p,A);
    if (nivel == K) {
      return Info(p,A);
    }
    else {
      while (!Nulo(c)) {
        claveAnt = ClaveMenorNivelK(A,c,K,nivel+1);
        if (claveAnt != -1 && (claveMenor == -1 || claveAnt < claveMenor))
          claveMenor = claveAnt;
        c = HermanoDer(c,A);
      }
      return claveMenor;
    }
  }
}

// Inciso 4 (2.5 pts)
// Inciso 4.a
void ProcesoCola(TCola *C,TMat Mat,int N) {
  TElementoC reg;
  TCola ColaAux;
  IniciaC(&ColaAux);
  int i,int j;
  while (!VaciaC(*C)) {
    SacaC(C,&reg);
    if (reg.id1 > reg.id2) {
      i = reg.id1;
      j = reg.id2;
    }
    else {
      i = reg.id2;
      j = reg.id1;
    }
    if (Mat[i][j] != 0 && Mat[i][j] <= reg.cos)
      PoneC(&ColaAux,reg);
  }
  while (!VaciaC(ColaAux)) {
    SacaC(&ColaAux,&reg);
    PoneC(C,reg);
  }
}

// Inciso 4.b
"Colas.h"
#define MaxElem 40
typedef struct {
  int id1,id2,cos;
} TElementoC;
typedef struct {
  TElementoC datos[MaxElem];
  int pri,ult;
} TCola;

void IniciaC(TCola *C);
int VaciaC(TCola C);
void SacaC(TCola *C,TElementoC *reg);
void PoneC(TCola *C,TElementoC reg);

"Colas.c"
#include "Colas.h"
void IniciaC(TCola *C){
  C->pri = C->ult = -1;
}
int VaciaC(TCola C) {
  return C->pri == -1;
}
void SacaC(TCola *C,TElementoC *reg){
  if (C->pri != -1) {
    *reg = C->datos[C->pri];
    if (C->pri == C->ult)
      IniciaC(C);
    else
      (C->pri)++;
  }
}
void PoneC(TCola *C, TElementoC reg) {
    if (!(C->ult == C->pri - 1 || (C->pri == 0 && C->ult == MaxElem - 1)) {
        if (VaciaC(*C)) {
            C->pri = 0;
            C->ult = 0;
        } else {
            if (C->ult != MaxElem - 1)
              C->ult += 1;
            else
              C->ult = 0;
        }
        C->datos[C->ult] = reg;
    }
}

// Correcciones:
Ejercicio 2:
  Si elimino la cabecera, no reconecto el antSub
Ejercicio 3:
  Falto la condicion de no hoja
Ejercicio 4:
  Falta la condicion de circular en SacaC con C->pri
// Puntaje:
Ejercicio 1: 1.5/1.5
Ejercicio 2: 3/4
Ejercicio 3: 1.2/2
Ejercicio 4: 2/2.5
Total: 7.5/10
