/**

    @file      Stack.h
    @brief     Ficheiro .h com as funcoes da stack utilizada nos algoritmos de procura
    @details   ~
    @author    Diogo Machado 26042
    @date      22.05.2024
    @copyright © Diogo Machado, 2023. All right reserved.

**/
#pragma once
#include <stdbool.h>
typedef struct Stack {
    int id;
    struct Stack* next;
}Stack;

/**
    @brief  Funcao que cria um valor da stack em memoria
    @param  cod - codigo do valor da stack
    @retval     - valor da stack criado em memoria
**/
Stack* CriaStackValor(int cod);
/**
    @brief  Funcao que insere novo valor no fim da stack
    @param  inicio - stack guardada em memoria
    @param  novo   - novo valor da stack que se pretende  inserir na stack guardada em memoria
    @retval        - stack guarada em memoria
**/
Stack* InsereNaStack(Stack* inicio, Stack* novo);
/**
    @brief  Funcao que Remove o valor de topo da stack
    @param  inicio - stack guardada em memoria
    @retval        - stack guardada em memoria depois de remover o valor de topo
**/
Stack* RemoveValorStack(Stack* inicio);
/**
    @brief Funcao que da output aos valores guardados numa stack
    @param stack - stack guardada em memoria
**/
void OutputStack(Stack* stack);
/**
    @brief  Funcao que procura pelo codigo do valor de topo da stack
    @param  stack - stack guardada em memoria
    @retval       - valor inteiro do codigo do valor de topo da stack
**/
int StackPeek(Stack* stack);
/**
    @brief  Funcao que verifica se a stack esta vazia
    @param  stack - stack guardada em memoria
    @retval       - 1 se estiver vazia e 0 se nao estiver
**/
int IsStackEmpty(Stack* stack);