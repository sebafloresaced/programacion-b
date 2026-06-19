// Inciso 1 (3 puntos)
int GradoNodo(Tarbol A,int K){
  int cont=0;
  Tarbol h;
  h = A->izq;
  while (h != NULL) {
    cont++;
    h = h->der;
  }
  return cont;
}
int UnNodoGradoK(Tarbol A,int K) {
  int grado;
  if (A == NULL)
    return 0;
  else {
    grado = GradoNodo(A,K);
    return (grado == K && !UnNodoGradoK(A->der,K) && !UnNodoGradoK(A->izq,K)) ||
          (grado != K && UnNodoGradoK(A->der,K) && !UnNodoGradoK(A->izq,K)) ||
          (grado != K && !UnNodoGradoK(A->der,K) && UnNodoGradoK(A->izq,K));
  }
}
int CantCumplen(Tarbol A,int K) {
  int cont=0;
  while (A != NULL) {
    if (GradoNodo(A,K) == K && !UnNodoGradoK(A->izq,K) || GradoNodo(A,K) != K && UnNodoGradoK(A->izq,K))
      cont++;
    A = A->der;
  }
  return cont;
}
// Invocacion: cumplen = CantCumplen(A,K);

// Inciso 2 (3 puntos)
int EsVocal(char c){
  return c == 'a' || c == 'A' ||
         c == 'e' || c == 'E' ||
         c == 'i' || c == 'I' ||
         c == 'o' || c == 'O' ||
         c == 'u' || c == 'U';
}
void NivelesTienenVocal(TarbolN A,pos p,int nivel,int *altura,TVec Vec){
  pos c;
  if (!Nulo(p,A)) {
    if (nivel > *altura)
      *altura = nivel;
    if (EsVocal(Info(p,A)))
      Vec[nivel] = 1;
    c = HijoMasIzq(p,A);
    while (!Nulo(c,A)) {
      NivelesTienenVocal(A,c,nivel + 1,altura,Vec);
      c = HermanoDer(c,A);
    }
  }
}
int VerificaTodosCumplen(TarbolN A,TVec Vec,int *altura){
  int i=0,cumple=1;
  *altura = 0;
  NivelesTienenVocal(A,Raiz(A),0,altura,Vec);
  while (i<=altura && cumple){
    if (Vec[i] == 0)
      cumple = 0;
    i++;
  }
  return cumple;
}
// Invocacion: cumple = VerificaTodosCumplen(A,Vec,&altura);

// Inciso 3 (3 puntos)


// El el inciso 4 puse el 71 a la derecha del 100, me rompe todo el ejercicio
