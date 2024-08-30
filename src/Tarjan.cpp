#include "Graph.h"
#include <stack>

class TarjanSCC {
private:
    int index;
    std::vector<int> indices, lowlink;
    std::vector<bool> onStack;
    std::stack<nodeId_t> stack;
    std::vector<std::vector<nodeId_t>> sccs;

public:
    TarjanSCC(LinkGraph &graph) : index(0), indices(graph.getNodeNum(), -1), lowlink(graph.getNodeNum(), -1), onStack(graph.getNodeNum(), false) {
        for (nodeId_t i = 0; i < graph.getNodeNum(); i++) {
            if (indices[i] == -1) {
                dfs(graph, i);
            }
        }
    }

    void dfs(LinkGraph &graph, nodeId_t u) {
        indices[u] = lowlink[u] = index++;
        stack.push(u);
        onStack[u] = true;

        auto pointer = graph.getSuccessors(u);
        while (!pointer.end()) {
            nodeId_t v = pointer.getId();
            if (indices[v] == -1) {
                dfs(graph, v);
                lowlink[u] = std::min(lowlink[u], lowlink[v]);
            } else if (onStack[v]) {
                lowlink[u] = std::min(lowlink[u], indices[v]);
            }
            pointer.toNext();
        }

        if (lowlink[u] == indices[u]) {
            std::vector<nodeId_t> scc;
            nodeId_t v;
            do {
                v = stack.top();
                stack.pop();
                onStack[v] = false;
                scc.push_back(v);
            } while (v != u);
            sccs.push_back(scc);
        }
    }

    std::vector<std::vector<nodeId_t>> getSCCs() {
        return sccs;
    }
};
