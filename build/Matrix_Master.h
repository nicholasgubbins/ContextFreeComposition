//
//  Matrix_Master.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 07/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Matrix_Master__
#define __Algorithmic_Composer__Matrix_Master__


#include "Implementation.h"
#include "Part_Matrix.h"
#include "Rhythmic_Matrix.h"
#include "Chord_Matrix.h"

#include "Score.h"

class Matrix_Master {
//ATTRIBUTES*********************
    int order;
    vector<Part_Matrix *> major;
    vector<Part_Matrix *> minor;
    vector<Rhythmic_Matrix *> rm;
    Chord_Matrix *cm;
    
//METHODS*********************
public:
    Matrix_Master(int order);
    void update(Score *s);
    void update_harmony(vector<vector<int>> note_difs);
    int what_order();
    ~Matrix_Master();
    
    //ALL GENERATORS FOR NEW MATERIAL
    Simple_Note get_random_note(vector<Simple_Note> previous_notes, int voice, int mode);
    Simple_Note get_random_end_note(vector<Simple_Note> previous_notes, int voice, int mode);
    string get_random_duration(vector<string> previous_rhythms, int voice);
    string get_random_end_duration(vector<string> previous_rhythms, int voice);
    vector<int> harmonise_voice(vector<vector<int>> previous_chords, int voice, int note, int modality, bool forwards);
    vector<int> find_shared_chord(vector<vector<int>> notes_forward, vector<vector<int>> notes_backward,int voice, int pitch, int modality);

};



#endif /* defined(__Algorithmic_Composer__Matrix_Master__) */
