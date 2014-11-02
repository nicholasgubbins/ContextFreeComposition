//
//  Chord.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 02/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include "Chord.h"

#include <iostream>

#include "All_Chords.h"
#include "Implementation.h"

using namespace std;



//--------------------------------------------------------------------------------
//Constructor
//--------------------------------------------------------------------------------
Chord::Chord(vector<Note*> _notes){
    root.octave = ERROR_INT;
    root.pitch = ERROR_INT;
    float shortest_length = ERROR_INT;
    if (_notes.size() == 0) {cerr << "No notes in this chord" << endl; inversion = -1; quality = "UNKNOWN"; base = -1;}
    else{
        for (int i = 0; i < _notes.size(); i++){        //get info from each note
            float my_length = _notes[i]->what_subdivforchord();
            shortest_length = (my_length < shortest_length) ? my_length : shortest_length;
            Simple_Note temp = _notes[i]->get_simple();
            notes.push_back(temp);
            root = (temp < root) ? temp : root;
        }
        analyse();      //work out what this is in western classical tradition
        length = shortest_length;
        name = get_type();
    }
    
}



//PUBLIC FUNCTIONS*********************

//attribute accessors
string Chord::get_name() {return name;}

vector<int> Chord::get_notes(){
    vector<int> ret;
    for (int i = 0; i < notes.size(); i++){ret.push_back(notes[i].pitch + notes[i].octave*12);}
    return ret;
}

//--------------------------------------------------------------------------------
//checks if a note is a member of this chord
//--------------------------------------------------------------------------------
bool Chord::is_member(int pitch){
    for (int i = 0; i < notes.size() ; i++){
        if (pitch == notes[i].pitch) return true;
    }
    return false;
}





//PRIVATE FUNCTIONS*********************


//--------------------------------------------------------------------------------
//analysis based on the western classical tradition using defined chords in All_Chords.h
//--------------------------------------------------------------------------------
void Chord::analyse(){
    
    vector<int> note_values;
    for (int x = 0; x < notes.size(); x++){if(notes[x].pitch != -1)note_values.push_back(notes[x].pitch);}
    sort(note_values.begin(), note_values.end());
    
    note_values.erase(unique(note_values.begin(), note_values.end()),note_values.end());
    bool major, minor, dim, dom_sev, maj_sev, min_sev, half_dim, sus4, sus2, found;
    major = minor = dim = dom_sev = maj_sev = min_sev = half_dim = sus4 = sus2 = found = false;
  
    if (note_values.size() == 3){
        for (int i = 0; i < 12; i++){
            if (note_values == MAJOR_TRIADS[i]){
                quality= "MAJOR";
                base = i;
                major = found = true; break;
            }
            else if (note_values == MINOR_TRIADS[i]){
                quality= "MINOR";
                base = i;
                minor = found = true; break;
            }
            else if (note_values == DIM_TRIADS[i]){
                quality= "DIM";
                base = i;
                dim = found = true; break;
            }
            else if (note_values == SUS4_TRIADS[i]){
                quality= "SUS4";
                base = i;
                sus4 = found = true; break;
            }
            else if (note_values == SUS2_TRIADS[i]){
                quality= "SUS2";
                base = i;
                sus2 = found = true; break;
            }
        }
        for (int i = 0; i < 4; i++){
            if (note_values == AUG_TRIADS[i]){
                quality = "AUG";
                base = root.pitch;
                inversion = 0;
                return;
            }
        }
    }
    else if (note_values.size() == 4){
        for (int i = 0; i < 12; i++){
            if (note_values == DOM_SEVENTH_CHORDS[i]){
                quality= "DOM_SEVENTH";
                base = i;
                dom_sev = found = true; break;
            }
            else if (note_values == MAJOR_SEVENTH_CHORDS[i]){
                quality= "MAJOR_SEVENTH";
                base = i;
                maj_sev = found = true; break;
            }
            else if (note_values == MINOR_SEVENTH_CHORDS[i]){
                quality= "MINOR_SEVENTH";
                base = i;
                min_sev = found = true; break;
            }
            else if (note_values == HALF_DIM_SEVENTH_CHORDS[i]){
                quality= "HALF_DIM_SEVENTH";
                base = i;
                half_dim = found = true; break;
            }
        }
        for (int i = 0; i < 3; i++){
            if (note_values == DIM_SEVENTH_CHORDS[i]){
                quality = "DIM_SEVENTH";
                base = root.pitch;
                inversion = 0;
                return;
            }
        }
    }
    if (!found){inversion = -1; quality = "UNKNOWN"; base = -1; return;}
    
    if (base==-1){return;}
    else if (base == root.pitch){inversion = 0;}
    else {
        if (major){
            if ((base+4)%12 == root.pitch){inversion = 1;}
            else if ((base+7)%12 == root.pitch){inversion = 2;}
            else {inversion = -1;}
        }
        else if (minor){
            if ((base+3)%12 == root.pitch){inversion = 1;}
            else if ((base+7)%12 == root.pitch){inversion = 2;}
            else {inversion = -1;}
        }
        else if (dom_sev){
            if ((base+4)%12 == root.pitch){inversion = 1;}
            else if ((base+7)%12 == root.pitch){inversion = 2;}
            else if ((base+10)%12 == root.pitch){inversion = 3;}
            else {inversion = -1;}
        }
        else if (maj_sev){
            if ((base+4)%12 == root.pitch){inversion = 1;}
            else if ((base+7)%12 == root.pitch){inversion = 2;}
            else if ((base+11)%12 == root.pitch){inversion = 3;}
            else {inversion = -1;}
        }
        else if (min_sev){
            if ((base+3)%12 == root.pitch){inversion = 1;}
            else if ((base+7)%12 == root.pitch){inversion = 2;}
            else if ((base+10)%12 == root.pitch){inversion = 3;}
            else {inversion = -1;}
        }
        else if (half_dim){
            if ((base+3)%12 == root.pitch){inversion = 1;}
            else if ((base+6)%12 == root.pitch){inversion = 2;}
            else if ((base+10)%12 == root.pitch){inversion = 3;}
            else {inversion = -1;}
        }
        else if (dim){
            if ((base+3)%12 == root.pitch){inversion = 1;}
            else if ((base+6)%12 == root.pitch){inversion = 2;}
            else {inversion = -1;}
        }
        else if (sus4){
            if ((base+5)%12 == root.pitch){inversion = 1;}
            else if ((base+7)%12 == root.pitch){inversion = 2;}
            else {inversion = -1;}
        }
        else if (sus2){
            if ((base+2)%12 == root.pitch){inversion = 1;}
            else if ((base+7)%12 == root.pitch){inversion = 2;}
            else {inversion = -1;}
        }
    }
}


//--------------------------------------------------------------------------------
//used for writing the whole name of a chord incl inversion and quality
//--------------------------------------------------------------------------------
string Chord::get_type(){string ret; ret += convert_to_note(base) + quality + to_string(inversion); return ret;}



//PROTECTED FUNCTIONS*********************

//--------------------------------------------------------------------------------
//used to update length if next chord is the same as this
//--------------------------------------------------------------------------------
void Chord::update_length(float len){
    length += len;
}



