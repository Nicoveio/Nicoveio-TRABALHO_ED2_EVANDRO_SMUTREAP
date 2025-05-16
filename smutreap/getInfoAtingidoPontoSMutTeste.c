#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "smutreap.h"

// Definição da função f (teste)
bool f(SmuTreap t, Node n, Info i, double x, double y) {
    // Exemplo simples: se o ponto estiver dentro de uma certa área (ou qualquer outra verificação)
    return true; // Simulando que todos os pontos são "internos" para fins de exemplo
}

double* criaRetangulo(double x, double y, double w, double h) {
    double* r = malloc(4 * sizeof(double));
    r[0] = x;
    r[1] = y;
    r[2] = w;
    r[3] = h;
    return r;
}
void fCalculaBoundingBox(DescritorTipoInfo d, Info i, double* x, double* y, double* w, double* h) {
    // Supondo que Info seja um (double*) com [x, y, largura, altura]
    double* dados = (double*) i;

    *x = dados[0];     // x
    *y = dados[1];     // y
    *w = dados[2];     // largura
    *h = dados[3];     // altura
}


int main() {
    SmuTreap t = newSmuTreap(10, 1.1, 0.01);

    Info r1 = criaRetangulo(10, 10, 20, 20); // bounding box: (10,10)-(30,30)
    Info r2 = criaRetangulo(40, 40, 10, 10); // bounding box: (40,40)-(50,50)

    insertSmuT(t, 20, 20, r1, 0, fCalculaBoundingBox);
    insertSmuT(t, 45, 45, r2, 0, fCalculaBoundingBox);

    Lista L = lista_cria(); // Sua função para criar uma nova lista

    bool encontrado = getInfosAtingidoPontoSmuT(t, 25.0, 25.0, f, L);

    if (encontrado) {
        printf("Ponto dentro de uma ou mais infos!\n");
    } else {
        printf("Nenhuma info contém o ponto.\n");
    }

    return 0;
}
