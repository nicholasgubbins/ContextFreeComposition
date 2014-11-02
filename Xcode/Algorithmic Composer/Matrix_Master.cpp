//
//  Matrix_Master.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 07/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

//--------------------------------------------------------------------------------
//this class contains all the matrices (forwards and backwards),
//and acts as an intermediary routing any requests to the appropriate matrices
//--------------------------------------------------------------------------------

#include "Matrix_Master.h"

#include <iostream>

using namespace std;

//--------------------------------------------------------------------------------
//constructor
//--------------------------------------------------------------------------------
Matrix_Master::Matrix_Master(int _order){
    
    order = _order;
    
    Part_Matrix *S_major_pm = new Part_Matrix("Soprano_Major", order);
    Part_Matrix *A_major_pm = new Part_Matrix("Alto_Major", order);
    Part_Matrix *T_major_pm = new Part_Matrix("Tenor_Major", order);
    Part_Matrix *B_major_pm = new Part_Matrix("Bass_Major", order);
    
    Part_Matrix *S_minor_pm = new Part_Matrix("Soprano_Minor", order);
    Part_Matrix *A_minor_pm = new Part_Matrix("Alto_Minor", order);
    Part_Matrix *T_minor_pm = new Part_Matrix("Tenor_Minor", order);
    Part_Matrix *B_minor_pm = new Part_Matrix("Bass_Minor", order);
    
    Rhythmic_Matrix *S_rhythmic_rm = new Rhythmic_Matrix("Soprano_RM", order);
    Rhythmic_Matrix *A_rhythmic_rm = new Rhythmic_Matrix("Alto_RM", order);
    Rhythmic_Matrix *T_rhythmic_rm = new Rhythmic_Matrix("Tenor_RM", order);
    Rhythmic_Matrix *B_rhythmic_rm = new Rhythmic_Matrix("Bass_RM", order);
    
    major.push_back(S_major_pm);
    major.push_back(A_major_pm);
    major.push_back(T_major_pm);
    major.push_back(B_major_pm);
    
    minor.push_back(S_minor_pm);
    minor.push_back(A_minor_pm);
    minor.push_back(T_minor_pm);
    minor.push_back(B_minor_pm);
    
    rm.push_back(S_rhythmic_rm);
    rm.push_back(A_rhythmic_rm);
    rm.push_back(T_rhythmic_rm);
    rm.push_back(B_rhythmic_rm);
    
    
    cm = new Chord_Matrix(order);
    
}

//--------------------------------------------------------------------------------
//updates all matrices based on a supplied score
//--------------------------------------------------------------------------------
void Matrix_Master::update(Score *s){
    vector<string> parts = s->what_part_names();
    int mode = s->is_major();
    if (mode == -1) {cerr<<"UNKNOWN MODALITY - SKIPPING" << endl; return;}
    
    for (int i = 0; i < parts.size(); i++){
        int voice = which_voice(parts[i]);
        if (voice == -1) {continue;}
        if (mode == MAJOR){
            s->matrix_update(major[voice], i);
        }
        else{s->matrix_update(minor[voice], i);}
        s->matrix_update(rm[voice], i);
    }
    s->matrix_update(cm);
}

//--------------------------------------------------------------------------------
//returns the order
//--------------------------------------------------------------------------------
int Matrix_Master::what_order(){return order;}



//--------------------------------------------------------------------------------
//return a random pitch from the appropriate forward matrix
//--------------------------------------------------------------------------------
Simple_Note Matrix_Master::get_random_note(vector<Simple_Note> previous_notes, int voice, int mode){
    if (mode == MAJOR){return major[voice]->get_random_note(previous_notes);}
    else return minor[voice]->get_random_note(previous_notes);
}

//--------------------------------------------------------------------------------
//return a random pitch from the appropriate backwards matrix
//--------------------------------------------------------------------------------
Simple_Note Matrix_Master::get_random_end_note(vector<Simple_Note> previous_notes, int voice, int mode){
    if (mode == MAJOR){return major[voice]->get_random_end_note(previous_notes);}
    else return minor[voice]->get_random_end_note(previous_notes);
}

//--------------------------------------------------------------------------------
//return a random rhythm from the appropriate forward matrix
//--------------------------------------------------------------------------------
string Matrix_Master::get_random_duration(vector<string> previous_rhythms, int voice){
    return rm[voice]->get_random_length(previous_rhythms);
}
//--------------------------------------------------------------------------------
//return a random rhythm from the appropriate backwards matrix
//--------------------------------------------------------------------------------
string Matrix_Master::get_random_end_duration(vector<string> previous_rhythms, int voice){
    return rm[voice]->get_random_end_length(previous_rhythms);
}

//--------------------------------------------------------------------------------
//return a random chord which includes the note at the voice location
//--------------------------------------------------------------------------------
vector<int> Matrix_Master::harmonise_voice(vector<vector<int>> previous_chords, int voice, int note, int modality, bool forwards){
    while (true){
        if (forwards){
            return cm->get_random_harmonising_chord(previous_chords, voice, note, modality);}
        else {return cm->get_random_end_harmonising_chord(previous_chords, voice, note, modality);}
    }
}
//--------------------------------------------------------------------------------
//return a random chord which includes the note at the voice location shared
// by both forwards and backwards matrices
//--------------------------------------------------------------------------------
vector<int> Matrix_Master::find_shared_chord(vector<vector<int>> notes_forward, vector<vector<int>> notes_backward,int voice, int pitch, int modality){
    return cm->find_shared_chord(notes_forward, notes_backward ,voice, pitch, modality);
}



//--------------------------------------------------------------------------------
//Destructor
//--------------------------------------------------------------------------------
Matrix_Master::~Matrix_Master(){
    for (int i = 0; i < major.size() ; i++){
   //     major[i]->print_matrix(); <-- use this to print out the part matrices
        delete major[i];
        delete minor[i];
        delete rm[i];
    }
}

