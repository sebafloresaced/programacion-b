typedef int TElementoC;

typedef struct nodo {
 TElementoC dato;
 struct nodo * sig;} nodo;
typedef struct {
nodo *pri, *ult;} TCola;

void IniciaC (TCola * C);
int VaciaC (TCola C);
TElementoC consultaC (TCola C);
void sacaC (TCola *C, TElementoC* x);
void poneC (TCola *C, TElementoC x);
