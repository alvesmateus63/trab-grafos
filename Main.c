#include "include/Grafo.h"
#include "include/Defines.h"
#include "include/Divisao.h"
#include <time.h>



int processar_instancia( Grafo *grafo, const char *nome_arquivo, char *diretorio) {
    //Parâmetros fixos:
    char numero[4];
    for (int i=1;i<4;i++){
        numero[i-1]=nome_arquivo[i];
    }
    numero[3]='\0';
    grafo->numero_de_nos = (size_t)atoi(numero);
    grafo->arestas_ponderadas = 0;
    grafo->nos_ponderados = 1;
    grafo->direcionado = 0;
    int p;
    
    printf("\nINSTANCIA: %s\n", nome_arquivo);
    

    
    // Concatena o diretório de instâncias com o nome do arquivo
    char caminho_arquivo[strlen(diretorio) + strlen(nome_arquivo) + 1]; // +1 para o caractere nulo
    strcpy(caminho_arquivo, diretorio);
    strcat(caminho_arquivo, nome_arquivo);
    
    // Abre o arquivo de instância
    FILE *input_file = fopen(caminho_arquivo, "r");
    if (input_file == NULL) {
        printf("Erro ao abrir o arquivo de instancia %s.\n",caminho_arquivo);
        return 0;
    }
    p = inicializar_grafo_MGGPP(grafo, input_file);
    // Fechar os arquivos
    fclose(input_file);
    return p;
}

int principal(char *arquivo_entrada, char *diretorio){
    Grafo grafo;

    // Processa a instância
    int p = processar_instancia(&grafo, arquivo_entrada,diretorio);
    if (!p) return (1);
    
    printf("Algoritmo  Alpha Melhor Gap  Pior Gap Gap Medio  Melhor Tmp    Pior Tmp   Tmp Médio  Falhas\n");

    //printf("      Opcao escolhida: ALGORITMO GULOSO \n");
    Resultado *r1 = iteracoes_construtivo(&grafo,p,1);
    imprimir_r(*r1,1,0);
    
    float alphas[5] = {0.05, 0.10, 0.15, 0.30, 0.50};
    //printf("      Opcao escolhida: ALGORITMO GULOSO RANDOMIZADO\n");
    for (int i=0;i<5;i++){
        Resultado *r2 = iteracoes_construtivo_adaptativo(&grafo,p,1000,alphas[i]);
        imprimir_r(*r2,2,alphas[i]);
    }
   
    //printf("      Opcao escolhida: ALGORITMO GULOSO RANDOMIZADO REATIVO\n");
    Resultado *r3 = iteracoes_construtivo_adaptativo_reativo(&grafo,p,2500,100,alphas);
    imprimir_r(*r3,3,0);
    destruir_grafo(&grafo);
    return 0;
}
// argc: número de argumentos passados para o programa
// argv: vetor de strings com os argumentos passados para o programa
int main(int argc,char **argv)
{
    int count = 0;
    struct dirent *entrada;
    DIR *dp = opendir(argv[1]);

    if (dp == NULL) {
        perror("Erro ao abrir o diretório");
        return -1;
    }

    while ((entrada = readdir(dp)) != NULL) {
        if (strstr(entrada->d_name, ".txt") != NULL) {
            principal(entrada->d_name,argv[1]);
        }
    }

    closedir(dp);
    return count;
    

}
