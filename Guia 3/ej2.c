#include <stdio.h>
#define MaxElem 20
//Inciso A
void CargaVecA(int V[],unsigned int *N);
int Suma(int V[],unsigned int N);
void MuestraVector(int V[],unsigned int N);
void MuestraVectorInverso(int V[],unsigned int N);
//Inciso B
void CargaVecB(float V[],unsigned int *N);
int BusquedaLineal(float V[],unsigned int i,unsigned int N,float X);
int BusquedaBinaria(float V[], int i, int N, float X);
//Inciso C
void CargaMatC(int V[][MaxElem],unsigned int *N);
int BuscarMin(int V[][MaxElem],unsigned int i,unsigned int j,unsigned int N);
//Inciso D
void CargaMatD(int V[][MaxElem],unsigned int *N,unsigned int *M);
void MaximosMat(int Maximos[],int V[][MaxElem],unsigned int j,unsigned int N,unsigned int M);
//Inciso E
void MezclaVec(int A[], int B[], int C[],unsigned int i,unsigned int j,unsigned int *k,unsigned int nA,unsigned int nB);

int main(){
  int Va[MaxElem],Matc[MaxElem][MaxElem],Matd[MaxElem][MaxElem],Maximosd[MaxElem]={0},VeA[MaxElem],VeB[MaxElem],VeC[MaxElem];
  unsigned int Na,Nb,Nc,Nd,Md,NeA,NeB,NeC=0;
  float Vb[MaxElem],X;
  //Inciso A
  printf("Inciso A");
  CargaVecA(Va,&Na);
  printf("\nLa suma de los elementos del vector es %d",Suma(Va,Na-1));
  MuestraVector(Va,Na-1);
  MuestraVectorInverso(Va,Na-1);
  //Inciso B
  printf("\nInciso B");
  CargaVecB(Vb,&Nb);
  printf("\nIngresa X: ");
  scanf("%f",&X);
  printf("\nLa posicion es %d",BusquedaLineal(Vb,0,Nb-1,X));
  printf("\nLa posicion es %d",BusquedaBinaria(Vb,0,Nb-1,X));
  //Inciso C
  printf("\nInciso C");
  CargaMatC(Matc,&Nc);
  printf("\nEl minimo de la matriz es %d",BuscarMin(Matc,Nc-1,Nc-1,Nc-1));
  //Inciso D
  printf("\nInciso D");
  CargaMatD(Matd,&Nd,&Md);
  MaximosMat(Maximosd,Matd,Md-1,Nd-1,Md-1);
  MuestraVector(Maximosd,Nd-1);
  //Inciso E
  printf("\nInciso E");
  CargaVecA(VeA,&NeA);
  CargaVecA(VeB,&NeB);
  MezclaVec(VeA,VeB,VeC,0,0,&NeC,NeA,NeB);
  MuestraVector(VeC,NeC-1);
  return 0;
}

//Inciso A
void CargaVecA(int V[],unsigned int *N){
  unsigned int i;
  printf("\nIngresa N: ");
  scanf("%u",N);
  for (i=0;i<*N;i++)
    scanf("%d",&V[i]);
}
int Suma(int V[],unsigned int N){
  return (N==0)? V[N]:(V[N] + Suma(V,N-1));
}
void MuestraVector(int V[],unsigned int N){
  if (N==0)
    printf("%d ",V[N]);
  else {
    MuestraVector(V,N-1);
    printf("%d ",V[N]);
  }
}
void MuestraVectorInverso(int V[],unsigned int N){
  if (N==0)
    printf("%d ",V[N]);
  else {
    printf("%d ",V[N]);
    MuestraVectorInverso(V,N-1);
  }
}
//Inciso B
void CargaVecB(float V[],unsigned int *N){
  unsigned int i;
  printf("\nIngresa N: ");
  scanf("%u",N);
  for (i=0;i<*N;i++)
    scanf("%f",&V[i]);
}
int BusquedaLineal(float V[],unsigned int i,unsigned int N,float X){
  if (i==N)
    return (V[i]==X)? i:-1;
  else
    if (V[i]==X)
      return i;
    else
      return BusquedaLineal(V,i+1,N,X);
}
int BusquedaBinaria(float V[], int i, int N, float X){
  int medio;
  if (i > N)
    return -1; // no encontrado
  medio = (i + N) / 2;
  if (V[medio] == X)
    return medio;
  else
    if (X < V[medio])
      return BusquedaBinaria(V, i, medio - 1, X);
    else
      return BusquedaBinaria(V, medio + 1, N, X);
}
//Inciso C
void CargaMatC(int V[][MaxElem],unsigned int *N){
  unsigned int i,j;
  printf("\nIngresa N: ");
  scanf("%u",N);
  for (i=0;i<*N;i++)
    for (j=0;j<*N;j++)
      scanf("%d",&V[i][j]);
}
int BuscarMin(int V[][MaxElem],unsigned int i,unsigned int j,unsigned int N){
  int aux;
  if ((i==0)&&(j==0))
    return V[i][j];
  else {
    if (j==N)
      aux=BuscarMin(V,i-1,N,N);
    else
      aux=BuscarMin(V,i,j-1,N);
    return (aux<V[i][j])? aux:V[i][j];
    }
}
//Inciso D
void CargaMatD(int V[][MaxElem],unsigned int *N,unsigned int *M){
  unsigned int i,j;
  printf("\nIngresa N y M: ");
  scanf("%u %u",N,M);
  for (i=0;i<*N;i++)
    for (j=0;j<*M;j++)
      scanf("%d",&V[i][j]);
}
void MaximosMat(int Maximos[],int V[][MaxElem],unsigned int j,unsigned int N,unsigned int M){
  if (N>0) {
    if (j>0)
      MaximosMat(Maximos,V,j-1,N,M);
    else
      MaximosMat(Maximos,V,M,N-1,M);
    if (Maximos[N]<V[N][j])
        Maximos[N]=V[N][j];
  }
  else {
    if (j>0)
      MaximosMat(Maximos,V,j-1,N,M);
    if (Maximos[N]<V[N][j])
        Maximos[N]=V[N][j];
  }
}
//Inciso E
void MezclaVec(int A[], int B[], int C[],unsigned int i,unsigned int j,unsigned int *k,unsigned int nA,unsigned int nB){
  if ((i != nA)||(j != nB)) {
    if ((i == nA)||(A[i]>B[j])) {
      C[*k]=B[j];
      (*k)++;
      MezclaVec(A,B,C,i,j+1,k,nA,nB);
    }
    else
      if ((j == nB)||(A[i]<B[j])) {
        C[*k]=A[i];
        (*k)++;
        MezclaVec(A,B,C,i+1,j,k,nA,nB);
      }
      else {
        // A[i] == B[j]
        C[*k]=A[i];
        (*k)++;
        MezclaVec(A,B,C,i+1,j+1,k,nA,nB);
      }
  }
}
