//
//  Chord_Sequence.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 08/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include "Chord_Sequence.h"
#include <fstream>



//--------------------------------------------------------------------------------
//Constructor
//--------------------------------------------------------------------------------
Chord_Sequence::Chord_Sequence(){}





//PROTECTED FUNCTIONS*********************

//--------------------------------------------------------------------------------
//Add a new chord to this sequence, constructing a new chord instance
//--------------------------------------------------------------------------------
void Chord_Sequence::add_chord(vector<Note*> notes){
    Chord *ret = new Chord(notes);
    if (sequence.size() > 0){
        if (ret->name == sequence.back()->name){sequence.back()->update_length(ret->length); return;}
    }
    sequence.push_back(ret);
}

//--------------------------------------------------------------------------------
//print the sequence in western classical form
//--------------------------------------------------------------------------------
void Chord_Sequence::print_sequence(){
    for (int i = 0; i < sequence.size(); i++){
        if (sequence[i]->get_name() == "RESTUNKNOWN-1") continue;
        cout << " " + sequence[i]->get_name() ;
    }
    cout << endl;
    
}

//--------------------------------------------------------------------------------
//print the sequence in note word form <N1, N2, N3, N4> and deposit the sentence
//into grammar.txt to be read by Grammar_Parser.cpp
//--------------------------------------------------------------------------------
void Chord_Sequence::print_notes(){
    ofstream outstream("grammar.txt", ofstream::app);
    outstream << "* ";
    for (int i = 0; i < sequence.size(); i++){
        vector<int> n = sequence[i]->get_notes();
        string word = "<";
        for (int j = 0; j < n.size(); j++){
            word += to_string(n[j]);
            if (j < n.size()-1) word += ",";
        }
        
        word+= ">";
        outstream<<word;
        string len = to_string(sequence[i]->length);    //update note lengths if values from TS 3/4
        if (len == "0.0833333"){ len = "0.0625";}
        else if (len == "0.166667") { len = "0.125";}
        else if (len == "0.333333"){len = "0.25";}
        else if (len == "0.666667") { len = "0.5";}
        outstream << " ";

    }
    outstream << " #" << endl;
    outstream.close();
}

//--------------------------------------------------------------------------------
//print the sequence in note word form <N1, N2, N3, N4> and deposit the sentence
//into grammar.txt to be read by Grammar_Parser.cpp
//--------------------------------------------------------------------------------
vector<vector<int>> Chord_Sequence::get_note_sequence(){
    vector<vector<int>> ret;
    for (int i = 0; i < sequence.size(); i++){ret.push_back(sequence[i]->get_notes());}
    return ret;
}

//--------------------------------------------------------------------------------
//checks if the last chord is an appropriate value in case the file
//was incorrectly labelled in terms of key signature
//--------------------------------------------------------------------------------
bool Chord_Sequence::right_key(){
    string final = sequence[sequence.size()-1]->get_name();
    if (final == "AMAJOR0" || final == "CMAJOR0" || final == "AMINOR0" || final == "RESTUNKNOWN-1"){return true;}
    return false;
}

//--------------------------------------------------------------------------------
//destructor
//--------------------------------------------------------------------------------
Chord_Sequence::~Chord_Sequence(){
     for (int i = 0; i < sequence.size(); i++){
         delete sequence[i];
     }
}

