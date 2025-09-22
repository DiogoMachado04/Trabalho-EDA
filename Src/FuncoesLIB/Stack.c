/**

    @file      Stack.c
    @brief     Ficheiro .c com as funcoes da stack utilizada nos algoritmos de procura
    @details   ~
    @author    Diogo Machado 26042
    @date      21.05.2024
    @copyright © Diogo Machado, 2023. All right reserved.

**/
#include "GereGrafos.h"
#include "Grafos.h"
#include "Constantes.h"
#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

/**
    @brief  Funcao que cria um valor da stack em memoria
    @param  cod - codigo do valor da stack
    @retval     - valor da stack criado em memoria 
**/
Stack* CriaStackValor(int cod) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->id = cod;
    stack->next = NULL;
    return stack;
}

/**
    @brief  Funcao que insere novo valor no fim da stack
    @param  inicio - stack guardada em memoria
    @param  novo   - novo valor da stack que se pretende  inserir na stack guardada em memoria
    @retval        - stack guarada em memoria
**/
Stack* InsereNaStack(Stack* inicio, Stack* novo) {
    if (inicio == NULL) {
        inicio = novo;
        return inicio;
    }

    Stack* aux = inicio;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = novo;
    return inicio;
}

/**
    @brief  Funcao que Remove o valor de topo da stack
    @param  inicio - stack guardada em memoria
    @retval        - stack guardada em memoria depois de remover o valor de topo
**/
Stack* RemoveValorStack(Stack* inicio) {
    Stack* aux = inicio;
    if (aux->next == NULL) {
        free(aux);
        inicio = NULL;
        return inicio;
    }

    Stack* ant = aux;
    aux = aux->next;
    while (aux->next != NULL) {
        ant = aux;
        aux = aux->next;
    }
    ant->next = NULL;
    free(aux);
    aux = NULL;
    return inicio;
}

/**
    @brief Funcao que da output aos valores guardados numa stack
    @param stack - stack guardada em memoria
**/
void OutputStack(Stack* stack) {
    Stack* aux = stack;
    while (aux != NULL) {
        printf("%d;", aux->id);
        aux = aux->next;
    }
    printf("\n");
}

/**
    @brief  Funcao que procura pelo codigo do valor de topo da stack
    @param  stack - stack guardada em memoria
    @retval       - valor inteiro do codigo do valor de topo da stack
**/
int StackPeek(Stack* stack){
    if (stack == NULL) {
        return stack;
    }
    Stack* aux = stack;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    return aux->id;
}

/**
    @brief  Funcao que verifica se a stack esta vazia
    @param  stack - stack guardada em memoria
    @retval       - 1 se estiver vazia e 0 se nao estiver
**/
int IsStackEmpty(Stack* stack) {
    if (stack == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}
