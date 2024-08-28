#include "Graph.h"
#include <ctime>
#include <set>
using namespace std;


nodeId_t inf = 0x3f3f3f3f;

/// @brief 随机生成图的各条边及权值，不会出现重边
/// @param n 节点数
/// @param m 边数
/// @param sources 头数组
/// @param dests 尾数组
/// @param weights 权数组
/// @return 
void generateRandomEdges(nodeId_t n,nodeId_t m,vector<nodeId_t>& sources,vector<nodeId_t>& dests,vector<weight_t>& weights){
    set<pair<nodeId_t,nodeId_t>> tempEdges;
    while(tempEdges.size()<m){
        nodeId_t u=rand()%n;
        nodeId_t v=rand()%n;
        weight_t w=rand()%inf;
        pair<set<pair<nodeId_t,nodeId_t>>::iterator, bool> p;
        p=tempEdges.insert(make_pair(u,v));
        if(p.second){
            sources.push_back(u);
            dests.push_back(v);
            weights.push_back(w);
        }
    }
    
}