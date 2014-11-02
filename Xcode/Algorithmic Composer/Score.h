//
//  Score.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 15/07/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Score__
#define __Algorithmic_Composer__Score__

#include "Implementation.h"
#include "Part.h"
#include "Part_Matrix.h"
#include "Chord_Sequence.h"
#include "Chord_Matrix.h"

class Score{
    
    friend class Score_Maker; friend class XML_Creator;
    
//ATTRIBUTES*********************
private:
    int number_of_measures;
    int number_of_voices;
    TS time_signature;
    vector<Part *> staves;
    vector<string> key;
    int divisions;
    vector<string> part_list;
    Chord_Sequence *sequence;
    
//METHODS*********************
public:
    
    Score(MusicXML2::Sxmlelement elt);

    int how_many_measures();
    int how_many_voices();
    TS what_time_signature();
    int is_major();
    vector<string> what_part_names();
    void print_notes();
    void matrix_update(Matrix *m, int voice);
    void matrix_update(Chord_Matrix *m);
    ~Score();
    bool delete_me();
    
    
protected:
    Score(int _number_of_mesaures, vector<Part*> parts, int modality);
    void add_part(Part *p);
    Part* get_part(int n);
    
private:
    void get_part_list(MusicXML2::Sxmlelement elt);
    TS get_time_sig(MusicXML2::Sxmlelement elt);
    vector<string> get_key(MusicXML2::Sxmlelement elt);
    vector<string> chord_progression();
    void get_chords();
    
};

#endif /* defined(__Algorithmic_Composer__Score__) */
