#include <stdio.h>
void CargaMatriz(int Mat[4][5],unsigned int *N, unsigned int *M);
void BuscaX(int Mat[4][5],unsigned int N, unsigned int M,int x, int *i, int *j);
void CalcularPromedio(int Mat[4][5],unsigned int N, unsigned int M, float *Promedio);
void SuperanPromedio(int Mat[4][5],unsigned int N, unsigned int M, float Promedio);
int main(){
  int Mat[4][5] = {
  {2,0,5,7,1},
  {3,4,0,8,6},
  {9,2,1,0,3},
  {5,6,7,4,2}
  };
  unsigned int N=4,M=5;
  int i,j,x;
  float Promedio;
  //CargaMatriz(Mat,&N,&M);
  printf("Ingresa x: ");
  scanf("%d",&x);
  BuscaX(Mat,N,M,x,&i,&j);
  (i!=N)? printf("\nSe encontro el numero %d en la posicion %d %d",x,i,j):printf("No se encontro el numero %d en la Matriz",x);
  CalcularPromedio(Mat,N,M,&Promedio);
  SuperanPromedio(Mat,N,M,Promedio);
  printf("\n%f",Promedio);
  return 0;
}
void CargaMatriz(int Mat[4][5],unsigned int *N,unsigned int *M){
  unsigned int i,j;
  printf("\nIngresa los valores de N y M: ");
  scanf("%u %u",N,M);
  for (i=0;i<*N;i++)
    for (j=0;j<*M;j++)
      scanf("%d",&Mat[i][j]);
}
void BuscaX(int Mat[4][5],unsigned int N, unsigned int M,int x, int *i, int *j){
  *i=0; *j=0;
  while ((*i<N)&&(Mat[*i][*j]!=x)){
    *j=0;
    while ((*j<M)&&(Mat[*i][*j]!=x))
      (*j)++;
    if (Mat[*i][*j]!=x)
      (*i)++;
  }
}
void CalcularPromedio(int Mat[4][5],unsigned int N, unsigned int M, float *Promedio){
  unsigned int AcumT=0,AcumC,i,j;
  for (j=0;j<M;j++){
    AcumC=0;
    for (i=0;i<N;i++)
      AcumC+=Mat[i][j];
    printf("\nPromedio de la columna %u: %5.2f",j,(float)AcumC/N);
    AcumT+=AcumC;
  }
  *Promedio = (float)AcumT/(N*M);
}
void SuperanPromedio(int Mat[4][5],unsigned int N, unsigned int M, float Promedio){
  unsigned int i,j,ContCumplen,Cumple; // 1 verdadero - 0 falso
  for (i=0;i<N;i++){
    Cumple=0; ContCumplen=0;
    for (j=0;j<M;j++){
      if ((Cumple==0)&&(Mat[i][j]==0))
        Cumple=1;
      if (Mat[i][j]>Promedio)
        ContCumplen++;
    }
    if (Cumple==1)
      printf("\nLa fila %u contiene un cero, y tiene %u numeros que superan el promedio",i,ContCumplen);
  }
}
