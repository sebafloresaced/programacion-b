// Ejercicio 1 (1.5 pts)
Indicar V o F:
a) "A partir de la matriz final An de Floyd sobre un digrafo G, se puede hallar la matriz de clausura transitiva con solo un recorrido sobre An,"
 "sin necesidad de volver a acceder a la matriz de adyacencia de G"
 La matriz final de Floyd almacena en (i,j) el costo minimo del camino para ir del vertice i al vertice j y la matriz de clausura transitiva es una matriz
 booleana que indica si existe (1) un camino para ir de i a j o si no existe (INF). Por lo tanto, todo par (i,j) distinto de INF en la matriz final de Floyd sera un 1
 en la matriz de clausura transitiva, y todo par (i,j) igual a INF en la matriz final de Floyd, sera un 0 en la de clausura transitiva.

b) "Dado un grafo de N vertices, conexo, existen entre N y 2N posibles recorridos en amplitud"
 Falso. Contraejemplo: Grafo K4 (4 vertices que se conectan entre si)
 V = {A, B, C, D}
 Posibles recorridos en amplitud:
 A-B-C-D
 A-B-D-C
 A-C-B-D
 A-C-D-B
 A-D-B-C
 A-D-C-B

 Empezando el recorrido desde A existen 6 posibles caminos. Como son 4 vertices, tomando todas las posibilidades serian 4 * 6 = 24 recorridos posibles.
 24 > 2 * 4 => la afirmacion es falsa

// Ejercicio 2 (4.5 pts)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colas.h"

typedef struct {
  char CodigoLote[6]; // validado, puede repetirse, ordenada
  char DocumentoOfertante[10];
  float PrecioOfertado;
  char Medio; // [T]elefono / [M]ail
  // ninguna persona oferta mas de una vez para el mismo lote;
  // CodigoLote + DocumentoOfertante -> clave primaria
} Roferta;

typedef struct nodoC {
  char CodigoLote[6]; // ordenada
  float PrecioBase;
  struct nodoC *sig;
} nodoC;
typedef nodoC *TListaC;

typedef struct nodito {
  char DocumentoOfertante[10];
  float PrecioOfertado;
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

typedef struct nodo {
  char CodigoLote[6]; // ordenada, no se repite
  float PrecioRealEstimado;
  TSubL ofertasTel,ofertasMail;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;

// Inciso A)

/*
  Inciso i)
  Generar L, solo para aquellos lotes que tuvieron alguna oferta (mail/telefono). PrecioRealEstimado = PrecioBase + 0.2 * (MaxOferta + MinOferta)/2.0
*/
float BuscaPrecioBase(TListaC LC, char codigo[]) {
    TListaC aux;
    int encontre=0;
    if (LC == NULL)
        return 0;
    else {
      aux = LC;
      do {
          aux = aux->sig;
          if (strcmp(aux->codigoLote, codigo) == 0) {
              encontre=1;
          }
      } while (aux != LC && !encontre);
      return aux->PrecioBase;
    }
}
void InsertaOferta(TSubL *L, char documento[], float precio) {
    TSubL nuevo;
    nuevo = malloc(sizeof(TNodoOferta));
    strcpy(nuevo->documento, documento);
    nuevo->precioOfertado = precio;
    nuevo->sig = *L;
    *L = nuevo;
}
void AgregaFinal(TLista *L, TLista *ult, TLista nuevo) {
    nuevo->sig = NULL;
    if (*L == NULL) {
        *L = nuevo;
        *ult = nuevo;
    } else {
        (*ult)->sig = nuevo;
        *ult = nuevo;
    }
}
void GeneraL(TListaC LC, TLista *L) {
    FILE *arch;
    ROferta reg;
    int leido;
    char codigoActual[6];
    float maxOferta, minOferta;
    float precioBase;
    TLista nuevo, ult;
    *L = NULL;
    ult = NULL;
    arch = fopen("OFERTAS.DAT", "rb");
    if (arch != NULL) {
        leido = fread(&reg, sizeof(ROferta), 1, arch);
        while (leido == 1) {
            strcpy(codigoActual, reg.CodigoLote);
            nuevo = malloc(sizeof(TNodoLote));
            strcpy(nuevo->CodigoLote, codigoActual);
            nuevo->OfertasTel = NULL;
            nuevo->OfertasMail = NULL;
            nuevo->sig = NULL;
            maxOferta = reg.PrecioOfertado;
            minOferta = reg.PrecioOfertado;
            while (leido == 1 && strcmp(reg.CodigoLote, codigoActual) == 0) {
                if (reg.PrecioOfertado > maxOferta)
                    maxOferta = reg.PrecioOfertado;
                if (reg.PrecioOfertado < minOferta)
                    minOferta = reg.PrecioOfertado;
                if (reg.Medio == 'T')
                    InsertaOferta(&(nuevo->OfertasTel), reg.DocumentoOfertante, reg.PrecioOfertado);
                else
                    InsertaOferta(&(nuevo->OfertasMail), reg.DocumentoOfertante, reg.PrecioOfertado);
                leido = fread(&reg, sizeof(ROferta), 1, arch);
            }
            precioBase = BuscaPrecioBase(LC,codigoActual);
            if (precioBase != 0) {
                nuevo->PrecioRealEstimado = precioBase + 0.20 * ((maxOferta + minOferta) / 2.0);
                AgregaFinal(L, &ult, nuevo);
            } else {
                // si no está el lote en LC, libero el nodo generado.
                free(nuevo);
            }
        }
        fclose(arch);
    }
}
/*
  Inciso ii)
  En una Cola C se tienen los CodigosLote que se vendieron, se pide eliminarlos de L (si estan), generando un archivo LOTESBAJA.TXT que contenga un lote eliminado por linea con
  CodigoLote, CantOfertasTotales. La cola puede perderse.
*/
int LiberaSublista(TSubL L) {
    TSubL aux;
    int cant = 0;
    while (L != NULL) {
        aux = L;
        L = L->sig;
        free(aux);
        cant++;
    }
    return cant;
}
int EliminaLote(TLista *L, char codigo[], int *cantOfertasTotales) {
    TLista act, ant;
    act = *L;
    ant = NULL;
    while (act != NULL && strcmp(act->CodigoLote, codigo) < 0) {
        ant = act;
        act = act->sig;
    }
    if (act != NULL && strcmp(act->CodigoLote, codigo) == 0) {
        *cantOfertasTotales = LiberaSublista(act->OfertasTel) + LiberaSublista(act->OfertasMail);
        if (ant == NULL)
            *L = act->sig;
        else
            ant->sig = act->sig;
        free(act);
        return 1;
    }
    return 0;
}
void EliminaVendidosInternet(TLista *L, TCola *C) {
    FILE *txt;
    TElementoC elem;
    int cantOfertas;
    txt = fopen("LOTESBAJA.TXT", "w");
    if (txt != NULL) {
        while (!VaciaC(*C)) {
            SacaC(C, &elem);
            if (EliminaLote(L, elem.CodigoLote, &cantOfertas)) {
                fprintf(txt, "%s %d\n", elem.codigoLote, cantOfertas);
            }
        }
        fclose(txt);
    }
}

/*
  Inciso B)
  Definir el tipo de C asumiendo que es circular. Desarrollar SacaC().
*/

// "Colas.h"
#define MaxElem 50
typedef struct {
  char CodigoLote[6];
} TElementoC;
typedef struct {
  TElementoC datos[MaxElem];
  int pri,ult;
} TCola;

void SacaC(TCola *C,TElementoC *x);

// "Colas.c"
#include "Colas.h"
void SacaC(TCola *C,TElementoC *x){
  if (C->pri != -1) {
    *x = C->datos[C->pri];
    if (C->pri == C->ult)
      C->pri = C->ult = -1;
    else
      if (C->pri != MaxElem - 1)
        C->pri += 1;
      else
        C->pri = 0;
  }
}

// Ejercicio 3 (2 pts)
int AlgunoVerifica(arbol A,pos p) {
  int verificaSub = 0,cumple = 1;
  pos c;
  if (Nulo(p))
    return 0;
  else {
    c = HijoMasIzq(p,A);
    if (Nulo(c,A)) // es hoja
      return 0;
    else {
      while (!Nulo(c,A) && !verificaSub) {
        verificaSub = AlgunoVerifica(A,c);
        if (cumple == 1)
          cumple = Info(c,A) > Info(p,A);
        c = HermanoDer(c,A);
      }
      return cumple || verificaSub;
    }
  }
}
// Invocacion: verifica = AlgunoVerifica(A,Raiz(A));

// Ejercicio 4 (2 pts)
int EsVocal(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
         c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}
int cantNodosVerifican(arbol A) {
  int nodoCumple;
  arbol aux;
  if (A == NULL)
    return 0;
  else {
    nodoCumple = EsVocal(A->dato);
    aux = A->izq;
    while (aux != NULL && nodoCumple == 1) {
      nodoCumple = !EsVocal(aux->dato);
      aux = aux->der;
    }
    return cantNodosVerifican(A->izq) + cantNodosVerifican(A->der) + nodoCumple;
  }
}
int cantArbolesVerifican(arbol A) {
  int aux=0;
  while (A != NULL) {
    aux += cantNodosVerifican(A) >= 2;
    A = A->der;
  }
  return aux;
}
// Invocacion cantArbolesCumplen = cantArbolesVerifican(A);

// Correcciones
En el 4 cuento mal los nodos que verifican, tendria que hacer una funcion que devuelva si el nodo observado verifica la condicion,
y otra que cuente la cantidad de nodos que verifican la condicion en el arbol

// Puntaje:
Ejercicio 1: 1.5/1.5
Ejercicio 2: 4.5/4.5
Ejercicio 3: 2/2
Ejercicio 4: 1.1/2
Total: 9.1/10
