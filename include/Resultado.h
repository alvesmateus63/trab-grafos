#ifndef resultado_h
#define resultado_h
#include "Divisao.h"
typedef struct Divisao Divisao;

typedef struct Resultado{
    float melhor_gap;
    float pior_gap;
    float gap_soma;
    double melhor_tempo;
    double pior_tempo;
    double tempo_soma;
    int falha;
} Resultado;

void atualizar_r(Resultado *global, Divisao *d, double tempo, int iteracoes);
void inicializar_r(Resultado *resultado);
void imprimir_r(Resultado r,int tipo,float alpha);
#endif
