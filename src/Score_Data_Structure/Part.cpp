//
//  Part.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 15/07/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include<iostream>

#include "Part.h"
#include "Measure.h"
#include "Note.h"
#include "Implementation.h"

#include "xml.h"
#include "xmlfile.h"
#include "xmlreader.h"
#include "partsummary.h"
#include "smartlist.h"
#include "xml_tree_browser.h"

using namespace MusicXML2;
using namespace std;

//--------------------------------------------------------------------------------
//Constructor called by Score.cpp
//--------------------------------------------------------------------------------
Part::Part(string _name, Sxmlelement elt){
    name = _name;
    int count = 0;
    int divisions = 1;
    TS time_signature;
    float max_beats = 0;
    ctree<xmlelement>::iterator iter = elt;
    while (iter != elt->end()){
        Sxmlelement xml = *iter;
        if (xml){
            if (xml->getName() == "part" && (iter != elt))
                break;
            else if (xml->getName() == "measure"){          //NB max beats is passed by reference to be updated as for each bar the number of
                count++;                                    //divisions can change despite there being a constant time signuature
                bars.push_back(new Measure(count, max_beats, divisions, time_signature, xml));
            }
        }
        iter++;
    }
    number_of_measures = count;
    fix_pointers();
}



//PRIVATE FUNCTIONS*********************

//--------------------------------------------------------------------------------
//now the score is set up go through and fix the note pointers between measures
//--------------------------------------------------------------------------------
void Part::fix_pointers(){
    for (int i = 1; i < bars.size(); i++){
        bars[i-1]->get_tail()->update_next(bars[i]->get_head());
        bars[i]->get_head()->update_previous(bars[i-1]->get_tail());
    }
    bars[number_of_measures-1]->get_tail()->update_next(nullptr);
    bars[0]->get_head()->update_previous(nullptr);
}

//PUBLIC FUNCTIONS*********************

//--------------------------------------------------------------------------------
//attribute accessors
//--------------------------------------------------------------------------------
const string Part::what_name(){return name;}
const int Part::how_many_measures(){return number_of_measures;}
Note* Part::get_part_head(){return bars[0]->get_head();}
Note* Part::get_part_tail(){return bars[number_of_measures-1]->get_tail();}
Measure* Part::get_measure(int n){return bars[n];}
//--------------------------------------------------------------------------------
//Part Printer
//--------------------------------------------------------------------------------
void Part::print_me(){
    cout << "printing part " << this->name << endl;
    for (int i = 0; i < bars.size(); i++)
        bars[i]->print_measure();
}

//--------------------------------------------------------------------------------
//Constructor for Score_Creator
//--------------------------------------------------------------------------------
Part::Part(string _name, int _number_of_measures){
    name = _name;
    number_of_measures = _number_of_measures;
}
//--------------------------------------------------------------------------------
//Function to add bar for Score_Creator
//--------------------------------------------------------------------------------
void Part::add_bar(Measure *m){
    bars.push_back(m);
    if (m->what_measure_num() == number_of_measures){
        fix_pointers();
    }
}




//--------------------------------------------------------------------------------
//destructor
//--------------------------------------------------------------------------------
Part::~Part(){for (int i = 0; i < number_of_measures; i++){delete bars[i];}}

