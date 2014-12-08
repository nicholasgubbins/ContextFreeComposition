//
//  Part_Matrix.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 01/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Part_Matrix__
#define __Algorithmic_Composer__Part_Matrix__

#include "Matrix.h"
#include "Implementation.h"
#include "Part.h"
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_multimap<vector<Simple_Note>, vector<Simple_Note>, Simple_Note_Hasher>partMap;

class Part_Matrix : public Matrix{
    
//ATTRIBUTES*********************
private:
    string name;
    partMap map;
    partMap reverse_map;
    vector<Simple_Note> start_notes;
    vector<Simple_Note> end_notes;
    
//METHODS*********************
public:
    Part_Matrix(string _name, int _order);
    void update(Part *p);
    Simple_Note get_random_note(vector<Simple_Note>);
    Simple_Note get_random_end_note(vector<Simple_Note>);
    void print_matrix();
    
};

#endif /* defined(__Algorithmic_Composer__Part_Matrix__) */
