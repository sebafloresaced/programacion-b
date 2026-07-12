// Inciso 1 (1.5 pts)
Indicar V o F:
  a) "En la matriz final tras ejecutar el algoritmo de Floyd, todos los elementos de la diagonal principal son 0,"
  "a menos que haya un bucle"
  Falso. El algoritmo de Floyd siempre deja ceros en la diagonal principal de la matriz final.

  b) "Una cola implementada dinamicamente en modo circular, permite aprovechar aquellos nodos que ya no tienen datos significativos"
  Falso. Las implementaciones dinamicas no "desperdician" espacio.
  La cola estatica implementada en modo circular sí permite aprovechar los espacios que ya no tienen datos significativos.

// Inciso 2 (3.5 pts)
typedef struct nodoD {
  int zona; // 1 a 10, se puede repetir
  char cod[5]; // comeinza con C si es camara o R si es radar
  TPila infracciones; // podria estar vacia
  struct nodoD *ant,*sig;
} nodoD;
typedef nodoD *PnodoD;
typedef struct {
  PnodoD pri,ult;
} TListaD;

// Inciso 2.a
void BuscaPila(TPila *P,int *encontre) {
  TElementoP aux;
  if (!VaciaP(*P)) {
    SacaP(P,&aux);
    if (aux.fecha[0] == '1' && aux.fecha[1] == '9' && aux.fecha[2] == '1' && aux.fecha[3] == '2')
      *encontre = 1;
    else
      BuscaPila(P,encontre);
    PoneP(P,aux);
  }
}
void CantZonasInfFecha(TPila P,TListaD LD,int *cant){
  TListaD aux;
  int encontre=0;
  aux = LD.pri;
  while (aux != NULL) {
    if (aux->zona % 2 == 0 && aux->cod[0] == 'R') {
      BuscaPila(&(aux->infracciones),&encontre);
      *cant += encontre;
    }
    aux = aux->sig;
  }
}

// Inciso 2.b
typedef struct nodoC {
  int zona,cantRadar,cantCamaras;
  struct nodoC *sig;
} nodoC;
typedef nodoC *TListaC;

void ProcesaZona(TListaD LD,int zona,int *cantRadar,*cantCamaras){
  TListaD aux;
  TPila P;
  TElementoP infraccion;
  aux = LD.pri;
  while (aux != NULL) {
    if (aux->zona == zona) {
      P = aux->infracciones;
      if (aux->cod[0] == 'R')
        while (!Vacia(P)) {
          SacaP(&P,&infraccion);
          *cantRadar += 1;
        }
      else
        while (!Vacia(P)) {
          SacaP(&P,&infraccion);
          *cantCamara += 1;
        }
    }
    aux = aux->sig;
  }
}
void CreaListaC(TListaC *LC,TListaD LD){
  TListaC nuevoC,antC,actC;
  int cantRadar,cantCamaras,i,totalInfracciones;
  for (i==1;i<=10;i++){
    nuevoC = (TListaC)malloc(sizeof(nodoC));
    nuevoC->zona = i;
    cantRadar = cantCamaras = totalInfracciones = 0;
    ProcesaZona(LD,i,&cantRadar,&cantCamaras);
    if (cantRadar > 0 && cantCamaras > 0) {
      nuevoC->cantRadar = cantRadar;
      nuevoC->cantCamaras = cantCamaras;
      totalInfracciones = cantRadar+cantCamaras;
      if (*LC == NULL) {
        nuevoC->sig = nuevoC;
        *LC = nuevoC;
      }
      else {
        actC = (*LC)->sig;
        antC = *LC;
        do {
          antC = actC;
          actC = actC->sig;
        } while (actC != *LC && actC->cantRadar + actC->cantCamaras < totalInfracciones);
        if (actC == *LC) { // nueva cabeza
          nuevoC->sig = actC->sig;
          *LC = nuevoC;
        }
        else {
          nuevoC->sig = actC;
        }
        antC->sig = nuevoC;
      }
    }
    else
      free(nuevoC);
  }
}

// Inciso 2.c
"Pilas.h"
#define MaxElem 30
typedef struct {
  char fecha[11],patente[8];
} TElementoP;
typedef struct {
  TElementoP datos[MaxElem];
  int tope;
} TPila;

void PoneP(TPila *P,TElementoP x);
void SacaP(TPila *P,TElementoP *x);

"Pilas.c"
#include "Pilas.h"
void PoneP(TPila *P,TElementoP x){
  if (P->tope != MaxElem -1) {
    P->tope++;
    P->datos[P->tope] = x;
  }
}

void SacaP(TPila *P,TElementoP *x) {
  if (P->tope != -1) {
    *x = P->datos[P->tope];
    P->tope--;
  }
}

// Inciso 3 (2.5 pts)
#define MaxChar 20
int EsVocal(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
         c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}
int cantCadenasCumplen(arbolN A,pos p,int nivel) {
  char cadena[MaxChar];
  pos c;
  int acum=0;
  if (Nulo(p))
    return 0;
  else {
    c = HijoMasIzq(p,A);
    while (!Nulo(c)) {
      acum += cantCadenasCumplen(A,c,nivel+1);
      c = HermanoDer(c,A);
    }
    strcpy(cadena,Info(p,A));
    return acum + (strlen(cadena) % 2 == 1 && nivel % 2 == 1 && EsVocal(cadena[0]) && EsVocal(cadena[strlen(cadena) - 1]));
  }
}

// Inciso 4 (2.5 pts)
#define MaxElem 20
typedef int TMat[MaxElem][MaxElem];
typedef struct nodo {
  int clave;
  struct nodo *izq,*der;
} nodo;
typedef nodo *arbol;

int BuscaABB(arbol A,int x){
  if (A == NULL)
    return 0;
  else {
    if (A->clave == x)
      return 1;
    else
      if (A->clave < x)
        return BuscaABB(A->der,x);
      else
        return BuscaABB(A->izq,x);
  }
}

int GradoEntrada(TMat Mat,int i,int v,int N) {
  if (i == N)
    return 0;
  else {
    return (Mat[i][v] != 0) + GradoEntrada(Mat,i+1,v,N);
  }
}

int TodosCumplen(arbol A,TMat Mat,int i,int N) {
  if (i == N)
    return 1;
  else {
    if (Mat[i][i] != 0)
      return TodosCumplen(Mat,i+1,N) && BuscaABB(A,GradoEntrada(Mat,0,i,N));
    else
      return TodosCumplen(Mat,i+1,N);
  }
}

// Correcciones:
Ejercicio 2:
  En el a me falto inicializar encontre en 0 para cada zona
  En el b, que actC == *LC no implica que el nuevo sea mayor, ademas salteo el primer nodo

// Puntaje:
Ejercicio 1: 1.5/1.5
Ejercicio 2: 2.3/3.5
Ejercicio 3: 2.5/2.5
Ejercicio 4: 2.5/2.5
Total: 8.8/10
