//
//  Measure.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 15/07/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Measure__
#define __Algorithmic_Composer__Measure__

#include "Implementation.h"
#include "Note.h"


class Measure{
    friend class Score_Maker;
//ATTRIBUTES*********************
private:
    vector<Note*> notes;
    int number_of_notes;
    float current_subdivision;
    float max_beats;
    int measure_num;


//METHODS*********************    
public:
    Measure(int _measure_num,float &_max_beats, int &divisions, TS &time_signature, MusicXML2::Sxmlelement elt);
    void print_measure();
    const int how_many_notes();
    Note* get_head();
    Note* get_tail();
    const int what_measure_num();
    ~Measure();
    
protected:
    Measure(int _measure_num);
    void add_note(Note *n);
    
private:
    vector<string> get_note_info(MusicXML2::Sxmlelement elt);
    void add_note(string value, int duration, char pitch, int octave, int alteration, bool rest);
   
    
};

#endif /* defined(__Algorithmic_Composer__Measure__) */
