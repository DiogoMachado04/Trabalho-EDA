/**

    @file      Funcoes.c
    @brief     Ficheiro .c com as funcoes de procura do trabalho
    @details   ~
    @author    Diogo Machado 26042
    @date      22.05.2024
    @copyright © Diogo Machado, 2023. All right reserved.

**/
#include "Grafos.h"
#include "Stack.h"
#include "Utilidades.h"
#include "Constantes.h"
#include "Stack.h"
#include <stdio.h>

/**
    @brief  Funcao Depth First Traversal que passa por todos os vertices do grafo em profundidade
    @param  grafo  - grafo guardado em memoria
    @param  codIni - codigo do vertice onde comeca a procura
    @retval        - Stack com os registos onde se passou para a procura
**/
Stack* DepthFirstTraversal(Grafo* grafo, int codIni) {
    Vertice* auxVert = ProcuraVerticeCod(grafo->inicio, codIni);
    auxVert->visitado = true;
    Stack* stack = CriaStackValor(auxVert->cod);
    Stack* registo = CriaStackValor(auxVert->cod);
    Stack* novo = NULL;
    Stack* novoReg = NULL;
    registo = InsereNaStack(NULL, registo);
    stack = InsereNaStack(NULL, stack);
    while (!IsStackEmpty(stack)) {
        auxVert = ProcuraVerticeCod(grafo->inicio, StackPeek(stack));
        auxVert->visitado = true;
        Adjacencia* auxAdj = auxVert->adjacencias;
        while(auxAdj != NULL) {
            Vertice* vertAdj = ProcuraVerticeCod(grafo->inicio, auxAdj->codVert);
            if (auxAdj->visitado == false && vertAdj->visitado == false) {
                auxAdj->visitado = true;
                novo = CriaStackValor(vertAdj->cod);
                novoReg = CriaStackValor(vertAdj->cod);
                stack = InsereNaStack(stack, novo);
                registo = InsereNaStack(registo, novoReg);
                break;
            }
            auxAdj = auxAdj->next;
            if (auxAdj == NULL) {
                stack = RemoveValorStack(stack);
            }
        }
    }
    return registo;
}

/**
    @brief Funcao que imprime no ecra o vertice da Depth First search recursiva
    @param id - id do vertice que se pretende imprimir
**/
void ProcessaVertice(int id) {
    printf("%d;", id);
}

/**
    @brief  Funcao Depth First Traversal que passa por todos os vertices do grafo em profundidade
    @param  auxVert - lista de vertices do grafo
    @param  origem  - onde comeca a procura
    @param  dest    - destino da procura
    @retval         - retorna sucesso ou insucesso de encontrar o vertice
**/
bool DepthFirstSearchRec(Vertice* auxVert, int origem, int dest){
	if (origem == dest) return SUCESSO;

	Vertice* aux = ProcuraVerticeCod(auxVert, origem);
	aux->visitado = true;
	ProcessaVertice(aux->cod);

	Adjacencia* auxAdj = aux->adjacencias;
	while (auxAdj) {
		Vertice* aux = ProcuraVerticeCod(auxVert, auxAdj->codVert);
		if (aux->visitado == false)
		{
			bool existe = DepthFirstSearchRec(auxVert, auxAdj->codVert, dest);
			return existe;
		}
		else
			aux = aux->next;
	}
	return true;
}

/**
    @brief  Calcula a soma dos pesos das adjacencias entre dois vertices
    @param  grafo   - grafo guardado em memoria
    @param  codIni  - codigo do vertice onde se comeca a pesquisa 
    @param  codDest - codigo do vertice onde se pretende chegar 
    @retval         - valor da soma dos pesos
**/
int CalculoSomaEntreDoisVertices(Grafo* grafo, int codIni, int codDest) {
    Vertice* auxVert = ProcuraVerticeCod(grafo->inicio, codIni);
    auxVert->visitado = true;
    Stack* stack = CriaStackValor(auxVert->cod);
    Stack* novo = NULL;
    stack = InsereNaStack(NULL, stack);
    int soma = 0;
    auxVert = ProcuraVerticeCod(grafo->inicio, StackPeek(stack));
    while (auxVert->cod != codDest) {
        auxVert->visitado = true;
        Adjacencia* auxAdj = auxVert->adjacencias;
        while (auxAdj != NULL) {
            Vertice* vertAdj = ProcuraVerticeCod(grafo->inicio, auxAdj->codVert);
            if (auxAdj->visitado == false && vertAdj->visitado == false) {
                soma += auxAdj->peso;
                auxAdj->visitado = true;
                novo = CriaStackValor(vertAdj->cod);
                stack = InsereNaStack(stack, novo);
                auxVert = ProcuraVerticeCod(grafo->inicio, StackPeek(stack));
                break;
            }
            auxAdj = auxAdj->next;
            if (auxAdj == NULL) {
                int vertFim = StackPeek(stack);
                stack = RemoveValorStack(stack);
                int vertIni = StackPeek(stack);
                Vertice* vertRem = ProcuraVerticeCod(grafo->inicio, vertIni);
                Adjacencia* adjRem = vertRem->adjacencias;
                while (adjRem->codVert != vertFim) {
                    adjRem = adjRem->next;
                }
                soma -= adjRem->peso;
                auxVert = ProcuraVerticeCod(grafo->inicio, StackPeek(stack));
            }
        }
    }
    return soma;
}
