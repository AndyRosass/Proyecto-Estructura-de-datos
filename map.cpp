#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct arista {
  int destination;
  int weight;
};

struct nodo {
  int value;
  list<arista> edges;
};

nodo *agregarnodo(int value) {
  nodo *newNode = new nodo;
  newNode->value = value;
  return newNode;
}

void addaristas(nodo *source, nodo *destination, int weight) {
  source->edges.push_back({destination->value, weight});
  destination->edges.push_back({source->value, weight});
}

void printGraph(vector<nodo *> nodes, map<int, string> nombredenodo) {
  for (int i = 0; i < nodes.size(); ++i) {
    cout << "nodo " << nombredenodos
[nodes[i]->value] << " -> ";
    for (arista edge : nodes[i]->edges) {
      cout << nombredenodos
  [edge.destination] << "(" << edge.weight << ") ";
    }
    cout << endl;
  }
}

void prim(vector<nodo *> nodes, nodo *startNode) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<bool> visited(nodes.size(), false);
  vector<pair<int, int>> mstEdges;

  pq.push({0, startNode->value});

  while (!pq.empty()) {
    int weight = pq.top().first;
    int nodeValue = pq.top().second;
    pq.pop();

    if (visited[nodeValue - 1])
      continue;
    visited[nodeValue - 1] = true;

    for (nodo *node : nodes) {
      if (node->value == nodeValue) {
        for (arista edge : node->edges) {
          if (!visited[edge.destination - 1]) {
            pq.push({edge.weight, edge.destination});
            mstEdges.push_back({nodeValue, edge.destination});
          }
        }
        break;
      }
    }
  }
}

int main() {
  map<int, string> nombredenodos = {
    {1, "Iturbide"}, {2, "Del Sol"}, {3, "Plaza de Armas"},
    {4, "O'Higgins"}, {5, "Artigas"}, {6, "San Martin"},
    {7, "Bolivar"}, {8, "Roraima"}, {9, "Torres del Paine"},
    {10, "Angostura"}, {11, "Formosa"}, {12, "Toledo"},
    {13, "Komsomolskaya"}, {14, "Abrantes"}, {15, "Grand Central Terminal"},
    {16, "Arts et Métiers"}, {17, "Kungsträdgården"}, {18, "Münchner Freiheit"},
    {19, "Westfriedhof"}, {20, "Bilbao"}, {21, "Shanghai"}, {22, "T-Centralen"},
    {23, "Atocha"}, {24, "Lisboa"}, {25, "Singapur"}, {26, "Plaza Venezuela"},
    {27, "Solna Centrum"}, {28, "Westminster"}, {29, "Alameda"}, {30, "Avtovo"}
  };

  nodo *node1 = agregarnodo(1); 
  nodo *node2 = agregarnodo(2); 
  nodo *node3 = agregarnodo(3);
  nodo *node4 = agregarnodo(4); 
  nodo *node5 = agregarnodo(5);
  nodo *node6 = agregarnodo(6);
  nodo *node7 = agregarnodo(7); 
  nodo *node8 = agregarnodo(8); 
  nodo *node9 = agregarnodo(9); 
  nodo *node10 = agregarnodo(10); 
  nodo *node11 = agregarnodo(11); 
  nodo *node12 = agregarnodo(12); 
  nodo *node13 = agregarnodo(13); 
  nodo *node14 = agregarnodo(14); 
  nodo *node15 = agregarnodo(15);

  addaristas(node1, node2, 5);
  addaristas(node1, node3, 2);
  addaristas(node2, node4, 8);
  addaristas(node2, node5, 14);
  addaristas(node5, node8, 12);
  addaristas(node6, node9, 11);
  addaristas(node6, node10, 9);
  addaristas(node3, node11, 6);
  addaristas(node4, node12, 8);
  addaristas(node8, node6, 20);
  addaristas(node9, node15, 21);
  addaristas(node9, node14, 7);
  addaristas(node10, node1, 9);
  addaristas(node11, node7, 3);
  addaristas(node12, node3, 1);
  addaristas(node13, node10, 19);
  addaristas(node14, node7, 24);
  addaristas(node15, node8, 23);
  addaristas(node13, node7, 5);
  addaristas(node14, node6, 6);
  addaristas(node15, node5, 8);

  vector<nodo*> graph = {
    node1, node2, node3,
    node4, node5, node6,
    node7, node8, node9,
    node10, node11, node12,
    node13, node14, node15, node16, 
    node17, node18, node19, node20,
    node21, node22, node23, node24,
    node25, node26, node27, node28,
    node29, node30};
  
  return 0;
}
