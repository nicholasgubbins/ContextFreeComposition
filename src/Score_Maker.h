//
//  Score_Maker.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 10/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Score_Maker__
#define __Algorithmic_Composer__Score_Maker__

#include <iostream>
#include "Matrix_Master.h"
#include "Grammar_Parser.h"


class Score_Maker {

//ATTRIBUTES*********************
private:
    Matrix_Master *mm;
    Grammar_Parser *gp;
    string output;
    int order;
    
//METHODS*********************
public:
    Score_Maker(Matrix_Master *_m, Grammar_Parser *_gp, string output);
    void create_new_score();
    
private:
    //the three score creation options
    void create_new_blind(int measures, int modality);
    void create_new_harmony_first();
    void create_new_melody_first(int measures, int modality);
   
    //Markovian generators
    float randomDuration(int voice, vector<string> previous_rhythms);
    Simple_Note randomNote(int voice, vector<Simple_Note> previous_notes, int modality);
    float randomendDuration(int voice, vector<string> previous_rhythms);
    Simple_Note randomendNote(int voice, vector<Simple_Note> previous_notes, int modality);
    
    //Part creators
    void create_blind_part(Part *p, int modality);
    void create_weighted_part(Part *part, Part *melody, vector<vector<int>> harmony, int voice, int modality);
    
    //grammar generator and part creators
    void create_part_from_grammar(Part *p, vector<vector<double>> rhythms, vector<int> pitches);
    vector<float> get_values_from_grammar(string chord);
};

#endif /* defined(__Algorithmic_Composer__Score_Maker__) */
