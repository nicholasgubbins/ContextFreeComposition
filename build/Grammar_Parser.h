//
//  Grammar_Parser.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 11/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Grammar_Parser__
#define __Algorithmic_Composer__Grammar_Parser__

#include <iostream>
#include "Implementation.h"
#include "MiscUtils.h"
#include "RDSGraph.h"
#include "special.h"
#include "TimeFuncs.h"

class Grammar_Parser {
    RDSGraph *graph;
    vector<vector<string>> sequences;
    SearchPath sp;
    float eta;
    float alpha;
    int context_size;
    float coverage;
    
public:
    Grammar_Parser(string filename);
    vector<string> generate_new();
    ~Grammar_Parser();

private:
    void read(string filename);
};

#endif /* defined(__Algorithmic_Composer__Grammar_Parser__) */
