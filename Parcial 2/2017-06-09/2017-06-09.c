// Inciso 1 (3 puntos)
int GradoNodo(TVec VecLista,int nodo,int N) {
  TLista aux;
  int cont=0;
  aux = VecLista[nodo];
  while (aux != NULL) {
    cont++;
    aux = aux->sig;
  }
  return cont;
}
int CantCumplen(TVec VecLista,Tarbol A,int nivel,int N) {
  int grado;
  if (A == NULL)
    return 0;
  else {
    grado = GradoNodo(VecLista,A->dato,N);
    return (grado == nivel) + CantCumplen(VecLista,A->der,nivel+1,N) + CantCumplen(VecLista,A->izq,nivel+1,N);
  }
}
// Invocacion: cumplen = CantCumplen(VecLista,A,0,N);

// Inciso 2 (3 puntos)
int CantCumplen(TarbolN A,pos p){
  pos c;
  int acum=0,cumple;
  if (Nulo(p,A))
    return 0;
  else {
    c = HijoMasIzq(p,A);
    cumple = (Nulo(c,A) && Info(p,A) == 0)? 1:0;
    while (!Nulo(c,A)) {
      acum += CantCumplen(A,c);
      c = HermanoDer(c,A);
    }
    return cumple + acum;
  }
}
// Invocacion: cumplen = CantCumplen(A,Raiz(A));

// Inciso 3 (3 puntos)
int MayorVer(TMat Mat,int N) {
  int max=-1,i,j,k,cont,VerMax;
  for (i=0;i<N;i++) {
    cont = 0;
    for (j=0;j<N;j++) {
      if (Mat[i][j] != 0) {
        // Verifico que tenga grado de salida 0
        k = 0;
        while (k<N && Mat[j][k] == 0)
          k++;
        if (k==N)
          cont++;
      }
    }
    if (cont > max) {
      max = cont;
      VerMax = i;
    }
  }
  return VerMax;
}


