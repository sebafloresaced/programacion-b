#include <stdio.h>

void GenerarCuadrado(int N);

int main() {
    int N;
    printf("Ingresa un numero natural: ");
    scanf("%d", &N);

    GenerarCuadrado(N);

    return 0;
}

void GenerarCuadrado(int N) {
    int i, j;

    for (i = 1; i <= N; i++) {
        printf("#");
    }
    printf("\n");

    for (i = 2; i < N; i++) {
        printf("#");
        for (j = 2; j < N; j++) {
            printf(" ");
        }
        printf("#\n");
    }

    if (N > 1) {
        for (i = 1; i <= N; i++) {
            printf("#");
        }
        printf("\n");
    }
}
