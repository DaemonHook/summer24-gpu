#include "Graph.h"
#include <algorithm>
#include <iostream>
using namespace std;

template<typename Derived, typename Base>
std::unique_ptr<Derived> dynamic_unique_ptr_cast(std::unique_ptr<Base>&& base) {
    if (auto derived = dynamic_cast<Derived*>(base.get())) {
        return std::unique_ptr<Derived>(derived);
    }
    return nullptr;
}

void printMatrix(const std::vector<std::vector<nodeId_t>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;  // 每行结束后换行
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    srand((unsigned)time(NULL));

    vector<nodeId_t> sources, dests;
    vector<weight_t> weights;

    //自动生成
    generateRandomEdges(n,m,sources,dests,weights);

    //手动输入
    // for (int i = 0; i < m; i++) {
    //     int s, d, w;
    //     cin >> s >> d >> w;
    //     sources.push_back(s);
    //     dests.push_back(d);
    //     weights.push_back(w);
    // }

    LinkGraph linkGraph(n, sources, dests, weights);
    std::vector<std::vector<nodeId_t>> dist = linkGraph.floyd();
    std::vector<nodeId_t> order = linkGraph.dfs(0);
    for (int id : order) {
        std::cout << id << " ";
    }
    std::cout << std::endl;

    bool c = linkGraph.isConnected();
    std::cout << c << std::endl;
    // printMatrix(dist);


    nodeId_t id;
    while (cin >> id) {
        auto it = linkGraph.getSuccessors(id);
        cout << "(neighborId, edge weights) of "  << ":\n";
        for (; !it.end(); it.toNext()) {
            cout << "(" << it.getId() << ", " << it.getWeight() << ")" << '\n';
        }
    }
}