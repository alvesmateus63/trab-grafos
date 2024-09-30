#ifndef GRAFO_H
#define GRAFO_H

#include "Defines.h"
#include "No.h"
#include "Divisao.h"
#include "Resultado.h"

typedef struct No No;
typedef struct Divisao Divisao;
typedef struct Resultado Resultado;

typedef struct Grafo {
  size_t numero_de_nos;
  size_t numero_de_arestas;
  int direcionado;
  int arestas_ponderadas;
  int nos_ponderados;
  No *primeiro;
  No *ultimo;
  No **adj;

} Grafo;

void inicializar_grafo(Grafo *grafo);
void inicializar_grafo_com_parametros(Grafo *grafo,
                                      int direcionado,
                                      int arestas_ponderadas,
                                      int nos_ponderados);
void inicializar_grafo_com_arquivo(Grafo *grafo, FILE *instance);
int inicializar_grafo_MGGPP(Grafo* grafo, FILE *input_file);
void destruir_grafo(Grafo *grafo);
void remover_no(Grafo *grafo, unsigned int  id_no);
void remover_aresta(Grafo *grafo, unsigned int  id_no_1, unsigned int  id_no_2);
void adicionar_no(Grafo *grafo, unsigned int  id_no, float peso);
void adicionar_aresta(Grafo *grafo, unsigned int  id_no_1, unsigned int  id_no_2, float peso);
void imprimir_grafo_em_arquivo(Grafo *grafo, FILE *output_file);
void imprimir_grafo_console(Grafo *grafo);
void imprimir_grafo(Grafo *grafo);
int conectado(Grafo *grafo, unsigned int  id_no_1, unsigned int  id_no_2);

// Funções adicionadas
void inicializa_graus(Grafo *grafo);
No *encontrar_no_por_id(Grafo *grafo, unsigned int id);
Aresta *encontrar_antecessor_aresta(Grafo *grafo, unsigned int id_origem,
                                    unsigned int id_destino);
void busca_prof(Grafo *grafo);
void busca_prof_visit(Grafo *grafo, unsigned int u, int *visitados,
int *vertices_visitados, int *contador_visitados);
void busca_prof_visit_inversa(Grafo *grafo, unsigned int u, int *visitados,
int *vertices_visitados, int *contador_visitados);
int* fecho_transitivo_direto(Grafo *grafo, unsigned int u);
void fecho_transitivo_indireto(Grafo *grafo, unsigned int u);
int comparar(const void *a, const void *b);
Grafo caminho_Dijkstra(Grafo *grafo, unsigned int o, unsigned int d );
Grafo caminho_Floyd_Warshall(Grafo *grafo, unsigned int o, unsigned int d );
Grafo AGM_Kruskal(Grafo grafo);
Grafo AGM_Prim(Grafo grafo);
int grafo_vazio(Grafo grafo);
Grafo caminhamento_Profundidade(Grafo *grafo, unsigned int o);
Resultado* iteracoes_construtivo(Grafo *grafo, int p,int iteracoes);
Resultado* iteracoes_construtivo_adaptativo(Grafo *grafo, int p,int iteracoes,float alpha);
Resultado* iteracoes_construtivo_adaptativo_reativo(Grafo *grafo, int p,int iteracoes,int bloco,float *alphas);
#endif // GRAFO_H
