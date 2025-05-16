#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "smutreap.h"

//AS ESTRUTURAS FORAM COLOCADAS NA MAIN AFIM DE TESTES
typedef struct boundingBox{
    double x1, x2, y1, y2;
}boundingBox;
typedef struct NodeST{
    double x,y;
    int prioridade;
    Info info;
    DescritorTipoInfo descritor;
    int hits;
    struct NodeST *dir, *esq;
    boundingBox *bb;

}NodeST;

typedef struct SmuTreapImp{
    NodeST *raiz;
    int hitCount;
    double promotionRate;
    double epsilon;

}SmuTreapImp;

//AS ESTRUTURAS FORAM COLOCADAS NA MAIN AFIM DE TESTES

// Inclua aqui os headers e structs necessários
void exportaBoundingBoxesSVG(NodeST* no, FILE* svg, int isRaiz) {
    if (!no) return;

    // Se for o nó raiz, muda a cor da bolinha
    const char* corBolinha = isRaiz ? "green" : "red"; // Verde para raiz, vermelho para outros nós

    // Desenha o bounding box atual
    fprintf(svg,
        "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" "
        "fill=\"none\" stroke=\"blue\" stroke-width=\"1\" />\n",
        no->bb->x1,
        no->bb->y1,
        no->bb->x2 - no->bb->x1,
        no->bb->y2 - no->bb->y1
    );

    // Marca o ponto do nó
    fprintf(svg,
        "<circle cx=\"%lf\" cy=\"%lf\" r=\"1.5\" fill=\"%s\" />\n",
        no->x, no->y, corBolinha
    );

    // Verifica se a linha deve ser da esquerda ou direita
    if (no->esq) {
        // Linha do filho esquerdo
        fprintf(svg,
            "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"blue\" stroke-width=\"1\" />\n",
            no->x, no->y, no->esq->x, no->esq->y
        );
    }

    if (no->dir) {
        // Linha do filho direito
        fprintf(svg,
            "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"green\" stroke-width=\"1\" />\n",
            no->x, no->y, no->dir->x, no->dir->y
        );
    }

    // Chama recursivamente para os filhos
    exportaBoundingBoxesSVG(no->esq, svg, 0);  // Passa 0 para não ser raiz
    exportaBoundingBoxesSVG(no->dir, svg, 0);  // Passa 0 para não ser raiz
}

void gerarSVG(SmuTreap t, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "w");
    if (!f) {
        perror("Erro ao abrir SVG");
        return;
    }

    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\">\n");
    exportaBoundingBoxesSVG(((SmuTreapImp*)t)->raiz, f, 1); // Passa 1 para a raiz
    fprintf(f, "</svg>\n");

    fclose(f);
}



// Calcula bounding box fake (pra testar)
void fCalculaBBExemplo(DescritorTipoInfo d, Info info, double* x, double* y, double* w, double* h) {
    // Só pra testar, cria uma caixinha 10x10 em torno de (x,y) dado no info
    double* coords = (double*) info;
    *x = coords[0] - 5;
    *y = coords[1] - 5;
    *w = 10;
    *h = 10;
}

int main() {
 srand(time(NULL));

SmuTreap t = newSmuTreap(3, 0.3, 0.001);

// Inserindo outros nós manualmente
double* p1 = malloc(sizeof(double) * 2); p1[0] = 50; p1[1] = 50;
double* p2 = malloc(sizeof(double) * 2); p2[0] = 70; p2[1] = 60;
double* p3 = malloc(sizeof(double) * 2); p3[0] = 40; p3[1] = 90;
double* p4 = malloc(sizeof(double) * 2); p4[0] = 90; p4[1] = 120;
double* p5 = malloc(sizeof(double) * 2); p5[0] = 30; p5[1] = 70;

insertSmuT(t, p1[0], p1[1], p1, 0, fCalculaBBExemplo);
insertSmuT(t, p2[0], p2[1], p2, 0, fCalculaBBExemplo);
insertSmuT(t, p3[0], p3[1], p3, 0, fCalculaBBExemplo);
insertSmuT(t, p4[0], p4[1], p4, 0, fCalculaBBExemplo);
insertSmuT(t, p5[0], p5[1], p5, 0, fCalculaBBExemplo);

gerarSVG(t, "saida2.svg");

printf("SVG gerado em saida2.svg!\n");

    return 0;
}
