//
//  Engine.cpp
//  TopicosC++
//
//  Created by Gabriel Ramirez on 23/08/18.
//  Copyright © 2018 Gabriel Ramirez. All rights reserved.
//

#include "Engine.hpp"

DataArray::DataArray(){
    alpha = 0.0f;
}

DataArray::DataArray(std::vector<std::vector<int>> dataRec){
    int s = (int)dataRec.at(0).size();
    bool can = true;
    for(std::vector<int> sizes : dataRec){
        if (s != (int)sizes.size()){
            //can = false;
            can = false;
        }
    }
    if(can){
        data = dataRec;
    }else{
        std::cout << "Data generate with mistakes: Data is incomplete or undefined \n";
        data = dataRec;
    }
    
    
}

DataArray::DataArray(std::string address){
    
    std::ifstream in(address);
    std::string line, c;
    for(unsigned int i = 0; getline(in,line); i++){
        c.clear();
        std::stringstream ss(line);
        std::vector<int> temp;
        for(int j = 0; getline(ss,c,','); j++){
            temp.push_back(stoi(c));
        }
        data.push_back(temp);
    }
        
    
}
void DataArray::showCards(){
    int c = 0;
    for(int card : cards){
        std::cout << "cardinalidad de variable " << c << ": " << card << "\n";
        c++;
    }
}
void DataArray::showCounting(){
    for (std::vector<int> val : counting){
        std::cout << "Var \n";
        for (int i = 0; i < val.size();i++){
            std::cout << i << "\t" << val.at(i) <<"\n";
        }
        std::cout << std::endl;
    }
}

void DataArray::fillCard(std::vector<int> cardinals){
    cards = cardinals;
}
void DataArray::fillCounting(){
    for (std::vector<int> var : data){
        std::set<int> s(std::make_move_iterator(var.begin()),std::make_move_iterator(var.end()));
        std::vector<int> sa((int)s.size());
        for (int val : var){
            sa.at(val) += 1;
        }
        counting.push_back(sa);
        }
    
}

int DataArray::getCounting(std::vector<int> queryData,std::vector<int> queryValue){
    int e = (int)queryData.size();
    int counter = 0;
    for (std::vector<int> instance : data){
        bool is_there = true;
        for(int i = 0; i < e; i++){
            if(instance.at(queryData.at(i)) != queryValue.at(i)) is_there = false;
        }
        if(is_there) counter++;
    }

    return counter;
}


int DataArray::getCounting(std::vector<int> queryData,std::vector<int> queryValue,bool debug){
    int e = (int)queryData.size();
    int counter = 0;
    for (std::vector<int> instance : data){
        bool is_there = true;
        for(int i = 0; i < e; i++){
            if(instance.at(queryData.at(i)) != queryValue.at(i)) is_there = false;
        }
        if(is_there) counter++;
    }
    std::string mix = "";
    for (int i = 0; i < queryData.size(); i++) {
        mix += std::to_string(queryData.at(i)) + ",";
        
    }
    if(debug){
            std::cout << "Se ha contado " << counter << " de la condicion " << mix << "\n";
    }
    
    return counter;
}

int DataArray::getCountingReducted(std::vector<int> queryData,std::vector<int> queryValue){
    int e = (int)queryData.size();
    int counter = 0;
    for (std::vector<int> instance : reducted){
        bool is_there = true;
        for(int i = 0; i < e; i++){
            if(instance.at(queryData.at(i)) != queryValue.at(i)) is_there = false;
        }
        if(is_there) counter++;
    }
    std::cout << "Se ha contado " << counter << "\n";
    return counter;
}

void DataArray::reduct(std::vector<int> redVar, std::vector<int> redVal){
    reducted.clear();
    bool add = true;
    for (std::vector<int> instance : data) {
        add = true;
        int i = 0;
        for(int val : redVal){
            if(instance.at(val) != redVal.at(i)) add = false;
        }
        if(add) reducted.push_back(instance);
    }
}

double DataArray::getDistribution(std::vector<int> vars, std::vector<int> vals){
     double s = (double)data.size();
    double a = (double)getCounting(vars, vals);
    double card = 1;
    for(int val : vals){
        card *= cards[val];
    }
    if(a == 0) return 0.0f;
    return (a + alpha) / (s + alpha*card); //fixed
}

void DataArray::getDistribution(std::vector<int> vars){
    int cardMax = 1;
    for(int value : vars){
        cardMax *= cards.at(value);
    }
    std::cout << "Cardinalidad " << cardMax << std::endl;
    std::vector<std::vector<int>> valArray = calcularFactores(cardMax, vars);
    for(std::vector<int> values : valArray){
        printArray(values);
        std::cout << getDistribution(vars, values) << std::endl;
    }
    
}

double DataArray::getDistributionReducted(std::vector<int> vars, std::vector<int> vals){
    double s = (double)reducted.size();
    double a = (double)getCounting(vars, vals);
    return a / s;
}

double DataArray::getMarginal(int var, int val){
    double s = (double)data.size();
    double counter = 0;
    for(std::vector<int> instance : data){
        if(instance.at(var) == val){
            counter++;
        }
    }
    double ans = (counter + alpha)/(s + (alpha * cards[val]));
    std::cout << "Var \t Val \t P \n" << var <<  "\t" << val << "\t" << ans << "\n";
    return ans;
    
}

void DataArray::getAllMarginal(int var){
    double s = (double)data.size();
    double counter = 0;
    for(std::string stringVal : valNames[var]){
        int val = findIndex(valNames[var], stringVal);
        for(std::vector<int> instance : data){
            if(instance.at(var) == val){
                counter++;
            }
        }
        double ans = counter/s;
        std::cout << "Var \t Val \t P \n" << var <<  "\t" << val << "\t" << ans << "\n";
    }
    
}

double DataArray::getMarginalReducted(int var, int val){
    double s = (double)reducted.size();
    double counter = 0;
    for(std::vector<int> instance : reducted){
        if(instance.at(var) == val){
            counter++;
        }
    }
    double ans = counter/s;
    std::cout << "Var \t Val \t P \n" << var <<  "\t" << val << "\t" << ans << "\n";
    return ans;
}

double DataArray::condition(int var, int val, std::vector<int> vars_cond, std::vector<int> vals_cond){
    std::vector<int> TopVars;
    std::vector<int> TopVals;
    TopVars.push_back(var);
    TopVals.push_back(val);
    for (int i = 0; i < vars_cond.size(); i++) {
        TopVars.push_back(vars_cond.at(i));
        TopVals.push_back(vals_cond.at(i));
    }
    double top = getDistribution(TopVars, TopVals);
    double buttom = getDistribution(vars_cond, vals_cond);
    if(buttom == 0.0f) return 0.0f;
    return top/buttom;
}


void DataArray::normalize(int var){
    //From reduced one
    //We assume that is binary(will fix that in future)
    double a = getMarginalReducted(var, 0);
    double b = getMarginalReducted(var, 1);
    
    if(a + b == 1){
        std::cout << "No se necesito normalizar \n";
    }else{
        std::cout << "Normalizacion completa \n";
    }
    std::cout << "Resultado de normalizado P(" << var << " = 0) = " << a << " y P(" << var << " = 1) = " << b << "\n";
}

void DataArray::conditioning(int value, std::vector<int> vars, std::vector<int> vals){
    reduct(vars,vals);
    normalize(value);
}


void DataArray::marginalize(std::vector<int> vars){
    //We asume we get the var sorted 0..1...2..
    std::vector<std::vector<int>> marginalData;
    
    for (std::vector<int> instance : data) {
        int c = 0;
        std::vector<int> temp;
        for(int i = 0; i < instance.size(); i++){
            if(vars.at(c) == i){
                c++;
            }else{
                temp.push_back(instance.at(i));
            }
        }
        marginalData.push_back(temp);
    }
}

double DataArray::calcularDisCond(int varPrin, std::vector<int> varPadres,int valPrin, std::vector<int> valPadres, float alpha){
    int cardMax = 1;
    for(int value : varPadres){
        cardMax *= cards.at(value);
    }
    std::vector<int> TopVars;
    std::vector<int> TopVals;
    TopVars.push_back(varPrin);
    TopVals.push_back(valPrin);
    for (int i = 0; i < varPadres.size(); i++) {
        TopVars.push_back(varPadres.at(i));
        TopVals.push_back(valPadres.at(i));
    }

    double top = getDistribution(TopVars, TopVals);

    double buttom = getDistribution(varPadres, valPadres) ;
    if(buttom == 0) return 0.0f;
    return top/buttom;
}

void DataArray::calcularDisCond(int varPrin, std::vector<int> varPadres, float alpha){
    int cardMax = 1;
    std::vector<int> varTotal;
    varTotal.push_back(varPrin);
    for(int value : varPadres){
        varTotal.push_back(value);
        cardMax *= cards.at(value);
    }
    cardMax *= cards.at(varPrin);
    for(int i = 0; i < cardMax; i++){
        std::vector<int> valTotal = calcularFactor(i,varTotal);

        int valPrin = valTotal.at(0);

        std::vector<int> valPadres;
        for(int j = 1; j < valTotal.size(); j++){
            valPadres.push_back(valTotal.at(j));
        }

        double ans = calcularDisCond(varPrin,varPadres,valPrin, valPadres, alpha);
        std::cout << ans << "\n";
    }
    
   
    //probs = calcularFactor(1, probs, varPadres, cards, data);
    
}

std::vector<std::vector<int>> DataArray::calcularFactores(int size, std::vector<int> vars){
    std::vector<std::vector<int>> combinations;
    for(int i = 0; i < size; i++){
        int m = (int)vars.size();
        std::vector<int> vals(m);
        int cardAnt = 1;
        int iVar;
        
        cardAnt = 1;
        for (int j = 0; j < m; j++) {
            iVar = vars[j];
            double fl = i / cardAnt;
            fl = std::floor(fl);
            vals[j] = (int)((int)fl % cards[iVar]);
            cardAnt *= cards[iVar];
        }
        combinations.push_back(vals);
    }
    return combinations;
}

std::vector<int> DataArray::calcularFactor(int i, std::vector<int> vars){
    int m = (int)vars.size();
    std::vector<int> vals(m);
    int cardAnt = 1;
    int iVar;
    int w;
    
    
    cardAnt = 1;
    for (int j = 0; j < m; j++) {
        iVar = vars[j];
        double fl = i / cardAnt;
        fl = std::floor(fl);
        vals[j] = (int)((int)fl % cards[iVar]);
        cardAnt *= cards[iVar];
    }
    
    for (w = 0; w<vals.size(); w++) {
        std::cout << vals[w] << "\t";
        
        
        
    }
    return vals;
}





void DataArray::checkIndependenceMI(std::vector<int> fullVar){
    double suma = 0;
    double c = 1.0f;
    for(int var : fullVar){
        c*= cards[var];
    }
    std::vector<int> VwithoutT(fullVar.begin() + 1,fullVar.end());
    std::vector<int> VwithoutTE(fullVar.begin() + 2,fullVar.end());
    std::vector<int> VwithoutE = fullVar;
    VwithoutE.erase(VwithoutE.begin() + 1);
    
    std::vector<std::vector<int>> combinations = calcularFactores(c, fullVar);
    int n = (int)data.size();
    for(std::vector<int> combination : combinations){
        double tek = getCounting(fullVar, combination);
        std::vector<int> withoutT(combination.begin() + 1,combination.end());
        std::vector<int> withoutTE(combination.begin() + 2,combination.end());
        std::vector<int> withoutE = combination;
        withoutE.erase(withoutE.begin() + 1);
        double k = getCounting(VwithoutTE, withoutTE);
        double tk = getCounting(VwithoutE, withoutE);
        double ek = getCounting(VwithoutT, withoutT);
        if (k <= 0 || tk <= 0 || ek <= 0 || tk <= 0 || tek <= 0){
            //value = 0
            for(int vale : combination){
                std::cout << vale <<"\t";
            }
            std::cout << "0 \n";
        }else{
            double value = (tek/n)*(log2((tek * k)/(tk * ek) ) );
            for(int vale : combination){
                std::cout << vale <<"\t";
            }
            std::cout << value << std::endl;
            suma += value;
            //operation
        }
    }
    std::cout << "Mutual Information = " << suma << "\n";
}

void DataArray::checkIndependenceMI2(std::vector<int> fullVar){
    double suma = 0;
    double c = 1.0f;
    for(int var : fullVar){
        c*= cards[var];
    }
    std::vector<int> VwithoutT(fullVar.begin() + 1,fullVar.end());
    std::vector<int> VwithoutTE(fullVar.begin() + 2,fullVar.end());
    std::vector<int> VwithoutE = fullVar;
    VwithoutE.erase(VwithoutE.begin() + 1);
    
    std::vector<std::vector<int>> combinations = calcularFactores(c, fullVar);
    int n = (int)data.size();
    for(std::vector<int> combination : combinations){
        double tek = getCounting(fullVar, combination);
        std::vector<int> withoutT(combination.begin() + 1,combination.end());
        std::vector<int> withoutTE(combination.begin() + 2,combination.end());
        std::vector<int> withoutE = combination;
        withoutE.erase(withoutE.begin() + 1);
        double k = data.size();
        double tk = getCounting(VwithoutE, withoutE);
        double ek = getCounting(VwithoutT, withoutT);
        if (k <= 0 || tk <= 0 || ek <= 0 || tk <= 0 || tek <= 0){
            //value = 0
            for(int vale : combination){
                std::cout << vale <<"\t";
            }
            std::cout << "0 \n";
        }else{
            double value = (tek/n)*(log2((tek * k)/(tk * ek) ) );
            for(int vale : combination){
                std::cout << vale <<"\t";
            }
            std::cout << value << std::endl;
            suma += value;
            //operation
        }
    }
    std::cout << "Mutual Information = " << suma << "\n";
}

void DataArray::checkIndependencePearson(std::vector<int> fullVar){
    double suma = 0;
    double c = 1.0f;
    for(int var : fullVar){
        c*= cards[var];
    }
    std::cout << c << "\n";
    std::vector<int> VwithoutT(fullVar.begin() + 1,fullVar.end());
    std::vector<int> VwithoutTE(fullVar.begin() + 2,fullVar.end());
    std::vector<int> VwithoutE = fullVar;
    VwithoutE.erase(VwithoutE.begin() + 1);
    
    std::vector<std::vector<int>> combinations = calcularFactores(c, fullVar);
    for(std::vector<int> combination : combinations){
        double tek = getCounting(fullVar, combination);
        std::vector<int> withoutT(combination.begin() + 1,combination.end());
        std::vector<int> withoutTE(combination.begin() + 2,combination.end());
        std::vector<int> withoutE = combination;
        withoutE.erase(withoutE.begin() + 1);
        double k = getCounting(VwithoutTE, withoutTE);
        double tk = getCounting(VwithoutE, withoutE);
        double ek = getCounting(VwithoutT, withoutT);
        double mtek = 0;
        if(k != 0.0f) mtek= (tk*ek)/ k;
        if (mtek == 0){
            //value = 0
            for(int vale : combination){
                std::cout << vale <<"\t";
            }
            std::cout << "0 \n";
        }else{
            double value = pow((tek - mtek),2)/mtek;
            for(int vale : combination){
                std::cout << vale <<"\t";
            }
            std::cout << value << std::endl;
            suma += value;
            //operation
        }
    }
    std::cout << "Pearson = " << suma << "\n";
}

void DataArray::addParent(int var, int varParent){
    depedencyMatrix[var][varParent] = 1;
}

bool DataArray::checkComplete(){
    if(cards.size() == 0) return false;
    if(varNames.size() == 0) return false;
    for (int thiscard : cards) {
        if (thiscard == 0) return false;
    }
    //time to replace all
    std::vector<std::vector<int>> replacementData;
    for(std::vector<std::string> line : stringData){
        bool valid = true;
        std::vector<int> temp;
        for(int i = 0; i < line.size(); i++){
            if(findIndex(valNames[i], line[i]) != -1){
                temp.push_back(findIndex(valNames[i], line[i]));
            }else{
                valid = false;
                break;
            }
        }
        if(valid) replacementData.push_back(temp);
    }
    data = replacementData;
    for(std::vector<int> line : data){
        for(int value : line){
            std::cout << value << "\t";
        }
        std::cout << std::endl;
    }
    isComplete = true;
    return true;
}
