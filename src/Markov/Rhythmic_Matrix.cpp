//
//  Rhythmic_Matrix.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 01/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include "Rhythmic_Matrix.h"
#include "Matrix.h"
#include "Implementation.h"


#include <iostream>

#include "Part.h"
#include <unordered_map>
#include <algorithm>


using namespace std;

//--------------------------------------------------------------------------------
//constructor
//--------------------------------------------------------------------------------
Rhythmic_Matrix::Rhythmic_Matrix(string _name, int _order) : Matrix(_order){
    name = _name;
}


//--------------------------------------------------------------------------------
//update the matrix with a full part
//--------------------------------------------------------------------------------
void Rhythmic_Matrix::update(Part *p){
    Note* current = p->get_part_head();
    start_rhythms.push_back(current->what_value()); //add the first rhythm to start_rhythms
    
    while (current != p->get_part_tail()){      //cycle through all notes
        Note* t = current;
        vector<string> temp;                    //n-gram
        
        for (int i = 0; i < order; i++){        //expand n-gram up to n-order
            if (t->what_value() == "") continue;
        
            temp.push_back(t->what_value());
            t = t->get_next();
            
            if (t->what_value() == "") continue;
            if (t == p->get_part_tail()) {break;}
            
            if (map.count(temp) == 0){      //if this n-gram doen't appear in the matrix
                vector<string> next(1, t->what_value());    //get the state to transition to
                map.insert({temp,next});                    //add to matrix
            }
            else {                        // if n-gram already appears, add the transition state
                map.find(temp)->second.push_back(t->what_value());
            }
        }
        current = current->get_next();
    }
                                                    /// perform the backwards process
    current = p->get_part_tail();
    end_rhythms.push_back(current->what_value());
    while (current != p->get_part_head()){
        Note* t = current;
        vector<string> temp;
        for (int i = 0; i < order; i++){
            if (t->what_value() == "") continue;
            temp.push_back(t->what_value());
            t = t->get_previous();
            if (t->what_value() == "") continue;
            if (t == p->get_part_head()) {break;}
            if (reverse_map.count(temp) == 0){
                vector<string> next(1, t->what_value());
                reverse_map.insert({temp,next});
            }
            else {
                reverse_map.find(temp)->second.push_back(t->what_value());
            }
        }
        current = current->get_previous();
    }
    
}

//--------------------------------------------------------------------------------
//get a random value based on n-gram prev
//--------------------------------------------------------------------------------
string Rhythmic_Matrix::get_random_length(vector<string> prev){
    
    if (prev.size() == 0){          //if n-gram empty return a start position
        random_shuffle(start_rhythms.begin(), start_rhythms.end());
        int r = rand() % start_rhythms.size();
        return start_rhythms[r];
    }
    
    string ret;
    ret = "quarter";                //while n-gram not in the map, pop from the front of the n-gram
    while (map.count(prev) == 0 && prev.size()>0){prev.erase(prev.begin());}
    if (prev.size() == 0){
        random_shuffle(start_rhythms.begin(), start_rhythms.end());
        int r = rand() % start_rhythms.size();
        return start_rhythms[r];
    }
    else{       //if we've found the n-gram, return a random value from the map
        rhythmMap::iterator it = map.find(prev);
        random_shuffle(it->second.begin(), it->second.end());
        int r = rand() % it->second.size();
        return it->second[r];
    }
    return ret;
}


//--------------------------------------------------------------------------------
//get a random end value based on n-gram prev    (same as get_random_length)
//--------------------------------------------------------------------------------
string Rhythmic_Matrix::get_random_end_length(vector<string> prev){
    if (prev.size() == 0){
        random_shuffle(end_rhythms.begin(), end_rhythms.end());
        int r = rand() % end_rhythms.size();
        return end_rhythms[r];
    }
    
    string ret;
    ret = "whole";
    while (reverse_map.count(prev) == 0 && prev.size()>0){prev.erase(prev.begin());}
    if (prev.size() == 0){
        random_shuffle(end_rhythms.begin(), end_rhythms.end());
        int r = rand() % end_rhythms.size();
        return end_rhythms[r];
    }
    else{
        rhythmMap::iterator it = reverse_map.find(prev);
        random_shuffle(it->second.begin(), it->second.end());
        int r = rand() % it->second.size();
        return it->second[r];
    }
    return ret;
}


void Rhythmic_Matrix::print_matrix(){
    cout << "rm" << endl;
    for (auto& x: map){
        cout << x.first.size() << endl;
    }
}

