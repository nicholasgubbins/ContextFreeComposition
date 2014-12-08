//
//  Implementation.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 15/07/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Implementation__
#define __Algorithmic_Composer__Implementation__

#include "xml.h"
#include <boost/functional/hash.hpp>
#include "Global_Variables.h"

using namespace std;



//----------------------------------------------------------------------------------------------------------------
//Time signature struct
//----------------------------------------------------------------------------------------------------------------
struct TS {
    int top;
    int bottom;
};

//----------------------------------------------------------------------------------------------------------------
//simple representation of a note used throughout the program consisting of a pitch and an octave. also overridden operators
//----------------------------------------------------------------------------------------------------------------
struct Simple_Note {
    
    int pitch;
    int octave;
    
    bool operator<(const Simple_Note& sn) const
    {return (octave < sn.octave || (octave == sn.octave && pitch < sn.pitch));}
    
    bool operator>(const Simple_Note& sn) const
    {return (octave > sn.octave || (octave == sn.octave && pitch > sn.pitch));}
    
    bool operator==(const Simple_Note& sn) const
    {return (octave == sn.octave && pitch == sn.pitch);}
    
    int dif(const Simple_Note sn) const {
        int me = octave*12 + pitch;
        int you = sn.octave*12 + sn.pitch;
        if (me > you){
            return me - you;
        }
        else if (you > me){
            return (you - me) * -1;
        }
        return 0;
    }
};

//----------------------------------------------------------------------------------------------------------------
//Hasher of simple notes for the Part_Matrix unordered_multimap
//----------------------------------------------------------------------------------------------------------------
struct Simple_Note_Hasher
{
    std::size_t operator()(const Simple_Note& sn) const
    {
        using boost::hash_value;
        using boost::hash_combine;
        
        std::size_t seed = 0;
        
        hash_combine(seed,hash_value(sn.pitch));
        hash_combine(seed,hash_value(sn.octave));
        
        return seed;
    }
    
    
    std::size_t operator()(const vector<Simple_Note>& sn) const
    {
        using boost::hash_value;
        using boost::hash_combine;

        std::size_t seed = 0;

        for (int i = 0; i < sn.size(); i++){
            hash_combine(seed,hash_value(sn[i].pitch));
            hash_combine(seed,hash_value(sn[i].octave));
            seed = seed/2;

        }
        return seed;
    }
};

//----------------------------------------------------------------------------------------------------------------
//Hasher of strings for the Rhytm_Matrix unordered_multimap
//----------------------------------------------------------------------------------------------------------------
struct String_Hasher
{
    std::size_t operator()(const vector<string>& st) const
    {
        using boost::hash_value;
        using boost::hash_combine;
        
        std::size_t seed = 0;
        
        for (int i = 0; i < st.size(); i++){
            hash_combine(seed,hash_value(st[i]));
            seed = seed/2;
        }

        return seed;
    }

    
};

//----------------------------------------------------------------------------------------------------------------
//Hasher of vector of vector of ints for the Chord_Matrix unordered_multimap
//----------------------------------------------------------------------------------------------------------------
struct VectorVectorInt_Hasher{
    std::size_t operator()(const vector<vector<int> >& vt) const{
        using boost::hash_value;
        using boost::hash_combine;
        
        std::size_t seed = 0;
        
        for (int i = 0; i < vt.size(); i++){
            for (int j = 0; j < vt[i].size(); j++){
                hash_combine(seed,hash_value(vt[i][j]));
                seed = seed/2;
            }
        }

        return seed;
    }
};

//----------------------------------------------------------------------------------------------------------------
//Function declarations from Implementation.cpp
//----------------------------------------------------------------------------------------------------------------
Simple_Note convert_to_simple_note(char pitch, int alter, int octave);

string convert_to_note(Simple_Note sn);
string convert_to_note(int sn);

float value_to_sub_div(string value);
int which_voice(string name);
float get_max_length(double dur);

const char* duration2type(float dur);

#endif /* defined(__Algorithmic_Composer__Implementation__) */



