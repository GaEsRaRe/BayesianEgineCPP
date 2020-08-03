
#ifndef dataSet_hpp
#define dataSet_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

class dataSet{
    public:
    int size;
    int alpha = 0;
    int valSize = 0;
    std::vector<std::string> valNames;
    
    
    std::vector<std::vector<int>> data;
    std::vector<std::vector<std::string>> stringData;
    std::vector<int> cards;
    int dataLenght;
    std::vector<std::string> varNames;
    
    std::vector<std::string> varVals;
    std::string name;
    std::vector<std::vector<double>> factores;
    std::vector<std::vector<int>> varsComb;
    
    dataSet();
    dataSet(std::string address);

    
};


#endif /* dataSet_hpp */
