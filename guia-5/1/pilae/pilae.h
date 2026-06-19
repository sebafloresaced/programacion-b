#define MaxElem 20
typedef int TElementoP;
typedef struct {
  TElementoP datos[MaxElem];
  int tope;
} TPila;
void IniciaP (TPila * P);
void poneP (TPila * P, TElementoP x);
void sacaP (TPila * P, TElementoP * x);
TElementoP consultaP(TPila P);
int VaciaP (TPila P);
