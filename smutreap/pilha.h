#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

typedef void* Elemento;
// Tipo genérico que representa um elemento armazenado na pilha.
// Pode ser qualquer tipo de dado (via casting para void*).

typedef struct pilha* Pilha;
// Estrutura opaca que representa uma pilha.
// O acesso aos seus campos internos é restrito ao arquivo pilha.c.

Pilha pilha_cria();
// Cria e retorna uma nova pilha vazia.
// Retorna NULL em caso de falha de alocação.

void pilha_libera(Pilha p);
// Libera toda a memória alocada para a pilha 'p'.
// Observação: Não libera os elementos armazenados, apenas a estrutura da pilha.
// Requer: p != NULL.

bool pilha_empilha(Pilha p, Elemento elem);
// Empilha um novo elemento na pilha 'p'.
// Requer: p != NULL (pilha válida).
// Retorna: true se o elemento foi empilhado com sucesso, false em caso de erro.

Elemento pilha_desempilha(Pilha p);
// Desempilha o elemento do topo da pilha 'p'.
// Retorna NULL se a pilha estiver vazia.
// Observação: O chamador é responsável por liberar a memória do elemento removido.

Elemento pilha_topo(Pilha p);
// Retorna o elemento do topo da pilha 'p' sem removê-lo.
// Retorna NULL se a pilha estiver vazia.
// Requer: p != NULL (pilha válida).

bool pilha_vazia(Pilha p);
// Verifica se a pilha 'p' está vazia.
// Retorna true se vazia, false caso contrário.
// Requer: p != NULL.

#endif
