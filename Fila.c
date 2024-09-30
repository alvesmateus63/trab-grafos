#include "include/Fila.h"
#include "include/Defines.h"
#include "include/No.h"


Fila* cria_f(void){
    Fila *nova = (Fila*) malloc(sizeof(Fila));
    nova->head = NULL;
    nova->tail = NULL;
    nova->tam = 0;
    return nova;
}
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
int vazia_f(Fila f){
    return (f.tam==0);
}
int contem_f(Fila f,unsigned int id){
    No_f *target = f.head;
    while (target!=NULL){
        if (target->vertice->id == id)
            return 1;
        target = target->proximo;
    }
    return 0;
}

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

void mostra_f(Fila f){
    No_f *target = f.head;
    while (target!=NULL){
        printf("%d - ",target->vertice->id);
        target = target->proximo;
    }
    printf("\n");
}
