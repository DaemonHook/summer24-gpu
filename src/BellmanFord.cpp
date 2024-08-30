#include "Graph.h"

/// @brief Bellman-Ford Algorithm - Adjacency List O(VE)
/// @param start Starting node
/// @return Vector of distances from start to all other nodes
std::vector<nodeId_t> LinkGraph::bellmanFord(nodeId_t start) {
    nodeId_t inf = 0x3f3f3f3f;
    std::vector<nodeId_t> dist(this->vertexNum, inf);
    dist[start] = 0;

    for (nodeId_t i = 0; i < this->vertexNum - 1; ++i) {
        for (nodeId_t u = 0; u < this->vertexNum; ++u) {
            auto pointer = this->getSuccessors(u);
            while (!pointer.end()) {
                nodeId_t v = pointer.getId();
                weight_t weight = pointer.getWeight();
                if (dist[u] != inf && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
                pointer.toNext();
            }
        }
    }

    for (auto& d : dist) {
        if (d >= inf) d = -1;
    }

    return dist;
}
