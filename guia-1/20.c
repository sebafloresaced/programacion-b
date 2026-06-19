#include <stdio.h>
void decimalABinario(int n);
int main() {
    int num;
    printf("Introduce un numero decimal: ");
    scanf("%d", &num);
    printf("Binario: ");
    decimalABinario(num);
    return 0;
}
void decimalABinario(int n) {
    int binario[32]; // Array para almacenar los bits
    int i = 0;
    // Caso especial para el 0
    if (n == 0) {
        printf("0");
    }
    // Algoritmo: divisiones sucesivas
    while (n > 0) {
        binario[i] = n % 2; // Guardar resto
        n = n / 2;          // Dividir n
        i++;
    }
    // Imprimir array al revés
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binario[j]);
    }
}
