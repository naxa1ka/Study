#include <iostream>
#include "windows.h"
#include <climits>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "queue"
#define SIZE_GRAPH 14
#define INF 999999

#define BELLMAN_PRINT
#define FLOYD_PRINT
#define DEXTER_PRINT
using namespace std;


class Edge {
public:
    int source, dest, weight;
};

void restorePath(int startVertex, int endVertex, const int *predPath){
    queue<int> path;
    int nextVertex = predPath[endVertex];
    path.push(nextVertex);
    while(nextVertex != startVertex){
        nextVertex = predPath[nextVertex];
        path.push(nextVertex);
    }
    while ( !path.empty()){
        cout << path.front() << endl;
        path.pop();
    }
}

void dexter(int startVertex, const int GRAPH[][SIZE_GRAPH]) {
    int *distance = new int[SIZE_GRAPH];    //Массив расстояний
    bool *isVisited = new bool[SIZE_GRAPH]; //Массив флагов посещения вершины
    int *pred = new int[SIZE_GRAPH];
    for (int i = 0; i < SIZE_GRAPH; ++i) {
        distance[i] = INT_MAX;              //Начальное мин. расстояние до вершины
        isVisited[i] = false;               //Обнуляем флаги посещения вершины
    }
    distance[startVertex] = 0;              //C этой вершины ищем кратчайшие пути

    int indexMin;
    int u;
    for (int i = 0; i < SIZE_GRAPH; ++i) {
        int min = INT_MAX;
        for (int j = 0; j < SIZE_GRAPH; ++j) {       //ищем вершину с минимальным расстоянием
            if (!isVisited[j] && distance[j] < min) {
                min = distance[j];
                indexMin = j;
            }
        }
        u = indexMin;
        isVisited[u] = true;
#ifdef DEXTER_PRINT
        cout << endl << "Минимальная вершина сейчас = " << u << endl << endl;
#endif
        for (int j = 0; j < SIZE_GRAPH; ++j) {
            if (!isVisited[j] && GRAPH[u][j] && distance[u] != INT_MAX) {
                if (distance[u] + GRAPH[u][j] < distance[j])
#ifdef DEXTER_PRINT
                    {
#endif
                    distance[j] = distance[u] + GRAPH[u][j];
                    pred[j] = u;
#ifdef DEXTER_PRINT
                cout << "Новый минимальный путь от " << u << " вершины до " << j << " = " << distance[j] << endl;
            } else {
                cout << "Расстояние от " << u << " вершины до " << j << " | " << distance[u] + GRAPH[u][j]
                     << " больше " << distance[j] << " | не подходит" << endl;
            }
#endif
            }
        }
    }
    cout << "Кратчайшие пути:\n";
    for (int i = 0; i < SIZE_GRAPH; i++) {
        if (distance[i] != INT_MAX) {
            cout << startVertex << " -> " << i << " = " << distance[i] << endl;
        } else {
            cout << startVertex << " -> " << i << " = " << "error" << endl;
        }
    }
    for (int i = 0; i < SIZE_GRAPH; ++i) {
        cout << "Предок " << i << ": " << pred[i] << endl;
    }
    restorePath(startVertex, 12, pred);
}

void floydWarshall(const int GRAPH[][SIZE_GRAPH]) {
    //Пробегаемся по всем вершинам и ищем более короткий путь
    //через вершину k

    int matrix[SIZE_GRAPH][SIZE_GRAPH];
    cout << endl << endl;
    for (int i = 0; i < SIZE_GRAPH; ++i) {
        for (int j = 0; j < SIZE_GRAPH; ++j) {
            cout << setw(3) << GRAPH[i][j] << " ";
            if (GRAPH[i][j] == 0) {
                matrix[i][j] = INF;
            } else {
                matrix[i][j] = GRAPH[i][j];
            }
        }
        cout << endl;
    }
    cout << endl << endl;


    for (int k = 0; k < SIZE_GRAPH; k++) {
        cout << endl << "k: " << k << endl;;
        for (int i = 0; i < SIZE_GRAPH; i++) {
            for (int j = 0; j < SIZE_GRAPH; j++) {
                //Новое значение ребра равно минимальному между старым
                //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)

                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
#ifdef FLOYD_PRINT
                    printf("changed: [%i][%i]: %i\n", i, j, matrix[i][j]);
                    printf("to:  [%i][%i](%i) + [%i][%i](%i): %i\n\n",
                           i, k, matrix[i][k], k, j, matrix[k][j], matrix[i][k] + matrix[k][j]
                    );
#endif
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
        cout << "     ";
        for (int i = 0; i < SIZE_GRAPH; ++i) {
            cout << setw(3) << i << " ";
        }
        cout << endl << "    --------------------------------------------------------" << endl;
        for (int i = 0; i < SIZE_GRAPH; ++i) {
            cout << setw(2) << i << " | ";
            for (int j = 0; j < SIZE_GRAPH; ++j) {
                if (matrix[i][j] == INF)
                    cout << setw(3) << "- " << " ";
                else
                    cout << setw(3) << matrix[i][j] << " ";
            }
            cout << endl;
        }


    }


}

void bellmanFord(int startVertex, const int GRAPH[][SIZE_GRAPH]) {
    int *distance = new int[SIZE_GRAPH];    //Массив расстояний

    for (int i = 0; i < SIZE_GRAPH; ++i)
        distance[i] = INF;
    distance[startVertex] = 0;

    for (int i = 0; i < SIZE_GRAPH - 1; ++i)
        for (int j = 0; j < SIZE_GRAPH; ++j) {
            if (GRAPH[i][j] > 0) {
                if ((distance[i] + GRAPH[i][j]) < distance[j]) {

#ifdef BELLMAN_PRINT
                    printf("dist[%i](%i) + GRAPH[%i][%i](%i) < dist[%i](%i)\n",
                           i, distance[i], i, j, GRAPH[i][j], j, distance[j]);
                    printf("dist[%i](%i) = dist[%i](%i) + GRAPH[%i][%i](%i)\n\n",
                           j, distance[j], i, distance[i], i, j, GRAPH[i][j]);
#endif
                    distance[j] = distance[i] + GRAPH[i][j];
                }
            }
        }

    for (int i = 0; i < SIZE_GRAPH; ++i) {
        cout << distance[i] << " ";
    }
    cout << endl;
}


//функция для сравнения двух элементов edge для сортировки
bool compare(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

int findParent(int v, int *parent) {
    if (parent[v] == v) {
        // cout << "only v " << v << endl;
        return v;
    } //если потомок сама вершина
    //   cout << "finding parent " << v << endl;
    return findParent(parent[v], parent);
}

void Kruskals(Edge *input, int n, int E) {
    sort(input, input + E, compare);

    Edge *output = new Edge[n - 1];
    int *parent = new int[n];

    for (int i = 0; i < n; i++)
        parent[i] = i;

    int i = 0, count = 0;

    while (count != n - 1) {
        Edge currentEdge = input[i];
        int sourceParent = findParent(currentEdge.source, parent);
        cout << currentEdge.source << " srcPar: " << sourceParent << endl;
        int destParent = findParent(currentEdge.dest, parent);
        cout << currentEdge.dest << " destPar: " << destParent << endl << endl;
        if (sourceParent != destParent) {
            output[count] = currentEdge;
            count++;
            parent[sourceParent] = destParent;
        }
        i++;
    }
    int minWeight = 0;
    for (i = 0; i < n - 1; i++) {
        if (output[i].source < output[i].dest) {
            cout << output[i].source << " -> " << output[i].dest << " : " << output[i].weight << endl;
        } else {
            cout << output[i].dest << " -> " << output[i].source << " : " << output[i].weight << endl;
        }
        minWeight += output[i].weight;
    }
    cout << "WEIGHT: " << minWeight << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int GRAPH[SIZE_GRAPH][SIZE_GRAPH] = {{0, 2, 0, 1, 3, 4, 5, 0,  0,  0, 0, 0, 0, 0},
                                         {0, 0, 3, 0, 0, 0, 0, 10, 0,  0, 0, 0, 0, 0},
                                         {0, 0, 0, 7, 0, 0, 0, 0,  0,  0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 4, 0, 0, 0,  4,  0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 5, 0, 0,  0,  7, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 2, 0,  0,  5, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0,  0,  0, 4, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0,  10, 0, 0, 7, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0,  0,  9, 0, 3, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0,  0,  0, 0, 7, 4, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0,  0,  0, 0, 0, 9, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0,  0,  0, 0, 0, 0, 5},
                                         {0, 0, 0, 0, 0, 0, 0, 0,  0,  0, 0, 0, 0, 7},
                                         {0, 0, 0, 0, 0, 0, 0, 0,  0,  0, 0, 0, 0, 0}

    };

    Edge *input = new Edge[24];
    int counter = 0;
    for (int i = 0; i < SIZE_GRAPH; ++i) {
        for (int j = 0; j < SIZE_GRAPH; ++j) {
            if (GRAPH[i][j] != 0) {
                input[counter].source = i;
                input[counter].dest = j;
                input[counter].weight = GRAPH[i][j];
                counter++;
            }
        }
    }

    int startVertex = 0;
    dexter(startVertex, GRAPH);
    //floydWarshall(GRAPH);
    //bellmanFord(startVertex, GRAPH);

    //Kruskals(input, SIZE_GRAPH, counter);
    return 0;
}
