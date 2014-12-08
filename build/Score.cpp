//
//  Score.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 15/07/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include "Score.h"

#include<iostream>

#include "xml.h"
#include "xmlfile.h"
#include "xmlreader.h"
#include "partsummary.h"
#include "smartlist.h"
#include "xml_tree_browser.h"

#include "Note.h"
#include "Chord.h"
#include "Part.h"
#include "Chord_Sequence.h"
#include "Implementation.h"

#include "Matrix.h"
#include "Chord_Matrix.h"

using namespace MusicXML2;
using namespace std;

//--------------------------------------------------------------------------------
//Constructor
//--------------------------------------------------------------------------------
Score::Score(Sxmlelement elt){
    time_signature = get_time_sig(elt);
    get_part_list(elt);
    number_of_voices = part_list.size();
    key = get_key(elt);
    int count = 0;
    ctree<xmlelement>::iterator iter = elt->begin();
    while (iter != elt->end()){
        Sxmlelement xml = *iter;
        if (xml){
            if (xml->getName() == "part"){
                staves.push_back(new Part(part_list[count], xml));
                count++;}
        }
        iter++;
    }
    
    number_of_measures = staves[0]->how_many_measures();
    sequence = new Chord_Sequence();
    get_chords();
    sequence->print_notes();
}


//--------------------------------------------------------------------------------
//function to test whether or not the score is in the correct key and should be ignored or not
//--------------------------------------------------------------------------------

bool Score::delete_me(){
    if (sequence->right_key()) return false;
    return true;
}


//PRIVATE FUNCTIONS*********************

//--------------------------------------------------------------------------------
//utility function for the constructor which extracts the part names from the xmltree
//--------------------------------------------------------------------------------
void Score::get_part_list(Sxmlelement elt){
    ctree<xmlelement>::iterator iter = elt->begin();
   // vector<string> part_list;
    int count = 0;
    while (iter != elt->end()){
        Sxmlelement xml = *iter;
        if (xml){
            if (xml->getName() == "part-name"){
                part_list.push_back(xml->getValue());
                count++;
            }
        }
        iter++;
    }
}

//--------------------------------------------------------------------------------
//utility function for the constructor which extracts the key signature from the xmltree
//--------------------------------------------------------------------------------
vector<string> Score::get_key(Sxmlelement elt){
    ctree<xmlelement>::iterator iter = elt->begin();
    vector<string> ret;
    while (iter != elt->end()){
        Sxmlelement xml = *iter;
        if (xml){
            if (xml->getName() == "fifths")
                ret.push_back(xml->getValue());
            else if (xml->getName() == "mode")
                ret.push_back(xml->getValue());
        }
        iter++;
    }
    return ret;
}



//--------------------------------------------------------------------------------
//utility function for the constructor which extracts the time signature from the xmltree
//--------------------------------------------------------------------------------
TS Score::get_time_sig(Sxmlelement elt){
    ctree<xmlelement>::iterator iter = elt->begin();
    TS timesig;
    timesig.top = 0;
    timesig.bottom = 0;
    while (iter != elt->end()){
        Sxmlelement xml = *iter;
        if (xml){
            if (xml->getName() == "beats"){
                string top = xml->getValue();
                timesig.top = atoi(top.c_str());
            }
            else if (xml->getName() == "beat-type"){
                string bottom = xml->getValue();
                timesig.bottom = atoi(bottom.c_str());
                return timesig;
            }
        }
        iter++;
    }
    return timesig;
}




void Score::get_chords(){
    bool end = false;
    
    vector<Note *> note_pointers;           //note pointers for each part
    vector<Simple_Note>current(number_of_voices);   //used for the current chords
    vector<Simple_Note>previous(number_of_voices);
    
    for (int j = 0; j< number_of_voices; j++){note_pointers.push_back(staves[j]->bars[0]->get_head());} //get all starting positions
    for (int j = 0; j< number_of_voices; j++){current[j] = note_pointers[j]->get_simple();}
    
    vector<float> time_left(number_of_voices);  //how much time is left per note per part
    for (int j = 0; j< number_of_voices; j++)
        time_left[j] = note_pointers[j]->what_subdivforchord();
    
    while (!end){
        if (!end){sequence->add_chord(note_pointers);}  //add current chord to the chord sequence
        
        float min_push_ahead = ERROR_INT;
        for (int j = 0; j< number_of_voices; j++)       //get the smallest amount of time left on any note in current chord
            min_push_ahead = (note_pointers[j]->what_subdivforchord() < min_push_ahead) ? note_pointers[j]->what_subdivforchord() : min_push_ahead;

        for (int j = 0; j< number_of_voices; j++){      //push ahead each note that has now expired based on the minimum push ahead
            time_left[j] -= min_push_ahead;
            if (time_left[j] <= 0){
                note_pointers[j] = note_pointers[j]->get_next();    //if a note has run out, move onto the next note
                if (note_pointers[j] == nullptr){               //check if we've got to the end for any part
                    end = true;
                    break;}
                if (note_pointers[j] != nullptr){
                    time_left[j] = note_pointers[j]->what_subdivforchord();}       //how much does this new note have left
            }
        }
    }
}



//--------------------------------------------------------------------------------
//attribute accessors
//--------------------------------------------------------------------------------
int Score::how_many_measures(){return number_of_measures;}
int Score::how_many_voices(){return number_of_voices;}
TS Score::what_time_signature(){return time_signature;}
vector<string> Score::what_part_names(){return part_list;}

int Score::is_major(){
    if (key[1] == "major")
        return MAJOR;
    else if(key[1] == "minor")
        return MINOR;
    else
        cerr<< "neither major or minor";
    return -1;
}


//--------------------------------------------------------------------------------
//scan through each part and use it to update the transition matrix
//--------------------------------------------------------------------------------
void Score::matrix_update(Matrix *m, int voice){m->update(staves[voice]);}
void Score::matrix_update(Chord_Matrix *m){
    int modality = (this-> is_major() == MAJOR) ? MAJOR : MINOR;
    m->update_harmony(sequence->get_note_sequence(), modality);}


//PROTECTED FUNCTIONS*********************
//--------------------------------------------------------------------------------
//functions for the Score_Creator
//--------------------------------------------------------------------------------

Score::Score(int _number_of_measures, vector<Part*> parts, int modality){
    number_of_measures = _number_of_measures;
    number_of_voices = parts.size();
    for (int i = 0; i < number_of_voices; i++){
        staves.push_back(parts[i]);
        part_list.push_back(parts[i]->what_name());
    }
    if (modality == MAJOR){
        key.push_back("0");
        key.push_back("major");
    }
    if (modality == MINOR){
        key.push_back("0");
        key.push_back("minor");
    }
    
    time_signature.top = TIME_SIG_TOP;
    time_signature.bottom = TIME_SIG_BOTTOM;
    
    sequence = new Chord_Sequence();
    get_chords();
    cout << endl;
    cout << endl << "Western Classical Chord Sequence: " << endl;
    sequence->print_sequence();
}


void Score::add_part(Part *p){staves.push_back(p);}





Part* Score::get_part(int n){
    if (n < 0 || n >= number_of_voices){cerr << "NO PART" << endl; return nullptr;}
    else{return staves[n];}
}



//--------------------------------------------------------------------------------
//destructor
//--------------------------------------------------------------------------------
Score::~Score(){
    for (int i = 0; i < number_of_voices; i++){
        delete staves[i];}
    delete sequence;
}