//
//  Chord_Matrix.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 01/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include "Chord_Matrix.h"
#include "Matrix.h"
#include "Implementation.h"


#include <iostream>
#include <iomanip>

#include <unordered_map>
#include <algorithm>

using namespace std;

//--------------------------------------------------------------------------------
//constructor
//--------------------------------------------------------------------------------
Chord_Matrix::Chord_Matrix(int _order) : Matrix(_order){};

//this function is not used, rather we use update_harmony as using chord seq, not Part
void Chord_Matrix::update(Part *p){};

//--------------------------------------------------------------------------------
//update the matrix with a full chord sequence (SEE RHYTHM MATRIX FOR EXPLANATION OF PROCESS)
//--------------------------------------------------------------------------------
void Chord_Matrix::update_harmony(vector<vector<int> > notes, int modality){
    if (modality == MAJOR){start_chords_major.push_back(notes[0]);}
    else start_chords_minor.push_back(notes[0]);
    
    for (int i = 0; i < notes.size()-order-1; i++){
        vector<vector<int> > temp;
        for (int j = 0; j < order; j++){
            temp.push_back(notes[i+j]);
            if (map.count(temp) == 0){
                vector<vector<int> > next (1, notes[i+j+1]);
                map.insert({temp,next});
            }
            else {
                map.find(temp)->second.push_back(notes[i+j+1]);
            }
        }
    }
    
    if (modality == MAJOR){
        end_chords_major.push_back(notes[notes.size()-1]);}
    else end_chords_minor.push_back(notes[notes.size()-1]);
    
    for (int i = notes.size()-1; i >= order; i--){
        vector<vector<int> > temp;
        for (int j = 0; j < order; j++){
            temp.push_back(notes[i-j]);
            if (reverse_map.count(temp) == 0){
                vector<vector<int> > next (1, notes[i-j-1]);
                reverse_map.insert({temp,next});
            }
            else {
                reverse_map.find(temp)->second.push_back(notes[i-j-1]);
            }
        }
    }

    
}


//--------------------------------------------------------------------------------
//get a random value based on n-gram prev  (SEE RHYTHM MATRIX FOR EXPLANATION OF PROCESS)
//--------------------------------------------------------------------------------
vector<int> Chord_Matrix::get_random_chord(vector<vector<int> > notes, int modality){
    if (notes.size() == 0){
        if (modality == MAJOR){
        random_shuffle(start_chords_major.begin(), start_chords_major.end());
        int r = rand() % start_chords_major.size();
            return start_chords_major[r];}
        else{
            random_shuffle(start_chords_minor.begin(), start_chords_minor.end());
            int r = rand() % start_chords_minor.size();
            return start_chords_minor[r];}
        
    }
    while(true){
        while (map.count(notes) == 0 &&  notes.size()>1){ notes.erase( notes.begin());}
        if ( notes.size() <= 1 && map.count(notes) == 0){
            if (modality == MAJOR){
                random_shuffle(start_chords_major.begin(), start_chords_major.end());
                int r = rand() % start_chords_major.size();
                return start_chords_major[r];}
            else{
                random_shuffle(start_chords_minor.begin(), start_chords_minor.end());
                int r = rand() % start_chords_minor.size();
                return start_chords_minor[r];}
        }
        else{
            harmonicMap::iterator it = map.find(notes);
            random_shuffle(it->second.begin(), it->second.end());
            int r = rand() % it->second.size();
            return it->second[r];}
        }
}



//--------------------------------------------------------------------------------
//get a random value based on n-gram prev, as well as a pitch at voice index
//--------------------------------------------------------------------------------
vector<int> Chord_Matrix::get_random_harmonising_chord(vector<vector<int> > notes, int voice, int pitch, int modality){
    if (notes.size() == 0){
        if (modality == MAJOR){
            random_shuffle(start_chords_major.begin(), start_chords_major.end());
            int r = rand() % start_chords_major.size();
            return start_chords_major[r];}
        else{
            random_shuffle(start_chords_minor.begin(), start_chords_minor.end());
            int r = rand() % start_chords_minor.size();
            return start_chords_minor[r];}
    }
    int count = ERROR_INT;
    
    while(true){
        if (count == 0) {notes.erase(notes.begin()); count = ERROR_INT;}
        while (map.count(notes) == 0 &&  notes.size()>1){ notes.erase( notes.begin());}
        if ( notes.size() <= 1 && map.count(notes) == 0){
            if (modality == MAJOR){
                random_shuffle(start_chords_major.begin(), start_chords_major.end());
                int r = rand() % start_chords_major.size();
                return start_chords_major[r];}
            else{
                random_shuffle(start_chords_minor.begin(), start_chords_minor.end());
                int r = rand() % start_chords_minor.size();
                return start_chords_minor[r];}
        }
        else{
            harmonicMap::iterator it = map.find(notes);
            random_shuffle(it->second.begin(), it->second.end());
            int r = rand() % it->second.size();
            if (pitch == -1) {vector<int> ret = it->second[r]; ret[voice] = pitch; return ret;}
            for (int i = 0; i < it->second[r].size(); i++){
                if (pitch == (it->second[r][i] %12)) return it->second[r];
            }
            count--;
        }
    }
}

//--------------------------------------------------------------------------------
//get a random reverse value based on n-gram prev, as well as a pitch at voice index
//--------------------------------------------------------------------------------
vector<int> Chord_Matrix::get_random_end_harmonising_chord(vector<vector<int> > notes, int voice, int pitch, int modality){
    if (notes.size() == 0){
        if (modality == MAJOR){
            random_shuffle(end_chords_major.begin(), end_chords_major.end());
            int r = rand() % end_chords_major.size();
            return end_chords_major[r];}
        else{
            random_shuffle(end_chords_minor.begin(), end_chords_minor.end());
            int r = rand() % end_chords_minor.size();
            return end_chords_minor[r];}
    }
    int count = ERROR_INT;
    
    while(true){
        if (count == 0) {notes.erase(notes.begin()); count = ERROR_INT;}
        while (reverse_map.count(notes) == 0 &&  notes.size()>1){ notes.erase( notes.begin());}
        if ( notes.size() <= 1 && reverse_map.count(notes) == 0){
            if (modality == MAJOR){
                random_shuffle(end_chords_major.begin(), end_chords_major.end());
                int r = rand() % end_chords_major.size();
                return end_chords_major[r];}
            else{
                random_shuffle(end_chords_minor.begin(), end_chords_minor.end());
                int r = rand() % end_chords_minor.size();
                return end_chords_minor[r];}
        }
        else{
            harmonicMap::iterator it = reverse_map.find(notes);
            random_shuffle(it->second.begin(), it->second.end());
            int r = rand() % it->second.size();
            if (pitch == -1) {vector<int> ret = it->second[r]; ret[voice] = pitch; return ret;}
            for (int i = 0; i < it->second[r].size(); i++){
                if (pitch == (it->second[r][i]%12)) return it->second[r];
            }
            count--;
        }
    }
}

//--------------------------------------------------------------------------------
//get a random value based on n-gram prev, as well as a pitch at voice index,
//shared by both forwards and backwards matrices
//--------------------------------------------------------------------------------
vector<int> Chord_Matrix::find_shared_chord(vector<vector<int> > notes1, vector<vector<int> > notes2,int voice, int pitch, int modality){
    while (map.count(notes1) == 0 &&  notes1.size()>1){ notes1.erase( notes1.begin());}
    while (reverse_map.count(notes2) == 0 &&  notes2.size()>1){ notes2.erase( notes2.begin());}
    if (map.count(notes1) == 0 || reverse_map.count(notes2) == 0){
        return {-1,-1,-1,-1};}
    else{
        harmonicMap::iterator it_forwards = map.find(notes1);
        random_shuffle(it_forwards->second.begin(), it_forwards->second.end());
        harmonicMap::iterator it_backwards = reverse_map.find(notes2);
        random_shuffle(it_backwards->second.begin(), it_backwards->second.end());
        for (int i = 0; i < it_forwards->second.size(); i++){
            for (int j = 0; j <it_backwards->second.size(); j++){
                if (it_forwards->second[i] == it_backwards->second[j])
                    for (int x = 0; x < it_forwards->second[i].size(); x++){
                        if (pitch == it_forwards->second[i][x]) return it_forwards->second[i];
                }
            }
        }
        return {-1,-1,-1,-1};
    
    }
}



