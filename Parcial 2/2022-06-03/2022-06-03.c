// Inciso 1 (3 puntos)
int GradoNodo(arbol A) {
  int cont=0;
  arbol aux;
  aux = A->izq;
  while (aux != NULL) {
    cont++;
    aux = aux->der;
  }
  return cont;
}
int Suma(arbol A,int nivel,int K){
  int grado;
  if (A == NULL)
    return 0;
  else {
    grado = GradoNodo(A);
    if (grado % 2 == 1 && nivel < K)
      return A->dato + Suma(A->der,nivel,k) + Suma(A->izq,nivel+1,K);
    else
      if (nivel < k)
        return Suma(A->der,nivel,k) + Suma(A->izq,nivel+1,K);
      else
        return 0;
  }
}
// Invocacion: suma = Suma(A,0,K);

// Inciso 2 (2.5 puntos)
int EsVocal(char c){
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
         c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}
int Verifica(TarbolN A,pos p){
  pos c;
  int cumple = 1, cumpleSub=0;
  if (Nulo(p,A))
    return 0;
  else {
    c = HijoMasIzq(p,A);
    while (!Nulo(c,A) && !cumpleSub) {
      cumpleSub = Verifica(A,c);
      if (!EsVocal(Info(c,A)))
        cumple = 0;
      c = HermanoDer(c,A);
    }
    return (EsVocal(Info(p,A)) && cumple) || cumpleSub;
  }
}
// Invocacion: verifica = Verifica(A,Raiz(A));

// Inciso 3 (2.5 pts)
#define MaxElem 20
typedef struct nodo {
  int bucle,gradoS;
} nodo;
typdef nodo TVec[MaxElem];

typedef int TMat[MaxElem][MaxElem];

void CargaMat(TMat Mat,int *N);
void GeneraVec(TMat Mat,TVec Vec,int i,int j,int N);

int main(){
  TMat Mat;
  TVec Vec={0};
  int N;
  CargaMat(Mat,&N);
  printf("Grados de salida de vertices con bucle:")
  GeneraVec(Mat,Vec,1,1,N);
  return 0;
}
void GeneraVec(TMat Mat,TVec Vec,int i,int j,int N){
  if (i<=N) {
    if (j>N) {
      if (Vec[i].bucle)
        printf("\n Vertice %d: %d",i,Vec[i].gradoS);
      GeneraVec(Mat,Vec,i+1,1,N);
    }
    else {
      if (Mat[i][j] != 0) {
        Vec[i].gradoS++;
        if (i == j)
          Vec[i].bucle = 1;
      }
      GeneraVec(Mat,Vec,i,j+1,N);
    }
  }
}

// Inciso 4 (2 pts)
a) 4 aristas (ignorando la existencia de posibles bucles)
b.i) que CC[i] != CC[j]
ii) compJ = CC[j];
    for (k=1;k<=N;k++)
      if (CC[k] == compJ)
        CC[k] = CC[i];
