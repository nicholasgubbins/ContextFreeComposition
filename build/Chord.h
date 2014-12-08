//
//  Chord.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 02/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Chord__
#define __Algorithmic_Composer__Chord__

#include "Implementation.h"
#include "Note.h"

class Chord{
    friend class Chord_Sequence;
//ATTRIBUTES*********************
private:
    vector<Simple_Note> notes;
    Simple_Note root;
    int inversion;
    string quality;
    int base;
    float length;
    string name;
    
//METHODS*********************
public:
    Chord(vector<Note*> _notes);
    bool is_member(int pitch);
    string get_name();
    vector<int> get_notes();
    
private:
    void analyse();
    string get_type();
    
protected:
    void update_length(float len);
};


#endif /* defined(__Algorithmic_Composer__Chord__) */
