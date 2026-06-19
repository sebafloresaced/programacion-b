#include <stdio.h>
#define MaxElem 50
void CargaVector(int V[],unsigned int *N);
void Menu(int V[],unsigned int N);
void OpcionA(int V[],unsigned int N);
void OpcionB(int V[],unsigned int N,int K);
int OpcionC(int V[],unsigned int N,int X);
void MostrarVector(int V[],unsigned int N);
void main(){
  int V[MaxElem];
  unsigned int N;
  CargaVector(V,&N);
  Menu(V,N);
}
void CargaVector(int V[],unsigned int *N){
  unsigned int i;
  printf("Ingresa N: ");
  scanf("%u",N);
  for (i=0;i<*N;i++){
    printf("\nIngresa el elemento %u: ",i);
    scanf("%d",&V[i]);
  }
}
void Menu(int V[],unsigned int N){
  int K,X,idx;
  char Opcion;
  do {
    printf("Elegi una opcion:\n\ta\)Mostrar los elementos en posiciones impares\n\tb\)Generar otro vector con los elementos divisibles por k");
    printf("\n\tc\)Buscar la posición de un valor x\n\td\)Terminar programa");
    scanf(" %c",&Opcion);
    switch (Opcion) {
      case 'a':OpcionA(V,N);
               break;
      case 'b': printf("\n\nIngresa el valor de k: ");
                scanf("%d",&K);
                OpcionB(V,N,K);
                break;
      case 'c': printf("\n\nIngresa el valor de x: ");
                scanf("%d",&X);
                idx = OpcionC(V,N,X);
                (idx == -1)? printf("\nNo se encontro el valor ingresado"):printf("\nSe encontro el valor ingresado en la posicion %d",idx);
                break;
      default:  printf("\nOpcion invalida");
                break;
    }
  } while (Opcion != 'd');
}
void OpcionA(int V[],unsigned int N) {
  unsigned int i;
  for (i=1;i<N;i+=2)
    printf("%d ",V[i]);
}
void OpcionB(int V[],unsigned int N,int K) {
  int Vk[MaxElem],i;
  unsigned int M=0;
  for (i=0;i<N;i++)
    if (V[i]%K == 0)
      Vk[M++] = V[i];
  MostrarVector(Vk,M);
}
int OpcionC(int V[],unsigned int N,int X) {
  int i=0;
  while ((V[i]!=X)&&(i < N-1))
    i++;
  return (V[i]==X)? i:-1;
}
void MostrarVector(int V[],unsigned int N){
  unsigned int i;
  printf("\n");
  for (i=0;i<N;i++)
    printf("%d ",V[i]);
}
