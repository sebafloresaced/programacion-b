// Inciso 1 (1.5 pts)
Indicar V o F:
  a) "La implementacion de una pila en memoria estatica podria hacerse inicializando el primero en MAX en lugar de en -1 (siendo MAX la dimension fisica del vector)
  Verdadero. Se pueden usar los indices "invertidos". Se le suma 1 al tope cuando se saca un elemento y se le resta 1 cuando se pone un elemento.

  b) "Si se aplica el recorrido en profundidad sobre un digrafo no conexo el mismo podria fallar al vaciarse la pila y no conseguir llegar a un vertice no visitado de otra componente conexa"
  Verdadero. Si se aplica el recorrido en profundidad sin tener en cuenta que este podria ser no conexo (usando una variable cc y "saltando" entre componentes conexas), la pila podria vaciarse
  y no se podria alcanzar un vertice no visitado.

// Inciso 2 (4 pts)
typedef struct nodito {
  char empresa[11]; // puede repetirse, ordenada, si inicia con '#' es extranjera
  int rol,mesesTrabajados; // rol(1..9)
  struct nodito *sig;
} nodito;
typedef nodito *TSubL;

typedef struct nodo {
  char idPersona[7]; // ordenado, no se repite
  int rol; // 0..9, 0 indica que no tiene proyecto
  char fechaInicio[9]; // formato aaaammdd, vacio si no tiene proyecto
  TSubL proyectos; // Sublista de proyectos en los que ya participo (no actual)
  struct nodo *sig;
} nodo;
typedef nodo *TLista;

typedef struct {
    char idPersona[7];
    char empresa[11];
    int rol;
    char termino; // 'S' o 'N'
} TRegFeb;

int CANTM(char fechaIni[], char fechaFin[]);

/*
Inciso 2.a:
En FEBRERO.TXT hay info de personas (validados) que participan en proyectos en el mes de febrero de 2023. Cada linea (separando cada dato por un espacio) contiene: idPersona(ordenado), empresa,
rol,termino[S/N]. Leer la informacion y actualizar la lista y sublistas.
*/

void InsertaProyecto(TSubL *S, char empresa[], int rol, int meses) {
    TSubL nuevo, act, ant;
    nuevo = malloc(sizeof(nodito));
    strcpy(nuevo->empresa, empresa);
    nuevo->rol = rol;
    nuevo->mesesTrabajados = meses;
    act = *S;
    ant = NULL;
    while (act != NULL && strcmp(act->empresa, empresa) <= 0) {
        ant = act;
        act = act->sig;
    }
    nuevo->sig = act;
    if (ant == NULL)
        *S = nuevo;
    else
        ant->sig = nuevo;
}
TLista BuscaPersona(TLista L, char idPersona[]) {
    while (L != NULL && strcmp(L->idPersona, idPersona) < 0)
        L = L->sig;
    if (L != NULL && strcmp(L->idPersona, idPersona) == 0)
        return L;
    else
        return NULL;
}
void ProcesaRegistroFebrero(TLista L, TRegFeb reg) {
    TLista persona;
    int meses;
    persona = BuscaPersona(L, reg.idPersona);
    if (persona != NULL) {
        if (reg.termino == 'S') {
            meses = CANTM(persona->fechaInicio, "20230228");
            InsertaProyecto(&(persona->proyectos), reg.empresa, reg.rol, meses);
            persona->rol = 0;
            strcpy(persona->fechaInicio, "");
        } else {
            persona->rol = reg.rol;
            if (strcmp(persona->fechaInicio, "") == 0)
                strcpy(persona->fechaInicio, "20230201");
        }
    }
}
void ActualizaDesdeFebrero(TLista L) {
    FILE *arch;
    TRegFeb reg;
    arch = fopen("FEBRERO.TXT", "r");
    if (arch != NULL) {
        while (fscanf(arch, "%6s %10s %d %c",reg.idPersona,reg.empresa,&reg.rol,&reg.termino) == 4) {
            ProcesaRegistroFebrero(L, reg);
        }
        fclose(arch);
    }
}

// Inciso 2.b
void EliminaProyectosEmpresa(TLista L, char P[], char E[], int *cant) {
    TLista persona;
    TSubL act, ant, borra;
    persona = BuscaPersona(L, P);
    if (persona != NULL) {
        act = persona->proyectos;
        ant = NULL;
        while (act != NULL && strcmp(act->empresa, E) < 0) {
            ant = act;
            act = act->sig;
        }
        while (act != NULL && strcmp(act->empresa, E) == 0) {
            borra = act;
            (*cant)++;
            if (ant == NULL) {
                persona->proyectos = act->sig;
                act = persona->proyectos;
            } else {
                ant->sig = act->sig;
                act = ant->sig;
            }
            free(borra);
        }
    }
}

// Inciso 2.c
typedef struct nodoD {
    char empresa[11];
    int cantP;
    struct nodoD *ant, *sig;
} nodoD;
typedef nodoD *PnodoD;
typedef struct {
    PnodoD pri, ult;
} TListaD;

void IniciaLD(TListaD *LD) {
  LD->pri = NULL;
  LD->ult = NULL;
}
void SumaEmpresaLD(TListaD *LD, char empresa[]) {
  PnodoD act, nuevo;
  act = LD->pri;
  while (act != NULL && strcmp(act->empresa, empresa) < 0)
    act = act->sig;
  if (act != NULL && strcmp(act->empresa, empresa) == 0) {
    act->cantP++;
  }
  else {
    nuevo = malloc(sizeof(nodoD));
    strcpy(nuevo->empresa, empresa);
    nuevo->cantP = 1;
    nuevo->sig = act;
    if (act == NULL) {
      nuevo->ant = LD->ult;
      if (LD->ult == NULL)
        LD->pri = nuevo;
      else
        LD->ult->sig = nuevo;
      LD->ult = nuevo;
    }
    else {
      nuevo->ant = act->ant;
      if (act->ant == NULL)
        LD->pri = nuevo;
      else
        act->ant->sig = nuevo;
      act->ant = nuevo;
    }
  }
}
void GeneraListaDobleEmpresas(TLista L, TListaD *LD) {
  TSubL auxS;
  char empresaActual[11];
  IniciaLD(LD);
  while (L != NULL) {
    auxS = L->proyectos;
    while (auxS != NULL) {
      strcpy(empresaActual, auxS->empresa);
      if (empresaActual[0] == '#') {
        SumaEmpresaLD(LD, empresaActual);
        while (auxS != NULL && strcmp(auxS->empresa, empresaActual) == 0)
          auxS = auxS->sig;
      }
      else {
        auxS = auxS->sig;
      }
    }
    L = L->sig;
  }
}

// Inciso 3 (2 pts)
int BuscoAN(arbolN AN,pos p,int nivel,int K,int x){
  pos c;
  int encontre=0;
  if (Nulo(p) || nivel > K)
    return 0;
  else {
    if (nivel == K && Info(p,AN) == x)
      return 1;
    else {
      c = HijoMasIzq(p,AN);
      while (!Nulo(c) && !encontre) {
        encontre = BuscoAN(AN, c, nivel + 1, K, x);
        c = HermanoDer(c,AN);
      }
      return encontre;
    }
  }
}
int CantClavesNoRaiz(arbol AB) {
  if (AB == NULL)
    return 0;
  else
   return 1 + CantClaves(AB->izq) + CantClaves(AB->der);
}
int CantCumplen(arbol AB,arbolN AN,int K){
  arbol aux;
  int cont=0;
  aux = AB;
  while (aux != NULL) {
    cont += BuscoAN(AN,Raiz(AN),0,K,CantClavesNoRaiz(aux->izq) + 1);
  }
  return cont;
}

// Inciso 4 (2.5 pts)
int GradoV(TMat Mat,int V,int N){
  if (N == 0)
    return 0;
  else
    return (Mat[V][N] != 0) + GradoV(Mat,V,N-1);
}
int TodosCumplen(Pila *P,TMat Mat,int N){
  TElementoP aux;
  if (VaciaP(*P))
    return 1;
  else {
    SacaP(P,&aux);
    return GradoV(Mat,aux.V,N) == aux.G && TodosCumplen(P,Mat,N);
  }
}

"Pilas.h"
#define MaxElem 20
typedef struct {
  int V,G;
} TElementoP;
typedef struct {
  TElementoP datos[MaxElem];
  int tope;
} Pila;

int VaciaP(Pila P);
void SacaP(Pila *P,TElementoP *aux);

"Pilas.c"
#include "Pilas.h"
int VaciaP(Pila P){
  return P.tope == -1;
}
void SacaP(Pila *P,TElementoP *aux){
  if (P->tope != -1) {
    *aux = P->datos[P->tope];
    P->tope--;
  }
}

// Correcciones:

// Puntaje:
Ejercicio 1: 1.5/1.5
Ejercicio 2: 4/4
Ejercicio 3: 2/2
Ejercicio 4: 2.5/2.5
Total: 10/10
