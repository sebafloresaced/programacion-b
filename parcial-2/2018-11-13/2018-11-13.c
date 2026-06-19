// Inciso 1 (3 puntos)
int SumaHijos(arbol A){
  int aux=0;
  A = A->izq;
  while (A != NULL) {
    aux += A->dato;
    A = A->der;
  }
  return aux;
}
int CuantosCumplen(arbol A){
  int aux=0;
  if (A == NULL)
    return 0;
  else {
    return (A->izq != NULL && A->dato < SumaHijos(A)) + CuantosCumplen(A->der) + CuantosCumplen(A->izq);
  }
}
// Invocacion: cumplen = CuantosCumplen(A);

// Inciso 2 (3 puntos)
int Existe(arbol A,pos p,int nivel,int K){
  pos c;
  int aux=0;
  if (Nulo(p,A))
    return 0;
  else {
    c = HijoIzq(p,A);
    if (Nulo(c,A) && nivel == K && Info(p,A) == K)
      return 1;
    else {
      while (!Nulo(c,A) && !aux) {
        aux = Existe(A,c,nivel+1,K);
        c = HermanoDer(c,A);
      }
      return aux;
    }
  }
}
// Invocacion: (tomando que la catedra toma la raiz como nivel 0) existe = Existe(A,Raiz(A),0,K);

// Inciso 3 (3 puntos)
// Defino tipos:
#define MaxElem 20
typedef struct nodo{
  struct nodo *sig;
  int nodo,costo;
} nodo;
typedef nodo *TLista;
typedef TLista TVec[MaxElem];

int MayorCostoProm(TVec Vec,int N){
  int MaxVer=-1,i,j,bucle,cont,acum;
  float MaxCostoProm=0;
  TLista aux;
  for (i=0;i<N;i++) {
    aux = Vec[i];
    bucle = acum = cont = 0;
    while (aux != NULL && !bucle) {
      if (aux->nodo == i)
        bucle = 1;
      aux = aux->sig;
    }
    if (bucle) {
      for (j=0;j<N;j++)
        if (i != j) {
          aux = Vec[j];
          while (aux != NULL) {
             if (aux->nodo == i) {
               cont++;
               acum += aux->costo;
             }
             aux = aux->sig;
          }
        }
      if (cont && (float)acum/cont > MaxCostoProm) {
        MaxCostoProm = (float)acum/cont;
        MaxVer = i;
      }
    }
  }
 return MaxVer;
}
/* Correccion:
En el 3 pide recorrer una sola vez el grafo
*/
