//
//  Engine.hpp
//  TopicosC++
//
//  Created by Gabriel Ramirez on 23/08/18.
//  Copyright © 2018 Gabriel Ramirez. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cmath>

#include "tools.hpp"

class DataArray{
public:
    //INICIALIZAR
    DataArray();
    DataArray(std::vector<std::vector<int>> recivedData);
    DataArray(std::vector<std::vector<std::string>> recivedData);
    
    DataArray(std::string address); //DESDE CSV
    
    std::vector<std::string> varNames;
    std::vector<std::vector<std::string>> valNames;
    std::vector<int> varTags;
    std::vector<std::vector<std::string>> stringData;
    std::vector<std::vector<int>> data;
    std::vector<int> cards;
    
    std::vector<std::vector<int>> counting;
    std::vector<std::vector<int>> reducted;
    
    std::vector<std::vector<int>> depedencyMatrix;
    
    //Vars
    
    float alpha;
//FUNCTIONS
    void fillCounting();
    void fillCard(std::vector<int> cardinals);
    void showCards();
    
    
    bool isComplete = false; //When done, convert all vals to int based on the order or vals
    
    bool checkComplete();
    void addParent(int var, int varParent);
    //CONTEO GENERAL
    void getCounting(std::string query);
    //CONTEO
    int getCounting(std::vector<int> queryData,std::vector<int> queryValue);
    int getCounting(std::vector<int> queryData,std::vector<int> queryValue,bool debug);
    int getCountingReducted(std::vector<int> queryData,std::vector<int> queryValue);
    
    //MARGINAL
    double getMarginal(int var, int val);
    void getAllMarginal(int var);
    double getMarginalReducted(int var, int val);
    
    //CONJUNTA
    double getDistribution(std::vector<int> vars, std::vector<int> vals);
    void getDistribution(std::vector<int> vars);
    double getDistributionReducted(std::vector<int> vars, std::vector<int> vals);
    
    //CONDICIONAL
    double condition(int var, int val, std::vector<int> vars_cond, std::vector<int> vals_cond);
    //CODICIONAR REDUCCION
    void reduct(std::vector<int> redVar, std::vector<int> redVal);
    //CODICIONAR REDUCCION
    void normalize(int var);
    
    void conditioning(int ,std::vector<int> vars, std::vector<int> vals);
    
    void calcularDisCond(int varPrin, std::vector<int> varPadres, float alpha);
    double calcularDisCond(int varPrin, std::vector<int> varPadres,int valPrin, std::vector<int> valPadres, float alpha);
    //EXTRAS
    void marginalize(std::vector<int> vars);
    
    
    //MOSTRAR
    void showCounting();
    
    void checkIndependenceMI(std::vector<int> fullVar);
    void checkIndependenceMI2(std::vector<int> fullVar);
    
    void checkIndependencePearson(std::vector<int> fullVar);
    
    //To get
    
private:
    std::vector<int> calcularFactor(int index, std::vector<int> vars);
    std::vector<std::vector<int>> calcularFactores(int size, std::vector<int> vars);
    
};



#endif /* Engine_hpp */



