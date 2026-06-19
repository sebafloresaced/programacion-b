#include <stdio.h>
#define MaxElem 20
unsigned int Producto(unsigned int a,unsigned int b);
void Division(unsigned int a,unsigned int b, unsigned int *cociente,unsigned int *resto);
void CargaVector(int V[],unsigned int *n);
int MaxInt(int V[], unsigned int n);
void MaxVoid(int V[],unsigned int n,int *Max);
int main(){
  int V[MaxElem],Max;
  unsigned int a,b,cociente=0,resto,n;
  printf("Ingresa dos numeros naturales: ");
  scanf("%u %u",&a,&b);
  printf("\nSu producto es %u",Producto(a,b));
  Division(a,b,&cociente,&resto);
  printf("\nEl cociente de su division es %u y su resto %u",cociente,resto);
  CargaVector(V,&n);
  Max = MaxInt(V,n-1);
  printf("\nEl elemento maximo del vector es %d",Max);
  MaxVoid(V,n-1,&Max);
  printf("\nEl elemento maximo del vector es %d",Max);
  return 0;
}
unsigned int Producto(unsigned int a,unsigned int b){
  return (b==1)? a:a + Producto(a,b-1);
}
void Division(unsigned int a,unsigned int b, unsigned int *cociente,unsigned int *resto){
  if (a>=b) {
    *cociente +=1;
    Division(a-b,b,cociente,resto);
  }
  else
    *resto = a;
}
void CargaVector(int V[],unsigned int *n){
  unsigned int i;
  printf("\nIngresa N: ");
  scanf("%u",&n);
  for (i=0;i<*  n;i++)
    scanf("%d",&V[i]);
}
int MaxInt(int V[], unsigned int n){
  int aux;
  if (n==0)
    return V[n];
  else {
    aux = MaxInt(V,n-1);
    return (V[n]>aux)? V[n]:aux;
  }
}
void MaxVoid(int V[],unsigned int n,int *Max){
  if (n==0)
    *Max = V[n];
  else {
    if (*Max < V[n])
      *Max = V[n];
    MaxVoid(V,n-1,Max);
  }
}
