#include "include/Fila.h"
#include "include/Defines.h"
#include "include/No.h"

/*======================================================
*           CRIA FILA
*---------------------------------------------------------
* Função: Cria uma fila
* Parametros: void
* Retorno: Fila* - ponteiro para a fila
======================================================*/
Fila* cria_f(void){
    Fila *nova = (Fila*) malloc(sizeof(Fila));
    nova->head = NULL;
    nova->tail = NULL;
    nova->tam = 0;
    return nova;
}

/*======================================================
*           INSERE NÓ NA FILA
*---------------------------------------------------------
* Função: Insere um nó na fila
* Parametros: f - ponteiro para a fila
*             no_grafo - nó a ser inserido
* Retorno: void
======================================================*/
void insere_f(Fila *f,No* no_grafo){
    No_f *novo = (No_f*)malloc(sizeof(No_f));
    novo->vertice = no_grafo;
    novo->proximo = NULL;  // Corrigir a inicialização do ponteiro

    if (vazia_f(*f)) {
        f->head = novo;
        f->tail = novo;
    } else {
        f->tail->proximo = novo;
        f->tail = novo;
    }

    f->tam++;

}

/*======================================================
*           REMOVE NÓ DA FILA
*---------------------------------------------------------
* Função: Remove um nó da fila
* Parametros: f - ponteiro para a fila
* Retorno: No* - nó removido
======================================================*/
No* remove_f(Fila *f){

    if (vazia_f(*f)){
        return (NULL);
    }
    No_f *target = f->head;
    No *vertice = f->head->vertice;
    f->head = f->head->proximo;
    f->tam--;
    free(target);
    if (vazia_f(*f)){
        f->tail=NULL;
    }
    return vertice;  
}

/*======================================================
*           FILA VAZIA
*---------------------------------------------------------
* Função: Verifica se a fila está vazia
* Parametros: f - fila
* Retorno: int - 1 se a fila está vazia, 0 caso contrário
======================================================*/
int vazia_f(Fila f){
    return (f.tam==0);
}

/*======================================================
*           CONTÉM NÓ
*---------------------------------------------------------
* Função: Verifica se a fila contém um nó
* Parametros: f - fila
*             id - id do nó
* Retorno: int - 1 se a fila contém o nó, 0 caso contrário
======================================================*/
int contem_f(Fila f,unsigned int id){
    No_f *target = f.head;
    while (target!=NULL){
        if (target->vertice->id == id)
            return 1;
        target = target->proximo;
    }
    return 0;
}

/*======================================================
*           DESTROI FILA
*---------------------------------------------------------
* Função: Destroi a fila
* Parametros: f - ponteiro para a fila
* Retorno: void
======================================================*/
void destroi_f(Fila *f){
    if (vazia_f(*f)){
        free(f);
        return;
    }
    No_f *target = f->head;
    while (f->head!=f->tail){
        f->head = f->head->proximo;
        free(target);
        target = f->head;
    }
    free(f);
}

/*======================================================
*           MOSTRA FILA
*---------------------------------------------------------
* Função: Mostra a fila
* Parametros: f - fila
* Retorno: void
======================================================*/
void mostra_f(Fila f){
    No_f *target = f.head;
    while (target!=NULL){
        printf("%d - ",target->vertice->id);
        target = target->proximo;
    }
    printf("\n");
}
