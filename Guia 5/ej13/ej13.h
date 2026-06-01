#define MaxElem 20

typedef int TElementoC;

typedef struct {
  int inicio,fin,cant;
  TElementoC datos[MaxElem];
} TCola;

void IniciaC (TCola *C);
int VaciaC (TCola C);
TElementoC consultaC (TCola C);
void sacaC (TCola *C, TElementoC *x);
void poneC (TCola *C, TElementoC x);
