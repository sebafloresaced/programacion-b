// Inciso 1 (3 pts)
int EmpiezaPorConsonante(char str[]) {
  return str[0] != 'a' && str[0] != 'e' && str[0] != 'i' && str[0] != 'o' && str[0] != 'u' &&
         str[0] != 'A' && str[0] != 'E' && str[0] != 'I' && str[0] != 'O' && str[0] != 'U';
}
int GradoOriginal(arbol A){
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
int AlgunNodoVerifica(arbol A) {
  int grado;
  if (A == NULL)
    return 0;
  else {
    grado = GradoOriginal(A);
    return (EmpiezaPorConsonante(A->dato) && grado>0 && grado % 2 == 0) || AlgunNodoVerifica(A->izq) || AlgunNodoVerifica(A->der);
  }
}
int BosquesVerifican(arbol A) {
  int cumple=1,grado;
  arbol aux;
  aux = A;
  if (A == NULL)
    return 0;
  else {
    while (aux != NULL && cumple) {
      grado = GradoOriginal(aux);
      cumple = (EmpiezaPorConsonante(aux->dato) && grado>0 && grado % 2 == 0) || AlgunNodoVerifica(aux->izq);
      aux = aux->der;
    }
    return cumple;
  }
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

    }
  }
}
int CantCumplen(arbolN A,pos p,int nivel,int K) {
  int cont=0,clavePrim=0,multiplo=1;
  pos c;
  if (Nulo(p,A) || nivel == K)
    return 0;
  else {
    c = HijoMasIzq(p,A);
    if (Nulo(c,A)) // p es hoja
      return 0;
    else {
      if (Nulo(HijoMasIzq(c,A))) { // el primer hijo es hoja
        clavePrim = Info(c,A);
      }
      while (!Nulo(c,A)) {
        cont += CantCumplen(A,c,nivel+1,K);
        if (clavePrim == 0 || Info(c,A) % clavePrim != 0) // Si es una hoja o su clave
          multiplo = 0;
        c = HermanoDer(c,A);
      }
      return cont + multiplo;
    }
  }
}

// Inciso 3 (3 pts)
int GradoSalMat(TMat Mat,int v,int j,int N) {
  if (j == N)
    return 0;
  else {
    return (Mat[v][j] != 0) + GradoSalMat(Mat,v,j+1,N);
  }
}
int Verifican(TMat Mat,TVec Vec,int N) {
  int bucle, gradoE, i=0,j, cumplen=1;
  TLista aux;
  while (i<N && cumplen) {
    aux = Vec[i];
    bucle = 0;
    while (aux != NULL && !bucle) {
      if (aux->nodo == i)
        bucle=1;
      aux = aux->sig;
    }
    if (!bucle) {
      gradoE=0;
      for (j=0;j<N;j++) {
        if (j != i) { // No recorro su mismo vertice porque ya se que no tiene bucle
          aux = Vec[j];
          while (aux != NULL) {
            if (aux->nodo == i)
              gradoE++;
            aux = aux->sig;
          }
        }
      }
      if (gradoE % 2 == 0)
        if (Mat[i][i] == 0 || GradoSalMat(Mat,i,0,N) % 2 != 1)
          cumplen = 0;
      }
      i++;
  }
  return cumplen;
}
