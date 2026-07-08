// Inciso 1 (1.5 pts)
Indicar V o F:
a) "Un arbol AVL es un arbol binario en el cual se verifica que la longitud de todas sus ramas es la misma o difieren en, a lo sumo, 1"
Falso. Un arbol AVL es un arbol binario de busqueda en el cual se verifica que la longitud de todas sus ramas es la misma o difieren en, a lo sumo, 1
Un arbol binario de busqueda es aquel donde el valor de un nodo es mayor al de su hijo izquierdo y menor al de su hijo derecho

b) "No podria implementarse una pila en memoria estatica iniciando el tope en un valor coincidente con el tamanio del arreglo"
 Falso. Si la pila inicializa el tope en el valor de la cantidad de elementos que puede almacenar, podemos implementar la pila restandole 1 al tope cada vez que pongo un elemento y
 sumandole 1 cada vez que saco un elemento. Uso los indices de atras para adelante.

// Inciso 2 (4 pts)
// Inciso 2.a.i
void ProcesaElemento(TElementoP *Reg,TLista L) {
  TLista act;
  act = L;
  while (act != NULL && (act->cadena)[0] != Reg.C) {
    act = act->sig;
  }
  while (act != NULL && (act->cadena)[0] == Reg.C) {
    Reg.E += 1;
    act = act->sig;
  }
}
void ProcesaPila(TPila *P,TLista L, int Letras[]) {
  TElementoP Reg;
  if (!VaciaP(*P)) {
    SacaP(P,&Reg);
    Letras[Reg.C - 'A'] = 1;
    ProcesaElemento(&Reg,L);
    ProcesoPila(P,L,Letras);
    PoneP(P,Reg);
  }
}
// Inciso 2.a.ii
int EsVocal(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
         c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}
void AnalizoPalabra(char S[],int *cantVocales,int *cantConsonantes){
  int i;
  for (i=0;i<strlen(S);i++) {
    if (EsVocal(S[i]))
      *cantVocales += 1;
    else
      *cantConsonantes += 1;
  }
}
void EliminaNoUsados(TLista *L, int Letras[]) {
  int i;
  FILE *arch;
  TLista borra,aux,act;
  TReg regArch;
  char LetraAct;
  if ((arch = fopen("RESUMEN.DAT","wb")) == NULL)
    printf("Error al abrir el archivo");
  else {
    for (i=0;i<26;i++) {
      if (Letras[i] == 0) {
        act = *L;
        LetraAct = i + 'A';
        while (act != NULL && (act->cadena)[0] != LetraAct) {
          act = act->sig;
        }
        aux = act->ant;
        while (act != NULL && (act->cadena)[0] == LetraAct) {
          borra = act;
          regArch.cadena = borra->cadena;
          AnalizoPalabra(regArch.cadena,&(regArch.cantVocales),&(regArch.cantConsonantes));
          fwrite(&regArch,sizeof(TReg),1,arch);
          act = act->sig;
          free(borra);
        }
        aux->sig = act;
        act->ant = aux;
      }
    }
  }
}

// Inciso 2.b
"Pilas.h"
#define MaxElem 30
typedef struct {
  int E;
  char C;
} TElementoP;
typedef struct {
  TElementoP datos[MaxElem];
  int tope;
} TPila;

void SacaP(TPila *P,TElementoP *x);
void PoneP(TPila *P,TElementoP x);

"Pilas.c"
#include "Pilas.h"
void SacaP(TPila *P,TElementoP *x){
  if (P->tope != -1) {
    *x = P->datos[P->tope];
    (P->tope)--;
  }
}
void PoneP(TPila *P,TElementoP x){
  if (P->tope != MaxElem - 1) {
    P->tope += 1;
    P->datos[P->tope] = x;
  }
}

// Inciso 3 (2.5 pts)
int BuscoABB(arbol A,int x) {
  if (A == NULL)
    return 0;
  else {
    if (A->dato == x)
      return 1;
    else {
      if (A->dato>x)
        return BuscoABB(A->izq,x);
      else
        return BuscoABB(A->der,x);
    }
  }
}
int CantCumplen(Arbol A,TVec V,int N) {
  int costoMin, bucle, i, cont = 0;
  TLista aux;
  for (i=0;i<N;i++) {
    bucle = 0;
    costoMin = 999;
    aux = V[i];
    while (aux != NULL) {
      if (!bucle && aux->vertice == i)
        bucle = 1;
      if (aux->costo < costoMin)
        costoMin = aux->costo;
      aux = aux->sig;
    }
    if (!bucle && !BuscoABB(A,costoMin))
      cont++;
  }
  return cont;
}

// Inciso 4 (2 pts)
int ContGradoK(arbolN A,pos p,int K) {
  pos c;
  int grado = 0, aux = 0;
  if (Nulo(p))
    return 0;
  else {
    c = HijoMasIzq(p,A);
    while (!Nulo(c)) {
      grado++;
      aux += ContGradoK(A,c,K);
      c = HermanoDer(c,A);
    }
    return (grado == K) + aux;
  }
}
int VerificaUnGradoK(arbolN A,int K) {
  return ContGradoK(A,Raiz(A),K) == 1;
}

// Correcciones:
Ejercicio 1:
  La correcion de arbol binario de busqueda esta bien, pero falto poner que para todo nodo, la diferencia de altura del subarbol izquierdo y derecho es a lo sumo 1.
Ejercicio 2:
  Falta inicializar Reg.E en 0
  Nunca chequeo no eliminar la cabeza de L, ni que act se me haya ido a NULL
  Falta inicializar cantVocales y cantConsonantes
Ejercicio 3:
  Si un vertice no tiene aristas de salida, costoMin queda en 999 y se lo busca en el ABB
Ejercicio 4:
  No corto cuando encuentro mas de uno

// Puntaje:
Ejercicio 1: 1.25/1.5
Ejercicio 2: 2.1/4
Ejercicio 3: 2/2.5
Ejercicio 4: 1.5/2
Total: 6.85/10

Version con corte Ejercicio 4:
int ContGradoKHasta2(arbolN A, pos p, int K) {
  pos c;
  int grado = 0, cant = 0;
  if (Nulo(p, A))
      return 0;
  else {
    c = HijoMasIzq(p, A);
    while (!Nulo(c, A) && cant <= 1) {
        grado++;
        cant += ContGradoKHasta2(A, c, K);
        c = HermanoDer(c, A);
    }
    if (grado == K)
        cant++;
    if (cant > 1)
        return 2;
    else
        return cant;
  }
}
