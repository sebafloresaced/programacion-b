#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxElem 10
typedef struct nodo {
  char dato[MaxElem];
  unsigned int cont;
  struct nodo *sig;
} nodo;
typedef nodo *TLista;
void LeeArchivo(TLista *L);
int main(){
  TLista L;
  LeeArchivo(&L);
  return 0;
}
void LeeArchivo(TLista *L) {
  char palabra[MaxElem];
  FILE *arch;
  TLista aux,ant,act;
  *L = NULL;
  if ((arch = fopen("Datos.txt","rt")) == NULL)
    printf("Error al abrir el archivo");
  else {
  while (fscanf(arch,"%s",palabra) == 1) {
    if ((*L)==NULL || strcmp((*L)->dato,palabra)>0) {
      aux = (TLista)malloc(sizeof(nodo));
      strcpy(aux->dato,palabra);
      aux->sig = *L;
      aux->cont = 1;
      *L = aux;
    }
    else {
      if (strcmp((*L)->dato,palabra)==0)
        (*L)->cont++;
      else {
        act = *L;
        ant = NULL;
        while (act != NULL && strcmp(palabra,act->dato)>0) {
          ant = act;
          act = act->sig;
        }
        if (act != NULL && strcmp(palabra,act->dato)==0)
          act->cont++;
        else {
          aux = (TLista)malloc(sizeof(nodo));
          strcpy(aux->dato,palabra);
          aux->cont = 1;
          aux->sig = act;
          ant->sig = aux;
        }
      }
    }
  }
  fclose(arch);
  }
}
