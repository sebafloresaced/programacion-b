// Inciso 1 (1.5 pts)
Indicar V o F:
  a) "La implementacion circular de una Cola, permite aprovechar los espacios libres que van quedando al poner y sacar elementos"
  Verdadero. La Cola estatica implementada de modo circular permite ir modificando los indices del primer y el ultimo elemento,
  de modo que se aprovechan los espacios con datos insignificantes.

  b) "Si luego de aplicar una rotacion simple sobre un arbol AVL que se habia desbalanceado, el mismo sigue desbalanceado,"
  "implica que debio haberse aplicado una rotacion compuesta"
  Falso. Al eliminar un nodo puede pasar que se deban realizar varias rotaciones antes de que el arbol quede balanceado.
  Contraejemplo:
             10
       8            14
    6    9     12       16
  4              13   15   19
                             20

Al eliminar el 10, el mismo puede ser reemplazado por el 9:
             9
       8           14
    6         12         16
  4              13   15     19
                                20
Se aplica rotacion simple II en el 8:
              9
       6           14
    4    8     12         16
                 13   15     19
                                20
El 9 sigue desbalanceado. Hi = 2 y Hd = 4. FE = -2

// Inciso 2 (4 pts)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "Colas.h"
#define MaxMail 25

typedef struct nodito {
  char nombreCompleto[26],mail[MaxMail];
  int cantEntradas;
  char tipoEntrada; // ordenado por este campo (A/B/C)
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

typedef struct nodo {
  char codPartido[7]; // ordenado por este campo
  int capacidad,cantEntradasVendidas;
  TSubL entradasVendidas;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;

// Inciso 2.a
typedef struct {
  char codPartido[7],nombreCompleto[26],mail[MaxMail];
  int cantEntradas;
  char tipoEntrada;
} TReg;

void ProcesaCompras(TLista *L,`TCola *C){
  TLista act,ant;
  TSubL actSub,antSub,nuevoSub;
  TReg compra;
  TElementoC ventaCancelada;
  FILE *arch;
  if ((arch = fopen("COMPRAS.DAT","rb")) == NULL)
    printf("Error al abrir el archivo");
  else {
    IniciaC(C);
    while (fread(&compra,sizeof(TReg),1,arch) == 1) {
      act = *L;
      ant = NULL;
      while (act != NULL && strcmp(act->codPartido,compra.codPartido) < 0) {
        ant = act;
        act = act->sig;
      }
      if (act != NULL && strcmp(act->codPartido,compra.codPartido) == 0) { // los datos son validos
        if ((act->cantEntradasVendidas + compra.cantEntradas) * 100.0 / act->capacidad <= 40) {
            // se puede realizar la compra
            act->cantEntradasVendidas += compra.cantEntradas;
            nuevoSub = (TSubL)malloc(sizeof(nodito));
            strcpy(nuevoSub->nombreCompleto,compra.nombreCompleto);
            strcpy(nuevoSub->mail,compra.mail);
            nuevoSub->tipoEntrada = compra.tipoEntrada;
            nuevoSub->cantEntradas = compra.cantEntradas;

            // inserto en la sublista ordenada
            actSub = act->entradasVendidas;
            antSub = NULL;
            while (actSub != NULL && actSub->tipo < nuevoSub->tipo) {
              antSub = actSub;
              actSub = actSub->sig;
            }
            if (actSub == act->entradasVendidas) { // modifico cabeza
              nuevoSub->sig = act->entradasVendidas;
              act->entradasVendidas = nuevoSub;
            }
            else {
              nuevoSub->sig = actSub;
              antSub->sig = nuevoSub;
            }
        }
        else {
          // no se puede realizar la compra porque supera el aforo
          printf("\nNo se pudo realizar la compra de %s para el partido %s porque supera el aforo del estadio"
                 ,compra.nombreCompleto,compra.codPartido);
          strcpy(ventaCancelada.nombreCompleto,compra.nombreCompleto);
          strcpy(ventaCancelada.mail,compra.mail);
          strcpy(ventaCancelada.codPartido,compra.codPartido);
          PoneC(C,ventaCancelada);
        }
      }
    }
    fclose(arch);
  }
}

// Inciso 2.b
"Colas.h"
#define MaxElem 20
#define MaxCharMail 30
typedef struct {
  char nombreCompleto[26],mail[MaxCharMail],codPartido[7];
} TElementoC;
typedef struct {
  TElementoC datos[MaxElem];
  int pri,ult;
} TCola;

void IniciaC(TCola *C);
void PoneC(TCola *C, TElementoC x);

"Colas.c"
#include "Colas.h"
void IniciaC(TCola *C){
  C->pri = C->ult = -1;
}
void PoneC(TCola *C, TElementoC x) {
    if (!LlenaC(*C)) {
        if (C->pri == -1) {
            C->pri = 0;
            C->ult = 0;
        } else {
            if (C->ult == MaxElem - 1)
                C->ult = 0;
            else
                C->ult++;
        }
        C->datos[C->ult] = x;
    }
}

// Inciso 3 (2.5 pts)
int BuscaANEnHoja(arbolN AN,pos p,int x){
  pos c;
  int encontre=0;
  if (Nulo(p))
    return 0;
  else {
    c = HijoMasIzq(p,AN);
    if (Nulo(c)) // p es hoja
      return Info(p,AN) == x;
    else {
      while (!Nulo(c) && !encontre) {
        encontre = BuscaANEnHoja(AN,c,x);
        c = HermanoDer(c,AN);
      }
      return encontre;
    }
  }
}
int SumaClavesNoRaiz(arbolB AB){
  if (AB == NULL)
    return 0;
  else
    return SumaClavesNoRaiz(AB->izq) + SumaClavesNoRaiz(AB->der) + AB->clave;
}
int Verifica(arbolN AN,arbolB AB){
  arbolB aux;
  int cumple=1;
  aux = AB;
  while (aux != NULL && cumple){
    cumple = BuscaANEnHoja(AN,Raiz(AN),SumaClavesNoRaiz(aux->izq) + aux->clave);
    aux = aux->der;
  }
  return cumple;
}

// Inciso 4 (2 pts)
#define MaxVertices 20
typedef struct nodo {
  int costo,AAM,vertice;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;
typedef TLista TVec[MaxVertices];

void InformaAMM(TVec Vec,int N){
  int i,costoTotal=0,mayorPeso=0,v1,v2;
  TLista aux;
  for (i=0;i<N;i++) {
    aux = Vec[i];
    while (aux != NULL) {
      if (aux->AAM == 1 && aux->vertice > i) {
        // la condicion aux->vertice > i me sirve para recorrer unicamente una vez cada arista
        costoTotal += aux->costo;
        if (aux->costo >= mayorPeso) {
          mayorPeso = aux->costo;
          v1 = i;
          v2 = aux->vertice;
        }
      }
      aux = aux->sig;
    }
  }
  printf("El costo total del AAM es: %d",costoTotal);
  printf("\nEl mayor peso de una arista es %d y une el vertice %d con el vertice %d",mayorPeso,v1,v2);
}

// Correcciones:

// Puntaje:
Ejercicio 1: 1.5/1.5
Ejercicio 2: 4/4
Ejercicio 3: 2.5/2.5
Ejercicio 4: 2/2

