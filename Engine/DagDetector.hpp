//
//  DagDetector.hpp
//  TopicosC++
//
//  Created by Gabriel Ramirez on 14/08/18.
//  Copyright © 2018 Gabriel Ramirez. All rights reserved.
//

#ifndef DagDetector_hpp
#define DagDetector_hpp

#include <stdio.h>
#include <vector>
#include <stack>
#include <iostream>

class DagDetector{
private:
    std::vector<bool> marked;
    std::vector<int> edgeTo;
    std::vector<bool> onStack;
    std::vector<int> Cycle;
    
public:
    DagDetector();
    DagDetector(std::vector<std::vector<int>> G);
    std::vector<int> obtenerVecinos(std::vector<std::vector<int>> G, int v);
    void dfs(std::vector<std::vector<int>> G, int v);
    bool hasCycle();
};

#endif /* DagDetector_hpp */
