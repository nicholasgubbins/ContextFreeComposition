//
//  Note.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 15/07/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Note__
#define __Algorithmic_Composer__Note__

#include "Implementation.h"

class Note{
    
    friend class Score; friend class Measure; friend class Part; friend class Score_Maker;
    
//ATTRIBUTES*********************
private:
    string value;
    int duration;
    float other_duration;
    char pitch;
    int octave;
    int alteration;
    bool rest;
    float subdivision;
    float subdiv_for_chord;
    Note* next;
    Note* previous;
    Simple_Note sn;
    
    
//METHODS*********************
private:
    void update_next(Note* _next);
    void update_previous(Note* _previous);
    
public:
    Note(string _value, int _duration, char _pitch, int _octave, int _alteration, float _subdivision, float maxbeats);
    Note(string _value, int _duration, float _subdivision, float maxbeats);
    const bool is_rest();
    const  char what_pitch();
    const  string what_value();
    const int what_octave();
    const int what_alter();
    string overall_note();
    const float what_subdivision();
    Note* get_next();
    Note* get_previous();
    const Simple_Note get_simple();
    const float what_subdivforchord();
    const float get_other_duration();

    
protected:
    Note(string _value, float _subdivision, float _duration, Simple_Note _note, bool _rest);
    void update_length(float i);
};


#endif /* defined(__Algorithmic_Composer__Note__) */
