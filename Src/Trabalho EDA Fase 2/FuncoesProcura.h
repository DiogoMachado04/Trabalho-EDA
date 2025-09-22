/**

    @file      FuncoesProcura.h
    @brief     Ficheiro .h com as funcoes de procura do trabalho
    @details   ~
    @author    Diogo Machado 26042
    @date      22.05.2024
    @copyright © Diogo Machado, 2023. All right reserved.

**/
#pragma once
#include "Grafos.h"
#include "Stack.h"

/**
    @brief  Funcao Depth First Traversal que passa por todos os vertices do grafo em profundidade
    @param  grafo  - grafo guardado em memoria
    @param  codIni - codigo do vertice onde comeca a procura
    @retval        - Stack com os registos onde se passou para a procura
**/
Stack* DepthFirstTraversal(Grafo* grafo, int codIni);
/**
    @brief Funcao que imprime no ecra o vertice da Depth First search recursiva
    @param id - id do vertice que se pretende imprimir
**/
void ProcessaVertice(int id);
/**
    @brief  Funcao Depth First Traversal que passa por todos os vertices do grafo em profundidade
    @param  auxVert - lista de vertices do grafo
    @param  origem  - onde comeca a procura
    @param  dest    - destino da procura
    @retval         - retorna sucesso ou insucesso de encontrar o vertice
**/
bool DepthFirstSearchRec(Vertice* auxVert, int origem, int dest);
/**
    @brief  Calcula a soma dos pesos das adjacencias entre dois vertices
    @param  grafo   - grafo guardado em memoria
    @param  codIni  - codigo do vertice onde se comeca a pesquisa
    @param  codDest - codigo do vertice onde se pretende chegar
    @retval         - valor da soma dos pesos
**/
int CalculoSomaEntreDoisVertices(Grafo* grafo, int codIni, int codDest);