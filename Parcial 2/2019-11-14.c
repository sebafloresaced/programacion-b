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
int Suma(arbol A,int nivel){
  if (A == NULL)
    return 0;
  else {
    if (A->dato == nivel && A->dato == GradoNodo(A))
      return A->dato + Suma(A->der,nivel) + Suma(A->izq,nivel + 1);
    else
      return Suma(A->der,nivel) + Suma(A->izq,nivel + 1);
  }
}
// Invocacion: suma = Suma(A,0);

// Inciso 2 (3 puntos)
int MayorNivel(TarbolN A,pos p,int nivel){
  pos c;
  int aux,mayor=-1;
  if (Nulo(p,A))
    return -1;
  else {
    c = HijoMasIzq(p,A);
    while (!Nulo(c,A)) {
      aux = MayorNivel(A,c,nivel+1);
      if (aux>mayor)
        mayor = aux;
      c = HermanoDer(c,A);
    }
    if (Info(p,A) == 0 && nivel > mayor)
      mayor = nivel;
    return mayor;
  }
}
// Invocacion mayornivel = MayorNivel(A,Raiz(A),0);

// Inciso 3 (3 puntos)
int TodosVisit(TVec VV,int N){
  int i=0;
  while (i<N && VV[i] != 0)
    i++;
  return (i<N)? 0:1;
}

void Profundidad(TMat Mat,TVec VV,int N){
  int v,j,camino=1;
  pila P;
  Inicia(&P);
  v=0;
  VV[v]=1;
  PoneP(&P,v);
  printf("%d - ",v);
  while (!TodosVisit(VV,N)) {
    v = ConsultaP(P);
    j = 0;
    while (j<N && (Mat[v][j] == 0 || VV[j] == 1))
      j++;
    if (j<N) {
      PoneP(&P,j);
      VV[j] = 1;
      printf("%d - ",j);
    }
    else {
      Saca(&P,&v);
      camino = 0;
    }
  }
  if (camino)
    printf("\n Se recorrio como un camino");
  else
    printf("\n No se recorrio como un camino");
}
// Invocacion: Profundidad(Mat,VV,N);

// Inciso 4 (1 punto)
a) Verdadero, ya que un grafo conexo aciclico tiene la estructura de un arbol pero sin jerarquia.
b) Falso. La matriz final de Floyd indica el costo minimo del camino de i a j. Si A[i][j] es cero, significa que no tiene costo ir de i a j, lo cual es absurdo,
   salvo que i == j. Aunque en ese caso tampoco asegura que exista (vi,vi) (bucle).

// Corecciones:
1) Pedia que A->dato sea igual a la altura, no a su nivel, es decir, la distancia con el nodo hasta su hoja mas profunda
