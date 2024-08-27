#include "Graph.h"

std::vector<nodeId_t> LinkGraph::dijkstra(nodeId_t start) {
	nodeId_t inf = 0x3f3f3f3f;
	std::vector<nodeId_t> dist(this->vertexNum, inf);
	dist[start] = 0;
	std::priority_queue<std::pair<nodeId_t, nodeId_t>, std::vector<std::pair<nodeId_t, nodeId_t>>, std::greater<>> pq;
	pq.emplace(0, start);
	while (!pq.empty()) {
		auto [dis, node] = pq.top();
		pq.pop();
		if (dis > dist[node]) { 
				continue;
		}
		// 获取 node 的邻居节点
		auto pointer = this->getNeighbors(node);
		while(pointer->end()) {
			nodeId_t neighbor_id =  pointer->get();
			// 带改动
			weight_t neighbor_weight = weights[0];
			nodeId_t new_dis = dis + neighbor_weight;
			if(new_dis < dist[neighbor_id]) {
				dist[neighbor_id] = new_dis;
				pq.emplace(new_dis,neighbor_id);
			}
			pointer->toNext();
		}
  }
	return dist;
}