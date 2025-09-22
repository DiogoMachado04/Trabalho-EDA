/**

    @file      Utilidades.h
    @brief     Ficheiro .h com algumas funcoes para manipular o grafo
    @details   ~
    @author    Diogo Machado 26042
    @date      21.05.2024
    @copyright © Diogo Machado, 2023. All right reserved.

**/
#pragma once
#include "Grafos.h"

#pragma region VERTICES
/**
    @brief  Funcao que verifica se o vertice com um determinado codigo ja existe ou nao
    @param  listaVert - lista de vertices do grafo
    @param  codVert   - codigo do vertice que pretendemos adicionar
    @retval           - se ja existe o vertice ou nao
**/
int VerificaExisteVertice(Vertice* listaVert, int codVert);
/**
    @brief  Funcao que adiciona vertice ao grafo
    @param  grafo   - grafo guardado em memoria
    @param  codVert - codigo do vertice que pretendemos adicionar
    @retval         - grafo guardado em memoria
**/
Grafo* AdicionaVertice(Grafo* grafo, int codVert);
/**
    @brief  Funcao que remove vertice do grafo
    @param  grafo   - grafo guardado em memoria
    @param  codVert - codigo do vertice que se pretende adicionar
    @retval         - grafo guardado em memoria
**/
Grafo* RemoveVertice(Grafo* grafo, int codVert);
/**
    @brief  Funcao que procura vertice com um determinado codigo
    @param  auxVert - lista dos vertices
    @param  cod     - codigo que se pretende encontrar
    @retval         - vertice com o codigo pretendido
**/
Vertice* ProcuraVerticeCod(Vertice* auxVert, int cod);
#pragma endregion

#pragma region ADJACENCIAS
/**
    @brief  Funcao que limpa lista de adjacencias de um determinado vertice
    @param  vert - vertice que se pretende eliminar a lista de adjacencias
    @retval      - resultado da funcao
**/
int LimpaListaAdjacencias(Vertice* vert);
/**
    @brief  Funcao que verifica se existe uma determinada adjacencia na lista de adjacencias
    @param  listaAdj - lista de adjacencias
    @param  codDest  - codigo da adjacencia que se pretende eliminar
    @retval          - resultado da funcao
**/
int VerificaExisteAdjacencia(Adjacencia* listaAdj, int codDest);
/**
    @brief  Funcao que remove uma adjacencia de um determinado vertice
    @param  grafo   - grafo guardado em memoria
    @param  codVert - codigo do vertice que se pretende remover a adjacencia
    @param  codAdj  - codigo da adjacencia que se pretende remover
    @retval         - grafo guardado em memoria
**/
Grafo* RemoveAdjacencia(Grafo* grafo, int codVert, int codAdj);
/**
    @brief  Funcao que adiciona uma determinada adjacencia a vertice destino
    @param  grafo   - grafo guardado em memoria
    @param  codVert - codigo do vertice de partida
    @param  peso    - peso da adjacencia
    @param  codDest - codigo do vertice destino
    @retval         - grafo guardado em memoria
**/
Grafo* AdicionaAdjacencia(Grafo* grafo, int codVert, int peso, int codDest);
#pragma endregion
