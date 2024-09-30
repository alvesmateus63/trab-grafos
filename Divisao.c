#include "include/Divisao.h"
#include "include/Defines.h"
#include "include/Fila.h"
#include "include/Grafo.h"
#include <limits.h>
#include <stdlib.h>

/*======================================================
*           CRIA DIVISÃO
*---------------------------------------------------------
* Função: Cria uma estrutura de divisão
* Parametros: numero_de_nos - número de nós do grafo
*             numero_subgrafos - número de subgrafos
*             inicial - valor inicial para os subgrafos
* Retorno: Divisao - estrutura de divisão
======================================================*/
Divisao* cria_d(int numero_de_nos, int numero_subgrafos, int inicial){
    //Nessa estrutura todas as posições dos vetores começam o armazenamento em 1,
    //para compatibilizar com o id dos nós.
    //Cria a estrutura
    Divisao* novo = (Divisao*)malloc(sizeof(Divisao));
    novo->n_nos = numero_de_nos;
    
    //Cria o vetor de classificação dos nós
    novo->sub =(int*)malloc((numero_de_nos+1)*sizeof(int));
    for(int i=0;i<=numero_de_nos;i++){
        novo->sub[i]=inicial;
    }
    novo->n_subs = inicial;
    
    //Cria os vetores para guardar o máximo e o mínimo e o tamanho de cada subgrafo
    novo->max_sub = (float*)malloc((numero_subgrafos+1)*sizeof(float));
    novo->min_sub = (float*)malloc((numero_subgrafos+1)*sizeof(float));
    novo->tam_sub = (int*)malloc((numero_subgrafos+1)*sizeof(int));

    for(int i=0;i<=numero_subgrafos;i++){
        novo->min_sub[i] = FLT_MAX;
        novo->max_sub[i] = 0;
        novo->tam_sub[i]=0;
    }
    return novo;
}

/*======================================================
*           INSERE NÓ NA DIVISÃO
*---------------------------------------------------------
* Função: Insere um nó na divisão
* Parametros: d - ponteiro para a divisão
*             no - nó a ser inserido
*             subgrafo - subgrafo ao qual o nó pertence
* Retorno: void
======================================================*/
void insere_d(Divisao *d, No *no, int subgrafo){
    d->sub[no->id] = subgrafo;
    d->tam_sub[subgrafo]++;
    
    if (no->peso > d->max_sub[subgrafo]){
        d->max_sub[subgrafo] = no->peso;
    }
    if (no->peso < d->min_sub[subgrafo]){
        d->min_sub[subgrafo] = no->peso;
    }
}

/*======================================================
*           GAP LOCAL
*---------------------------------------------------------
* Função: Calcula o gap local de um subgrafo
* Parametros: d - divisão
*             subgrafo - subgrafo
* Retorno: float - gap local
======================================================*/
float gap_local(Divisao d, int subgrafo){
    return d.max_sub[subgrafo] - d.min_sub[subgrafo];
}

/*======================================================
*           GAP GLOBAL
*---------------------------------------------------------
* Função: Calcula o gap global da divisão
* Parametros: d - divisão
* Retorno: float - gap global
======================================================*/
float gap_global(Divisao d){
    float soma = 0;
    for(int i=1;i<=d.n_subs;i++){
        soma+=gap_local(d, i);
    }
    return soma;
}

/*======================================================
*           DIFERENÇA NO GAP
*---------------------------------------------------------
* Função: Calcula a diferença no gap de um nó
* Parametros: d - divisão
*             peso - peso do nó
*             subgrafo - subgrafo ao qual o nó pertence
* Retorno: float - diferença no gap
======================================================*/
float diferenca_no_gap(Divisao d, float peso, int subgrafo){
    if (peso > d.max_sub[subgrafo]){
        return peso - d.min_sub[subgrafo];
    }else if (peso<d.min_sub[subgrafo]){
        return d.max_sub[subgrafo] - peso;
    }
    return 0;
}

/*======================================================
*           IMPRIMIR DIVISÃO
*---------------------------------------------------------
* Função: Imprime a divisão
* Parametros: d - divisão
* Retorno: void
======================================================*/
void imprimir_d(Divisao d){
    printf("Gap Global: %10.2f\n",gap_global(d));
    printf("Gaps Locais:\n");
    for(int i=1;i<=d.n_subs;i++){
        printf("Subgrafo: %d - Tam: %3d - Min: %10.2f - Max: %10.2f - Gap: %10.2f\n",i, d.tam_sub[i], d.min_sub[i],d.max_sub[i],gap_local(d,i));
    }
}

/*======================================================
*           DESTRUIR DIVISÃO
*---------------------------------------------------------
* Função: Destroi a divisão
* Parametros: d - ponteiro para a divisão
* Retorno: void
======================================================*/
void destruir_d(Divisao *d){
    free(d->sub);
    free(d->max_sub);
    free(d->min_sub);
    free(d);
    d = NULL;
}

/*======================================================
*           ENCONTRAR MENOR GAP
*---------------------------------------------------------
* Função: Encontra o menor gap
* Parametros: d - ponteiro para a divisão
* Retorno: int - menor gap
======================================================*/
int encontrar_menor_gap(Divisao *d){
    int menor_gap=0;
    
    
    return menor_gap;
}
