#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

struct arista {
  int destination;
  int weight;
};

struct nodo {
  int value;
  std::list<arista> edges;
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

void printGraph(std::vector<nodo *> nodes,
                std::map<int, std::string> nombredenodo) {
  for (int i = 0; i < nodes.size(); ++i) {
    std::cout << "nodo " << nombredenodo[nodes[i]->value] << " -> ";
    for (arista edge : nodes[i]->edges) {
      std::cout << nombredenodo[edge.destination] << "(" << edge.weight << ") ";
    }
    std::cout << std::endl;
  }
}

void prim(std::vector<nodo *> nodes, nodo *startNode) {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;
  std::vector<bool> visited(nodes.size(), false);
  std::vector<std::pair<int, int>> mstEdges;

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

