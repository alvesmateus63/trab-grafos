#ifndef PILHA_H
#define PILHA_H

#include "Defines.h"
#include "No.h"
typedef struct No_p{
    struct No_p *proximo;
    unsigned int origem, destino;
    float peso;
}No_p;

typedef struct Pilha{
    struct No_p *head;
    int tam;
} Pilha;

Pilha* cria_p(void);
void insere_p(Pilha *p,unsigned int origem, unsigned int destino, float peso);
No_p* remove_p(Pilha *p);
int vazia_p(Pilha p);
void destroi_p(Pilha *p);
void mostra_p(Pilha p);

#endif /* Pilha_h */
