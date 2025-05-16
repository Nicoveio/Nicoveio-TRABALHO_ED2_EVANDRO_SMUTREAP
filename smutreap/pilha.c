#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// Estrutura interna da pilha
struct pilha {
    Elemento* dados;  // Array para armazenar os dados
    int topo;         // Índice do topo da pilha
    int capacidade;   // Capacidade máxima da pilha
};

// Função para criar a pilha
Pilha pilha_cria() {
    Pilha p = (Pilha)malloc(sizeof(struct pilha));
    if (p == NULL) {
        return NULL;  // Erro ao alocar memória
    }

    p->capacidade = 10;  // Capacidade inicial
    p->dados = (Elemento*)malloc(sizeof(Elemento) * p->capacidade);
    p->topo = -1;  // Pilha vazia

    return p;
}

// Função para liberar a pilha
void pilha_libera(Pilha p) {
    if (p != NULL) {
        free(p->dados);
        free(p);
    }
}

// Função para empilhar um elemento
bool pilha_empilha(Pilha p, Elemento elem) {
    if (p == NULL) return false;

    // Verifica se a pilha está cheia, se estiver, aumenta a capacidade
    if (p->topo == p->capacidade - 1) {
        p->capacidade *= 2;
        p->dados = (Elemento*)realloc(p->dados, sizeof(Elemento) * p->capacidade);
        if (p->dados == NULL) return false;  // Erro ao realocar
    }

    p->dados[++(p->topo)] = elem;
    return true;
}

// Função para desempilhar um elemento
Elemento pilha_desempilha(Pilha p) {
    if (p == NULL || pilha_vazia(p)) return NULL;

    return p->dados[(p->topo)--];
}

// Função para retornar o topo da pilha
Elemento pilha_topo(Pilha p) {
    if (p == NULL || pilha_vazia(p)) return NULL;

    return p->dados[p->topo];
}

// Função para verificar se a pilha está vazia
bool pilha_vazia(Pilha p) {
    return p == NULL || p->topo == -1;
}
