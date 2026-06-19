// Inciso 1 (2 pts)
int EsDigito(char c) {
  return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' ||
         c == '5' || c == '6' || c == '7' || c == '8' || c == '9';
}
int EsDosDigitos(int num) {
  return (num % 100 == num && num / 10.0 >= 1)
}
void RecorreArbol(arbol A,int *noDigto,int *dosDigitos) {
  if (A != NULL) {
    if ((A->izq == NULL || A->der == NULL) && !EsDigito(A->c))
      *noDigto += 1;
    if (EsDosDigitos(A->num))
      *dosDigitos += 1;
    RecorreArbol(A->izq,noDigto,dosDigitos);
    RecorreArbol(A->der,noDigto,dosDigitos);
  }
}
// Invocacion:
int noDigito = 0, int dosDigitos = 0;
RecorreArbol(A,&noDigito,&dosDigitos);

// Inciso 2 (3 pts)
int Verifica(arbolN A,pos p,int nivel,int K){
  pos c;
  int grado=0,acum=0,cumpleSub=1,clave;
  if (Nulo(p,A) || nivel == K)
    return 1;
  else {
    c = HijoMasIzq(p,A);
    while (!Nulo(c,A) && cumpleSub) {
      grado++;
      acum += Info(c,A);
      cumpleSub = Verifica(A,c,nivel+1,K);
      c = HermanoDer(c,A);
    }
    clave = Info(p,A);
    if (grado>0 && clave>0 && grado % 2 == 0 && nivel < K)
      if ((float)acum/grado >= 2 * clave)
        return cumpleSub;
      else
        return 0;
    else
      return cumpleSub;
  }
}
// Invocacion: cumple = Verifica(A,Raiz(A),0,K);

// Inciso 3 (3 pts)
void Elimina(TVec Vec,int N) {
  TLista act,ant;
  int i,cBucle;
  for (i=0;i<N;i++) {
    cBucle = 0;
    ant = NULL;
    act = Vec[i];
    while (act != NULL && !cBucle) {
      if (act->vertice == i)
        cBucle = act->costo;
      ant = act;
      act = act->sig;
    }
    if (cBucle != 0) {
      ant = NULL;
      act = Vec[i];
      while (act != NULL && act->costo >= cBucle) {
        ant = act;
        act = act->sig;
      }
      if (act != NULL) {
        if (act == Vec[i]) {
          Vec[i] = Vec[i]->sig;
        }
        else {
          ant->sig = act->sig;
        }
        free(act);
      }
    }
  }
}
// Invocacion: Elimina(Vec,N);

// Inciso 4.a) (1 pts)
Aplico Dijkstra desde C

S = {C}
D = [inf, 9, 0, 3, inf]
P = [inf, 0, 0, 0, inf]

S = {C,D}
D = [4, 5, 0, 3, 9]
P = [D, D, 0, 0, D]

S = {C,D,A}
D = [4, 8, 0, 3, 6]
P = [D, D, 0, 0, A]

S = {C,D,A,E}
D = [4, 8, 0, 3, 6]
P = [D, D, 0, 0, A]

S = {C,D,A,E,B}
D = [4, 8, 0, 3, 6]
P = [D, D, 0, 0, A]

S = V // Termina el algoritmo

C - 3 - D - 1 - A
C - 3 - D - 5 - B
C - 3 - D
C - 3 - D - 1 - A - 2 - E
