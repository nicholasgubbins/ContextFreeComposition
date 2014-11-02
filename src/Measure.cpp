//
//  Measure.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 15/07/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include "Measure.h"

#include<iostream>

#include "xml.h"
#include "xmlfile.h"
#include "xmlreader.h"
#include "partsummary.h"
#include "smartlist.h"
#include "xml_tree_browser.h"

using namespace MusicXML2;
using namespace std;



//-------------------------------------------------------------------
//constructor for the measure called by Part
//-------------------------------------------------------------------
Measure::Measure(int _measure_num, float &_max_beats, int &divisions, TS &time_signature, Sxmlelement elt){
    number_of_notes = 0;
    current_subdivision = 0.0;
    max_beats = _max_beats;
    measure_num = _measure_num;
    ctree<xmlelement>::iterator iter = elt;
    while (iter != elt->end()){
        Sxmlelement xml = *iter;
        if (xml){
            if (xml->getName() == "measure" && (iter != elt))
                break;
            else if (xml->getName() == "divisions") {divisions = stoi(xml->getValue());}
            else if (xml->getName() == "beats") {time_signature.top = stoi(xml->getValue());}
            else if (xml->getName() == "beat-type") {
                time_signature.bottom = stoi(xml->getValue());
                _max_beats = (float)(time_signature.top * (divisions * (time_signature.bottom/4)));
                max_beats = _max_beats;
            }
            if (xml->getName() == "note"){
                vector<string> n = get_note_info(xml);
                bool rest = (n[0] == "") ? true : false;
                string value = n[3];
                char pitch = (rest) ? '_' : n[0][0];
                int octave = (rest) ? 0 : stoi(n[1]);
                int duration;
                try{duration = std::stoi(n[2]);}
                catch (invalid_argument){ duration = value_to_sub_div(value);}
                int alteration = (rest) ? 0 : stoi(n[4]);
                add_note(value, duration, pitch, octave, alteration, rest);
                if (number_of_notes > 1){
                    notes[number_of_notes-2]->update_next(notes[number_of_notes-1]);
                    notes[number_of_notes-1]->update_previous(notes[number_of_notes-2]);}
            }
        }
        iter++;
    }
}





//PRIVATE FUNCTIONS*********************

//--------------------------------------------------------------------------------
//utility function for the constructor which extracts a note's info from the xmltree
//--------------------------------------------------------------------------------
vector<string> Measure::get_note_info(Sxmlelement elt){
    vector<string> parts;
  /*Returns a vector in this order: */  string step, octave, duration, type, alter;
    alter = "0";
    bool chord = false;
    ctree<xmlelement>::iterator iter = elt;
    while (iter != elt->end()){
        Sxmlelement xml = *iter;
        if (xml){
            if (xml->getName() == "chord"){chord = true;}
            if (xml->getName() == "note" && (iter != elt)){break;}
            if (xml->getName() == "step")
                step = xml->getValue();
            if (xml->getName() == "alter")
                alter = xml->getValue();
            if (xml->getName() == "octave")
                octave = xml->getValue();
            if (xml->getName() == "duration")
                duration = xml->getValue();
            if (xml->getName() == "type"){
                type = xml->getValue();
                break;}
        }
        iter++;
    }
    parts.push_back(step);
    parts.push_back(octave);
    parts.push_back(duration);
    parts.push_back(type);
    parts.push_back(alter);
    return parts;
}

//--------------------------------------------------------------------------------
//utility function for the constructor which creates a note and adds it to the
//array of notes for the measure. if a rest it calls the appropriate constructor
//--------------------------------------------------------------------------------
void Measure::add_note(string value, int duration, char pitch, int octave, int alteration, bool rest){
    if (rest)
        notes.push_back(new Note(value, duration, current_subdivision, max_beats));
    else
        
        notes.push_back(new Note(value, duration, pitch, octave, alteration, current_subdivision, max_beats));
    current_subdivision += duration;
    number_of_notes++;
    if (current_subdivision > (max_beats)){
        cerr << "ERROR TOO MANY NOTES IN THIS BAR" << endl;
        cerr << current_subdivision <<"/" << (max_beats) << " in measure " << measure_num << endl;
    }
    
}


//PUBLIC FUNCTIONS*********************

//--------------------------------------------------------------------------------
//attribute accessors
//--------------------------------------------------------------------------------
const int Measure::how_many_notes(){return number_of_notes;}
Note* Measure::get_head(){return notes[0];}
Note* Measure::get_tail(){return notes[number_of_notes-1];}
const int Measure::what_measure_num(){return measure_num;}


//--------------------------------------------------------------------------------
//print the contents of a measure
//--------------------------------------------------------------------------------
void Measure::print_measure(){
    cout << "Measure number " << measure_num << ":";
    for (int i = 0; i < notes.size(); i++){cout << " " << notes[i]->overall_note();}
    cout << endl;
}

//PROTECTED FUNCTIONS*********************
//--------------------------------------------------------------------------------
//functions for the Score_Creator to create and add to notes to measures;
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//Constructor for the Score_Creator
//--------------------------------------------------------------------------------
Measure::Measure(int _measure_num){
    measure_num = _measure_num;
    current_subdivision = 0.0;
    max_beats = MAX_BEATS_IN_BAR_FLOAT;
    number_of_notes = 0;
}

//--------------------------------------------------------------------------------
//Note addition for the Score_Creator
//--------------------------------------------------------------------------------
void Measure::add_note(Note *n){
    notes.push_back(n);
    if (number_of_notes > 0){notes[number_of_notes-1]->update_next(notes[number_of_notes]);
        notes[number_of_notes]->update_previous(notes[number_of_notes-1]);}
    number_of_notes++;
    current_subdivision += notes[number_of_notes-1]->what_subdivforchord();
}


//--------------------------------------------------------------------------------
//destructor
//--------------------------------------------------------------------------------
Measure::~Measure(){for (int i = 0; i < number_of_notes; i++){delete notes[i];}}



