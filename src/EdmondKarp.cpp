# include<Graph.h>
# include<algorithm>

weight_t LinkGraph::maxFlow(nodeId_t start, nodeId_t end){
    nodeId_t n = this->getNodeNum();
    std::vector<std::vector<nodeId_t>> cap(n, std::vector<int>(n, 0));
    for(int i=0;i<n;i++){
        auto pointer = getSuccessors(i);
        while(!pointer.end()) {
            nodeId_t nei = pointer.getId();
            cap[i][nei] = pointer.getWeight();
            pointer.toNext();
        }
    }
    int sumCap = 0;
    while(true){
        std::vector<nodeId_t> order = bfsUtil(start, end, cap);
        if(order.size()==0){
            break;
        }
        weight_t minCap = 0x3f3f3f3f;
        for(int i=0; i<order.size()-1; i++){
            minCap = std::min(minCap, cap[order[i]][order[i+1]]);
        }
        for(int i=0; i<order.size()-1; i++){
            cap[order[i]][order[i+1]] -= minCap;
            cap[order[i+1]][order[i]] += minCap;
        }
        sumCap += minCap;
    }

    return sumCap;
}

std::vector<nodeId_t> LinkGraph::bfsUtil(nodeId_t start, nodeId_t end, std::vector<std::vector<nodeId_t>>& cap){
    std::vector<bool>vis (this->getNodeNum());
    std::vector<nodeId_t>pre (this->getNodeNum(), -1);
    std::queue<nodeId_t>Q;
    std::vector<nodeId_t>result;
    Q.push(start);
    vis[start] = true;
    while(!Q.empty()) {
        nodeId_t front = Q.front();
        Q.pop();
        auto pointer = getSuccessors(front);
        while(!pointer.end()) {
            nodeId_t nei = pointer.getId();
            if((!vis[nei]) && (cap[front][nei] > 0)) {
                vis[nei]=true;
                Q.push(nei);
                pre[nei] = front;
            }
            pointer.toNext();
        }
        if(front == end){
            nodeId_t node = end;
            while(node!=start){
                result.push_back(node);
                node = pre[node];
            }
            result.push_back(start);
            std::reverse(result.begin(), result.end());
            break;
        } 
    }
    return result;
}