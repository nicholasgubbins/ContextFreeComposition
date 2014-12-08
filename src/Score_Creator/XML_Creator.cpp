//
//  XML_Creator.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 11/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//




#include "XML_Creator.h"

#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>


using namespace MusicXML2;
using namespace std;

//--------------------------------------------------------------------------------
//Constructor which takes in a score
//--------------------------------------------------------------------------------

XML_Creator::XML_Creator(Score *_s){
    score = _s;
}

//--------------------------------------------------------------------------------
//Function that allows for the user to choose what type of score to create
//if markovian, choose a length and modality in order to use the correct matrices
//--------------------------------------------------------------------------------
void XML_Creator::create(string path){
    

    
    cout << endl << "What's your name? ";
    string composer;
    cin >> composer;
    cout << endl;
    cout << endl << "What's your piece called? ";
    string title;
    cin >> title;
    cout << endl;
    
    path += title +".xml";
    
    boost::filesystem::path output_file(path);
    boost::filesystem::ofstream ofs(output_file);
    
    musicxmlfactory* f = factoryOpen();
    factoryRights (f, "Copyright Nick Gubbins 2014", 0);
    factoryCreator (f, composer.c_str(), "composer");
    factoryHeader (f, 0, title.c_str(), "Machine-Made Movement", title.c_str());
    factoryEncoding(f, "xmlfactory sample");
    
    for (int i = 0; i < score->how_many_voices(); i++){
        Part *p = score->get_part(i);           //get each part and it's info
        string name = p->what_name();
        string partnum = "P" + to_string(i);
        
        factoryAddPart (f, factoryScorepart (f, partnum.c_str(), name.c_str(), 0));     //add part to the score
        TElement part = factoryPart (f, partnum.c_str());
        
        int voice = which_voice(p->what_name());
        
        for (int j=0; j < p->how_many_measures(); j++){
            Measure *bar = p->get_measure(j);
            factoryAddElement (f, part, measure(f, j, voice, bar));
        }
        
        factoryAddPart(f, part);
    }
    
    factoryPrint(f, ofs);
    factoryClose (f);
    cout << "Written to " << path << endl;
    
}


//--------------------------------------------------------------------------------
//function for creating a measure in XMLfactor
//--------------------------------------------------------------------------------
TElement XML_Creator::measure (musicxmlfactory* f, int bar_num, int voice, Measure *bar) {
    string clef = "G";
    int line = 2;
    if (voice == 3 ||  voice == 2) { clef = "F"; line = 4;}//appropriate clef per voice type
    
    string time_signature = to_string(TIME_SIG_TOP) + "/" + to_string(TIME_SIG_BOTTOM); //time sig defined in Global Variables
    
	TElement m = bar_num ? factoryMeasure (f, bar_num+1)
    : factoryMeasureWithAttributes (f, bar_num+1, time_signature.c_str(), clef.c_str(), line, 0, 4);
    
    Note *current = bar->get_head();
    for (int i = 0; i < bar->how_many_notes(); i++){
		TElement note = 0;
        TElement rest = 0;
        
        if (current->what_octave() == -1){
            rest = MusicXML2::factoryRest(f, current->get_other_duration(), current->what_value().c_str());
            factoryAddElement(f, m, rest);}
        
        else{
            string p;
            p.push_back(current->what_pitch());
            note = MusicXML2::factoryNote(f, p.c_str(), current->what_alter(), current->what_octave() ,current->get_other_duration(), current->what_value().c_str());
            factoryAddElement(f, m, note);}
        
        current = current->get_next();
	}
	return m;
}







