//
//  cli.cpp
//  TopicosC++
//
//  Created by Gabriel Ramirez on 19/09/18.
//  Copyright © 2018 Gabriel Ramirez. All rights reserved.
//

#include "cli.hpp"


void consoleCLI::cli_data(std::string dir) {
	std::cout << "Reading data from " << dir << std::endl;
    std::ifstream in(dir);
    std::string line, c;
    std::vector<std::vector<std::string>> Array;
    for(unsigned int i = 0; getline(in,line); i++){
        c.clear();
        std::stringstream ss(line);
        std::vector<std::string> temp;
        for(int j = 0; getline(ss,c,','); j++){
            temp.push_back(c);
        }
        Array.push_back(temp);
    }
    Dataset.stringData.clear();
    Dataset.stringData = Array;
    for (std::vector<std::string> line : Array) {
        for(std::string value : line){
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
}

void consoleCLI::cli_vars(std::string svars) {
    std::vector<std::string> vars;
    if (size_t found = svars.find(" ", 0) != std::string::npos)
    {
        int pos = (int)svars.find(' ', 0);
        std::string left = svars.substr(0, pos);
        std::string right = svars.substr(pos + 1, std::string::npos);
        vars.push_back(left);
        while(size_t found = right.find(" ", 0) != std::string::npos){
            pos = (int)right.find(' ', 0);
            left = right.substr(0, pos);
            right = right.substr(pos + 1, std::string::npos);
            vars.push_back(left);
        }
        vars.push_back(right);
        Dataset.varNames = vars;
        Dataset.valNames.clear();
        std::vector<int> cards(vars.size(), 0);
        std::vector<std::vector<int>> dependency(vars.size(),cards);
        Dataset.cards = cards;
        Dataset.depedencyMatrix = dependency;
        for(int i = 0; i < cards.size(); i++){
            Dataset.valNames.push_back(std::vector<std::string>());
        }
        
    }else{
        std::cout << "Syntax error \n";
    }
}

void consoleCLI::cli_vals(std::string svals) {
    std::vector<std::string> vals;
    std::string var;
    if (size_t found = svals.find(" ", 0) != std::string::npos)
    {
        int pos = (int)svals.find(' ', 0);
        std::string left = svals.substr(0, pos);
        var = left;
        std::string right = svals.substr(pos + 1, std::string::npos);
        //Left var right vals
        while(size_t found = right.find(" ", 0) != std::string::npos){
            pos = (int)right.find(' ', 0);
            left = right.substr(0, pos);
            right = right.substr(pos + 1, std::string::npos);
            vals.push_back(left);
        }
        vals.push_back(right);
        
        //Add and cardinalidad
        int index = findIndex(Dataset.varNames, var);
        if(index != -1){
            Dataset.cards[index] = (int)vals.size();
            Dataset.valNames[index] = vals;
            if(Dataset.checkComplete())std::cout << "Complete \n";
        }else{
            std::cout << "Var not found \n";
        }
        
    }else{ //Want to see the var with that value
        
    }
}

void consoleCLI::cli_cards() {
	std::cout << "Cardinalidades \n";
    //Only show cars
    int i = 0;
    for (int card: Dataset.cards) {
        std::cout << "Variable[" << i << "] = " << card << "\n";
        i++;
    }
}

void consoleCLI::cli_arco(std::string instruction) {
    if (size_t found = instruction.find(" ", 0) != std::string::npos)
    {
        int pos = (int)instruction.find(' ', 0);
        std::string left = instruction.substr(0, pos);
        std::string right = instruction.substr(pos + 1, std::string::npos);
        int indexLeft = findIndex(Dataset.varNames, left);
        int indexRight = findIndex(Dataset.varNames, right);
        if( indexLeft != -1 &&  indexRight != -1){
            std::vector<std::vector<int>> dagChecker = Dataset.depedencyMatrix;
            dagChecker[indexLeft][indexRight] = 1;
            DagDetector test(dagChecker);
            if(test.hasCycle()){
                std::cout << "Sorry, this operation generate cycles \n";
                return;
            }
            Dataset.addParent(findIndex(Dataset.varNames, left), findIndex(Dataset.varNames, right));
            for (std::vector<int> n : Dataset.depedencyMatrix) {
                for(int value : n){
                    std::cout << value << "\t";
                }
                std::cout << std::endl;
            }
        }else{
            std::cout << "One or more variables don't exist in the dataset \n";
            return;
        }
        
    }else{ //Not complete instruction
        std::cout << "Instrucction incomplete \n";
        return;
    }
}

void consoleCLI::cli_prob(std::string prob) {
    if(!Dataset.isComplete){
        std::cout << "Dataset is not setup completly yet \n";
        return;
    }
	std::cout << "Seccion prob base of " << prob <<"\n";
    if (size_t found = prob.find(" ", 0) != std::string::npos)
    {
        int pos = (int)prob.find(' ', 0);
        std::string left = prob.substr(0, pos);
        std::string var = left;
        std::string right = prob.substr(pos + 1, std::string::npos);
        if (size_t found = right.find(" ", 0) != std::string::npos)
        {
            pos = (int)right.find(' ', 0);
            left = right.substr(0, pos);
            right = prob.substr(pos + 1, std::string::npos);
            if(left == "-v"){
                //continue
                pos = (int)right.find(' ', 0);
                right = right.substr(pos + 1, std::string::npos);
                if (size_t found = right.find(" ", 0) != std::string::npos)
                {
                    std::cout << "only one val is accepted \n";
                    }else{
                        std::cout << "Val selected " << right << "\n";
                        int varIndex = findIndex(Dataset.varNames, var);
                        int valIndex = findIndex(Dataset.valNames[findIndex(Dataset.varNames, var)], right);
                        Dataset.getMarginal(varIndex, valIndex);
                    }
            }else{
                return;
            }
           
        }else{
            std::cout << "Wrong sytaxis \n";
        }
    }else{ //Want to see all chances
        Dataset.getAllMarginal(findIndex(Dataset.varNames, prob));
    }
}

void consoleCLI::cli_alpha(std::string salpha) {
    try{
        size_t i(0);
        float alpha = std::stof(salpha, &i);
        std::cout << "alpha set to: " << alpha << std::endl;
        Dataset.alpha = alpha;
    }catch(...){
        std::cout << "Input for alpha: " << salpha << " is invalid \n";
    }
    
}
void consoleCLI::cli_probConj(std::string vals){
    std::vector<std::string> part = getSeparatedString(vals);
    bool valTime = false;
    std::vector<int> varArray;
    std::vector<int> valArray;
    int c = 0;
    if(findIndex(part, "-v") != -1){
        for(std::string value : part){
            if(value == "-v"){
                valTime = true;
                continue;
            }else{
                if(!valTime){
                    varArray.push_back(findIndex(Dataset.varNames, value));
                }else{
                    valArray.push_back(findIndex(Dataset.valNames[varArray[c]], value));
                    c++;
                }
            }
        }
        std::cout << "Probabilidad resultante: " << Dataset.getDistribution(varArray, valArray) << std::endl;
    }else{
        std::vector<int> values;
        for(std::string value : part){
            values.push_back(findIndex(Dataset.varNames, value));
        }
        Dataset.getDistribution(values);
    }
}

void consoleCLI::cli_probCond(std::string vals){
    std::vector<std::string> part = getSeparatedString(vals);
    bool valTime = false;
    std::vector<int> varArray;
    std::vector<int> valArray;
    int c = 0;
    if(findIndex(part, "-v") != -1){
        for(std::string value : part){
            if(value == "-v"){
                valTime = true;
                continue;
            }else{
                if(!valTime){
                    varArray.push_back(findIndex(Dataset.varNames, value));
                }else{
                    valArray.push_back(findIndex(Dataset.valNames[varArray[c]], value));
                    c++;
                }
            }
        }
        int mainVar = varArray[0];
        int mainVal = valArray[0];
        varArray.erase(varArray.begin());
        valArray.erase(valArray.begin());
        std::cout << Dataset.calcularDisCond(mainVar, varArray, mainVal, valArray, Dataset.alpha) << std::endl;
    }else{
            for(std::string value : part){
                        varArray.push_back(findIndex(Dataset.varNames, value));
            }
            int mainVar = varArray[0];
            varArray.erase(varArray.begin());
        Dataset.calcularDisCond(mainVar, varArray, Dataset.alpha);
    }
}


void consoleCLI::cli_probMarginal(std::string instructions) {
    std::vector<std::string> part = getSeparatedString(instructions);
    if(findIndex(part,"probCond") == -1){
        std::cout << "Wrong syntax, laking of Conditional instruction \n";
    }else{
        std::vector<std::string> toIgnore;
        std::vector<std::string> values;
        bool second = false;
        for(std::string value : part){
            if(value == "probCond"){
                second = true;
            }
            if(second && findIndex(toIgnore, value) != -1){
                values.push_back(value);
            }else if(!second){
                toIgnore.push_back(value);
            }
        }
        std::vector<int> vals;
        for(std::string value : values){
            vals.push_back(findIndex(Dataset.varNames, value));
        }
        Dataset.getDistribution(vals);
        
    }
    
}

void consoleCLI::cli_mutualInformation(std::string svars) {
    std::vector<std::string> part = getSeparatedString(svars);
    std::vector<int> vars;
    for(std::string var : part){
        if(findIndex(Dataset.varNames, var) != -1){
            vars.push_back(findIndex(Dataset.varNames, var));
        }else{
            std::cout << "Variable not valid \n";
            return;
        }
    }
    if(vars.size() >= 3){
            Dataset.checkIndependenceMI(vars);
    }else{
        Dataset.checkIndependenceMI2(vars);
    }
    
}

void consoleCLI::cli_pearson(std::string svars) {
    std::vector<std::string> part = getSeparatedString(svars);
    std::vector<int> vars;
    for(std::string var : part){
        if(findIndex(Dataset.varNames, var) != -1){
            vars.push_back(findIndex(Dataset.varNames, var));
        }else{
            std::cout << "Variable not valid \n";
            return;
        }
    }
    
    Dataset.checkIndependencePearson(vars);
}

void consoleCLI::cli_help() {
	std::cout << "HOW TO USE THIS ENGINE \nCOMMANDS: \ndata address \nprob var val \n";
}
void consoleCLI::selector(std::string text) {
    //MultiLine selector
	if (size_t found = text.find(" ", 0) != std::string::npos)
	{
		int pos = (int)text.find(' ', 0);
		std::string left = text.substr(0, pos);
		std::string right = text.substr(pos + 1, std::string::npos);

		//first selector: 
		if (left == "data") {
			cli_data(right);
		}
		else if (left == "vals") {
			cli_vals(right);
		}
        else if (left == "prob") {
            cli_prob(right);
        }else if (left == "probConj") {
            cli_probConj(right);
        }
        else if (left == "probCond") {
            cli_probCond(right);
        }
        else if (left == "mi") {
            cli_mutualInformation(right);
        }else if(left == "pearson"){
            cli_pearson(right);
        }
		else if (left == "vars") {
			cli_vars(right);
		}
		else if (left == "alpha") {
			cli_alpha(right);
		}
        else if (left == "arco") {
            cli_arco(right);
        }
		else if (left == "help") {
			cli_help();
		}
        else if (left == "marginal") {
            cli_probMarginal(right);
        }
		else {
			std::cout << "We are sorry the " <<  left <<" command do not exist..." << std::endl;
		}
    }else{ //One line var
        if (text == "cards") {
            cli_cards();
        }else if (text == "help"){
            cli_help();
        }
    }

}



void consoleCLI::start(){
    std::string line;
    while(line != "q"){
        if(line == "clear")std::cout << std::string(50, '\n');
        std::cout << ">>";
        getline (std::cin, line);
        //std::cout << ">>" << line << "\n";
        selector(line);
    }
}
