// Inciso 1 (2.5 puntos)
int EsVocal(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
         c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}
void GeneraVec(arbol A,TVec Vec, int nivel,int *altura,int K) {
  if (A != NULL) {
    if (nivel > *altura)
      *altura = nivel;
    if (nivel < K) {
      if (!EsVocal(A->dato))
        Vec[nivel]++;
      GeneraVec(A->izq,Vec,nivel+1,*altura,K);
      GeneraVec(A->der,Vec,nivel,*altura,K);
    }
  }
}
void MuestraCantNoVocales(arbol A,int K) {
  TVec Vec = {0};
  int i,altura=-1,iteraciones;
  GeneraVec(A,Vec,0,&altura,K);
  iteraciones = (altura<K)? altura:K;
  for (i=0;i<=altura && i<K;i++) {
    printf("\nNivel %d: %d nodos no vocales",i,Vec[i]);
  }
}
// Invocacion MuestraCantNoVocales(A,K);

// Inciso 2.a (2 pts)
int GradoNodo(arbolN A,pos p){
  pos c;
  int aux=0;
  c = HijoMasIzq(p,A);
  while (!Nulo(c,A)) {
    aux++;
    c = HermanoDer(c,A);
  }
  return aux;
}
int Verifica(arbolN A,pos p,int G) {
  int grado,verificasub=0,dato;
  pos c;
  if (Nulo(p,A))
    return 0;
  else {
    grado = GradoNodo(A,p);
    dato = Info(p,A);
    if (grado == G && dato < 0 && (-1 * dato) % 2 == 1)
      return 1;
    else {
      c = HijoMasIzq(p,A);
      while (!Nulo(c,A) && !verificasub) {
        verificasub = Verifica(A,c,G);
        c = HermanoDer(c,A);
      }
      return verificasub;
    }
  }
}
// Invocacion: cumple = Verifica(A,Raiz(A),G);

// Inciso 2.b (2 pts)
Dentro del else deberia ser:
  grado = GradoNodo(A,p);
  dato = Info(p,A);
  if (grado == G && dato < 0 && (-1 * dato) % 2 == 1)
    cumple = 1;
  c = HijoMasIzq(p,A);
  while (!Nulo(c,A)) {
    aux = Verifica(A,c,G);
    verificasub = (verificasub && !aux) || (!verificasub && aux);
    c = HermanoDer(c,A);
  }
  return (verificasub && !cumple) || (!verificasub && cumple);
Agrego dos variables:
  cumple verifica si el nodo que estoy mirando cumple la condicion
  aux verifica si existe un nodo del subarbol que verifique
  verificasub verifica si es unico

// Inciso 3 (2,5 pts)
void MuestraVerCumplen(TMat Mat,int N) {
  int i,j,gradoE,gradoS,mostrados=0;
  TVec Vec[] = {A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};
  for (i=0;i<N;i++)
    if (Mat[i][j] != 0) {
      gradoE = gradoS = 0;
      for (j=0;j<N;j++) {
        if (Mat[i][j] != 0)
          gradoS++;
        if (Mat[j][i] != 0)
          gradoE++;
      }
      if (gradoS == gradoE) {
        printf("\n%c",Vec[i]);
        mostrados++;
      }
    }
  if (N>0)
    printf("\nPorcentaje de vertices mostrados: %.2f",(float)mostrados/N);
  else
    printf("No hay vertices en el digrafo");
}
