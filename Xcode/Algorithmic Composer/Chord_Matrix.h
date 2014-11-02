//
//  Chord_Matrix.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 01/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Chord_Matrix__
#define __Algorithmic_Composer__Chord_Matrix__





#include "Matrix.h"
#include "Implementation.h"
#include "Part.h"
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

typedef unordered_multimap<vector<vector<int>>, vector<vector<int>>, VectorVectorInt_Hasher> harmonicMap;

class Chord_Matrix : public Matrix{
    
//ATTRIBUTES*********************
private:
    harmonicMap map;
    harmonicMap reverse_map;
    
    vector<vector<int>> start_chords_major;
    vector<vector<int>> start_chords_minor;
    vector<vector<int>> end_chords_major;
    vector<vector<int>> end_chords_minor;
    

//METHODS*********************
public:
    Chord_Matrix(int _order);
    void update(Part *p);
    void update_harmony(vector<vector<int>>, int modality);
    vector<int> get_random_chord(vector<vector<int>> notes, int modality);
    vector<int> get_random_harmonising_chord(vector<vector<int>> notes, int voice, int pitch, int modality);
    vector<int> get_random_end_harmonising_chord(vector<vector<int>> notes, int voice, int pitch, int modality);
    vector<int> find_shared_chord(vector<vector<int>> notes1, vector<vector<int>> notes2,int voice, int pitch, int modality);
};


#endif /* defined(__Algorithmic_Composer__Chord_Matrix__) */