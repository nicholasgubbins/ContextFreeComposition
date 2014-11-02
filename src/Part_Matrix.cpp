//
//  Part_Matrix.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 01/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "Part_Matrix.h"
#include "Part.h"
#include "Implementation.h"
#include <unordered_map>
#include <algorithm>

#include <stdlib.h>
#include <time.h>

using namespace std;


//--------------------------------------------------------------------------------
//constructor
//--------------------------------------------------------------------------------
Part_Matrix::Part_Matrix(string _name, int _order) : Matrix(_order){
    name = _name;

}

//--------------------------------------------------------------------------------
//update the matrix with a full part (SEE RHYTHM MATRIX FOR EXPLANATION OF PROCESS)
//--------------------------------------------------------------------------------
void Part_Matrix::update(Part *p){
    Note* current = p->get_part_head();
    start_notes.push_back(current->get_simple());
    while (current != p->get_part_tail()){
        Note* t = current;
        vector<Simple_Note> temp;
        for (int i = 0; i < order; i++){
            temp.push_back(t->get_simple());
            t = t->get_next();
            if (t == p->get_part_tail()) {break;}
            if (map.count(temp) == 0){
                vector<Simple_Note> next(1, t->get_simple());
                map.insert({temp,next});
            }
            else {
                map.find(temp)->second.push_back(t->get_simple());
            }
        }
        current = current->get_next();
    }
    //update backwards
    current = p->get_part_tail();
    end_notes.push_back(current->get_simple());
    while (current != p->get_part_head()){
        Note* t = current;
        vector<Simple_Note> temp;
        for (int i = 0; i < order; i++){
            temp.push_back(t->get_simple());
            t = t->get_previous();
            if (t == p->get_part_head()) {break;}
            if (reverse_map.count(temp) == 0){
                vector<Simple_Note> next(1, t->get_simple());
                reverse_map.insert({temp,next});
            }
            else {
                
                reverse_map.find(temp)->second.push_back(t->get_simple());
            }
        }
        current = current->get_previous();
    }
}

//--------------------------------------------------------------------------------
//get a random value based on n-gram prev  (SEE RHYTHM MATRIX FOR EXPLANATION OF PROCESS)
//--------------------------------------------------------------------------------
Simple_Note Part_Matrix::get_random_note(vector<Simple_Note> prev){
    if (prev.size() == 0){
        random_shuffle(start_notes.begin(), start_notes.end());
        int r = rand() % start_notes.size();
        return start_notes[r];
    }
    Simple_Note ret;
    ret.pitch = ret.octave = -1;
    while (map.count(prev) == 0 && prev.size()>0){prev.erase(prev.begin());}
    if (prev.size() == 0){
        random_shuffle(start_notes.begin(), start_notes.end());
        int r = rand() % start_notes.size();
        return start_notes[r];
    }
    partMap::iterator it = map.find(prev);
    random_shuffle(it->second.begin(), it->second.end());
    int r = rand() % it->second.size();
    return it->second[r];

}


//--------------------------------------------------------------------------------
//get a random end value based on n-gram prev    (same as get_random_note)
//--------------------------------------------------------------------------------
Simple_Note Part_Matrix::get_random_end_note(vector<Simple_Note> prev){
    if (prev.size() == 0){
        random_shuffle(end_notes.begin(), end_notes.end());
        int r = rand() % end_notes.size();
        return end_notes[r];
    }
    Simple_Note ret;
    ret.pitch = ret.octave = -1;
    while (reverse_map.count(prev) == 0 && prev.size()>0){prev.erase(prev.begin());}
    if (prev.size() == 0){
        random_shuffle(end_notes.begin(), end_notes.end());
        int r = rand() % end_notes.size();
        return end_notes[r];
    }
    partMap::iterator it = reverse_map.find(prev);
    random_shuffle(it->second.begin(), it->second.end());
    int r = rand() % it->second.size();
    return it->second[r];
}



//--------------------------------------------------------------------------------
//prints the entire part matrix (VERY INEFFICIENT ALGORITHM AND ONLY DONE FOR REPORT)
//--------------------------------------------------------------------------------
void Part_Matrix::print_matrix(){
    cout << endl << "Part Matrix: " << name << endl;
    set<string> keys;
    set<string> values;
    for (auto& x: map){
        string s;
        for (int i = 0; i < x.first.size(); i++){
             s += convert_to_note(x.first[i]) + to_string(x.first[i].octave);
        }
        keys.insert(s);
        for (int i = 0; i < x.second.size(); i++){
            string v = convert_to_note(x.second[i]) + to_string(x.second[i].octave);
            values.insert(v);
        }
    }
    
    set<string>::iterator it;
    
    cout << setw(7) << " ";
    for(it = values.begin(); it != values.end(); it++)
    {
        cout << setw(7) << *it;
    }
    cout << endl;
    
    for(it = keys.begin(); it != keys.end(); it++)
    {
        cout << setw(7) << *it;
        
        for (auto& x: map){
            string s;
            for (int i = 0; i < x.first.size(); i++){
                s += convert_to_note(x.first[i]) + to_string(x.first[i].octave);
            }
            if (s == *it){
                set<string>::iterator it2;
                for(it2 = values.begin(); it2 != values.end(); it2++)
                {
                    bool t = false;
                    for (int q = 0; q < x.second.size(); q++){
                        string v = convert_to_note(x.second[q]) + to_string(x.second[q].octave);
                        if (v == *it2){
                            string c = to_string(count(x.second.begin(), x.second.end(), x.second[q]));
                            cout << setw(7) << c; t = true; break;}
                    }
                    if (!t){
                        cout << setw(7) << "0";
                    }
                }
            }
        }
        cout << endl;
    }
}
