/**

    @file      GereGrafos.c
    @brief     Ficheiro .c que contém funções de gerir grafos
    @details   ~
    @author    Diogo Machado 26042
    @date      8.05.2024
    @copyright © Diogo Machado, 2023. All right reserved.

**/
#pragma warning (disable:4996)
#include "Grafos.h"
#include "Constantes.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

/**
    @brief  Cria espaco em memoria para um vertice e coloca valores nas suas variáveis
    @param  cod - numero de codigo do vertice
    @retval     - vertice criado
**/
Vertice* CriaVertice(int cod){
    Vertice* novo = (Vertice*)malloc(sizeof(Vertice));
    novo->cod = cod;
    novo->numAdj = 0;
    novo->visitado = false;
    novo->adjacencias = NULL;
    novo->next = NULL;
    return novo;
}

/**
    @brief  Insere vertice novo na lista ligada dos vertices
    @param  inicio - inicio da lista dos vertices
    @param  novo   - vertice novo que se pretende introduzir na lista
    @retval        - inicio da lista de vertices
**/
Vertice* InsereVertice(Vertice* inicio, Vertice* novo) {
    if (inicio == NULL) { //caso ainda nao exista lista de vertices para inserir
        inicio = novo;
        return inicio;
    }
    Vertice* aux = inicio;
    while (aux->next != NULL) { //itera ate ao fim da lista para de seguida adicionar o novo vertice
        aux = aux->next;
    }
    aux->next = novo;
    return inicio;
}

/**
    @brief  Insere lista de adjacencias no vertice correspondente
    @param  vertice   - vertice do grafo que pretendemos colocar as adjacencias
    @param  inicioAdj - lista de adjacentes do vertice 
    @retval           - vertice com as adjacencias colocadas
**/
Vertice* InsereAdjacenciaVertice(Vertice* vertice, Adjacencia* inicioAdj) {
    vertice->adjacencias = inicioAdj;
    return vertice;
}

/**
    @brief  Cria espaco em memoria para uma adjacencia e coloca valores nas suas variaveis
    @param  cod  - numero de codigo do vertice adjacente
    @param  peso - peso da adjacencia
    @retval      - adjacencia criada
**/
Adjacencia* CriaAdjacencia(int cod, int peso) {
    Adjacencia* novo = (Adjacencia*)malloc(sizeof(Adjacencia));
    novo->codVert = cod;
    novo->peso = peso;
    novo->visitado = false;
    novo->next = NULL;
    return novo;
}

/**
    @brief  Insere adjacencia nova na lista de adjacencias
    @param  inicio - inicio da lista de adjacencias 
    @param  nova   - nova adjacencia que se pretende colocar na lista
    @retval        - lista de adjacencias
**/
Adjacencia* InsereAdjacencia(Adjacencia* inicio, Adjacencia* nova) {
    if (inicio == NULL) {//caso ainda nao exista lista de adjacencias para inserir
        inicio = nova;
        return inicio;
    }
    Adjacencia* aux = inicio;
    while (aux->next != NULL) {//itera ate ao fim da lista para de serguida adicionar a nova adjacencia
        aux = aux->next;
    }
    aux->next = nova;
    return inicio;
}

/**
    @brief  Cria memoria para o grafo e introduz os valores nas variaveis
    @param  inicioVert - inicio da lista dos vertices
    @param  numVert    - numero de vertices do grafo
    @retval            - grafo com valores nas variaveis
**/
Grafo* CriaGrafo(Vertice* inicioVert, int numVert) {
    if (inicioVert == NULL || numVert <= 0) {
        return PARAMETROS_INVALIDOS;
    }

    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->inicio = inicioVert;
    grafo->numVert = numVert;
    return grafo;
}

/**
    @brief  Limpa memoria
    @param  grafo - grafo guardado em memoria
    @retval       - Resultado da funcao
**/
int LimpaGrafo(Grafo* grafo) {
    if (grafo == NULL || grafo->numVert == 0) {
        return GRAFO_NAO_EXISTE;
    }
    Vertice* auxVert = grafo->inicio;
    while (auxVert != NULL) {
        Adjacencia* auxAdj = auxVert->adjacencias;
        while (auxAdj != NULL) {
            Adjacencia* proxAdj = auxAdj->next;
            free(auxAdj);
            auxAdj = proxAdj;
        }
        Vertice* proxVert = auxVert->next;
        free(auxVert);
        auxVert = proxVert;
    }
    free(grafo);
    return SUCESSO;
}

/**
    @brief  Le grafo do ficheiro CSV
    @param  filename - nome do ficheiro
    @retval          - grafo
**/
Grafo* LeFicheiroGrafo(char* filename) { 
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        return ERRO_AO_ABRIR_FICHEIRO;
    }
    Vertice* novoVert = NULL;
    Vertice* inicioVert = NULL;
    Adjacencia* inicioAdj = NULL;
    Adjacencia* novaAdj = NULL;
    int vert = 0;
    int peso;
    char valorFich[MAX_CARATERES] = "";
    char ch;
    int codAdj = 0;
    int numAdj = 0;

    novoVert = CriaVertice(vert);
    while (1) {
        ch = fgetc(fp);
        if (ch != ';' && ch != '\n' && ch != EOF) {
            strncat(valorFich, &ch, sizeof(char));
            continue;
        }
        peso = atoi(valorFich);
        if (peso != 0) {
            valorFich[0] = '\0';
            novaAdj = CriaAdjacencia(codAdj, peso);
            inicioAdj = InsereAdjacencia(inicioAdj, novaAdj);
            numAdj++;
        }
        codAdj++;
        if (ch == '\n' || ch == EOF) {
            novoVert->numAdj = numAdj;
            novoVert = InsereAdjacenciaVertice(novoVert, inicioAdj);
            inicioVert = InsereVertice(inicioVert, novoVert);
            inicioAdj = NULL;
            novoVert = NULL;
            codAdj = 0;
            numAdj = 0;
            vert++;
            if (ch == EOF) {
                break;
            }
            novoVert = CriaVertice(vert);
            continue;
        }
    } 

    fclose(fp);
    Grafo* grafo = CriaGrafo(inicioVert, vert);
    return grafo;
}

/**
    @brief  Funcao que mostra grafo na linha de comandos
    @param  grafo - grafo guardado em memoria
    @retval       - Resultado da funcao
**/
int MostraGrafo(Grafo* grafo) {
    if (grafo == NULL) {
        return GRAFO_NAO_EXISTE;
    }
    Vertice* auxVert = grafo->inicio;
    Adjacencia* auxAdj = auxVert->adjacencias;

    for (int i = 0; i < grafo->numVert; i++) {
        if (auxVert->adjacencias != NULL) {
            printf("Vertice: %d\n\tAdjacencias:\n\t", auxVert->cod);
        }
        else {
            printf("Vertice: %d\n\tNao tem adjacencias.", auxVert->cod);
        }
        for (int j = 0; j < auxVert->numAdj; j++) {
            printf("(%d):Peso %d\n\t",auxAdj->codVert, auxAdj->peso);
            auxAdj = auxAdj->next;
        }
        if (auxVert->next != NULL) {
            auxVert = auxVert->next;
            auxAdj = auxVert->adjacencias;
            printf("\n");
        }
    }
    return SUCESSO;
}