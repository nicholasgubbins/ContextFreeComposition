//
//  Part.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 15/07/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Part__
#define __Algorithmic_Composer__Part__

#include "Implementation.h"
#include "Measure.h"

class Part{
    friend class Score;
    
//ATTRIBUTES*********************
private:
    
    string name;
    int number_of_measures;
    vector<Measure*> bars;

//METHODS*********************
private:
    void fix_pointers();
public:
    Part(string _name, MusicXML2::Sxmlelement elt);
    Part(string _name, int _number_of_measures);
    const string what_name();
    const int how_many_measures();
    void print_me();
    Note* get_part_head();
    Note* get_part_tail();
    ~Part();
    void add_bar(Measure *m);
    Measure* get_measure(int n);
};

#endif /* defined(__Algorithmic_Composer__Part__) */
