//
//  Implementation.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 15/07/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//


//--------------------------------------------------------------------------------
// some general utility functions used throughout the program
//--------------------------------------------------------------------------------

#include<iostream>

#include "Implementation.h"
#include "All_Part_Names.h"


using namespace std;
using namespace MusicXML2;


//--------------------------------------------------------------------------------
//function that converts a note value to the appropriate float length
//--------------------------------------------------------------------------------
float value_to_sub_div(string value){
    if (value == "breve")
        return 32.0;
    else if (value == "whole")
        return 16.0;
    else if (value == "half")
        return 8.0;
    else if (value == "quarter")
        return 4.0;
    else if (value == "eighth")
        return 2.0;
    else if (value == "16th")
        return 1.0;
    else if (value == "32nd")
        return 0.5;
    else if (value == "64th")
        return 0.25;
    else if (value == "128th")
        return 0.125;
    else if (value == "256th")
        return 0.0625;
    else
        cerr << "UNKNOWN NOTE LENGTH: " << value << endl;
    return 0.0;
};

//--------------------------------------------------------------------------------
//function that converts a note length to the appropriate string value
//--------------------------------------------------------------------------------
const char* duration2type(float dur) {
	
    if (dur == 0.0625)    return "256th";
    else if (dur == 0.125)     return "128th";
    else if (dur == 0.25)      return "64th";
    else if (dur == 0.5)       return "32nd";
    else if (dur == 1.0)		return "16th";
    else if (dur == 2.0 )		return "eighth";
    else if (dur == 4.0)		return "quarter";
    else if (dur == 8.0)     return "half";
    else if (dur == 16.0)      return "whole";
    else        return "unknown";
	
}

//----------------------------------------------------------------------------------------------------------------
//function used when a note is too long to see what the largest whole note that it can be converted into is (i.e used for dotted notes)
//----------------------------------------------------------------------------------------------------------------
float get_max_length(double dur){
    if (dur >= 16.0) return 16.0;
    else if (dur >= 8.0) return 8.0;
    else if (dur >= 4.0) return 4.0;
    else if (dur >= 2.0) return 2.0;
    else if (dur >= 1.0) return 1.0;
    else if (dur >= 0.5) return 0.5;
    else if (dur >= 0.25) return 0.25;
    else if (dur >= 0.125) return 0.125;
    else return 0.0625;
}

//----------------------------------------------------------------------------------------------------------------
//function converts a pitch, alteration and octave into simple note form
//----------------------------------------------------------------------------------------------------------------
Simple_Note convert_to_simple_note(char pitch, int alter, int octave){
    Simple_Note ret;
    ret.octave = octave;
    if (octave <0  || octave > 10) {cerr << "bad octave" << endl;}
    if (pitch=='A'){ret.pitch = 9;}
    else if (pitch == 'B'){ret.pitch = 11;}
    else if (pitch == 'C'){ret.pitch = 0;}
    else if (pitch == 'D'){ret.pitch = 2;}
    else if (pitch == 'E'){ret.pitch = 4;}
    else if (pitch == 'F'){ret.pitch = 5;}
    else if(pitch == 'G'){ret.pitch=7;}
    else {ret.pitch = 0; cerr << "INVALID PITCH :" << pitch << endl; return ret;}
    ret.pitch = (12+ ret.pitch + alter) % 12;
    return ret;
};

//----------------------------------------------------------------------------------------------------------------
//function used to convert from simple note to string representation
//----------------------------------------------------------------------------------------------------------------
string convert_to_note(Simple_Note sn){
    switch (sn.pitch){
        case 9: return "A";
        case 10: return "A#";
        case 11: return "B";
        case 0: return "C";
        case 1: return "C#";
        case 2: return "D";
        case 3: return "D#";
        case 4: return "E";
        case 5: return "F";
        case 6: return "F#";
        case 7: return "G";
        case 8: return "G#";
        case -1: return "REST";
    }
    return "REST";
}

//----------------------------------------------------------------------------------------------------------------
//function used to convert from pitch to string representation
//----------------------------------------------------------------------------------------------------------------
string convert_to_note(int pitch){
    switch (pitch){
        case 9: return "A";
        case 10: return "A#";
        case 11: return "B";
        case 0: return "C";
        case 1: return "C#";
        case 2: return "D";
        case 3: return "D#";
        case 4: return "E";
        case 5: return "F";
        case 6: return "F#";
        case 7: return "G";
        case 8: return "G#";
        case -1: return "REST";
    }
    return "REST";
}


//----------------------------------------------------------------------------------------------------------------
//function used work out which voice type/number a part is, using the names supplied in All_Part_Names.h
//----------------------------------------------------------------------------------------------------------------
int which_voice(string name){
    for (int i = 0; i < SOPRANO_PART_NAMES.size(); i++){
        if (name == SOPRANO_PART_NAMES[i]) return 0;
    }
    for (int i = 0; i < ALTO_PART_NAMES.size(); i++){
        if (name == ALTO_PART_NAMES[i]) return 1;
    }
    for (int i = 0; i < TENOR_PART_NAMES.size(); i++){
        if (name == TENOR_PART_NAMES[i]) return 2;
    }
    for (int i = 0; i < BASS_PART_NAMES.size(); i++){
        if (name == BASS_PART_NAMES[i]) return 3;
    }
    return -1;
}


