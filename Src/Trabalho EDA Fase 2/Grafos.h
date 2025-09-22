/**

    @file      Grafos.h
    @brief     Ficheiro .h com a estrutura de dados utilizada para o trabalho prático
    @details   ~
    @author    Diogo Machado 26042
    @date      8.05.2024
    @copyright © Diogo Machado, 2023. All right reserved.

**/
#pragma once
#include <stdbool.h>

#pragma region ESTRUTURA_GRAFO
typedef struct Adjacencia {
    int codVert;                //Codigo do vertice adjacente
    int peso;                   //Peso da adjacencia
    bool visitado;
    struct Adjacencia* next;    //Apontador para outra adjacencia
}Adjacencia;

typedef struct Vertice {
    int cod;                    //Codigo do vertice
    int numAdj;                 //Numero de adjacencias do vertice
    bool visitado;
    Adjacencia* adjacencias;    //Lista de adjacencias do vertice
    struct Vertice* next;       //Apontador para o vertice seguinte
}Vertice;

typedef struct Grafo {
    Vertice* inicio;            //Inicio da lista dos vertices do grafo
    int numVert;                //Numero de vertices do grafo
}Grafo;
#pragma endregion