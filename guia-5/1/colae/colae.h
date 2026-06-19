#define MaxElem 20
typedef int TElementoC;
typedef struct {
  TElementoC datos[MaxElem];
  int inicio,fin;
} TCola;
void IniciaC (TCola * C);
int VaciaC (TCola C);
TElementoC consultaC (TCola C);
void sacaC (TCola *C, TElementoC* x);
void poneC (TCola *C, TElementoC x);
