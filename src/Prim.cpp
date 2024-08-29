#include<Graph.h>
#include<iostream>

 weight_t LinkGraph::mst(){
	std::priority_queue<std::pair<weight_t, nodeId_t>, std::vector<std::pair<weight_t, nodeId_t>>, std::greater<>> pq;
    std::vector<bool>vis (this->getNodeNum());
    int n = this->getNodeNum();
    int now = 1;
    vis[0]=true;
    auto pointer = getSuccessors(0);
    while(!pointer.end()) {
        nodeId_t nei = pointer.getId();
        weight_t wei = pointer.getWeight();
        pq.push({wei, nei});
        pointer.toNext();
    }
    weight_t s = 0;
    while(now<n){
        std::pair<weight_t, nodeId_t> edge = pq.top();
        pq.pop();
        s += edge.first;
        if(!vis[edge.second]){
            vis[edge.second]=true;
            auto pointer = getSuccessors(edge.second);
            while(!pointer.end()) {
                nodeId_t nei = pointer.getId();
                weight_t wei = pointer.getWeight();
                if (!vis[nei]){
                    pq.push({wei, nei});
                }
                pointer.toNext();
            }
            now++;
        }
    }
    return s;

 }