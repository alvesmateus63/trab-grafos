#include "include/Lista.h"
#include "include/Defines.h"
#include "include/No.h"

#include <time.h>


int compara(int pri, int seg, char criterio, int igual){
    switch (criterio){
        case '>':
            if (igual)
                return pri>=seg;
            return pri>seg;
        case '<':
            if (igual)
                return pri<=seg;
            return pri<seg;
        default:return 0;
    }
}

void insere_l(Lista *l, No no, Aresta aresta){
    No_l *novo = (No_l*)malloc(sizeof(No_l));
    novo->origem = no.id;
    novo->destino = aresta.id_alvo;
    novo->peso = aresta.peso;
    l->tam +=1;
    if (l->tam==1){
        l->head = novo;
        novo->proximo = NULL;
        return;
    }
    if (l->head->peso>aresta.peso){
        novo->proximo= l->head;
        l->head = novo;
        return;
    }
    No_l *atual = l->head;
    while (atual->proximo!=NULL && atual->proximo->peso<aresta.peso){
        atual = atual->proximo;
    }
    //Se a aresta já está em lista, não inclui
    if (atual->proximo!=NULL && atual->proximo->peso==aresta.peso && atual->proximo->origem==no.id && atual->proximo->destino==aresta.id_alvo){
        free(novo);
    }else{
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}
void insere_no_final_l(Lista *l, No_l *novo){
    if (l->tam==0){
        novo->proximo = NULL;
        l->head = novo;
        l->tail = novo;
        
    }else{
        novo->proximo = l->tail->proximo;
        l->tail->proximo = novo;
        l->tail = novo;
    }
    l->tam++;

}

Lista* cria_l(Grafo grafo){
    Lista *nova = (Lista *)malloc(sizeof(Lista));
    nova->head = NULL;
    nova->tam = 0;
    No *no = grafo.primeiro;
    Aresta *aresta;
    while (no!=NULL){
        aresta = no->primeira_aresta;
        while (aresta!=NULL){
            insere_l(nova, *no, *aresta);
            aresta = aresta->prox_aresta;
        }
        no = no->proximo_no;
    }
    return nova;
}
Lista* cria_vazia_l(void){
    Lista *nova = (Lista *)malloc(sizeof(Lista));
    nova->head = NULL;
    nova->tail = NULL;
    nova->tam = 0;
    
    return nova;
}
No_l* remover_l(Lista *l){
    if (l->tam==0){
        return NULL;
    }
    No_l *removido = l->head;
    l->head = l->head->proximo;
    l->tam--;
    if (l->tam==0){
        l->tail = NULL;
    }
    return removido;
}
No_l* remover_pos_l(Lista *l, int pos){
    if (l->tam==0){
        return NULL;
    }
    No_l *removido;
    //Se só tem 1 nó tem que ser ele
    if (l->head->proximo==NULL){
        removido = l->head;
        l->head = NULL;
        l->tail = NULL;
    }
    //A partir de 1 nó
    No_l *aux = l->head;
    int i=0;
    while (aux->proximo->proximo!=NULL && i<pos){
        aux = aux->proximo;
        i++;
    }
    removido = aux->proximo;
    if (aux->proximo==l->tail){
        l->tail = aux;
    }
    aux->proximo = aux->proximo->proximo;
    l->tam--;
    return removido;
}
void mostra_l(Lista l){
    No_l *no = l.head;
    while (no!=NULL){
        printf("%d - %d - %f \n",no->origem, no->destino, no->peso);
        no = no->proximo;
    }
}
void destroi_l(Lista *lista) {
    No_l *atual = lista->head;
    while (atual != NULL) {
        No_l *proximo = atual->proximo; // Salva o próximo nó
        free(atual); // Libera o nó atual
        atual = proximo; // Move para o próximo nó
    }
    free(lista); // Libera a lista em si
}
Lista* cria_gap(Grafo grafo,char criterio){
    int nos[grafo.numero_de_nos];
    for (int i=0;i<grafo.numero_de_nos;i++){
        nos[i]=i+1;
    }
    int temp,a,b;
    srand(1);
    for (int i=0;i<grafo.numero_de_nos/2;i++){
        a = rand()%grafo.numero_de_nos;
        b = rand()%grafo.numero_de_nos;
        temp = nos[a];
        nos[a] = nos[b];
        nos[b] = temp;
    }
    Lista *nova = (Lista *)malloc(sizeof(Lista));
    nova->head = NULL;
    nova->tam = 0;
    No *origem;
    No *destino;
    Aresta *aresta;
    for(int i=0;i<grafo.numero_de_nos;i++){
        origem = encontrar_no_por_id(&grafo,nos[i]);
        if (origem->numero_de_arestas>1){ //o subgrafo não pode ter menos que 2 arestas)
            aresta = origem->primeira_aresta;
            while (aresta!=NULL){
                destino = encontrar_no_por_id(&grafo, aresta->id_alvo);
                if (destino->numero_de_arestas>1){
                    insere_gap(nova,origem->id, destino->id, fabs(origem->peso - destino->peso), criterio);
                }
                aresta = aresta->prox_aresta;
            }
        }
    }
    return nova;
}
void insere_gap(Lista *l, unsigned int origem, unsigned int destino, float gap, char criterio){
    No_l *novo = (No_l*)malloc(sizeof(No_l));
    novo->origem = origem;
    novo->destino = destino;
    novo->peso = gap;
    l->tam +=1;
    if (l->tam==1){
        l->head = novo;
        novo->proximo = NULL;
        return;
    }
    //Compara com o primeiro
    No_l *atual = l->head;
    if ((atual->origem==origem && atual->destino==destino) || // é a mesma aresta
        (atual->destino==origem && atual->origem==destino)){ //ou a sua recíproca
        free(novo);
        l->tam -=1;

    }else if(compara(gap,atual->peso,criterio,1)){
        novo->proximo = l->head;
        l->head = novo;
    }else {
        while (atual->proximo!=NULL && compara(atual->proximo->peso,gap,criterio,1)){
            //Se a aresta ou sua recíproca já está em lista, não inclui
            if ((atual->proximo->origem==origem && atual->proximo->destino==destino) || // é a mesma aresta
                (atual->proximo->destino==origem && atual->proximo->origem==destino)){ //ou a sua recíproca
                free(novo);
                l->tam -=1;

                break;
            }
            atual = atual->proximo;
        }
        if (atual->proximo == NULL||!compara(atual->proximo->peso,gap,criterio,1)){
            novo->proximo = atual->proximo;
            atual->proximo = novo;
        }
    }
}

void remover_aresta_l(Lista *l, unsigned int origem, unsigned int destino, char criterio){
    if (l->tam==0){
        return;
    }
    
    No_l *removido;
    //Se já é o 1o da lista:
    if (l->head->origem==origem && l->head->destino==destino){
        removido = l->head;
        l->head = l->head->proximo;
        free(removido);
        return;
    }
    //Procura no resto da lista
    No_l *atual = l->head;
    while (atual->proximo!=NULL && //até o final da lista
           compara(atual->proximo->peso, abs((int)origem-(int)destino), criterio,0) ){ //está ordenado por peso
        if (atual->proximo->origem==origem && atual->proximo->destino==destino){
            removido = atual->proximo;
            atual->proximo = atual->proximo->proximo;
            free(removido);
            return;
        }
        atual=atual->proximo;
    }
}

void remover_no_l(Lista *l, unsigned int alvo){
    if (l->tam==0){
        return;
    }
    No_l *removido;
    //Se o alvo já é o 1o da lista:
    if (l->head->origem==alvo || l->head->destino==alvo){
        removido = l->head;
        l->head = l->head->proximo;
        free(removido);
        return;
    }
    //Procura no resto da lista
    No_l *atual = l->head;
    while (atual->proximo!=NULL ){
        if (atual->proximo->origem==alvo &&
            atual->proximo->destino==alvo){
            removido = atual->proximo;
            atual->proximo = atual->proximo->proximo;
            free(removido);
        }
        atual=atual->proximo;
    }
}
int vazia_l(Lista l){
    return l.tam==0;
}



