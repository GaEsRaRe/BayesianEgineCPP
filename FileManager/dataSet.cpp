//
//  dataSet.cpp
//  TopicosC++
//
//  Created by Gabriel Ramirez on 13/08/18.
//  Copyright © 2018 Gabriel Ramirez. All rights reserved.
//

#include "dataSet.hpp"

#include <iostream>
#include <fstream>

dataSet::dataSet(){
    
}

dataSet::dataSet(std::string address){
    std::ifstream file;
    std::string test;
    
    std::cout << "testing de abrir: " << address << "\n";
    
    file.open(address);
    while(!file.eof()){
        file >> test;
        std::cout << test << "\n";
    }
    file.close();
    std::cout << "File " << address <<" done \n";
    
    
}

