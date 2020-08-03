//
//  DagDetector.cpp
//  TopicosC++
//
//  Created by Gabriel Ramirez on 14/08/18.
//  Copyright © 2018 Gabriel Ramirez. All rights reserved.
//

#include "DagDetector.hpp"


DagDetector::DagDetector(){
    std::vector<bool> marked;
    std::vector<int> edgeTo;
    std::vector<bool> onStack;
}

DagDetector::DagDetector(std::vector<std::vector<int>> G){
    int sizeG = (int)G.size();
    for (int i = 0; i < sizeG; i++) {
        marked.push_back(false);
        edgeTo.push_back(0);
        onStack.push_back(false);
    }
    for (int v = 0; v < (int)G.size(); v++) {
        if (!marked.at(v) && Cycle.size() == 0 )
        dfs(G,v);
        
    }
}
std::vector<int> DagDetector::obtenerVecinos(std::vector<std::vector<int>> G, int v){
    int i;
    std::vector<int> hijos;
    for (i = 0; i < (int)G.size(); i++) {
        
        if (G.at(i).at(v) != 0) hijos.push_back(i);
        
    }
    return hijos;
    
}
void DagDetector::dfs(std::vector<std::vector<int>> G, int v){
    onStack.at(v) = true;
    marked.at(v) = true;
    std::vector<int> vecino = obtenerVecinos(G, v);
    for(int w : vecino){
        if (!Cycle.empty()) {
            return;
        }else if (!marked.at(w)){
            edgeTo.at(w) = v;
            dfs(G, w);
        }else if(onStack.at(w)){
            Cycle.clear();
            for(int x = v; x != w; x = edgeTo.at(x)){
                Cycle.push_back(x);
                
            }
            Cycle.push_back(w);
            Cycle.push_back(v);
            
        }
    }
    onStack.at(v) = false;
}
bool DagDetector::hasCycle(){
    if(Cycle.empty()) return false;
    return true;
}
