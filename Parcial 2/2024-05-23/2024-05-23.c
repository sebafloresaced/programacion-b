// Inciso 1 (3 pts)
int GradoNodo(arbol A) {
  arbol aux;
  int grado=0;
  if (A == NULL)
    return 0;
  else {
    aux = A->izq;
    while (aux != NULL) {
      grado++;
      aux = aux->der;
    }
    return grado;
  }
}
int VerificaUnBosque(arbol A,int gradoRaiz) {
  if (A == NULL)
    return 1;
  else {
    return GradoNodo(A) == gradoRaiz && VerificaUnBosque(A->izq,gradoRaiz) && VerificaUnBosque(A->der,gradoRaiz);
  }
}
int VerificaBosques(arbol A){
  int gradoRaiz,cumple=1;
  arbol aux;
  aux = A;
  while (aux != NULL && cumple) {
    gradoRaiz = GradoNodo(aux);
    cumple = VerificaUnBosque(aux->izq,gradoRaiz);
    aux = aux->der;
  }
  return cumple;
}

// Inciso 2 (3 pts)
int GradoNodo(arbolN A,pos p){
  int grado=0;
  pos c;
  if (Nulo(p,A))
    return 0;
  else {
    c = HijoMasIzq(p,A);
    while (!Nulo(c,A)) {
      grado++;
      c = HermanoDer(c,A);
    }
    return grado;
  }
}
int Verifica(arbolN A,pos p){
  pos c;
  int gradoAct,gradoAnt=0,cumpleSub=0,cumpleAct=0;
  if (Nulo(p,A))
    return 1;
  else {
    c = HijoMasIzq(p,A);
    while (!Nulo(c,A) && !cumpleSub) {
      gradoAct = GradoNodo(A,c);
      if (gradoAct >= gradoAnt)
        cumpleAct = 1;
      else
        cumpleAct = 0;
      gradoAnt = gradoAct;
      cumpleSub = Verifica(A,c);
      c = HermanoDer(c,A);
;    }
    return cumpleAct || cumpleSub;
  }
}

// Inciso 3 (3 pts)
#define MaxElem 20
typedef struct {
  int bucle,alcanzado,alcanza;
} nodo;
typedef nodo TVec[MaxElem];

int CantCumplen(TMat Mat,TVec Vec,int i,int j,int N){
  if (i<N)
    if (j<N) {
      if (i == j)
        Vec[i].bucle = Mat[i][j];
      else {
        Vec[i].alcanza += Mat[i][j];
        Vec[i].alcanzado += Mat[j][i];
      }
      return CantCumplen(Mat,Vec,i,j+1,N);
    }
    else
      return CantCumplen(Mat,Vec,i+1,0,N);
  else {
    // Proceso Vector:
    if (j == N)
      return 0;
    else
      return (Vec[j].bucle == 0 && Vec[j].alcanzado == Vec[j].alcanza) + CantCumplen(Mat,Vec,i,j+1,N);
  }
}
// Invocacion:
TVec Vec = {0}
cumplen = CantCumplen(Mat,Vec,0,0,N);

// Inciso 4 (1 pts)

S = {A,D}
D = [0,15,21,13,INF]
P = [0,0,D,0,INF]

S = {A,D,B}
D = [0,15,19,13,22]
P = [0,0,B,0,B]

S = {A,D,B,C}
D = [0,15,19,13,21]
P = [0,0,B,0,C]

S = {A,D,B,C,E}
D = [0,15,19,13,21]
P = [0,0,B,0,C]

El algoritmo concluye ya que S = V
