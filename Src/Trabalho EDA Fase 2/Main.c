/**

    @file      Main.c
    @brief     Ficheiro main da segunda fase do trabalho de Estrutura de Dados Avançadas
    @details   ~
    @author    Diogo Machado 26042
    @date      6.05.2024
    @copyright © Diogo Machado, 2023. All right reserved.

**/

#pragma comment(lib,"FuncoesLIB.lib")

#include "GereGrafos.h"
#include "Utilidades.h"
#include "FuncoesProcura.h"
#include "Stack.h"
int main() {
    Grafo* grafo = LeFicheiroGrafo("Grafo.csv");
    int val = CalculoSomaEntreDoisVertices(grafo, 1, 2);
    bool res1 = DepthFirstTraversal(grafo, 0);
    MostraGrafo(grafo);
    int res = LimpaGrafo(grafo);
}