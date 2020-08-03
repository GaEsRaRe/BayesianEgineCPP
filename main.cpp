//
//  main.cpp
//  TopicosC++
//
//  Created by Gabriel Ramirez on 13/08/18.
//  Copyright © 2018 Gabriel Ramirez. All rights reserved.
//

#include <iostream>
#include "dataSet.hpp"
#include "tools.hpp"
#include <vector>
#include <list>
#include <math.h>
#include "DagDetector.hpp"
#include "Engine.hpp"
#include <cmath>

#include "cli.hpp"

int factorial(int size){
    int n = 1;
    for (int i = 1; i<=size; i++) n *= i;
    return n;
}

//Just In case
int factorial(int size, int min){
    int n = 1;
    for (int i = 1; i<=size; i++) n *= i;
    return n;
}


int combinatoria(int n, int x){
    int up = factorial(n);
    int down_1 = factorial(x);
    int down_2 = factorial(n-x);
    int result = up / (down_1*down_2);
    return result;
}



std::vector<int> Convert(int n,int size)
{
    std::vector<int> ans(size,0);
    int remainder = 1, step = 1;
    while (n!=0)
    {
        remainder = n%2;
        ans.at(ans.size() - step) = remainder;
        step++;
        n /= 2;
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    // For Testing purpouses 
    /*
    std::string fileAddress = "data.csv";
    
    DataArray testData = DataArray(fileAddress);
    dataSet testData2 = dataSet(fileAddress);
    
    std::cout << testData.data.at(3).at(2) << "\n";
    //Para contar elija
    testData.getCounting({0,1,1}, {0,1,1},true);
    std::cout<< "Marginal: \n";

    
    
    //Para Distribucion conjunta
    std::vector<int> conjVars({0,1,2});
    std::vector<int> conjVals({0,0,1});
    double conjunta = testData.getDistribution(conjVars,conjVals);
    std::cout << "Distribucion conjunta de P(";
    for (int i = 0; i < conjVars.size(); i++) {
        if(i == conjVars.size() - 1){
            std::cout << conjVars.at(i) << " = " << conjVals.at(i);
        }else{
             std::cout << conjVars.at(i) << " = " << conjVals.at(i) <<',';
        }
    }
    std::cout << ") = " << conjunta << "\n";
    
    int condVar = 0;
    int condVal = 1;
    std::vector<int> condVars({1,2});
    std::vector<int> condVals({1,1});
    double condicional = testData.condition(condVar, condVal, condVars, condVals);
    std::cout << "Distribucion condicional de P(" << condVar << "=" << condVal << " |";
    for (int i = 0; i < condVars.size(); i++) {
        if(i == conjVars.size() - 1){
            std::cout << condVars.at(i) << " = " << condVals.at(i);
        }else{
            std::cout << condVars.at(i) << " = " << condVals.at(i) <<',';
        }
    }
    std::cout << ") = " << condicional << "\n";
    
    std::cout << "CONDICIONAR \n";
    //Condicionar
    //TEMPORALMENTE ASUME QUE LA VARIABLE ES BINARIA, FALTA ARREGLAR
    //int value = 0;
    //std::vector<int> reductionVar({1});
    //std::vector<int> reductionVal({0});
    //testData.conditioning(value, reductionVar, reductionVal);
    //testData.showCards();
    
    
    //testData.fillCard({2,3,2,2});  //Llena las cardinalidades;
    
    //Llenar funcion
    
    // calcularDisCond(varPrin, varPadres, valPrin,  valPadres, alpha);
    //system("mkdir ./DataTest");
     */
    
    consoleCLI console;
    console.start();
    //probs = calcularFactor(4,probs, vars, testData.cards, testData.data);
    //testData.calcularDisCond(0,{1,2},1);
    //testData.calcularDisCond(0, vars, 1);
}


