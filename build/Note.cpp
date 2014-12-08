//
//  Note.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 15/07/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include "Note.h"
#include<iostream>

using namespace std;



//--------------------------------------------------------------------------------
//constructor for a normal note
//--------------------------------------------------------------------------------
Note::Note(string _value, int _duration, char _pitch, int _octave, int _alteration, float _subdivision, float maxbeats){
    duration = (_duration == 0) ? value_to_sub_div(_value): _duration;  //represents the length of a note but is depedent on the way a bar is divided in XML
    duration = get_max_length(duration);                                //in case the note is not a recognised value i.e dotted
    value = _value;                                                     //the value e.g quarter, half
    pitch = _pitch;                                                     //pitch in char form
    octave = _octave;                                                   //octave in int form
    rest = false;                                                       //rest
    subdivision = (_subdivision == 0) ? duration : _subdivision;        //subdivision within a bar (i.e where it falls in the bar/how far through (unused))
    alteration = _alteration;                                           //sharp or flat?
    sn = convert_to_simple_note(pitch, alteration, octave);             //simple note form of the pitch used by matrices
    subdiv_for_chord = (maxbeats == 0) ? duration : duration/maxbeats;  //get the subdivision based on the bar's time signature, not divisions
}

//--------------------------------------------------------------------------------
//constructor for a rest
//--------------------------------------------------------------------------------
Note::Note(string _value, int _duration, float _subdivision, float maxbeats){
    rest = true;
    duration = (_duration == 0) ? value_to_sub_div(_value): _duration;
    value = _value;
    subdivision = _subdivision;
    pitch = '_';
    octave = -1;
    alteration = 0;
    sn.pitch = -1;
    sn.octave = -1;
    subdiv_for_chord = (maxbeats == 0) ? duration : duration/maxbeats;
}

void Note::update_next(Note *_next){next = _next;}
void Note::update_previous(Note *_previous){previous = _previous;}


//PUBLIC FUNCTIONS*********************

//--------------------------------------------------------------------------------
//attribute accessors
//--------------------------------------------------------------------------------
const bool Note::is_rest(){return rest;}
const float Note::what_subdivision(){return subdivision;}
const char Note::what_pitch(){return (rest) ? '_' : pitch;}
const string Note::what_value(){return value;}
const int Note::what_alter(){return alteration;}
Note* Note::get_next(){return next;}
Note* Note::get_previous(){return previous;}
const Simple_Note Note::get_simple(){return sn;}
const float Note::what_subdivforchord(){return subdiv_for_chord;}
const float Note::get_other_duration(){return other_duration;}
const int Note::what_octave(){return octave;}


//--------------------------------------------------------------------------------
//function that  the overall note value (used by print measure)
//--------------------------------------------------------------------------------
string Note::overall_note(){
    string ret;
    ret +=  pitch;
    if (alteration == 1)
        ret += "#";
    else if (alteration == -1)
        ret += "b";
    ret +=  to_string(octave) + " " + to_string(duration) + "/" + to_string(subdivision)+ " , ";
    //ret += to_string(octave) + " " + value + "(" + to_string(duration) + ")";
    return ret;
}

//PROTECTED FUNCTIONS*********************

//--------------------------------------------------------------------------------
//Constructor for the Score_Creator to create notes
//--------------------------------------------------------------------------------

Note::Note(string _value, float _subdivision, float _duration, Simple_Note _note, bool _rest){
    value = _value;
    subdivision = _duration;            //location within a bar
    subdiv_for_chord = subdivision;     //used for the chord class represents float duration
    duration = _duration;               //duration based on the divisions of the bar
    rest = _rest;
    other_duration = _duration;
    sn = _note;
    alteration = 0;
    octave = sn.octave;
    if (rest) {pitch = '_', octave = -1; alteration = 0;}
    else{
        string v;
        v = convert_to_note(_note);
        if (v.length() > 1){
            if (v[1] == '#')
                alteration++;
        }
        pitch = v[0];
    }
    
}

void Note::update_length(float i){
    other_duration+= i;
    value = duration2type(other_duration);
    subdivision+= i;
    subdiv_for_chord += i;
}


