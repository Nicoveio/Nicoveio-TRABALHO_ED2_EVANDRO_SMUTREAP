#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

typedef void* Elemento;
// Tipo genérico que representa um elemento armazenado na lista.
// Pode ser qualquer tipo de dado (via casting para void*).

typedef struct lista* Lista;
// Estrutura opaca que representa uma lista encadeada simples.
// O acesso aos seus campos internos é restrito ao arquivo lista.c.

Lista lista_cria();
// Cria e retorna uma nova lista vazia.
// Retorna NULL em caso de falha de alocação.

void lista_insere(Lista l, Elemento elem);
// Insere o elemento 'elem' no início da lista 'l'.
// Requer: l != NULL (lista válida).

Elemento lista_remove_primeiro(Lista l);
// Remove e retorna o primeiro elemento da lista 'l'.
// Retorna NULL se a lista estiver vazia.
// Observação: O chamador é responsável por liberar a memória do elemento removido.

bool lista_vazia(Lista l);
// Verifica se a lista 'l' está vazia.
// Retorna true se vazia, false caso contrário.
// Requer: l != NULL.

void lista_libera(Lista l);
// Libera toda a memória alocada para a lista 'l'.
// Observação: Não libera os elementos armazenados, apenas a estrutura da lista.
// Requer: l != NULL.

void lista_percorre(Lista l, void (*func)(Elemento));
// Percorre a lista 'l' aplicando a função 'func' a cada elemento.
// Requer: l != NULL e func != NULL.
// A função deve ter a assinatura: void func(Elemento);

#endif