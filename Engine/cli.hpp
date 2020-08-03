//
//  cli.hpp
//  TopicosC++
//
//  Created by Gabriel Ramirez on 19/09/18.
//  Copyright © 2018 Gabriel Ramirez. All rights reserved.
//

#ifndef cli_hpp
#define cli_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <locale>
#include <vector>
#include "tools.hpp"
#include "Engine.hpp"
#include "DagDetector.hpp"

class consoleCLI{
    public:
    DataArray Dataset;
    
    void start();
    
    void selector(std::string s);
    
    void cli_data(std::string dir);
    void cli_vars(std::string vars); //Done
    void cli_vals(std::string vals); //Done
    void cli_cards(); //Done
    void cli_arco(std::string instruction); //Done
    void cli_dag(); //Done
    void cli_prob(std::string order); //Done
    void cli_alpha(std::string alpha); //Done
    void cli_marginalizar(std::string instruction); //Need
    void cli_probMarginal(std::string instructions);
    void cli_probCond(std::string vals);
    void cli_probConj(std::string vals);
    void cli_mutualInformation(std::string vars);
    void cli_pearson(std::string vars);
    void cli_condMarginal(std::string instruction);
    void cli_help();
};

//All commands


#endif /* cli_hpp */
