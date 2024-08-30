#include "Graph.h"
#include <algorithm>
#include <stack>

std::vector<nodeId_t> LinkGraph::findEulerianCircuit() {
    std::vector<nodeId_t> circuit; 
    std::stack<nodeId_t> currentPath; 
    std::vector<std::vector<bool>> usedEdges(vertexNum, std::vector<bool>(vertexNum, false)); 

    currentPath.push(0);
    nodeId_t currentNode = 0;

    while (!currentPath.empty()) {
        if (outDeg[currentNode] > 0) {
            auto pointer = getSuccessors(currentNode);
            while (pointer.end() || usedEdges[currentNode][pointer.getId()]) {
                pointer.toNext();
            }
            if (!pointer.end()) {
                usedEdges[currentNode][pointer.getId()] = true;
                currentPath.push(currentNode);
                currentNode = pointer.getId();
                outDeg[currentNode]--; 
            }
        } else {
            circuit.push_back(currentNode);
            currentNode = currentPath.top();
            currentPath.pop();
        }
    }

    std::reverse(circuit.begin(), circuit.end()); 
    return circuit;
}

bool LinkGraph::hasEulerianPathOrCircuit() {
    if (isConnected()) {
        int startNodes = 0, endNodes = 0;
        for (nodeId_t i = 0; i < getNodeNum(); ++i) {
            if (outDeg[i] - inDeg[i] > 1 || inDeg[i] - outDeg[i] > 1) {
                return false;
            } else if (outDeg[i] - inDeg[i] == 1) {
                startNodes++;
            } else if (inDeg[i] - outDeg[i] == 1) {
                endNodes++;
            }
        }
        return (startNodes == 0 && endNodes == 0) || (startNodes == 1 && endNodes == 1);
    } else {
        return false;
    }
}



