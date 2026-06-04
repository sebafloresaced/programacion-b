#include <stdio.h>
void Consecutivos(int,int,int);
int main(){
  int a,b,c;
  printf("Ingresa tres numeros enteros :");
  scanf("%d %d %d",&a,&b,&c);
  Consecutivos(a,b,c);
  return 0;
}
void Consecutivos(int a,int b,int c){
    int min = a;
    if(b < min) min = b;
    if(c < min) min = c;

    int max = a;
    if(b > max) max = b;
    if(c > max) max = c;

    if(max - min == 2)
      printf("Son consecutivos");
    else
      printf("No son consecutivos");
}
