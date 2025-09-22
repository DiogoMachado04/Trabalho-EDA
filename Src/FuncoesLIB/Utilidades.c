/**

    @file      Utilidades.c
    @brief     Ficheiro .c com algumas funcoes para manipular o grafo
    @details   ~
    @author    Diogo Machado 26042
    @date      21.05.2024
    @copyright © Diogo Machado, 2023. All right reserved.

**/
#include "Utilidades.h"
#include "Grafos.h"
#include "Constantes.h"
#include "GereGrafos.h"
#include <stdio.h>
#include <stdlib.h>


/**
    @brief  Funcao que verifica se o vertice com um determinado codigo ja existe ou nao
    @param  listaVert - lista de vertices do grafo
    @param  codVert   - codigo do vertice que pretendemos adicionar
    @retval           - se ja existe o vertice ou nao
**/
int VerificaExisteVertice(Vertice* listaVert, int codVert) {
    if (listaVert == NULL) {
        return GRAFO_NAO_EXISTE;
    }

    Vertice* auxVert = listaVert;
    while (auxVert != NULL) {
        if (auxVert->cod == codVert) {
            return VERTICE_JA_EXISTE;
        }
        auxVert = auxVert->next;
    }

    return VERTICE_NAO_EXISTE;
}

/**
    @brief  Funcao que adiciona vertice ao grafo
    @param  grafo   - grafo guardado em memoria
    @param  codVert - codigo do vertice que pretendemos adicionar
    @retval         - grafo guardado em memoria
**/
Grafo* AdicionaVertice(Grafo* grafo, int codVert) {
    if (grafo->inicio == NULL) {
        grafo->inicio = CriaVertice(codVert);
        grafo->numVert++;
        return grafo;
    }

    if (VerificaExisteVertice(grafo->inicio, codVert) == VERTICE_JA_EXISTE) {
        return grafo;
    }

    Vertice* auxVert = grafo->inicio;

    if (grafo->numVert == 1) {
        Vertice* novoVert = CriaVertice(codVert);
        if (auxVert->cod > codVert) {
            novoVert->next = auxVert;
            grafo->inicio = novoVert;
        }
        if(codVert > auxVert->cod){
            auxVert->next = novoVert;
        }
        grafo->numVert++;
        return grafo;
    }
 
    Vertice* proxVert = auxVert->next;
    for (int i = 0; i < grafo->numVert; i++) {
        if (auxVert->cod<codVert && proxVert->cod>codVert) {
            Vertice* novoVert = CriaVertice(codVert);
            novoVert->next = proxVert;
            auxVert->next = novoVert;
            grafo->numVert++;
            return grafo;
        }
        if (proxVert->next != NULL) {
            auxVert = auxVert->next;
            proxVert = auxVert->next;
        }
    }

    Vertice* novoVert = CriaVertice(codVert);
    proxVert->next = novoVert;
    grafo->numVert++;
    return grafo;
}

/**
    @brief  Funcao que remove vertice do grafo
    @param  grafo   - grafo guardado em memoria
    @param  codVert - codigo do vertice que se pretende adicionar
    @retval         - grafo guardado em memoria
**/
Grafo* RemoveVertice(Grafo* grafo, int codVert) { 
    if (grafo == NULL) {
        return GRAFO_NAO_EXISTE;
    }

    if (VerificaExisteVertice(grafo->inicio, codVert) == VERTICE_NAO_EXISTE) {
        return grafo;
    }

    Vertice* auxVert = grafo->inicio;
    if (codVert == 0) {
        Vertice* proxVert = auxVert->next;
        if (auxVert->adjacencias != NULL) {
            LimpaListaAdjacencias(auxVert);
        }
        free(auxVert);
        grafo->inicio = proxVert;
        grafo->numVert--;
        Vertice* vertPointer = grafo->inicio;
        while(vertPointer != NULL){
            grafo = RemoveAdjacencia(grafo, vertPointer->cod, codVert);
            vertPointer = vertPointer->next;
        }
        return grafo;
    }

    if (auxVert->next == NULL) {
        if (auxVert->adjacencias != NULL) {
            LimpaListaAdjacencias(auxVert);
        }
        free(auxVert);
        grafo->numVert--;
        return grafo;
    }

    Vertice* antVert = auxVert;
    auxVert = auxVert->next;
    if (antVert->cod == codVert) {
        if (auxVert->adjacencias != NULL) {
            LimpaListaAdjacencias(auxVert);
        }
        free(antVert);
        grafo->inicio = auxVert;
        grafo->numVert--;
        Vertice* vertPointer = grafo->inicio;
        while (vertPointer != NULL) {
            grafo = RemoveAdjacencia(grafo, vertPointer->cod, codVert);
            vertPointer = vertPointer->next;
        }
        return grafo;
    }

    while (auxVert->cod != codVert) {
        auxVert = auxVert->next;
        antVert = antVert->next;
    }
    
    if (auxVert->adjacencias != NULL) {
        LimpaListaAdjacencias(auxVert);
    }
    
    antVert->next = auxVert->next;
    free(auxVert);
    grafo->numVert--;
    Vertice* vertPointer = grafo->inicio;
    while (vertPointer != NULL) {
        grafo = RemoveAdjacencia(grafo, vertPointer->cod, codVert);
        vertPointer = vertPointer->next;
    }
    return grafo;
}

/**
    @brief  Funcao que limpa lista de adjacencias de um determinado vertice
    @param  vert - vertice que se pretende eliminar a lista de adjacencias 
    @retval      - resultado da funcao
**/
int LimpaListaAdjacencias(Vertice* vert) {  
    if (vert == NULL) {
        return LISTA_NAO_EXISTE;
    }

    Adjacencia* auxAdj = vert->adjacencias;
    if (auxAdj->next == NULL) {
        free(auxAdj);
    }
    
    while (auxAdj->next != NULL) {
        Adjacencia* proxAdj = auxAdj->next;
        free(auxAdj);
        auxAdj = proxAdj;
    }
    free(auxAdj);
    return SUCESSO;
}

/**
    @brief  Funcao que verifica se existe uma determinada adjacencia na lista de adjacencias
    @param  listaAdj - lista de adjacencias
    @param  codDest  - codigo da adjacencia que se pretende eliminar
    @retval          - resultado da funcao
**/
int VerificaExisteAdjacencia(Adjacencia* listaAdj, int codDest) {
    if (listaAdj == NULL) {
        return LISTA_NAO_EXISTE;
    }
    Adjacencia* auxAdj = listaAdj;
    while (auxAdj != NULL) {
        if (auxAdj->codVert == codDest) {
            return EXISTE_ADJACENCIA;
        }
        auxAdj = auxAdj->next;
    }
    return NAO_EXISTE_ADJACENCIA;   
}

/**
    @brief  Funcao que remove uma adjacencia de um determinado vertice
    @param  grafo   - grafo guardado em memoria
    @param  codVert - codigo do vertice que se pretende remover a adjacencia
    @param  codAdj  - codigo da adjacencia que se pretende remover
    @retval         - grafo guardado em memoria
**/
Grafo* RemoveAdjacencia(Grafo* grafo, int codVert, int codAdj) {
    if (grafo == NULL) {
        return GRAFO_NAO_EXISTE;
    }
    if (VerificaExisteVertice(grafo->inicio, codVert) == VERTICE_NAO_EXISTE) {
        return grafo;
    }
    
    Vertice* auxVert = grafo->inicio;
    while (auxVert->cod != codVert) {
        auxVert = auxVert->next;
    }

    if (VerificaExisteAdjacencia(auxVert->adjacencias, codAdj) == NAO_EXISTE_ADJACENCIA) {
        return grafo;
    }

    Adjacencia* auxAdj = auxVert->adjacencias;
    if (auxAdj->next == NULL) {
        free(auxAdj);
        auxVert->numAdj--;
        return grafo;
    }
    
    Adjacencia* antAdj = auxAdj;
    auxAdj = auxAdj->next;
    if (antAdj->codVert == codAdj) {
        auxVert->adjacencias = auxAdj;
        auxVert->numAdj--;
        free(antAdj);
        return grafo;
    }

    while (auxAdj->codVert != codAdj && auxAdj->next != NULL) {
        antAdj = auxAdj;
        auxAdj = auxAdj->next;
    }
    antAdj->next = auxAdj->next;
    free(auxAdj);
    auxVert->numAdj--;
    return grafo;
}

/**
    @brief  Funcao que adiciona uma determinada adjacencia a vertice destino
    @param  grafo   - grafo guardado em memoria
    @param  codVert - codigo do vertice de partida
    @param  peso    - peso da adjacencia
    @param  codDest - codigo do vertice destino
    @retval         - grafo guardado em memoria
**/
Grafo* AdicionaAdjacencia(Grafo* grafo, int codVert, int peso, int codDest) {
    if (grafo == NULL) {
        return GRAFO_NAO_EXISTE;
    }
    
    if (peso == 0) {
        return grafo;
    }

    if (VerificaExisteVertice(grafo->inicio, codVert) == VERTICE_NAO_EXISTE || VerificaExisteVertice(grafo->inicio, codDest) == VERTICE_NAO_EXISTE) {
        return grafo;
    }

    Vertice* auxVert = grafo->inicio;
    while (auxVert->cod != codVert) {
        auxVert = auxVert->next;
    }
    
    if (VerificaExisteAdjacencia(auxVert->adjacencias, codDest) == EXISTE_ADJACENCIA) {
        return grafo;
    }
    
    Adjacencia* auxAdj = auxVert->adjacencias;
    if (auxAdj == NULL) {
        auxAdj = CriaAdjacencia(codDest, peso);
        auxVert->adjacencias = auxAdj;
        auxVert->numAdj++;
        return grafo;
    }
    if (auxVert->numAdj == 1) {
        Adjacencia* novoAdj = CriaAdjacencia(codDest, peso);
        if (codDest < auxAdj->codVert) {
            novoAdj->next = auxAdj;
            auxVert->adjacencias = novoAdj;
        }
        if (codDest > auxAdj->codVert) {
            auxAdj->next = novoAdj;
        }
        auxVert->numAdj++;
        return grafo;
    }
    
    Adjacencia* proxAdj = auxAdj->next;
    for (int i = 0; i < auxVert->numAdj; i++) {
        if (auxAdj->codVert<codDest && proxAdj->codVert>codDest) {
            Adjacencia* novoAdj = CriaAdjacencia(codDest, peso);
            auxAdj->next = novoAdj;
            novoAdj->next = proxAdj;
            auxVert->numAdj++;
            return grafo;
        }
        if (proxAdj->next != NULL) {
            auxAdj = proxAdj;
            proxAdj = auxAdj->next;
        }
    }

    Adjacencia* novoAdj = CriaAdjacencia(codDest, peso);
    proxAdj->next = novoAdj;
    auxVert->numAdj++;
    return grafo;
}
/**
    @brief  Funcao que procura vertice com um determinado codigo
    @param  auxVert - lista dos vertices
    @param  cod     - codigo que se pretende encontrar
    @retval         - vertice com o codigo pretendido
**/
Vertice* ProcuraVerticeCod(Vertice* auxVert, int cod) {
    if (auxVert == NULL) {
        return auxVert;
    }

    if (VerificaExisteVertice(auxVert, cod) == VERTICE_NAO_EXISTE) {
        return auxVert;
    }

    while (auxVert->cod != cod) {
        auxVert = auxVert->next;
    
    }
    return auxVert;
}

