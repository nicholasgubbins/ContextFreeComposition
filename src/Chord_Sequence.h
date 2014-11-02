//
//  Chord_Sequence.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 08/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Chord_Sequence__
#define __Algorithmic_Composer__Chord_Sequence__

#include "Implementation.h"
#include "Chord.h"

class Chord_Sequence{
    friend class Score;
    
//ATTRIBUTES*********************
private:
    vector<Chord *> sequence;
    

//METHODS*********************
protected:
    Chord_Sequence();
    void add_chord(vector<Note*> notes);
    void print_sequence();
    void print_notes();
    ~Chord_Sequence();
    vector<vector<int>> get_note_sequence();
    bool right_key();
};



#endif /* defined(__Algorithmic_Composer__Chord_Sequence__) */
