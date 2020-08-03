//
//  tools.cpp
//  TopicosC++
//
//  Created by Gabriel Ramirez on 14/08/18.
//  Copyright © 2018 Gabriel Ramirez. All rights reserved.
//

#include "tools.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
void showMatrix(std::vector<std::vector<int>> matrix){
    int rows = (int)matrix.size();
    int cols = (int)matrix.at(0).size();
    std::cout << "matrix size of = " << rows << " x " << cols <<" \n" ;
    for (int i = 0; i < rows; i++) {
        for (int j = 0;j < cols; j++) {
            std::cout << matrix.at(i).at(j) << "\t";
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<int>> makeMatrix(std::vector<int> array, int size){
    std::vector<std::vector<int>> matrix;
    for (int i = 0; i< size; i++) {
        std::vector<int> temp;
        for (int j = 0; j< size; j++) {
            temp.push_back(0);
        }
        matrix.push_back(temp);
    }
    int s = 0;
    for(int i = 0; i <size; i++){
        for(int j = 0; j<size; j++){
            if(i != j){
                matrix.at(i).at(j) = array.at(s);
                s++;
                
            }
        }
    }
    return matrix;
}


std::vector<std::vector<int>> reduceBy(std::vector<std::vector<int>> data, std::vector<int> positions,std::vector<int> values){
    std::vector<std::vector<int>> reducted;
    bool add = true;
    for (std::vector<int> instance : data) {
        add = true;
        int i = 0;
        for(int val : positions){
            if(instance.at(val) != values.at(i)) add = false;
        }
        if(add) reducted.push_back(instance);
    }
    
    return data;
}

std::vector<std::vector<int>> readCsv(std::string file){
    std::ifstream in(file);
    std::string line, c;
    std::vector<std::vector<int>> datar;
    for(int i = 0; getline(in,line); i++){
        c.clear();
        std::stringstream ss(line);
        std::vector<int> temp;
        for(int j = 0; getline(ss,c,','); j++){
            temp.push_back(stoi(c));
        }
        datar.push_back(temp);
    }
    
    
    return datar;
}

int findIndex(std::vector<std::string> array, std::string dataToFind){
    int index = -1;
    for (int i = 0; i < array.size(); i++) {
        if(array[i] == dataToFind){
            index = i;

            break;
        }
    }
    return index;
}

std::vector<std::string> getSeparatedString(std::string vals){
    std::vector<std::string> part;
    if (size_t found = vals.find(" ", 0) != std::string::npos)
    {
        int pos = (int)vals.find(' ', 0);
        std::string left = vals.substr(0, pos);
        std::string right = vals.substr(pos + 1, std::string::npos);
        part.push_back(left);
        while(size_t found = right.find(" ", 0) != std::string::npos){
            pos = (int)right.find(' ', 0);
            left = right.substr(0, pos);
            right = right.substr(pos + 1, std::string::npos);
            part.push_back(left);
        }
        part.push_back(right);
    }
    
    return part;
    
}

void printArray(std::vector<int> array){
    for(int value :array){
        std::cout << value << "\t";
    }
}

void printArray(std::vector<int> array,std::string separator){
    for(int value :array){
        std::cout << value << separator;
    }
}
void debugHere(){
    std::cout << "here \n";
}
