// Inciso 1 (3 puntos)
int Verifica(Tarbol A) {
  Tarbol c;
  int clave1,clave2;
  if (A == NULL)
    return 0;
  else {
    clave1 = A->der->dato;
    clave2 = A->izq->dato;
    return clave1 == clave2 || clave1 == -1 * clave2 || Verifica(A->izq) || Verifica (A->der);
  }
}
// Invoco: cumple = Verifica(A)

// Inciso 2 (3 puntos)
int SumaEntreK1K2(TarbolN A,pos p,float K1,float K2){
  pos c;
  int acum,clave;
  if (Vacia(A))
    return 0;
  else {
    c = HijoMasIzq(p,A);
    while (!Nulo(c)) {
      acum += SumaEntreK1K2(A,c,K1,K2);
      c = HermadoDer(c,A);
    }
    clave = Info(p,A);
    if (clave >= K1 && clave <= K2)
      return clave + acum;
    else
      return acum;
  }
}
// Invoco: suma = SumaEntreK1K2(A,Raiz(A),K1,K2)

// Inciso 3 (3 puntos)
void GeneraVecGrados(TMat Mat,TVec Vec,int i,int j,int N){
  if (i<N) {
    if (j == i+1)
    GeneraVecGrados(Mat,Vec,i+1,0,N);
    else {
      if (Mat[i][j] != 0)
        Vec[i] += 1;
      GeneraVecGrados(Mat,Vec,i,j+1,N);
    }
  }
}
// Invoco: GeneraVecGrados(Mat,Vec,0,0,N)

// Inciso 4 (1 punto, sin codigo)

/* Correcciones
 Punto 1: if (A->izq != NULL && A->izq->der != NULL && A->izq->der->der == NULL) {
            clave1 = A->izq->dato;
            clave2 = A->izq->der->dato;
 Punto 2: La consigna pedia que el nivel este entre el intervalo, no la clave
 Punto 3: Como recorro media matriz deberia hacer
          Vec[i]++;
          Vec[j]++;
*/
