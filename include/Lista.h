#ifndef LISTA_h
#define LISTA_h

#include "Defines.h"
#include "No.h"
typedef struct No_l{
    struct No_l *proximo;
    unsigned int origem, destino;
    float peso;
}No_l;

typedef struct Lista{
    struct No_l *head;
    struct No_l *tail;
    int tam;
} Lista;

Lista* cria_l(Grafo grafo);
Lista* cria_vazia_l(void);
No_l* remover_l(Lista *l);

void insere_l(Lista *l,No no, Aresta aresta);
void insere_no_final_l(Lista *l, No_l *novo);
void retorna_elementos_l(Lista *l, Lista *guardados);
int vazia_l(Lista l);
void destroi_l(Lista *l);
void mostra_l(Lista l);
void insere_gap(Lista *l, unsigned int origem, unsigned int destino, float gap, char criterio);
Lista* cria_gap(Grafo grafo, char criterio);
void remover_aresta_l(Lista *l, unsigned int origem, unsigned int destino, char criterio);
void remover_no_l(Lista *l, unsigned int origem);
No_l* remover_pos_l(Lista *l, int pos);
void destroi_l(Lista *l);
#endif /* LISTA_h */
