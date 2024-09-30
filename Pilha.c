#include "include/Pilha.h"
#include "include/Defines.h"
#include "include/No.h"


Pilha* cria_p(void){
    Pilha *nova = (Pilha*) malloc(sizeof(Pilha));
    nova->head = NULL;
    nova->tam = 0;
    return nova;
}
void insere_p(Pilha *p,unsigned int origem, unsigned int destino, float peso){
    No_p *novo = (No_p*)malloc(sizeof(No_p));
    novo->origem = origem;
    novo->destino = destino;
    novo->peso = peso;
    novo->proximo = p->head;
    p->head = novo;
    p->tam++;

}
No_p* remove_p(Pilha *p){

    if (vazia_p(*p)){
        return (NULL);
    }
    No_p *target = p->head;
    p->head = p->head->proximo;
    p->tam--;
    return target;
    
}
int vazia_p(Pilha f){
    return (f.tam==0);
}


void destroi_p(Pilha *p){
    if (vazia_p(*p)){
        free(p);
        return;
    }
    No_p *target = p->head;
    while (p->head!=NULL){
        p->head = p->head->proximo;
        free(target);
        target = p->head;
    }
    free(p);
}

void mostra_p(Pilha f){
    No_p *target = f.head;
    while (target!=NULL){
        printf("(%d - %d - %f)",target->origem, target->destino, target->peso);
        target = target->proximo;
    }
    printf("\n");
}
