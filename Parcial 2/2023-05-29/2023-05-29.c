// Inciso 1 (3 pts)
int Verifica(arbol A){
  int mismaParidad=1;
  if (A == NULL || A->dato <= 0 || (A->izq == NULL && A->der == NULL))
    return 1;
  else {
    if ((A->izq != NULL && A->dato % 2 != A->izq->dato % 2) || (A->der != NULL && A->dato % 2 != A->der->dato % 2))
      mismaParidad=0;
    return mismaParidad && Verifica(A->izq) && Verifica(A->der);
  }
}

// Inciso 2 (3 pts)
void MayoresClavesNivelImpar(arbolN A,pos p,int nivel,int *mayor,int *segMayor){
  pos c;
  int clave;
  if (!Nulo(p,A)) {
    c = HijoMasIzq(p,A);
    while (!Nulo(c,A)) {
      MayoresClavesNivelImpar(A,c,nivel+1,mayor,segMayor);
      c = HermanoDer(c,A);
    }
    clave = Info(p,A);
    if (nivel % 2 == 1 && clave > *segMayor) {
      if (clave > *mayor) {
        *segMayor = *mayor;
        *mayor = clave;
      }
      else
        *segMayor = clave;
    }
  }
}
// Invocacion:
mayor = segMayor = -999;
MayoresClavesNivelImpar(A,Raiz(A),0,&mayor,&segMayor);


// Inciso 3 (3 pts)
int CostoAAM(TMat Mat,int i,int j,int N) { // Recorro media matriz porque es simetrica
  if (i<N) {
    if (j<i) {
      return Mat[i][j] + CostoAAM(Mat,i,j+1,N);
    }
    else
      return CostoAAM(Mat,i+1,0,N);
  }
  else
    return 0;
}
int CantAristasX(TMat Mat,int X,int j,int N){ // Recorro media matriz porque es simetrica
  if (j==N)
    return 0;
  else {
    return (Mat[X][j] != 0) + CantAristasX(Mat,X,j+1,N);
  }
}

// Inciso 4 (1 pts)
