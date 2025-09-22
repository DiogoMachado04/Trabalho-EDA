/**

    @file      GereGrafos.h
    @brief     Ficheiro .h que contem funcoes de gerir grafos
    @details   ~
    @author    Diogo Machado 26042
    @date      8.05.2024
    @copyright © Diogo Machado, 2023. All right reserved.

**/
#pragma once
#include "Grafos.h"

#pragma region VERTICES
/**
    @brief  Cria espaco em memoria para um vertice e coloca valores nas suas variáveis
    @param  cod - numero de codigo do vertice
    @retval     - vertice criado
**/
Vertice* CriaVertice(int cod);
/**
    @brief  Insere vertice novo na lista ligada dos vertices
    @param  inicio - inicio da lista dos vertices
    @param  novo   - vertice novo que se pretende introduzir na lista
    @retval        - inicio da lista de vertices
**/
Vertice* InsereVertice(Vertice* inicio, Vertice* novo);
#pragma endregion

#pragma region ADJACENCIAS
/**
    @brief  Cria espaco em memoria para uma adjacencia e coloca valores nas suas variaveis
    @param  cod  - numero de codigo do vertice adjacente
    @param  peso - peso da adjacencia
    @retval      - adjacencia criada
**/
Adjacencia* CriaAdjacencia(int cod, int peso);
/**
    @brief  Insere adjacencia nova na lista de adjacencias
    @param  inicio - inicio da lista de adjacencias
    @param  nova   - nova adjacencia que se pretende colocar na lista
    @retval        - lista de adjacencias
**/
Adjacencia* InsereAdjacencia(Adjacencia* inicio, Adjacencia* nova);
#pragma endregion

#pragma region GRAFOS
/**
    @brief  Insere lista de adjacencias no vertice correspondente
    @param  vertice   - vertice do grafo que pretendemos colocar as adjacencias
    @param  inicioAdj - lista de adjacentes do vertice
    @retval           - vertice com as adjacencias colocadas
**/
Vertice* InsereAdjacenciaVertice(Vertice* vertice, Adjacencia* inicioAdj);
/**
    @brief  Cria memoria para o grafo e introduz os valores nas variaveis
    @param  inicioVert - inicio da lista dos vertices
    @param  numVert    - numero de vertices do grafo
    @retval            - grafo com valores nas variaveis
**/
Grafo* CriaGrafo(Vertice* inicioVert, int numVert);
/**
    @brief  Limpa memoria
    @param  grafo - grafo guardado em memoria
    @retval       - Resultado da funcao
**/
int LimpaGrafo(Grafo* grafo);
/**
    @brief  Le ficheiro CSV com as informacoes do grafo
    @param  filename - nome do ficheiro
    @retval          - grafo com as informacoes lidas do ficheiro
**/
Grafo* LeFicheiroGrafo(char* filename);
/**
    @brief  Funcao que mostra grafo na linha de comandos
    @param  grafo - grafo guardado em memoria
    @retval       - Resultado da funcao
**/
int MostraGrafo(Grafo* grafo);
#pragma endregion
