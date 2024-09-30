# TEORIA DOS GRAFOS - DCC059 

## Desenvolvido por:
  > Anna Julia de Almeida Lucas

  > Mateus Alves da Silva

### Objetivo do trabalho:
Desenvolver um Tipo Abstrato de Dados - TAD ou uma Classe que represente grafos simples, orientados e não
orientados, ponderados e não ponderados (nos vértices e arestas) e implemente o conjunto de funcionalidades
apresentadas a seguir,

### Funcionalidades:
• O programa deve apresentar em tela a saída para as seguintes funcionalidades definidas nas saídas
conforme os parâmetros:

a) Parâmetro: um ID de um vértice de um grafo direcionado
```
Saída: o fecho transitivo direto deste vértice
```
b) Parâmetro: um ID de um vértice de um grafo direcionado;
```
Saída: o fecho transitivo indireto deste vértice
```
c) Parâmetro: dois IDs de vértices do grafo
```
Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Djkstra
```
d) Parâmetro: dois IDs de vértices do grafo
```
Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Floyd
```
e) Parâmetro: um subconjunto X de vértices do grafo
```
Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim
```
f) Parâmetro: um subconjunto X de vértices do grafo
```
Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal
```
g) Parâmetro: um ID de vértice;
```
Saída: a árvore dada pela ordem de caminhamento em profundidade a partir de nó dado parâmetro,
destacando as arestas de retorno;
```
h) Parâmetro: o próprio grafo acíclico direcionado D;
```
Saída: uma ordenação topológica em D ou a informação de que D não é um grafo acíclico direcionado
```
i) Parâmetro: o grafo (direcionado ou não direcionado) ponderado nas arestas 
```
Saída: O raio, o diâmetro, o centro e a periferia do grafo
```
j) Parâmetro: o grafo não direcionado 
```
Saída: O conjunto de vértices de articulação
```

## EXECUÇÃO 
Para executar o programa:
```
.\grafo <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>->
```

Exemplo de uso:
```
.\grafo 5nD.dat source/output/ 0 1 1 
```

