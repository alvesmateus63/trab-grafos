#include "../include/Grafo.h"
#include "../include/Defines.h"
#include "../include/No.h"
#include "../include/Fila.h"
#include "../include/Pilha.h"
#include "../include/Lista.h"
#include "../include/Divisao.h"
#include "../include/Resultado.h"

#include <limits.h>
#include <stdio.h>
#include <time.h>

#define INF FLT_MAX


/* =======================================================
*           GERA ARQUIVO DOT
*---------------------------------------------------------
* Função: Gera um arquivo DOT a partir de um grafo
* Recebe: grafo - ponteiro para o grafo
*         nome_arquivo - nome do arquivo de saída
* Retorno: void
* ======================================================*/
void gerar_arquivo_dot(Grafo *grafo, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }
    
    // Verifica se o grafo é direcionado
    if (grafo->direcionado) {
        fprintf(arquivo, "digraph G {\n");
    } else {
        fprintf(arquivo, "graph G {\n");
    }
    
    No *no_atual = grafo->primeiro;
    
    // Imprime os nós
    while (no_atual != NULL) {
        Aresta *aresta_atual = no_atual->primeira_aresta;
        while (aresta_atual != NULL) {
            if (grafo->direcionado) {
                // Para grafos direcionados, use "->"
                fprintf(arquivo, "  %d -> %d [label=\"%.2f\"];\n",
                        no_atual->id, aresta_atual->id_alvo, aresta_atual->peso);
            } else {
                // Para grafos não direcionados, garantir que uma aresta não seja duplicada
                if (no_atual->id < aresta_atual->id_alvo) {
                    fprintf(arquivo, "  %d -- %d [label=\"%.2f\"];\n",
                            no_atual->id, aresta_atual->id_alvo, aresta_atual->peso);
                }
            }
            aresta_atual = aresta_atual->prox_aresta;
        }
        no_atual = no_atual->proximo_no;
    }
    
    fprintf(arquivo, "}\n");
    fclose(arquivo);
}


/* =======================================================
*           GERA ARQUIVO DOT ARVORE DFS
*---------------------------------------------------------
* Função: Gera um arquivo DOT a partir de uma árvore DFS
* Recebe: arvore_dfs - vetor de arestas da árvore DFS
*         num_arestas_arvore - número de arestas da árvore DFS
*         arestas_retorno - vetor de arestas de retorno
*         num_arestas_retorno - número de arestas de retorno
*         nome_arquivo - nome do arquivo de saída
* Retorno: void
* ======================================================*/
void gerar_arquivo_dot_arvore_dfs(int *arvore_dfs, int num_arestas_arvore, int *arestas_retorno, int num_arestas_retorno, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita\n", nome_arquivo);
        return;
    }

    fprintf(arquivo, "digraph G {\n");
    fprintf(arquivo, "    node [shape=circle];\n");

    // Imprime as arestas da árvore DFS
    fprintf(arquivo, "    // Arestas da Arvore DFS\n");
    for (int i = 0; i < num_arestas_arvore; i++) {
        fprintf(arquivo, "    %d -> %d;\n", arvore_dfs[i*2], arvore_dfs[i*2+1]);
    }

    // Imprime as arestas de retorno
    fprintf(arquivo, "\n    // Arestas de retorno\n");
    for (int i = 0; i < num_arestas_retorno; i++) {
        fprintf(arquivo, "    %d -> %d [style=dotted];\n", arestas_retorno[i*2], arestas_retorno[i*2+1]);
    }

    fprintf(arquivo, "}\n");
    fclose(arquivo);
    printf("Arquivo DOT gerado com sucesso: %s\n", nome_arquivo);
}

// =============================================================================================================================================================================
//                                                                            ESTRUTURA BÁSICA DE UM GRAFO
// =============================================================================================================================================================================

/*======================================================
*           CONSTRUTOR INSTÂNCIA
* Função: Inicializar um grafo
* Recebe: ponteiro para um grafo e um ponteiro para um arquivo
* Retorno: void
* ======================================================*/
void inicializar_grafo_com_arquivo(Grafo *grafo, FILE *instance) {

    printf("\n Iniciando o grafo...\n\n");
    // Inicializando o grafo
    grafo->primeiro = NULL;
    grafo->ultimo = NULL;
    grafo->numero_de_nos = grafo->numero_de_arestas = 0;

    // Lendo o arquivo de instância
    if (instance != NULL) {
        char linha[100];

        // Lê a primeira linha do arquivo de instância
        if (fgets(linha, 100, instance) != NULL) 
        {
            sscanf(linha, "%d", &(grafo->numero_de_nos));
        } else {
            printf("Erro ao LER o nº total de nos!\n");
            return;
        }

        for(unsigned int i = 1; i <= grafo->numero_de_nos; i++)
        {
            adicionar_no(grafo, i, 0);
        }

        // Enquanto houver linhas no arquivo
        while (fgets(linha, 100, instance) != NULL) {
            // Armazena os valores da linha: ids dos nós e o peso da aresta
            unsigned int  id_no_1, id_no_2;
            float peso;

            // Verifica ponderações
            if(grafo->arestas_ponderadas == 1)
            {
                if (sscanf(linha, "%d %d %f", &id_no_1, &id_no_2, &peso) != 3) {
                    printf("Erro ao LER o arquivo de instancia\n");
                    break;
                }

                // Adiciona os nós e as arestas no grafo
                adicionar_aresta(grafo, id_no_1, id_no_2, peso);

                if (grafo->direcionado == 0){
                    adicionar_aresta(grafo, id_no_2, id_no_1, peso);
                } 
            } else {
                if (sscanf(linha, "%d %d", &id_no_1, &id_no_2) != 2) {
                    printf("Erro ao LER o arquivo de instancia\n");
                    break;
                }

                // Adiciona os nós e as arestas no grafo
                adicionar_aresta(grafo, id_no_1, id_no_2, 0);

                if (grafo->direcionado == 0){
                    adicionar_aresta(grafo, id_no_2, id_no_1, 0);
                } 
            }
        }

        // Inicializa os graus de entrada e saída dos nós
        //inicializa_graus(grafo); 
        //printf("Graus de entrada: %d", grafo->adj[0]->grau_entrada);

    } else {
        printf("Erro ao ABRIR o arquivo de instancia\n");
    }
}

/*======================================================
*           CONSTRUTOR PADRÃO 
* Função: Inicializar um grafo
* Recebe: ponteiro para um grafo
* Retorno: void
* ======================================================*/
void inicializar_grafo(Grafo *grafo) {
    grafo->numero_de_nos = 0;
    grafo->numero_de_arestas = 0;
    grafo->direcionado = 0;
    grafo->arestas_ponderadas = 0;
    grafo->nos_ponderados = 0;
    grafo->primeiro = NULL;
    grafo->ultimo = NULL;
}
/*======================================================
*           CONSTRUTOR COM PARAMETROS
* Função: Inicializar um grafo
* Recebe: ponteiro para um grafo
* Retorno: void
* ======================================================*/
void inicializar_grafo_com_parametros(Grafo *grafo,
                       int direcionado,
                       int arestas_ponderadas,
                       int nos_ponderados) {
    grafo->numero_de_nos = 0;
    grafo->numero_de_arestas = 0;
    grafo->direcionado = direcionado;
    grafo->arestas_ponderadas = arestas_ponderadas;
    grafo->nos_ponderados = nos_ponderados;
    grafo->primeiro = NULL;
    grafo->ultimo = NULL;
}
/*======================================================
*                   DESTRUTOR  
* Função: Destruir um grafo
* Recebe: ponteiro para um grafo
* Retorno: void
* ======================================================*/
void destruir_grafo(Grafo *grafo) {
    No *no_atual = grafo->primeiro;

    // Enquanto houver nós no grafo
    while (no_atual != NULL) {
        No *proximo_no = no_atual->proximo_no;
        Aresta *aresta_atual = no_atual->primeira_aresta;
        while (aresta_atual != NULL) {
            Aresta *proximo_aresta = aresta_atual->prox_aresta;
            free(aresta_atual);
            aresta_atual = proximo_aresta;
        }
        free(no_atual);
        no_atual = proximo_no;
    }
}

/*====================================================== 
*                    REMOVER NÓ 
* Função: remove um nó do grafo
* Recebe: id_no - id do nó a ser removido
* Retorno: void
* ======================================================*/
void remover_no(Grafo *grafo, unsigned int  id_no){
    // Verifica se o grafo e a lista de nós existem
    if (grafo == NULL || grafo->primeiro == NULL) {
        return;
    }


    No *no_atual = grafo->primeiro;
    No *no_remover = NULL;

    // Encontrar o nó a ser removido
    while (no_atual) {
        if (no_atual->id == id_no) {
            no_remover = no_atual;
            break;
        }
        no_atual = no_atual->proximo_no;
    }

    if (!no_remover) return; // Nó não encontrado

    // Remover todas as arestas que apontam para o nó a ser removido
    No *no_iter = grafo->primeiro;
    while (no_iter) {
        Aresta *aresta_atual = no_iter->primeira_aresta;
        Aresta *aresta_anterior = NULL;
        while (aresta_atual) {
            if (aresta_atual->id_alvo == id_no) {
                if (aresta_anterior) {
                    aresta_anterior->prox_aresta = aresta_atual->prox_aresta;
                } else {
                    no_iter->primeira_aresta = aresta_atual->prox_aresta;
                }
                free(aresta_atual);
                no_iter->numero_de_arestas--;
                break;
            }
            aresta_anterior = aresta_atual;
            aresta_atual = aresta_atual->prox_aresta;
        }
        no_iter = no_iter->proximo_no;
    }

    // Remover todas as arestas do nó a ser removido
    Aresta *aresta_atual = no_remover->primeira_aresta;
    while (aresta_atual) {
        Aresta *prox_aresta = aresta_atual->prox_aresta;
        free(aresta_atual);
        aresta_atual = prox_aresta;
    }

    // Ajustar os ponteiros do grafo
    if (no_remover->no_anterior) {
        no_remover->no_anterior->proximo_no = no_remover->proximo_no;
    } else {
        grafo->primeiro = no_remover->proximo_no;
    }
    if (no_remover->proximo_no) {
        no_remover->proximo_no->no_anterior = no_remover->no_anterior;
    } else {
        grafo->ultimo = no_remover->no_anterior;
    }

    // Liberar a memória do nó
    free(no_remover);

    // Atualizar os contadores do grafo
    grafo->numero_de_nos--;
}

/*====================================================== 
*                    REMOVER ARESTA
* Função: remove uma aresta do grafo
* Recebe: id_no_1 - id do nó 1
*         id_no_2 - id do nó 2
* Retorno: void
* ======================================================*/
void remover_aresta(Grafo *grafo, unsigned int  id_no_1, unsigned int  id_no_2) {

    // 1. Encontra o nó de origem
    No *no_origem = encontrar_no_por_id(grafo, id_no_1); 
    if (no_origem == NULL) {
        printf("Erro: Nó de origem %zu não encontrado.\n", id_no_1);
        return;
    }

    Aresta *aresta_atual = no_origem->primeira_aresta;
    Aresta *aresta_anterior = NULL;

    //2. Percorre a lista de arestas do nó de origem até encontrar a aresta que leva ao nó de destino
    while (aresta_atual != NULL && aresta_atual->id_alvo != id_no_2) {
        aresta_anterior = aresta_atual;
        aresta_atual = aresta_atual->prox_aresta;
    }

    if (aresta_atual == NULL) {
        printf("Erro: Aresta de %zu para %zu não encontrada.\n", id_no_1, id_no_2);
        return;
    }

    // 3. Remove a aresta ajustando os ponteiros da lista encadeada
    if (aresta_anterior == NULL) {
        no_origem->primeira_aresta = aresta_atual->prox_aresta;
    } else {
        aresta_anterior->prox_aresta = aresta_atual->prox_aresta;
    }
    no_origem->numero_de_arestas--;
    free(aresta_atual);
    grafo->numero_de_arestas--;

    // 4. Se o grafo não for direcionado, repete o processo para a aresta no nó destino
    if (!grafo->direcionado) {
        // Remover a aresta correspondente no nó de destino
        no_origem = encontrar_no_por_id(grafo, id_no_2);
        if (no_origem == NULL) {
            printf("Erro: Nó de destino %zu não encontrado.\n", id_no_2);
            return;
        }

        aresta_atual = no_origem->primeira_aresta;
        aresta_anterior = NULL;

        while (aresta_atual != NULL && aresta_atual->id_alvo != id_no_1) {
            aresta_anterior = aresta_atual;
            aresta_atual = aresta_atual->prox_aresta;
        }

        if (aresta_atual == NULL) {
            printf("Erro: Aresta de %zu para %zu não encontrada.\n", id_no_2, id_no_1);
            return;
        }

        if (aresta_anterior == NULL) {
            no_origem->primeira_aresta = aresta_atual->prox_aresta;
        } else {
            aresta_anterior->prox_aresta = aresta_atual->prox_aresta;
        }

        free(aresta_atual);
        no_origem->numero_de_arestas--;
    }
}



/*======================================================= 
*                      ADICIONAR NÓ  
* Função: adiciona um nó ao grafo
* Recebe: id_no - id do nó a ser adicionado
*         peso - peso do nó
* Retorno: void
* =======================================================*/
void adicionar_no(Grafo grafo, unsigned int  id_no, float peso) // adicionar nó na ordem
{
    // Verifica se o nó já existe no grafo
    No *no_atual = grafo->primeiro;
    while(no_atual != NULL) 
    {
        
        if(no_atual->id == id_no) // Se o nó já existe no grafo
        {
            printf("Já existe o no %d\n",id_no);
            return;
        }
        no_atual = no_atual->proximo_no; 
    }

    // O nó não existe, então podemos adicioná-lo ao grafo 

    if(grafo->primeiro == NULL) // grafo vazio
    {
        grafo->primeiro = (No*)malloc(sizeof(No)); 
        grafo->primeiro->id = id_no;
        grafo->primeiro->peso = peso;
        grafo->primeiro->proximo_no = NULL;
        //-->direcionar o anterior
        grafo->primeiro->no_anterior = NULL;
        grafo->primeiro->primeira_aresta = NULL;
        grafo->ultimo = grafo->primeiro;
        
    }
    else // grafo não vazio
    {
        No novo_no = (No)malloc(sizeof(No)); // cria um novo nó
        novo_no->id = id_no; 
        novo_no->peso = peso;
        novo_no->proximo_no = NULL;
        novo_no->primeira_aresta = NULL;
        novo_no->numero_de_arestas=0;
        
        grafo->ultimo->proximo_no = novo_no; 
        novo_no->no_anterior = grafo->ultimo; 
        grafo->ultimo = novo_no;    
    }
}

/*======================================================= 
*                      ADICIONAR ARESTA 
* Função: adiciona uma aresta ao grafo
* Recebe: id_no_1 - id do nó 1
*         id_no_2 - id do nó 2
*         peso - peso da aresta
* Retorno: void
* =======================================================*/
void adicionar_aresta(Grafo *grafo, unsigned int id_no_1, unsigned int  id_no_2, float peso)
{
    Aresta nova_aresta = (Aresta)malloc(sizeof(Aresta)); // cria uma nova aresta
    
    if (nova_aresta == NULL) 
    {
        printf("Erro ao alocar memoria para a nova aresta\n");
        return;
    }

    nova_aresta->id_alvo = id_no_2; 
    nova_aresta->peso = peso;
    nova_aresta->prox_aresta = NULL;
    
    No *no_origem = NULL;
    No *no_destino = NULL;

    // Verifica se o nó de origem existe no grafo
    No *no_atual = grafo->primeiro; 
  
    while (no_atual != NULL) 
    {
        if (no_atual->id == id_no_1) 
        {
            no_origem = no_atual; 
            break;
        }
        no_atual = no_atual->proximo_no; 
    }
  
    // Verifica se o nó de destino existe no grafo
    no_atual = grafo->primeiro; 
    while (no_atual != NULL) 
    {
        if (no_atual->id == id_no_2) 
        {
            no_destino = no_atual; 
            break;
        }
        no_atual = no_atual->proximo_no; 
    }

    // Se o nó de origem não existir no grafo
    if (no_origem == NULL) 
    {
        adicionar_no(grafo, id_no_1, 0);
        no_origem = grafo->ultimo; 
    }

    // Se o nó de destino não existir no grafo
    if (no_destino == NULL) 
    {

        adicionar_no(grafo, id_no_2, 0);
        no_destino = grafo->ultimo; 
    }
 
    // Se a alocação de memória falhou ou se algum dos nós não foi encontrado
    //-->Se a alocação de memória falhou, ele já fez o return lá em cima
    if (no_origem == NULL || no_destino == NULL) {
        free(nova_aresta); // Libera a memória alocada para a nova aresta
        return; // Sai do método se houver falha
    }

    // Se o nó de origem não tiver nenhuma aresta
    if (no_origem->primeira_aresta == NULL) 
    {
        no_origem->primeira_aresta = nova_aresta; 
    }
    else
    {
        Aresta *aresta_atual = no_origem->primeira_aresta;
        while (aresta_atual->prox_aresta != NULL) 
        {
            aresta_atual = aresta_atual->prox_aresta; 
        }
        aresta_atual->prox_aresta = nova_aresta; 
    }
    no_origem->numero_de_arestas+=1;
}

/*======================================================
*                  GRAFO VAZIO
*---------------------------------------------------------
* Função: Verifica se o grafo está vazio
* Recebe: grafo - ponteiro para o grafo
* Retorno: 1 se o grafo estiver vazio, 0 caso contrário
* ======================================================*/
int grafo_vazio(Grafo grafo){
    return  (grafo.primeiro == NULL);
}


/*=======================================================
*                  IMPRIMIR GRAFO 
* Função: imprime o grafo
* Recebe: grafo - ponteiro para o grafo
* Retorno: void
* =======================================================*/
void imprimir_grafo(Grafo *grafo)
{
   // Verifica se o grafo está vazio
    if (grafo->primeiro == NULL) {
        printf("O grafo esta vazio!\n");
        return;
    }
   
    No *no_atual = grafo->primeiro; // o nó atual é o primeiro nó do grafo

    if(grafo->arestas_ponderadas == 1)
    {
        // Enquanto houver nós no grafo
        while (no_atual != NULL) {
            if (grafo->nos_ponderados){
                printf("%.2f |%d|", no_atual->peso,no_atual->id);  // Imprime o id do nó - Lista encadeada de nós
            }else{
                printf("|%d|", no_atual->id);  // Imprime o id do nó - Lista encadeada de nós
            }
            if (no_atual->primeira_aresta != NULL)
            {
                Aresta *aresta_atual = no_atual->primeira_aresta;

                // Percorre todas as arestas do nó atual
                while (aresta_atual != NULL) {
                    // Imprime o ID do nó de origem e as informações da aresta
                    if (grafo->direcionado == 0){
                        printf(" - (%d, %.f)", aresta_atual->id_alvo, aresta_atual->peso);
                    } else {
                        printf(" -> (%d, %.f)", aresta_atual->id_alvo, aresta_atual->peso);
                    }
                    aresta_atual = aresta_atual->prox_aresta;
                }
            } else {
                printf(" -|");
            }

            printf("\n");
            no_atual = no_atual->proximo_no;
        }
    } 
    else {
       // Enquanto houver nós no grafo
        while (no_atual != NULL) {
            if (grafo->nos_ponderados){
                printf("%.2f |%d|", no_atual->peso,no_atual->id);  // Imprime o id do nó - Lista encadeada de nós
            }else{
                printf("|%d|", no_atual->id);  // Imprime o id do nó - Lista encadeada de nós
            }
            if (no_atual->primeira_aresta != NULL)
            {
                Aresta *aresta_atual = no_atual->primeira_aresta;
                // Percorre todas as arestas do nó atual
                while (aresta_atual != NULL) {
                    // Imprime o ID do nó de origem e as informações da aresta
                    printf(" - (%d)", aresta_atual->id_alvo);
                    aresta_atual = aresta_atual->prox_aresta;
                }
            } else {
                printf(" -|");
            }

            printf("\n");
            no_atual = no_atual->proximo_no;
        }  
    }
}


/*====================================================== 
*           IMPRIMIR GRAFO EM ARQUIVO
---------------------------------------------------------
* Função: imprime o grafo em um arquivo
* Recebe: grafo - ponteiro para o grafo
*         output_file - ponteiro para o arquivo de saída
* Retorno: void
====================================================== */
void imprimir_grafo_em_arquivo(Grafo *grafo, FILE *output_file)
{
    // Verifica se o arquivo foi aberto corretamente
    if (output_file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    No *no_atual = grafo->primeiro;

    if (grafo->arestas_ponderadas == 1) {
        // Enquanto houver nós no grafo
        while (no_atual != NULL) {
            fprintf(output_file, "|%d|", no_atual->id);  // Imprime o id do nó - Lista encadeada de nós

            if (no_atual->primeira_aresta != NULL) {
                Aresta *aresta_atual = no_atual->primeira_aresta;

                // Percorre todas as arestas do nó atual
                while (aresta_atual != NULL) {
                    // Imprime o ID do nó de origem e as informações da aresta
                    if (grafo->direcionado == 0) {
                        fprintf(output_file, " - (%d, %.f)", aresta_atual->id_alvo, aresta_atual->peso);
                    } else {
                        fprintf(output_file, " -> (%d, %.f)", aresta_atual->id_alvo, aresta_atual->peso);
                    }
                    aresta_atual = aresta_atual->prox_aresta;
                }
            } else {
                fprintf(output_file, " -|");
            }

            fprintf(output_file, "\n");
            no_atual = no_atual->proximo_no;
        }
    } else {
        // Enquanto houver nós no grafo
        while (no_atual != NULL) {
            fprintf(output_file, "|%d|", no_atual->id);  // Imprime o id do nó - Lista encadeada de nós

            if (no_atual->primeira_aresta != NULL) {
                Aresta *aresta_atual = no_atual->primeira_aresta;
                // Percorre todas as arestas do nó atual
                while (aresta_atual != NULL) {
                    // Imprime o ID do nó de origem e as informações da aresta
                    fprintf(output_file, " - (%d)", aresta_atual->id_alvo);
                    aresta_atual = aresta_atual->prox_aresta;
                }
            } else {
                fprintf(output_file, " -|");
            }

            fprintf(output_file, "\n");
            no_atual = no_atual->proximo_no;
        }
    }
    
    // Fecha o arquivo
    fclose(output_file);
}

/*====================================================== 
*                      CONECTADO 
---------------------------------------------------------
* Função: verifica se dois nós estão conectados
* Parametros: id_no_1 - id do nó 1
*             id_no_2 - id do nó 2
* Retorno: 1 se os nós estão conectados, 0 caso contrário
======================================================*/
int conectado(Grafo *grafo, unsigned int  id_no_1, unsigned int  id_no_2)
{
    if (grafo == NULL) {
        return 0;
    }

    No *no_1 = encontrar_no_por_id(grafo, id_no_1);
    No *no_2 = encontrar_no_por_id(grafo, id_no_2);

    if (no_1 == NULL || no_2 == NULL) {
        return 0;
    }

    // Inicializa divisao de visitados
    int *visitados = (int *)malloc(grafo->numero_de_nos * sizeof(int));
    for (size_t i = 0; i < grafo->numero_de_nos; i++) {
        visitados[i] = 0;
    }

    // Divisao para armazenar vértices visitados em ordem crescente durante a busca
    int *vertices_visitados = (int *)malloc(grafo->numero_de_nos * sizeof(int));
    int contador_visitados = 0;

    // Realiza busca em profundidade a partir de id_no_1
    busca_prof_visit(grafo, id_no_1, visitados, vertices_visitados, &contador_visitados);

    // Verifica se id_no_2 foi marcado como visitado durante a busca
    int conectado = 0;
    for (int i = 0; i < contador_visitados; i++) {
        // Convertendo id_no_2 para int para evitar comparação entre signed e unsigned
        if (vertices_visitados[i] == (int)id_no_2) {
            conectado = 1;
            break;
        }
    }

    free(visitados);
    free(vertices_visitados);

    return conectado;
}


// =============================================================================================================================================================================
//                                                                        ESTRUTURA COMPLEMENTAR DE UM GRAFO
// =============================================================================================================================================================================

/*====================================================== 
*               ENCONTRAR NÓ POR ID
---------------------------------------------------------
* Função: Encontra um nó no grafo a partir de um id
* Parametros: grafo - ponteiro para o grafo
*             id - id do nó
* Retorno: ponteiro para o nó encontrado
======================================================*/
No *encontrar_no_por_id(Grafo *grafo, unsigned int id) {
    No *tmp_iterator = grafo->primeiro;
    while (tmp_iterator != NULL) {
        if (tmp_iterator->id == id) {
            return tmp_iterator;
        }
        tmp_iterator = tmp_iterator->proximo_no;
    }
    return NULL;
}

/*====================================================== 
*               INICIALIZA GRAUS
---------------------------------------------------------
* Função: Inicializa os graus de entrada e saída de todos os nós
* Parametros: grafo - ponteiro para o grafo
* Retorno: void
======================================================*/
void inicializa_graus(Grafo *grafo)
{
    // Inicializa os graus de entrada e saída de todos os nós
    No* tmp_iterator = grafo->primeiro;

    // Zera os graus de entrada e saída de todos os nós
    while (tmp_iterator != NULL)
    {
        tmp_iterator->grau_entrada = 0;
        tmp_iterator->grau_saida = 0;
        tmp_iterator = tmp_iterator->proximo_no;
    }

    // Conta os graus de entrada e saída de cada nó
    tmp_iterator = grafo->primeiro;
    while (tmp_iterator != NULL)
    {
        Aresta *aresta_atual = tmp_iterator->primeira_aresta;
        while (aresta_atual != NULL)
        {
            // Incrementa o grau de saída do nó atual
            tmp_iterator->grau_saida++;

            // Encontra o nó de destino da aresta e incrementa o grau de entrada dele
            No *no_alvo = encontrar_no_por_id(grafo, aresta_atual->id_alvo);
            if (no_alvo != NULL)
                no_alvo->grau_entrada++;

            aresta_atual = aresta_atual->prox_aresta;
        }

        tmp_iterator = tmp_iterator->proximo_no;
    }

}


/*====================================================== 
*              COMPARAR ARESTAS
---------------------------------------------------------
* Função: Compara duas arestas 
* Parametros: a e b - ponteiros para as arestas
* Retorno: void
======================================================*/
int comparar(const void *a, const void *b) {
    return ((int)a - (int)b);
}


/*====================================================== 
*               BUSCA EM PROFUNDIDADE
---------------------------------------------------------
* Função: realiza a busca em profundidade 
* Parametros: grafo - ponteiro para o grafo
*             u - nó de origem
*             visitados - divisao de marcação, rastreia se um nó foi visitado durante a busca
*             vertices_visitados - divisao que armazena os ids dos vértices visitados em ordem crescente durante a busca 
*             contador_visitados - contador de vértices visitados
* Retorno: void
======================================================*/
void busca_prof_visit(Grafo *grafo, unsigned int u, int *visitados, int *vertices_visitados, int *contador_visitados) {
    visitados[u] = 1;
    vertices_visitados[(*contador_visitados)++] = u;

    No *no = encontrar_no_por_id(grafo, u);
    if (no == NULL) {
        return;  // Caso não encontre o nó, retorna
    }

    Aresta *aresta_atual = no->primeira_aresta; // Aresta atual é a primeira aresta do nó

    // Enquanto houver arestas, chama a busca em profundidade para o nó de destino
    while (aresta_atual != NULL) {
        unsigned int v = aresta_atual->id_alvo; 
        if (!visitados[v])  {
            busca_prof_visit(grafo, v, visitados, vertices_visitados, contador_visitados);
        }
        aresta_atual = aresta_atual->prox_aresta;
    }
}

/*====================================================== 
*      BUSCA EM PROFUNDIDADE INVERSA
---------------------------------------------------------
* Função: realiza a busca em profundidade inversa, ou seja, a partir do nó de destino
* Parametros: grafo - ponteiro para o grafo
*             u - nó de origem
* Retorno: void
======================================================*/
void busca_prof_visit_inversa(Grafo *grafo, unsigned int u, int *visitados, int *vertices_visitados, int *contador_visitados) {
    visitados[u] = 1;
    vertices_visitados[(*contador_visitados)++] = u;

    for (No *tmp = grafo->primeiro; tmp != NULL; tmp = tmp->proximo_no) {
        Aresta *aresta_atual = tmp->primeira_aresta;
        while (aresta_atual != NULL) {
            if (aresta_atual->id_alvo == u && !visitados[tmp->id]) {
                busca_prof_visit_inversa(grafo, tmp->id, visitados, vertices_visitados, contador_visitados);
            }
            aresta_atual = aresta_atual->prox_aresta;
        }
    }
}

/*====================================================== 
*        BUSCA EM PROFUNDIDADE EM TODO O GRAFO
---------------------------------------------------------
* Função: realiza a busca em profundidade no grafo inteiro
* Parametros: grafo - ponteiro para o grafo
* Retorno: void
======================================================*/
void busca_prof(Grafo *grafo) {
    No *tmp_iterator = grafo->primeiro; // Iterador para percorrer os nós
    while (tmp_iterator != NULL) {
        tmp_iterator->visitado = 0; // Inicializa todos os vértices como não visitados
        tmp_iterator = tmp_iterator->proximo_no;
    }

    tmp_iterator = grafo->primeiro;
    int *visitados = (int *)calloc(grafo->numero_de_nos, sizeof(int));  // Aloca divisao de visitados uma vez
    if (visitados == NULL) {
        printf("Erro ao alocar memoria\n");
        return;
    }

    // Percorre todos os nos do grafo
    while (tmp_iterator != NULL) {
        if (visitados[tmp_iterator->id] == 0) {
            int *vertices_visitados = (int *)malloc(grafo->numero_de_nos * sizeof(int)); 
            int contador_visitados = 0; //
            if (vertices_visitados == NULL) {
                printf("Erro ao alocar memoria\n");
                free(visitados);
                return;
            }

            busca_prof_visit(grafo, tmp_iterator->id, visitados, vertices_visitados, &contador_visitados);

            // Ordena os vertices visitados
            qsort(vertices_visitados, contador_visitados, sizeof(int), comparar);

            // Imprime os vertices em ordem crescente
            for (int i = 0; i < contador_visitados; i++) {
                printf("%d ", vertices_visitados[i]);
            }
            printf("\n");

            free(vertices_visitados);
        }
        tmp_iterator = tmp_iterator->proximo_no;
    }
    free(visitados);  // Libera a memória do divisao de visitados após a busca
}


/*====================================================== 
*        FECHO TRANSITIVO DIRETO
---------------------------------------------------------
* Função: realiza o fecho transitivo direto de um nó
* Parametros: grafo - ponteiro para o grafo
*             u - nó de origem
* Retorno: void
======================================================*/
Fecho fecho_transitivo_direto(Grafo *grafo, unsigned int u) {
    Fecho fecho = {NULL, 0};
    No *no = encontrar_no_por_id(grafo, u);
    if (no == NULL) {
        printf("O vertice %u nao existe no grafo\n", u);
        return fecho;
    }

    int *visitados = (int *)calloc(grafo->numero_de_nos, sizeof(int));
    int *vertices_visitados = (int *)malloc(grafo->numero_de_nos * sizeof(int));
    int contador_visitados = 0;

    if (visitados == NULL || vertices_visitados == NULL) {
        printf("Erro ao alocar memoria\n");
        free(visitados);
        free(vertices_visitados);
        return fecho;
    }

    busca_prof_visit(grafo, u, visitados, vertices_visitados, &contador_visitados);

    if (!grafo->direcionado) {
        for (unsigned int i = 1; i <= grafo->numero_de_nos; i++) { 
            if (i != u && encontrar_no_por_id(grafo, i) != NULL && !visitados[i]) {
                busca_prof_visit(grafo, i, visitados, vertices_visitados, &contador_visitados);
            }
        }
    }

    // Ordenar os vértices visitados
    qsort(vertices_visitados, contador_visitados, sizeof(int), comparar);

    // Atualizar o fecho transitivo direto
    fecho.vertices = vertices_visitados;
    fecho.tamanho = contador_visitados;

    free(visitados);
    return fecho;
}


/*====================================================== 
*        FECHO TRANSITIVO INDIRETO
---------------------------------------------------------
* Função: realiza o fecho transitivo indireto de um nó
* Parametros: grafo - ponteiro para o grafo
*             u - nó de origem
* Retorno: void
======================================================*/
Fecho fecho_transitivo_indireto(Grafo *grafo, unsigned int u) {
    Fecho fecho = {NULL, 0};
    No *no = encontrar_no_por_id(grafo, u);
    if (no == NULL) {
        printf("O vertice %u nao existe no grafo\n", u);
        return fecho;
    }

    int *visitados = (int *)calloc(grafo->numero_de_nos, sizeof(int));
    int *vertices_visitados = (int *)malloc(grafo->numero_de_nos * sizeof(int));
    int contador_visitados = 0;

    if (visitados == NULL || vertices_visitados == NULL) {
        printf("Erro ao alocar memoria\n");
        free(visitados);
        free(vertices_visitados);
        return fecho;
    }

    busca_prof_visit_inversa(grafo, u, visitados, vertices_visitados, &contador_visitados);

    if (!grafo->direcionado) {
        for (unsigned int i = 1; i <= grafo->numero_de_nos; i++) {
            if (i != u && encontrar_no_por_id(grafo, i) != NULL && !visitados[i]) {
                busca_prof_visit_inversa(grafo, i, visitados, vertices_visitados, &contador_visitados);
            }
        }
    }

    // Ordenar os vértices visitados
    qsort(vertices_visitados, contador_visitados, sizeof(int), comparar);

    // Atualizar o fecho transitivo indireto
    fecho.vertices = vertices_visitados;
    fecho.tamanho = contador_visitados;

    free(visitados);
    return fecho;
}


/*====================================================== 
*           IMPRIMIR FECHOS TRANSITIVOS
---------------------------------------------------------
* Função: imprime o fecho transitivo direto ou indireto de um nó
* Parametros: grafo - ponteiro para o grafo
*             u - nó de origem
*             tipo_str - tipo de fecho (direto ou indireto)
* Retorno: void
======================================================*/
void imprimir_fecho(Grafo *grafo, unsigned int u, const char *tipo_str) {
    Fecho fecho;

    // Verificar se o tipo de fecho é válido
    if (strcmp(tipo_str, "Direto") == 0) {
        fecho = fecho_transitivo_direto(grafo, u);
    } else if (strcmp(tipo_str, "Indireto") == 0) {
        fecho = fecho_transitivo_indireto(grafo, u);
    } else {
        printf("Tipo de fecho desconhecido\n");
        return;
    }

    // Imprimir o fecho transitivo
    if (fecho.vertices != NULL) {
        printf("Fecho Transitivo %s a partir do V%u: ", tipo_str, u);
        for (int i = 0; i < fecho.tamanho; i++) {
            printf("%d ", fecho.vertices[i]);
        }
        printf("\n");
        free(fecho.vertices);
    } else {
        printf("Nenhum vertice encontrado\n");
    }
}


// =============================================================================================================================================================================
//                                                                        ALGORITMOS GRAFO
// =============================================================================================================================================================================

/*======================================================
*               CAMINHO MÍNIMO - DIJKSTRA
---------------------------------------------------------
* Função: Encontra o caminho mínimo entre dois nós utilizando
*         o algoritmo de Dijkstra
* Parametros: grafo - ponteiro para o grafo
*             o - Identificador do nó de origem
*             d - Identificador do nó de destino
* Retorno: grafo com o caminho mínimo
======================================================*/
Grafo caminho_Dijkstra(Grafo *grafo, unsigned int o, unsigned int d) {
    Grafo resposta;
    inicializar_grafo(&resposta);
    resposta.direcionado = grafo->direcionado;
    resposta.arestas_ponderadas = grafo->arestas_ponderadas;
    
    // Procura os nós do caminho
    No *no_atual = encontrar_no_por_id(grafo, d);
    if (no_atual == NULL) {
        printf("Identificador de destino nao encontrado no grafo\n");
        return resposta;
    }
    no_atual = encontrar_no_por_id(grafo, o);
    if (no_atual == NULL) {
        printf("Identificador de origem nao encontrado no grafo\n");
        return resposta;
    }

    // Verificações
    if (o == d) {
        printf("Origem e destino iguais\n");
        return resposta;
    }
    
    // Cria os vetores de distância e de predecessor
    float *distancia = (float *)malloc(grafo->numero_de_nos * sizeof(float));
    int *predecessor = (int *)malloc(grafo->numero_de_nos * sizeof(int));
    Fila *visitados = cria_f();
    
    // atribuindo à todos os elementos de distância um valor muito grande
    for (unsigned int i = 0; i < grafo->numero_de_nos; i++) {
        distancia[i] = INT_MAX;
        predecessor[i] = -1;
    }
    
    // INICIANDO O ALGORITMO DE DIJKSTRA
    distancia[o - 1] = 0;
    No *prox_no;
    
    do {
        Aresta *aresta = no_atual->primeira_aresta;
        while (aresta != NULL) {
            prox_no = encontrar_no_por_id(grafo, aresta->id_alvo);

            // Enfila
            if (!contem_f(*visitados, prox_no->id)) {
                // getchar();
                if ((distancia[no_atual->id - 1] + aresta->peso) < distancia[aresta->id_alvo - 1]) {
                    distancia[aresta->id_alvo - 1] = distancia[no_atual->id - 1] + aresta->peso;
                    insere_f(visitados, prox_no);
                    predecessor[aresta->id_alvo - 1] = no_atual->id;
                }
            }
            aresta = aresta->prox_aresta;
        }
        no_atual = remove_f(visitados);
    } while (no_atual != NULL);
    
    // Deletando a fila visitados
    destroi_f(visitados);
    
    // Inserindo os nós na lista e ordenando
    unsigned int caminho[grafo->numero_de_nos];
    int tamanho_caminho = 0;
    No *atual = encontrar_no_por_id(grafo, d);
    
    while (atual->id != o) {
        caminho[tamanho_caminho++] = atual->id;
        atual = encontrar_no_por_id(grafo, predecessor[atual->id - 1]);
        if (atual == NULL) {
            return resposta;
        }
    }
    caminho[tamanho_caminho++] = o;
    
    // Ordenando o caminho
    for (int i = 0; i < tamanho_caminho - 1; i++) {
        for (int j = i + 1; j < tamanho_caminho; j++) {
            if (caminho[i] > caminho[j]) {
                unsigned int temp = caminho[i];
                caminho[i] = caminho[j];
                caminho[j] = temp;
            }
        }
    }
    
    // Adicionando os nós e arestas ao grafo resposta
    for (int i = 0; i < tamanho_caminho - 1; i++) {
        No *no1 = encontrar_no_por_id(grafo, caminho[i]);
        No *no2 = encontrar_no_por_id(grafo, caminho[i + 1]);
        adicionar_no(&resposta, no1->id, no1->peso);
        adicionar_aresta(&resposta, no1->id, no2->id, distancia[no2->id - 1] - distancia[no1->id - 1]);
    }
    adicionar_no(&resposta, d, distancia[d - 1]);
    
    return resposta;
}


/*======================================================
*                 CAMINHO MÍNIMO - FLOYD
---------------------------------------------------------
* Função: Encontra o caminho mínimo entre dois nós utilizando
*         o algoritmo de Floyd
* Parametros: grafo - ponteiro para o grafo
*             o - Identificador do nó de origem
*             d - Identificador do nó de destino
* Retorno: grafo com o caminho mínimo
======================================================*/
Grafo caminho_Floyd(Grafo *grafo, unsigned int o, unsigned int d ){
    Grafo resposta;
    inicializar_grafo(&resposta);
    resposta.direcionado = grafo->direcionado;
    resposta.arestas_ponderadas = grafo->arestas_ponderadas;

    // Verificação dos nós de origem e destino
    No *no_atual = encontrar_no_por_id(grafo, d);
    if (no_atual == NULL) {
        printf("Identificador de destino nao encontrado no grafo\n");
        return resposta;
    }
    no_atual = encontrar_no_por_id(grafo, o);
    if (no_atual == NULL) {
        printf("Identificador de origem nao encontrado no grafo\n");
        return resposta;
    }

    // Verificações adicionais
    if (o == d) {
        printf("Origem e destino iguais\n");
        return resposta;
    }

    // Montar a matriz de distâncias e predecessores
    float distancia[grafo->numero_de_nos][grafo->numero_de_nos];
    int predecessor[grafo->numero_de_nos][grafo->numero_de_nos];
    
    for (unsigned int lin = 0; lin < grafo->numero_de_nos; lin++) {
        for (unsigned int col = 0; col < grafo->numero_de_nos; col++) {
            if (lin == col) {
                distancia[lin][col] = 0;
                predecessor[lin][col] = lin;
            } else {
                distancia[lin][col] = FLT_MAX;
                predecessor[lin][col] = -1;
            }
        }
    }
    
    No *v_lin = grafo->primeiro;
    Aresta *v_col;
    while (v_lin != NULL) {
        v_col = v_lin->primeira_aresta;
        while (v_col != NULL) {
            distancia[v_lin->id - 1][v_col->id_alvo - 1] = v_col->peso;
            predecessor[v_lin->id - 1][v_col->id_alvo - 1] = v_lin->id - 1;
            v_col = v_col->prox_aresta;
        }
        v_lin = v_lin->proximo_no;
    }
    
    // Algoritmo de Floyd
    for (unsigned int k = 0; k < grafo->numero_de_nos; k++) {
        for (unsigned int i = 0; i < grafo->numero_de_nos; i++) {
            for (unsigned int j = 0; j < grafo->numero_de_nos; j++) {
                if (distancia[i][j] > distancia[i][k] + distancia[k][j]) {
                    distancia[i][j] = distancia[i][k] + distancia[k][j];
                    predecessor[i][j] = predecessor[k][j];
                }
            }
        }
    }

    // Reconstruir o caminho
    if (predecessor[o - 1][d - 1] == -1) {
        return resposta;
    }
    
    // Adicionar o nó de origem
    adicionar_no(&resposta, o, 0);
    No *atual = encontrar_no_por_id(grafo, d);
    
    // Adicionar todos os nós e arestas do caminho
    while (atual->id != o) {
        No *prev = encontrar_no_por_id(grafo, predecessor[o - 1][atual->id - 1] + 1);
        if (prev == NULL) {
            printf("Erro ao encontrar no anterior\n");
            return resposta;
        }
        adicionar_no(&resposta, prev->id, 0);
        adicionar_aresta(&resposta, prev->id, atual->id, distancia[prev->id - 1][atual->id - 1]);
        atual = prev;
    }
    
    // Adicionar o nó de destino
    adicionar_no(&resposta, d, 0);

    return resposta;
}


/*======================================================
*              VERIFICA SE ESTA ENTRE
---------------------------------------------------------
* Função: Verifica se um elemento está entre um vetor
* Parametros: vetor - vetor de inteiros
*             elemento - elemento a ser verificado
* Retorno: 1 se o elemento está no vetor, 0 caso contrário
======================================================*/
int esta_entre(unsigned int* vetor, unsigned int elemento){
     int tam = sizeof(vetor) / sizeof(int);
    for( int i=0;i<tam;i++){
        if (elemento==vetor[i])
            return 1;
    }
    return 0;
}

/*======================================================
*        ÁRVORE GERADORA MÍNIMA - KRUSKAL
---------------------------------------------------------
* Função: Encontra a árvore geradora mínima de um grafo
*         utilizando o algoritmo de Kruskal
* Parametros: grafo - ponteiro para o grafo
* Retorno: Grafo - árvore geradora mínima
======================================================*/
Grafo AGM_Kruskal(Grafo grafo){
    int n_nos = grafo.numero_de_nos;
    //Como detectar se o grafo não é
    if (grafo.numero_de_nos<3){
        return grafo;
    }
    //subs é um grafo que representa as subárvores
    Grafo subs;
    inicializar_grafo(&subs);
    //AGM é para grafos não orientados
    if (grafo.direcionado){
        printf("\tFalha. Esse eh um algoritmo para grafos nao direcionados\n");

        return subs;
    }
    subs.arestas_ponderadas = grafo.arestas_ponderadas;
    subs.nos_ponderados = grafo.nos_ponderados;
    
    //Copia os nós de grafo para subs
    No *no = grafo.primeiro;
    //Cria a lista de arestas ordenadas
    Lista *lista = cria_l(grafo);

    while (no!=NULL){
        adicionar_no(&subs,no->id, no->peso);
        subs.numero_de_nos++;
        no = no->proximo_no;
    }
    int contador = 0;
    No_l *aresta;
    Grafo fecho_o;
    Grafo fecho_d;

    while ((contador<n_nos - 1) && (lista->tam>0)){
        aresta = remover_l(lista);
        fecho_o = caminho_Dijkstra(&subs, aresta->origem,aresta->destino);

        if (fecho_o.numero_de_nos==0 && fecho_d.numero_de_nos==0){
            adicionar_aresta(&subs,aresta->origem, aresta->destino,aresta->peso);
            adicionar_aresta(&subs,aresta->destino, aresta->origem,aresta->peso);
            contador++;
        }
    }
    if (contador<n_nos - 1){
        destruir_grafo(&subs);
        inicializar_grafo(&subs);
        printf("\tFalha! Esse eh um algoritmo para grafos conexos\n");
    }
    return subs;
}


/*======================================================
*        ÁRVORE GERADORA MÍNIMA - PRIM
---------------------------------------------------------
* Função: Encontra a árvore geradora mínima de um grafo
*         utilizando o algoritmo de Prim
* Parametros: grafo - ponteiro para o grafo
* Retorno: Grafo - árvore geradora mínima
======================================================*/
Grafo AGM_Prim(Grafo grafo){
    if (grafo.numero_de_nos<3){
        return grafo;
    }
    //subs é um grafo que representa as subárvores
    Grafo subs;
    inicializar_grafo(&subs);
    //AGM é para grafos não orientados
    if (grafo.direcionado){
        printf("\tFalha. Esse é um algoritmo para grafos não direcionados.\n");
        return subs;
    }
    subs.arestas_ponderadas = grafo.arestas_ponderadas;
    subs.nos_ponderados = grafo.nos_ponderados;

    //Insere o 1o nó na AGM
    No *no = grafo.primeiro;
    adicionar_no(&subs,no->id, no->id);
    subs.numero_de_nos++;
    
    //Cria a lista de arestas ordenadas
    Lista *lista = cria_l(subs);
    
    //Repetir até inserir todos os nós:
    Aresta *aresta;
    while (subs.numero_de_nos<grafo.numero_de_nos && no!=NULL) {
        //Inserir todas as arestas do nó atual (franja)
        aresta = no->primeira_aresta;
        while (aresta!=NULL){
            insere_l(lista,*no,*aresta);
            aresta = aresta->prox_aresta;
        }
        //Procurar na franja, a menor aresta que inclua um nó que ainda não está no AGM
        if (lista->tam==0){
            //Grafo não é conexo
            break;
        }
        No_l *franja;
        while(lista->tam>0){
            franja = remover_l(lista);
            no = encontrar_no_por_id(&subs,franja->destino);
            if (no==NULL){
                adicionar_no(&subs,franja->destino,franja->destino);
                subs.numero_de_nos++;
                adicionar_aresta(&subs,franja->origem,franja->destino,franja->peso);
                adicionar_aresta(&subs,franja->destino,franja->origem,franja->peso);
                subs.numero_de_arestas++;
                no = encontrar_no_por_id(&grafo,franja->destino);
                break;
            }
            no=NULL;
        }
    }
    if (subs.numero_de_nos<grafo.numero_de_nos){
        destruir_grafo(&subs);
        inicializar_grafo(&subs);
        printf("\tFalha! Esse eh um algoritmo para grafos conexos\n");
    }
    return subs;
}


/*======================================================
*              VERTICES DE ARTICULACAO
---------------------------------------------------------
* Função: Encontra os vértices de articulação de um grafo
* Parametros: grafo - ponteiro para o grafo
*             no_atual - nó atual
*             visitado - vetor de visitados
*             disc - vetor de descobertas
*             low - vetor de low
*             pai - vetor de pais
*             articulacao - vetor de articulações
* Retorno: void
======================================================*/
void articulacoes_DFS(Grafo *grafo, No *no_atual, bool visitado[], int disc[], int low[], unsigned int pai[], bool articulacao[]) {
    static int tempo = 0;
    int filhos = 0;

    visitado[no_atual->id] = true;
    disc[no_atual->id] = low[no_atual->id] = ++tempo;

    Aresta *aresta = no_atual->primeira_aresta;
    while (aresta != NULL) {
        No *v = encontrar_no_por_id(grafo, aresta->id_alvo);

        if (!visitado[v->id]) {
            filhos++;
            pai[v->id] = no_atual->id;
            articulacoes_DFS(grafo, v, visitado, disc, low, pai, articulacao);

            low[no_atual->id] = (low[no_atual->id] < low[v->id]) ? low[no_atual->id] : low[v->id];

            if (pai[no_atual->id] == UINT_MAX && filhos > 1) {
                articulacao[no_atual->id] = true;
            }
            if (pai[no_atual->id] != UINT_MAX && low[v->id] >= disc[no_atual->id]) {
                articulacao[no_atual->id] = true;
            }
        } else if (v->id != pai[no_atual->id]) {
            low[no_atual->id] = (low[no_atual->id] < disc[v->id]) ? low[no_atual->id] : disc[v->id];
        }

        aresta = aresta->prox_aresta;
    }
}


/*======================================================
*              ENCONTRA NÓS DE ARTICULAÇÃO
---------------------------------------------------------
* Função: Encontra os vértices de articulação de um grafo
* Parametros: grafo - ponteiro para o grafo
* Retorno: void
======================================================*/
void encontra_nos_articulacao(Grafo *grafo) {
    bool visitado[grafo->numero_de_nos];
    int disc[grafo->numero_de_nos];
    int low[grafo->numero_de_nos];
    unsigned int *pai = (unsigned int *)malloc(grafo->numero_de_nos * sizeof(unsigned int));
    bool articulacao[grafo->numero_de_nos];

    // inicializa os vetores
    for (size_t i = 0; i < grafo->numero_de_nos; i++) {
        visitado[i] = false;
        articulacao[i] = false;
        pai[i] = UINT_MAX; // Inicializa pai com um valor que indica ausência de pai
    }

    No *atual = grafo->primeiro;
    while (atual != NULL) {
        if (!visitado[atual->id]) {
            articulacoes_DFS(grafo, atual, visitado, disc, low, pai, articulacao);
        }
        atual = atual->proximo_no;
    }

    printf("Vertices de articulacao: ");
    for (size_t i = 0; i < grafo->numero_de_nos; i++) {
        if (articulacao[i]) {
            printf("%u ", i);
        }
    }
    printf("\n");

    free(pai); // Não se esqueça de liberar a memória alocada
}


/*======================================================
*             PROPRIEDADES DO GRAFO
*---------------------------------------------------------
* Função: Calcula e exibe as propriedades de um grafo: raio,
*         diâmetro, centro e periferia
* Parametros: grafo - ponteiro para o grafo
* Retorno: void
======================================================*/
void calcular_propriedades_grafo(Grafo *grafo) {
    unsigned int n = grafo->numero_de_nos;

    // inicializar as matrizes de dist e predecessor
    float distancia[n][n];
    int predecessor[n][n];

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            if (i == j) {
                distancia[i][j] = 0;
                predecessor[i][j] = i;
            } else {
                distancia[i][j] = INF;
                predecessor[i][j] = -1;
            }
        }
    }

    No *v_lin = grafo->primeiro;
    Aresta *v_col;

    // preenche as matrizes de dist e predecessor
    while (v_lin != NULL) {
        v_col = v_lin->primeira_aresta;
        while (v_col != NULL) {
            distancia[v_lin->id - 1][v_col->id_alvo - 1] = v_col->peso;
            predecessor[v_lin->id - 1][v_col->id_alvo - 1] = v_lin->id - 1;
            v_col = v_col->prox_aresta;
        }
        v_lin = v_lin->proximo_no;
    }

    // algoritmo de Floyd
    for (unsigned int k = 0; k < n; k++) {
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = 0; j < n; j++) {
                // Se a distância de i a j for maior que a distância de i a k + k a j, atualiza
                if (distancia[i][j] > distancia[i][k] + distancia[k][j]) {
                    distancia[i][j] = distancia[i][k] + distancia[k][j];
                    predecessor[i][j] = predecessor[k][j];
                }
            }
        }
    }

    // inicializar variaveis para raio, diâmetro, excentricidade
    float raio = INF;
    float diametro = 0;
    float excentricidade[n];

    for (unsigned int i = 0; i < n; i++) {
        excentricidade[i] = 0;
        for (unsigned int j = 0; j < n; j++) {
            // se a distância de i a j for menor que infinito, atualiza a excentricidade
            if (distancia[i][j] < INF) {
                if (excentricidade[i] < distancia[i][j]) {
                    excentricidade[i] = distancia[i][j];
                }
            }
        }
        if (raio > excentricidade[i]) {
            raio = excentricidade[i];
        }
        if (diametro < excentricidade[i]) {
            diametro = excentricidade[i];
        }
    }

    // exibe as propriedades do grafo
    printf("\nRaio: %.2f\n", raio);
    printf("Diametro: %.2f\n", diametro);

    printf("Centro:");
    for (unsigned int i = 0; i < n; i++) {
        if (excentricidade[i] == raio) {
            printf(" %u ", i + 1);
        }
    }

    printf("\nPeriferia:");
    for (unsigned int i = 0; i < n; i++) {
        if (excentricidade[i] == diametro) {
            printf(" %u ", i + 1);
        }
    }
    printf("\n");
}


/*======================================================
*              ADICIONA ARESTA DE RETORNO
*---------------------------------------------------------
* Função: Adiciona uma aresta de retorno em um grafo
* Parametros: entrada - ponteiro para o grafo de entrada
*             saida - ponteiro para o grafo de saída
*             id - identificador da aresta
* Retorno: void
======================================================*/
void adiciona_aresta_de_retorno(Grafo *entrada, Grafo *saida, unsigned int id){
    No* no_saida = saida->primeiro;
    No* no_entrada;
    Aresta* aresta;
    while (no_saida!=NULL){
        no_entrada = encontrar_no_por_id(entrada,no_saida->id);
        if (no_entrada==NULL){
            no_saida = no_saida->proximo_no;
            continue; // para evitar algum erro caso a entrada não tenha o nó
        }
        aresta = no_entrada->primeira_aresta;
        while (aresta!=NULL){
            if (aresta->id_alvo==id){
                adicionar_aresta(saida,id,no_saida->id,-1); // -1 para indicar que é uma aresta de retorno
                return;
            }
            aresta = aresta->prox_aresta;
        }
        no_saida = no_saida->proximo_no;
    }
}


/*======================================================
*              RECURSÃO DO ENCAMINHAMENTO
*---------------------------------------------------------
* Função: Realiza a recursão do encaminhamento
* Parametros: entrada - ponteiro para o grafo de entrada
*             saida - ponteiro para o grafo de saída
*             no - nó atual
* Retorno: void
======================================================*/
void recursao_do_encaminhamento(Grafo *entrada,Grafo *saida, No *no){
    no->visitado = 1;
    adicionar_no(saida, no->id, no->id);
    saida->numero_de_nos++;
    No *atual;
    Aresta *aresta = no->primeira_aresta;
    while (aresta!=NULL){
        atual = encontrar_no_por_id(entrada,aresta->id_alvo);
        if (atual->visitado==0){
            recursao_do_encaminhamento(entrada, saida, atual);
            adicionar_aresta(saida,no->id, aresta->id_alvo, aresta->peso);
            adiciona_aresta_de_retorno(entrada,saida, aresta->id_alvo);
        }
        aresta = aresta->prox_aresta;
    }
}


/*======================================================
*              CAMINHAMENTO EM PROFUNDIDADE
*---------------------------------------------------------
* Função: Realiza o caminhamento em profundidade
* Parametros: grafo - ponteiro para o grafo
*             o - nó de origem
* Retorno: Grafo - grafo com o caminhamento em profundidade
======================================================*/
Grafo caminhamento_Profundidade(Grafo *grafo, unsigned int o){
    No *tmp_iterator = grafo->primeiro; // iterador para percorrer os nós
    while (tmp_iterator != NULL) {
        tmp_iterator->visitado = 0; // inicializa todos os vertices como não visitados
        tmp_iterator = tmp_iterator->proximo_no;
    }
   
    Grafo resposta;
    inicializar_grafo(&resposta);

    resposta.direcionado = 1;
    resposta.arestas_ponderadas = 1;
    
    No *origem = encontrar_no_por_id(grafo,o);

    recursao_do_encaminhamento(grafo, &resposta, origem);
    return resposta;
}


// =============================================================================================================================================================================
//                                                                        ALGORITMOS GULOSOS
// =============================================================================================================================================================================

Grafo* copia_grafo(Grafo grafo){
    Grafo* novo = (Grafo *)malloc(sizeof(Grafo));
    
    //Copia o grafo para subs:
    novo = (Grafo *)malloc(sizeof(Grafo));
    novo->numero_de_nos = 0;
    novo->direcionado = 0;
    novo->arestas_ponderadas = 0;
    novo->nos_ponderados = 1;
    novo->primeiro = NULL;
    novo->ultimo = NULL;
    No* aux = grafo.primeiro;
    for(int i=0;i<grafo.numero_de_nos;i++){
        adicionar_no(novo, aux->id, aux->peso);
        novo->numero_de_nos++;
        aux = aux->proximo_no;
    }
    aux = grafo.primeiro;
    for(int i=0;i<grafo.numero_de_nos;i++){
        Aresta* aresta = aux->primeira_aresta;
        for(int j=0;j<aux->numero_de_arestas;j++){
            adicionar_aresta(novo,aux->id, aresta->id_alvo, aresta->peso);
            aresta = aresta->prox_aresta;
        }
        aux = aux->proximo_no;
    }

    return novo;
}

int inicializar_grafo_MGGPP(Grafo *grafo, FILE *file) {
    int p;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char line[1024];
    int i = 0;

    // Ler o parâmetro 'p'
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "param p := %d ;", &p) == 1) {
            break;
        }
    }


    // Ler o conjunto V (vertices)
    grafo->primeiro = grafo->ultimo = NULL;
    grafo->numero_de_arestas = 0;
    int nos[grafo->numero_de_nos];


    // Ler os pesos 'w'
    int vertex, weight;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "param w :=")) {
            while (fgets(line, sizeof(line), file) && !strstr(line, ";")) {
                sscanf(line, "%d %d", &vertex, &weight);
                nos[vertex-1] = weight;
            }
            break;
        }
    }

    for (int i=0;i<grafo->numero_de_nos;i++){
        adicionar_no(grafo,i+1,nos[i]);
    }
    
    // Ler as arestas 'E'
    
    i = 0;
    int id_no_1, id_no_2;
    char *ptr;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "set E :=")) {
            while (fgets(line, sizeof(line), file) && !strstr(line, ";")) {
                // Ponteiro para percorrer a linha
                ptr = line;
                // Ler múltiplos pares numa linha
                while (1){
                    ptr = strchr(ptr + 1, '(');
                    if (ptr == NULL) {
                        break; // Não há mais pares na linha
                    }
                    sscanf(ptr, " (%d,%d)", &id_no_1, &id_no_2) ;
                    adicionar_aresta(grafo, id_no_1, id_no_2, 0);
                    adicionar_aresta(grafo, id_no_2, id_no_1, 0);

                    // Avançar o ponteiro para o próximo par
                    
                }
            }
        }
    }
    
    return p;

}

void chute_inicial(Divisao *divisao, Fila* fila, Grafo* grafo, int p){

    //Percorre todos o grafo para criar a lista de prioridades
    Lista *ordena_arestas = cria_gap(*grafo, '<');
    
    //Cria uma divisao para guardar os ids dos nós e o subgrafo ao qual eles pertencem (de 1 até n)
    
    //Variáveis que serão utilizadas temporariamente nas duas etapas:
    No_l *menor_a;
    No *origem, *destino;
    
    //Cria a primeira divisão dos subgrafos
    while (divisao->n_subs<p && !vazia_l(*ordena_arestas)){
        menor_a = remover_l(ordena_arestas);
        if (divisao->sub[menor_a->destino]==0 && divisao->sub[menor_a->destino]==0){
            
            origem = encontrar_no_por_id(grafo, menor_a->origem);
            destino = encontrar_no_por_id(grafo, menor_a->destino);
            
            divisao->n_subs++;
            
            insere_d(divisao,origem,divisao->n_subs);
            insere_d(divisao,destino,divisao->n_subs);

            insere_f(fila,origem);
            insere_f(fila,destino);
        }
    }

}

Divisao* procedimento_construtivo(Grafo *grafo, int p){

    if (grafo == NULL || grafo->numero_de_nos <= 0) {
        fprintf(stderr, "Erro: grafo não inicializado ou inválido.\n");
        return NULL; // Retorna NULL em caso de erro
    }

    Divisao* divisao = NULL;
    if (p >= grafo->numero_de_nos/2){
        return divisao;
    }

    //cria uma fila de nós para a franja
    Fila *analisar = cria_f();

    divisao = cria_d((int)grafo->numero_de_nos, p, 0);

    if (divisao == NULL) {
        fprintf(stderr, "Erro: não foi possível criar a divisao.\n");
        destroi_f(analisar); // Libere a fila antes de retornar
        return NULL; // Retorna NULL em caso de erro
    }

    chute_inicial(divisao, analisar, grafo,p);
    int inseridos = analisar->tam;
    
    Lista *lc = cria_vazia_l();
    if (lc == NULL) {
        fprintf(stderr, "Erro: não foi possível criar a lista.\n");
        destruir_d(divisao); // Libere divisao antes de retornar
        destroi_f(analisar); // Libere a fila antes de retornar
        return NULL; // Retorna NULL em caso de erro
    }
    
    //inserindo os outros nós
    No *no;     //cada nó na fila analisar
    Aresta *a;  //cada aresta do nó.
    
    No *novo; //novo nó a ser analisado
    No_l *menor; //menor nó removido
    srand((int)time(NULL));
    int fim_da_fila;

    while (inseridos < grafo->numero_de_nos) {
        // Analisar toda a franja
        fim_da_fila = analisar->tam;
        
        for (int i = 0; i < fim_da_fila; i++) {
            no = remove_f(analisar);
            
            // Verificar se o nó removido tem arestas
            if (no->primeira_aresta == NULL) {
                fprintf(stderr, "Aviso: o nó %d não possui arestas.\n", no->id);
                continue;  // Pula para o próximo nó se não houver arestas
            }

            a = no->primeira_aresta;
            
            // Iterar sobre as arestas do nó
            while (a != NULL) {
                // Verificar se a aresta atual é nula
                if (a == NULL) {
                    fprintf(stderr, "Erro: ponteiro 'a' é nulo na aresta do nó %d.\n", no->id);
                    exit(1);  // Saída segura, pois há um erro crítico
                }

                // Verificar se o grafo está inicializado corretamente
                if (grafo == NULL) {
                    fprintf(stderr, "Erro: grafo não inicializado.\n");
                    exit(2);  // Saída segura, pois o grafo não foi inicializado
                }

                // Encontrar o nó de destino da aresta atual
                novo = encontrar_no_por_id(grafo, a->id_alvo);
                
                if (novo == NULL) {
                    fprintf(stderr, "Erro: nó com ID %d não encontrado no grafo.\n", a->id_alvo);
                    continue;  // Pula para a próxima iteração se o nó não for encontrado
                }

                // Se o nó alvo ainda não está no subgrafo, insere o gap
                if (divisao->sub[novo->id] == 0) {
                    insere_gap(lc, no->id, novo->id, fabs(no->peso - novo->peso), '<');
                }
                
                // Avançar para a próxima aresta
                a = a->prox_aresta;
            }
        }

    // Verificar se a lista de candidatos (lc) está vazia
    if (lc->tam == 0 && inseridos < grafo->numero_de_nos) {
        // Caso não seja possível chegar a todos os subgrafos, retornar NULL
        fprintf(stderr, "Erro: Não é possível chegar em %d subgrafos com alpha atual. Tente novamente aumentando o alpha.\n", p);
        destruir_d(divisao);
        return NULL;
    }

    // Insere no subgrafo o nó com o menor peso
    menor = remover_l(lc);
    novo = encontrar_no_por_id(grafo, menor->destino);
    
    if (novo == NULL) {
        fprintf(stderr, "Erro: nó com ID %d não encontrado ao tentar inserir no subgrafo.\n", menor->destino);
        continue;  // Pula a iteração se o nó não for encontrado
    }

    insere_d(divisao, novo, divisao->sub[menor->origem]);
    insere_f(analisar, novo);
    inseridos++;
}

    return divisao;
}

Divisao* procedimento_construtivo_adaptativo(Grafo *grafo, int p, float alpha){

    Divisao* divisao = NULL;
    if (p >= grafo->numero_de_nos/2){
        return divisao;
    }

    //cria uma fila de nós para a franja
    Fila *analisar = cria_f();
    divisao = cria_d((int)grafo->numero_de_nos, p, 0);

    chute_inicial(divisao, analisar, grafo,p);
    int inseridos = analisar->tam;
    
    Lista *lc = cria_vazia_l();
    
    //inserindo os outros nós
    No *no;     //cada nó na fila analisar
    Aresta *a;  //cada aresta do nó.
    
    No *novo; //novo nó a ser analisado
    No_l *menor; //menor nó removido
    int range_alpha;
    srand((int)time(NULL));
    int fim_da_fila;
    int cont_ar = inseridos;
    while (inseridos < grafo->numero_de_nos) {
        // Analisar toda a franja
        fim_da_fila = analisar->tam;
        for (int i = 0; i < fim_da_fila; i++) {
            no = remove_f(analisar);
            a = no->primeira_aresta;

            while (a != NULL) {
                novo = encontrar_no_por_id(grafo, a->id_alvo);
                
                if (novo == NULL) {
                    fprintf(stderr, "Erro: novo é nulo para id_alvo %d.\n", a->id_alvo);
                    a = a->prox_aresta;
                    continue; // Ignora se o nó não for encontrado
                }

                // Se a->id_alvo não está em nenhum subgrafo
                if (divisao->sub[novo->id] == 0) {
                    insere_gap(lc, no->id, novo->id, fabs(no->peso - novo->peso), '<');
                }
                a = a->prox_aresta; // Prossiga para a próxima aresta
            }
        }

        if (lc->tam == 0 && inseridos < grafo->numero_de_nos) {
            destruir_d(divisao);
            return NULL; // Retorna NULL em caso de erro
        }

        // Insere no divisao e na fila, o nó com o menor peso.
        range_alpha = rand() % (int)(lc->tam * alpha);
        menor = remover_pos_l(lc, range_alpha);
        novo = encontrar_no_por_id(grafo, menor->destino);
        
        if (novo == NULL) {
            fprintf(stderr, "Erro: novo é nulo para menor->destino %d.\n", menor->destino);
            continue; // Trate a situação
        }

        insere_d(divisao, novo, divisao->sub[menor->origem]);
        insere_f(analisar, novo);
        inseridos++;
        cont_ar++;
    }
    
    return divisao;
}

Resultado* iteracoes_construtivo(Grafo *grafo, int p,int iteracoes){
    Resultado *global;
    global = (Resultado*)malloc(sizeof(Resultado));
    inicializar_r(global);
    Divisao *divisao;
    clock_t inicio, fim;
    float tempo;
    for(int i=0;i<iteracoes;i++){
        inicio = clock();
        divisao = procedimento_construtivo(grafo,p);
        fim = clock();
        tempo = (float)(fim - inicio)*1000/ CLOCKS_PER_SEC;
        atualizar_r(global, divisao, tempo, iteracoes);
    }
    global->gap_soma /=iteracoes;
    global->tempo_soma /=iteracoes;
    return global;
}
Resultado* iteracoes_construtivo_adaptativo(Grafo *grafo, int p,int iteracoes,float alpha){
    Resultado *global;
    global = (Resultado*)malloc(sizeof(Resultado));
    inicializar_r(global);
    Divisao *divisao;
    clock_t inicio, fim;
    float tempo;
    for(int i=0;i<iteracoes;i++){
        inicio = clock();
        divisao = procedimento_construtivo_adaptativo(grafo,p,alpha);
        fim = clock();
        tempo = (float)(fim - inicio)*1000/ CLOCKS_PER_SEC;
        atualizar_r(global, divisao, tempo, iteracoes);
    }
    global->gap_soma /=(iteracoes-global->falha);
    global->tempo_soma /=(iteracoes-global->falha);
    return global;
}
int escolhe_alpha(float probs[5]){
    srand(time(NULL));
    float chute = ((float)(rand()%100) / 100 );
    float prob_acumulada = 0;
    for (int i=0;i<4;i++){
        prob_acumulada+=probs[i];
        if (chute<=prob_acumulada){
            return i;
        }
    }
    return 4;
    
}
void atualiza_probabilidades(float probs[5],float somas[5],int freqs[5],float melhor_solucao){
    float q[5];
    float soma = 0;
    for (int i=0;i<5;i++){
        q[i]=melhor_solucao/(somas[i]/freqs[i]);
        soma+=q[i];
    }
    for (int i=0;i<5;i++){
        probs[i] = q[i]/soma;
        freqs[i]=1;
        somas[i]=1;
    }
    
}

Resultado* iteracoes_construtivo_adaptativo_reativo(Grafo *grafo, int p,int iteracoes,int bloco, float *alphas){
    float probs[5] ={0.2, 0.2, 0.2, 0.2, 0.2};
    float somas[5] ={1,1,1,1,1};
    int freqs[5] = {1,1,1,1,1};
    Resultado *global;
    global = (Resultado*)malloc(sizeof(Resultado));
    inicializar_r(global);
    Divisao *divisao;
    clock_t inicio, fim;
    float tempo;
    int alpha_index;
    for(int i=1;i<=iteracoes;i++){
        inicio = clock();
        if (i%bloco==0){
            atualiza_probabilidades(probs,somas,freqs,global->melhor_gap);
        }
        alpha_index = escolhe_alpha(probs);
        divisao = procedimento_construtivo_adaptativo(grafo,p,alphas[alpha_index]);
        if (divisao!=NULL){
            freqs[alpha_index]++;
            somas[alpha_index]+=gap_global(*divisao);
        }
        fim = clock();
        tempo = (double)(fim - inicio)*1000/ CLOCKS_PER_SEC;
        atualizar_r(global, divisao, tempo, iteracoes);
    }
    global->gap_soma /=(iteracoes-global->falha);
    global->tempo_soma /=(iteracoes-global->falha);

    return global;
}
