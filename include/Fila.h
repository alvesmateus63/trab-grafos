#ifndef FILA_H
#define FILA_H

#include "Defines.h"
#include "No.h"
typedef struct No_f{
    struct No_f *proximo;
    No *vertice;
}No_f;

typedef struct Fila{
    struct No_f *head;
    struct No_f *tail;
    int tam;
} Fila;

Fila* cria_f(void);
void insere_f(Fila *f,No *no_grafo);
No* remove_f(Fila *f);
int vazia_f(Fila f);
int contem_f(Fila f,unsigned int id);
void destroi_f(Fila *f);
void mostra_f(Fila f);

#endif /* Fila_h */
