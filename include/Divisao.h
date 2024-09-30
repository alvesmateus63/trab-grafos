#ifndef divisao_h
#define divisao_h
#include "No.h"

typedef struct No No;

typedef struct Divisao{
    int n_nos;
    int n_subs;

    int *sub;
    float *max_sub;
    float *min_sub;
    int *tam_sub;

}Divisao;

Divisao* cria_d(int n_nos, int n_subgrafos, int inicial );
void insere_d(Divisao *d, No *no, int subgrafo);
float gap_local(Divisao d, int subgrafo);
float gap_global(Divisao d);
float diferenca_no_gap(Divisao d, float peso, int subgrafo);
void imprimir_d(Divisao d);
void destruir_d(Divisao *divisao);
int encontrar_menor_gap(Divisao *divisao);
#endif /* divisao_h */
