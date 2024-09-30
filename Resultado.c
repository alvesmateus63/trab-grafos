#include "include/Resultado.h"
#include "include/Divisao.h"
#include "include/Defines.h"


void atualizar_r(Resultado *global, Divisao *d, double tempo, int iteracoes){
    if (d == NULL){
        global->falha++;
        return;
    }
    float gap_atual = gap_global(*d);
    
    if (gap_atual <global->melhor_gap){
        global->melhor_gap = gap_atual ;
    }
    if (gap_atual >global->pior_gap){
        global->pior_gap = gap_atual;
    }
    if (tempo<global->melhor_tempo){
        global->melhor_tempo = tempo;
    }
    if (tempo>global->pior_tempo){
        global->pior_tempo = tempo;
    }
    global->gap_soma += gap_atual;
    global->tempo_soma += tempo;
    
}
void inicializar_r(Resultado *resultado){
    resultado->melhor_gap = FLT_MAX;
    resultado->pior_gap = 0;
    resultado->gap_soma = 0;
    resultado->melhor_tempo = FLT_MAX;
    resultado->pior_tempo = 0;
    resultado->tempo_soma = 0;
    resultado->falha = 0;
}

void imprimir_r(Resultado r,int tipo, float alpha){
    switch (tipo){
        case 1: printf("C          -----  ");
            break;
        case 2: printf("CR         %5.3f  ",alpha);
            break;
        case 3: printf("CRR        -----  ");
            break;
    }
    if (r.melhor_gap==FLT_MAX){
        printf("--------- ");
    }else{
        printf("%9.2f ",r.melhor_gap);
    }
    if (r.melhor_gap==FLT_MAX){
        printf("--------- ");
    }else{
        printf("%9.2f ",r.pior_gap);
    }
    if (r.melhor_gap==FLT_MAX){
        printf("--------- ");
    }else{
        printf("%9.2f ",r.gap_soma);
    }
    if (r.melhor_gap==FLT_MAX){
        printf("----------- ");
    }else{
        printf("%11.2f ",r.melhor_tempo);
    }
    if (r.melhor_gap==FLT_MAX){
        printf("----------- ");
    }else{
        printf("%11.2f ",r.pior_tempo);
    }
    if (r.melhor_gap==FLT_MAX){
        printf("----------- ");
    }else{
        printf("%11.2f ",r.tempo_soma);
    }
    printf("%7d \n",r.falha);
    

}
