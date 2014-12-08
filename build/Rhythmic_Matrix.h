//
//  Rhythmic_Matrix.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 01/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Rhythmic_Matrix__
#define __Algorithmic_Composer__Rhythmic_Matrix__

#include "Matrix.h"
#include "Implementation.h"
#include "Part.h"
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

typedef unordered_multimap<vector<string>, vector<string>, String_Hasher> rhythmMap;

class Rhythmic_Matrix : public Matrix{
    
//ATTRIBUTES*********************
private:
    string name;
    rhythmMap map;
    rhythmMap reverse_map;
    vector<string> start_rhythms;
    vector<string> end_rhythms;
    
//METHODS*********************
public:
    Rhythmic_Matrix(string _name, int _order);
    void update(Part *p);
    string get_random_length(vector<string>);
    string get_random_end_length(vector<string>);
    void print_matrix();
};

#endif /* defined(__Algorithmic_Composer__Rhythmic_Matrix__) */
