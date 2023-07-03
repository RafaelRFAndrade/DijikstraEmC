#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

 /*
 Hoje � muito comum usar conceitos de grafos para diversas atividade da
 computa��o,como o mapa do Google, onde � usado o algoritmo de Dijkstra 
 para achar o melhor caminho entre dois pontos, A e B. O objetivo deste
 trabalho � desenvolver um software que use conceitos de grafos, como 
 mapa do Google. Construa um programa em C ANSI que implemente o
 algoritmo e Dijkstra  para achar o menor caminho entre os pontos A e B.
 */

// Estrutura para representar um n� do grafo
typedef struct Node {
    char label;
    struct Node* next;
    int weight;
} Node;

 

// Fun��o para criar um novo n�
Node* createNode(char label, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->label = label;
    newNode->next = NULL;
    newNode->weight = weight;
    return newNode;
}

 

// Fun��o para adicionar uma aresta no grafo
void addEdge(Node* graph[], char src, char dest, int weight) {
    // Adicionar aresta do src para o dest
    Node* newNode = createNode(dest, weight);
    newNode->next = graph[src - 'A'];
    graph[src - 'A'] = newNode;

 

    // Adicionar aresta de volta do dest para o src
    newNode = createNode(src, weight);
    newNode->next = graph[dest - 'A'];
    graph[dest - 'A'] = newNode;
}
// Fun��o para imprimir o caminho do in�cio ao destino
void printPath(char path[], int length) {
    for (int i = 0; i < length - 1; i++) {
        printf("%c -> ", path[i]);
    }
    printf("%c\n", path[length - 1]);
}

 

// Fun��o para encontrar o caminho mais curto de A para K
void findShortestPath(Node* graph[], char start, char end) {
    int numNodes = 11;
    int dist[numNodes];
    char path[numNodes];
    int visited[numNodes];

 

    // Inicializar as dist�ncias como infinito (exceto o n� de partida)
    for (int i = 0; i < numNodes; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start - 'A'] = 0; // A dist�ncia do n� de partida � 0

 

    // Encontrar o caminho mais curto para todos os n�s
    for (int count = 0; count < numNodes - 1; count++) {
        int minDist = INT_MAX;
        int minIndex = -1;

 

        // Encontrar o n� com a menor dist�ncia ainda n�o visitado
        for (int i = 0; i < numNodes; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }

 

        // Marcar o n� m�nimo como visitado
        visited[minIndex] = 1;

 

        // Atualizar as dist�ncias dos n�s adjacentes ao n� m�nimo
        Node* curr = graph[minIndex];
        while (curr != NULL) {
            int index = curr->label - 'A';
            if (!visited[index] && dist[minIndex] != INT_MAX &&
                dist[minIndex] + curr->weight < dist[index]) {
                dist[index] = dist[minIndex] + curr->weight;
            }
            curr = curr->next;
        }
    }

 

    // Construir o caminho mais curto de A para K
    int pathLength = 0;
    char currNode = end;
    while (currNode != start && currNode != -1) {
        path[pathLength++] = currNode;
        Node* curr = graph[currNode - 'A'];
        int minDist = INT_MAX;
        int nextNode = -1;
        while (curr != NULL) {
            int index = curr->label - 'A';
            if (dist[index] < minDist) {
                minDist = dist[index];
                nextNode = curr->label;
            }
            curr = curr->next;
        }
        currNode = nextNode;
    }
    path[pathLength++] = start;

 

    // Inverter o caminho para obter a ordem correta
    char reversedPath[numNodes];
    for (int i = 0; i < pathLength; i++) {
        reversedPath[i] = path[pathLength - 1 - i];
    }

 

    printf("Caminho mais curto de %c a %c: ", start, end);
    printPath(reversedPath, pathLength);
    printf("Distancia total: %d\n", dist[end - 'A']);
}

 

int main() {
    Node* graph[11];  // Grafo com 11 n�s (A-K)

 

    // Inicializar o grafo
    for (int i = 0; i < 11; i++) {
        graph[i] = NULL;
    }

 

    // Adicionar as arestas do grafo
    addEdge(graph, 'A', 'I', 500);
    addEdge(graph, 'A', 'F', 200);
    addEdge(graph, 'I', 'J', 69);
    addEdge(graph, 'I', 'C', 50);
    addEdge(graph, 'I', 'D', 70);
    addEdge(graph, 'J', 'K', 2000);
    addEdge(graph, 'K', 'G', 150);
    addEdge(graph, 'K', 'H', 100);
    addEdge(graph, 'H', 'E', 10);
    addEdge(graph, 'E', 'F', 45);
    addEdge(graph, 'E', 'B', 300);

 

    // Encontrar o caminho mais curto de A para K
    findShortestPath(graph, 'A', 'K');

 

    return 0;
}
