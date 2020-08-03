//
//  tools.hpp
//  TopicosC++
//
//  Created by Gabriel Ramirez on 14/08/18.
//  Copyright © 2018 Gabriel Ramirez. All rights reserved.
//

#ifndef tools_hpp
#define tools_hpp

#include <vector>
#include <string>

#include <stdio.h>


void showMatrix(std::vector<std::vector<int>> Matrix);
std::vector<std::vector<int>> makeMatrix(std::vector<int> array, int size);

std::vector<std::vector<int>> reduceBy(std::vector<std::vector<int>> data, int position, int value);

std::vector<std::vector<int>> readCsv(std::string file);

int findIndex(std::vector<std::string> array, std::string dataToFind);

std::vector<std::string> getSeparatedString(std::string vals);

void printArray(std::vector<int> array);

void printArray(std::vector<int> array, std::string separator);
void debugHere();
#endif /* tools_hpp */
