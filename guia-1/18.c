#include <stdio.h>
void DuplicaFor(int V[],unsigned int N);
void DuplicaWhile(int V[],unsigned int N);
void DuplicaDoWhile(int V[],unsigned int N);
void MuestraVector(int V[],unsigned int N);
void main() {
  unsigned int N = 7;
  int V[] = {1,2,3,4,5,6,7};
  DuplicaFor(V,N);
  MuestraVector(V,N);
  printf("\n");
  DuplicaWhile(V,N);
  MuestraVector(V,N);
  printf("\n");
  DuplicaDoWhile(V,N);
  MuestraVector(V,N);
}
void DuplicaFor(int V[],unsigned int N){
  unsigned int i;
  for (i=0;i<N;i+=2)
    V[i]*=2;
}
void DuplicaWhile(int V[],unsigned int N){
  unsigned int i=0;
  while (i<N){
    V[i]*=2;
    i+=2;
  }
}
void DuplicaDoWhile(int V[],unsigned int N){
  unsigned int i=0;
  do {
    V[i]*=2;
    i+=2;
  } while (i<N);
}
void MuestraVector(int V[],unsigned int N){
  unsigned int i;
  for (i=0;i<N;i++)
    printf("%d ",V[i]);
}
