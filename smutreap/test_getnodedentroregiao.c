#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"  // sua implementação de lista
#include "smutreap.h"  // interface com getNodesDentroRegiaoSmuT

typedef struct boundingBox {
    double x1, x2, y1, y2;
} boundingBox;

typedef struct NodeST {
    double x, y;
    int prioridade;
    void* info;
    int descritor;
    int hits;
    struct NodeST *dir, *esq;
    boundingBox* bb;
} NodeST;

typedef struct SmuTreapImp {
    NodeST* raiz;
    int hitCount;
    double promotionRate;
    double epsilon;
} SmuTreapImp;



// Função auxiliar de debug para imprimir cada nó
void imprimirNo(void* elem) {
    NodeST* n = (NodeST*)elem;
    printf("Nó (x=%.1f, y=%.1f)\n", n->x, n->y);
}

boundingBox* criarBB(double x1, double y1, double x2, double y2) {
    boundingBox* bb = malloc(sizeof(boundingBox));
    bb->x1 = x1;
    bb->x2 = x2;
    bb->y1 = y1;
    bb->y2 = y2;
    return bb;
}

int main() {
    // Monta uma SmuTreap simples manualmente
    NodeST* no1 = malloc(sizeof(NodeST));
    no1->x = 3.0; no1->y = 4.0;
    no1->dir = no1->esq = NULL;
    no1->bb = criarBB(3.0, 4.0, 3.0, 4.0);

    NodeST* no2 = malloc(sizeof(NodeST));
    no2->x = 6.0; no2->y = 5.0;
    no2->dir = no2->esq = NULL;
    no2->bb = criarBB(6.0, 5.0, 6.0, 5.0);

    NodeST* raiz = malloc(sizeof(NodeST));
    raiz->x = 5.0; raiz->y = 5.0;
    raiz->esq = no1;
    raiz->dir = no2;
    raiz->bb = criarBB(3.0, 4.0, 6.0, 5.0); // bounding box que engloba filhos

    SmuTreapImp* arvore = malloc(sizeof(SmuTreapImp));
    arvore->raiz = raiz;

    // Cria lista para receber os nós encontrados
    Lista lista = lista_cria();

    // Região de busca: inclui (4, 4) a (7, 6)
    bool encontrou = getNodesDentroRegiaoSmuT(arvore, 4.0, 4.0, 7.0, 6.0, lista);

    if (encontrou) {
        printf("NÓS ENCONTRADOS DENTRO DA REGIÃO:\n");
        lista_percorre(lista, imprimirNo);
    } else {
        printf("Nenhum nó encontrado dentro da região.\n");
    }

    lista_libera(lista);
    free(no1->bb); free(no1);
    free(no2->bb); free(no2);
    free(raiz->bb); free(raiz);
    free(arvore);
    return 0;
}
