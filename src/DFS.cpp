#include "Graph.h"

std::vector<nodeId_t> LinkGraph::dfs(nodeId_t start)
{
    std::vector<bool>vis (this->getNodeNum());
    std::vector<int> order;
    dfsUtil(start, vis, order);

    return order;
}

void LinkGraph::dfsUtil(nodeId_t u, std::vector<bool>& visited, std::vector<nodeId_t>& order) {
    visited[u] = true;
    order.push_back(u);  

    auto pointer = getSuccessors(u);
    while(!pointer.end()) {
        nodeId_t nei = pointer.getId();
        if (!visited[nei]){
            dfsUtil(nei, visited, order);
        }
        pointer.toNext();
    }
}

