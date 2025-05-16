#include "lista.h"
#include <stdlib.h>


typedef struct no {
    Elemento dado;
    struct no* prox;
} No;


struct lista {
    No* primeiro;
    int tamanho;  
};

Lista lista_cria() {
    struct lista* nova_lista = (struct lista*)malloc(sizeof(struct lista));
    if (!nova_lista) return NULL;
    
    nova_lista->primeiro = NULL;
    nova_lista->tamanho = 0;
    return nova_lista;
}

void lista_insere(Lista lista, Elemento elemento) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (!novo_no) return;

    novo_no->dado = elemento;
    novo_no->prox = lista->primeiro;
    lista->primeiro = novo_no;
    lista->tamanho++;
}

Elemento lista_remove_primeiro(Lista lista) {
    if (lista_vazia(lista)) return NULL;

    No* removido = lista->primeiro;
    Elemento dado = removido->dado;
    
    lista->primeiro = removido->prox;
    free(removido);
    lista->tamanho--;
    
    return dado;
}

bool lista_vazia(Lista lista) {
    return lista->primeiro == NULL;
}

void lista_libera(Lista lista) {
    No* atual = lista->primeiro;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

void lista_percorre(Lista lista, void (*func)(Elemento)) {
    for (No* atual = lista->primeiro; atual != NULL; atual = atual->prox) {
        func(atual->dado);
    }
}

