//
//  Score_Maker.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 10/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include "Score_Maker.h"
#include "Score.h"
#include "XML_Creator.h"
#include <boost/algorithm/string.hpp>
#include "Implementation.h"


//--------------------------------------------------------------------------------
//Constructor
//--------------------------------------------------------------------------------
Score_Maker::Score_Maker(Matrix_Master *_mm, Grammar_Parser *_gp, string _output){
    mm = _mm;
    gp = _gp;
    order = mm->what_order();
    output = _output;
}



//PUBLIC FUNCTIONS*********************

//--------------------------------------------------------------------------------
//Function that allows for the user to choose what type of score to create
//if markovian, choose a length and modality in order to use the correct matrices
//--------------------------------------------------------------------------------
void Score_Maker::create_new_score(){
    while (true){
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "To create a new piece please choose an option: " << endl;
        cout << "1. Markov - Melodic Composition;" << endl;
        cout << "2. Generative Grammar - Harmony-first Composition;" << endl;
        cout << "3. Markov - Melody-first Composition;" << endl;
        cout << "or type '.' to quit" << endl;
        cout << "Choice: ";
        string in;
        cin >> in;
        if (in == ".") return;
        else if (in == "2"){
            create_new_harmony_first();
        }
        else{
        cout << "How many measures would you like your piece to be: ";
        string num;
        cin >> num;
        cout << endl << "Choose a modality: " << endl;
        cout <<"1. Major" << endl <<"2. Minor" << endl;
        string mode;
        cout << "Choice: ";
        cin >> mode;
        cout << endl;
        int modality;
        int measures;
        try{measures = stoi(num);}
        catch(invalid_argument){cerr << "invalid_argument" << endl; measures = 8;}
        if (mode == "2"){modality = MINOR;}
        else {modality = MAJOR;}
        if (in == "1"){
            create_new_blind(measures, modality);
        }
        else if (in == "3"){
            create_new_melody_first(measures, modality);
        }
        else cout << "Sorry that is not an option, choose again." << endl;
        }
    }
}



//PRIVATE FUNCTIONS*********************

//--------------------------------------------------------------------------------
//Option 1. Make a Markovian melody
//--------------------------------------------------------------------------------

void Score_Maker::create_new_blind(int measures, int modality){
    
    vector<Part*> parts;
    bool correct = false;
    string choice;
    string name;
    while(!correct){
        cout << "Which voice would you like to make?" << endl;
        cout << "1. Soprano" << endl;
        cout << "2. Alto" << endl;
        cout << "3. Tenor" << endl;
        cout << "4. Bass" << endl;

        cout << "Choice: ";
        cin >> choice;
        cout << endl;
        if (choice == "1"){name = "Soprano"; correct = true;}
        else if (choice == "2"){name = "Alto"; correct = true;}
        else if (choice == "3"){name = "Tenor"; correct = true;}
        else if (choice == "4"){name = "Bass"; correct = true;}
        else {cout << "Incorrect choice, try again" << endl;}
        
    }
        
    
    Part *p = new Part(name, measures);
    create_blind_part(p, modality);
    
    parts.push_back(p);
    
    Score *s = new Score(measures, parts, modality);
    
    XML_Creator xml(s);
    xml.create(output);
    
    delete s;
}


//--------------------------------------------------------------------------------
//The function to create a new part using rhythm and pitch matrices.
//The part is created up until the last two measures at which point
//the reverse process is carried out
//--------------------------------------------------------------------------------
void Score_Maker::create_blind_part(Part *p, int modality){
    
    vector<Simple_Note> previous_notes; //pitch n-gram
    vector<string> previous_rhythms;    //rhythmic n-gram
    
    int voice = which_voice(p->what_name());
    
    //build all measures until the last two
    for (int i = 1; i <= p->how_many_measures()-2; i++){
        
        Measure *current_measure = new Measure(i);
        float how_much_left = MAX_BEATS_IN_BAR_FLOAT;
        
        while (how_much_left > 0){
            
            Simple_Note note = randomNote(voice, previous_notes, modality); //get note value
            previous_notes.push_back(note); //update n-gram
            while (previous_notes.size() > order){
                previous_notes.erase(previous_notes.begin());
            }
            
            float rhythm = randomDuration(voice, previous_rhythms); //get rhythmic value
            
            int attempts = ERROR_INT; //keep trying to get a rhythmic value less than or equal to how much left to fill in the bar. if timeout set to the amount left
            while (rhythm > how_much_left && attempts >0){
                rhythm = randomDuration(voice, previous_rhythms);
                attempts--;
            }
            if (attempts == 0) {rhythm = how_much_left;}
            previous_rhythms.push_back(duration2type(rhythm));
            how_much_left -= rhythm;
            
            bool rest = (note.pitch == -1) ? true : false;
            
            Note *n = new Note(duration2type(rhythm), how_much_left - rhythm, rhythm, note, rest);
            current_measure->add_note(n);
        }
        p->add_bar(current_measure);
    }
    
    //final two measures filled backwards in the same way as before
    vector<Simple_Note> future_notes;
    vector<string> future_rhythms;
    vector<Note*> future_full_notes;
    
    Measure *last_measure = new Measure(p->how_many_measures());
    Measure *penultimate_measure = new Measure(p->how_many_measures()-1);
    
    for (int i = 0; i < 2; i++){
        float how_much_left = MAX_BEATS_IN_BAR_FLOAT;
        while (how_much_left > 0){
            
            Simple_Note note = randomendNote(voice, future_notes, modality); //get note value
            future_notes.push_back(note);
            
            while (future_notes.size() > order){future_notes.erase(future_notes.begin());} //update n-gram
            
            float rhythm = randomendDuration(voice, future_rhythms); //set value
            while (rhythm > how_much_left){
                rhythm = randomendDuration(voice, future_rhythms);
            }
            future_rhythms.push_back(duration2type(rhythm));
            how_much_left -= rhythm;
            
            bool rest = (note.pitch == -1) ? true : false;
            
            Note *n = new Note(duration2type(rhythm), how_much_left - rhythm, rhythm, note, rest);
            future_full_notes.push_back(n);
        }
        //add the final two measures to the part
        for (int j = future_full_notes.size()-1; j >= 0; j--){
            if (i == 0){last_measure->add_note(future_full_notes[j]);}
            else {penultimate_measure->add_note(future_full_notes[j]);}
        }
        future_full_notes.clear();
    }
    p->add_bar(penultimate_measure);
    p->add_bar(last_measure);
}








//--------------------------------------------------------------------------------
//Option 2. Generative Grammar composition
//--------------------------------------------------------------------------------
void Score_Maker::create_new_harmony_first(){
    
    vector<string> harmony = gp->generate_new();    //get a new sentence from the grammar tree
    
    cout << endl;

    vector<int> soprano;
    vector<int> alto;
    vector<int> tenor;
    vector<int> bass;
    vector<double> rhythms;
    
    double count = 0;
    for (int i = 0; i < harmony.size() ; i++){                  //parse through each word in the sentence and extract each note
        vector<string> tokens;
        boost::split(tokens, harmony[i], boost::is_any_of("<,>"));
        if (tokens.size() != 6) continue;
        else {
            soprano.push_back(stoi(tokens[1]));
            alto.push_back(stoi(tokens[2]));
            tenor.push_back(stoi(tokens[3]));
            bass.push_back(stoi(tokens[4]));
            
            double r = 0.25; //each chord is 1 beat long
            rhythms.push_back(r*16.0);
            count += r*16;
        }
    }
    
    vector<vector<double>> measures;        //the number of measures that will ultimately be in our piece
    
    int i = 0;
    while (i < rhythms.size()){
        double measure_left = 16.0;
        vector<double> m;
        while (measure_left > 0){
            if (rhythms[i] > measure_left){         //if the rhythm is greater than it should be, get the maximum value that can fit in the bar and use that
                m.push_back(get_max_length(measure_left));
                measure_left -= get_max_length(measure_left);
            }
            
            else{
                m.push_back(get_max_length(rhythms[i]));
                measure_left -= get_max_length(rhythms[i]);
            }
            
            i++;
            if (i == rhythms.size()){
                if (measure_left > 0){
                    while (measure_left>0){
                        m.push_back(get_max_length(measure_left));
                        measure_left -= get_max_length(measure_left);
                    }
                }
            }
        }
        measures.push_back(m);
    }
    

    vector<Part*> parts;
    
    Part *s = new Part("Soprano", measures.size());         //create each part
    create_part_from_grammar(s, measures, soprano);
    Part *a = new Part("Alto", measures.size());
    create_part_from_grammar(a, measures, alto);
    Part *t = new Part("Tenor", measures.size());
    create_part_from_grammar(t, measures, tenor);
    Part *b = new Part("Bass", measures.size());
    create_part_from_grammar(b, measures, bass);
    
    parts.push_back(s);
    parts.push_back(a);
    parts.push_back(t);
    parts.push_back(b);
    
    Score *score = new Score(measures.size(), parts, MAJOR);
    
    XML_Creator xml(score);
    xml.create(output);
    delete s;
}



//--------------------------------------------------------------------------------
//Function that creates a part from a series of pitches derived from the
//generative grammar
//--------------------------------------------------------------------------------
void Score_Maker::create_part_from_grammar(Part *p, vector<vector<double>> rhythms, vector<int> pitches){
    
    vector<Simple_Note> previous_notes; //n-gram
    
    int pitch_count = 0;    //how many pitches have been created
    
    for (int i = 1; i <= p->how_many_measures(); i++){
        
        Measure *current_measure = new Measure(i);
        float how_much_left = 16;
        while (how_much_left > 0){
            int rhythm_count = 0;
            Simple_Note note;
            
            if (pitch_count < pitches.size()){
                int unadjusted_pitch = pitches[pitch_count];    //get the next pitch from the grammar
                note.pitch = unadjusted_pitch%12;
                note.octave = unadjusted_pitch/12;
                pitch_count++;}
            
            else {note.pitch = -1; note.octave = 1;}        //if still composing but out of pitches make a rst
            
            previous_notes.push_back(note);     //update n-gram
            while (previous_notes.size() > order){
                previous_notes.erase(previous_notes.begin());
            }
        
            float rhythm = rhythms[i-1][rhythm_count];  //get the next rhythm
            rhythm_count++;
            
            bool updated_prev = false;
            if (how_much_left < 16){                //check if the previous note was the same pitch value
                Note* prev = current_measure->notes[current_measure->notes.size()-1];
                if (prev->get_simple() == note && rhythm <= how_much_left){
                    if (string(duration2type(prev->get_other_duration()+rhythm)) != "unknown"){ //if it was and the lengths together make a whole note, update the length of the previous note
                        prev->update_length(rhythm);
                        updated_prev = true;}
                }
            }
            
            how_much_left -= rhythm;
            
            if (! updated_prev){    //if we didn't update the previous, create the new note and add it to the bar
                bool rest = (note.pitch == -1) ? true : false;
                Note *n = new Note(duration2type(rhythm), how_much_left - rhythm, rhythm, note, rest);
                current_measure->add_note(n);}
        }
        p->add_bar(current_measure);
    }
    
}






//--------------------------------------------------------------------------------
//Option 3. Melody-first Markovian composition - create a blind melody, harmonise it in both
//directions, then add the voices based on the harmonisation
//--------------------------------------------------------------------------------
void Score_Maker::create_new_melody_first(int measures, int modality){
    
    vector<Part*> parts;
    
    Part *soprano = new Part("Soprano", measures);      //make the soprano melody
    create_blind_part(soprano, modality);
    parts.push_back(soprano);
    cout << "Made soprano" << endl;
    
    vector<vector<int>> final_harmony_forwards;     //final harmonic structure of the piece (one chord per note)
    vector<vector<int>> final_harmony_backwards;
    
    vector<vector<int>> markov_front_harmony;       //n-grams
    vector<vector<int>> markov_back_harmony;
    
    bool forwards = true;       //these variables are used for the matrix master
    bool backwards = false;
    
    Note* current_front = soprano->get_part_head(); //first note
    Note* intermediate_front = current_front->get_next();   //always check the note ahead

    Note* current_back = soprano->get_part_tail();  //last note
    Note* intermediate_back = current_back->get_previous(); //always check the note previous
    
    while (true){
        vector<int> front_chord = mm->harmonise_voice(markov_front_harmony, 0, current_front->get_simple().pitch, modality, forwards);  //harmonise chords moving inwars
        vector<int> back_chord = mm->harmonise_voice(markov_back_harmony, 0, current_back->get_simple().pitch, modality, backwards);
        vector<int> check_front, check_back;
        
        check_front = check_back = {-1,-1,-1,-1};       //this represents all rests other than the melody note (couldn't find a chord)
        check_front[0] = current_front->get_simple().pitch;
        check_back[0] = current_back->get_simple().pitch;
        
        if (front_chord != check_front){                    //if we found a chord, add it to the n-gram, otherwise don't since we want the harmonic progression
            markov_front_harmony.push_back(front_chord);}   //to continue using the previous full harmony
        
        if (back_chord != check_back){
            markov_back_harmony.push_back(back_chord);}
            
        while (markov_front_harmony.size() > order){                //update both n-grams
            markov_front_harmony.erase(markov_front_harmony.begin());}
        while (markov_back_harmony.size() > order){
            markov_back_harmony.erase(markov_back_harmony.begin());}
        
        final_harmony_forwards.push_back(front_chord);      //add chords to the final harmony
        final_harmony_backwards.push_back(back_chord);
        
        if (intermediate_front == intermediate_back || intermediate_front->get_next()== intermediate_back){break;}      //if forwards and backwards have met break
        
        current_front = current_front->get_next();              //update all melodic note pointers
        intermediate_front = intermediate_front->get_next();
        current_back = current_back->get_previous();
        intermediate_back = intermediate_back->get_previous();
    }
    
    if (intermediate_front != intermediate_back){       //if we broke but there are two notes between the pointers pull the backwards markov process forward one
        vector<int> back_chord = mm->harmonise_voice(markov_back_harmony, 0, current_back->get_simple().pitch, modality, backwards);
        vector<int> check_back = {-1,-1,-1,-1};
        if (back_chord != check_back){ markov_back_harmony.push_back(back_chord);}
        while (markov_back_harmony.size() > order){
            markov_back_harmony.erase(markov_back_harmony.begin());}
        final_harmony_backwards.push_back(back_chord);
        current_back = current_back->get_previous();
        intermediate_back = intermediate_back->get_previous();
    }
    //now we have one chord left, find a shared chord that matches with both the forwards and backwards n-grams
    vector<int> shared = mm->find_shared_chord(markov_front_harmony, markov_back_harmony, 0, intermediate_front->get_simple().pitch, modality);
    final_harmony_forwards.push_back(shared);
    
    //add all backwards harmony into forwrds harmony
    for (int i = final_harmony_backwards.size()-1; i >= 0; i--){ final_harmony_forwards.push_back(final_harmony_backwards[i]);}

    //now make the other parts using this harmony
    cout << "Making alto" << endl;
    Part *alto = new Part("Alto", measures);
    create_weighted_part(alto, soprano, final_harmony_forwards, which_voice(alto->what_name()), modality);
    cout << "Making tenor" << endl;
    Part *tenor = new Part("Tenor", measures);
    create_weighted_part(tenor, soprano, final_harmony_forwards, which_voice(tenor->what_name()), modality);
    cout << "Making bass" << endl;
    Part *bass = new Part("Bass", measures);
    create_weighted_part(bass, soprano, final_harmony_forwards, which_voice(bass->what_name()), modality);
    
    parts.push_back(alto);
    parts.push_back(tenor);
    parts.push_back(bass);
    
    Score *s = new Score(measures, parts, modality);
    
    XML_Creator xml(s);
    
    xml.create(output);
    
    delete s;
}


//--------------------------------------------------------------------------------
//Function for creating a voice based on a harmonisation of a Markovian melody
//--------------------------------------------------------------------------------
void Score_Maker::create_weighted_part(Part *p, Part *melody, vector<vector<int>> harmony, int voice, int modality){
    
    vector<Simple_Note> previous_notes; //n-gram
    Note *melody_note = melody->get_part_head(); //pointer to the harmonised melody
    
    int count = 0;
    
        for (int i = 1; i <= p->how_many_measures(); i++){
            
            if (melody_note == nullptr){break;}
            
            Measure *current_measure = new Measure(i);
            float how_much_left = MAX_BEATS_IN_BAR_FLOAT;
            while (how_much_left > 0){
            
                if (melody_note == nullptr){break;}
                
                Simple_Note note = randomNote(voice, previous_notes, modality); //if we generate a rest, use the rest as opposed to the harmony
           
                if (note.pitch != -1){                          //if not a rest, use the harmony generated
                    note.pitch = harmony[count][voice] %12;
                    note.octave = harmony[count][voice]/12;}
                
                previous_notes.push_back(note); //add to n-gram and update n-gram
                while (previous_notes.size() > order){
                    previous_notes.erase(previous_notes.begin());
                }
                
                float rhythm = melody_note->get_other_duration();   //get the appropriate rhythmic duration from the melody
                
                bool updated_prev = false;
                
                if (how_much_left < MAX_BEATS_IN_BAR){              //check if the previous note was the same pitch value
                    Note* prev = current_measure->notes[current_measure->notes.size()-1];
                    if (prev->get_simple() == note && rhythm <= how_much_left){     //if it was and the lengths together make a whole note, update the length of the previous note
                        if (string(duration2type(prev->get_other_duration()+rhythm)) != "unknown"){
                            prev->update_length(rhythm);
                            updated_prev = true;}
                    }
                }

                how_much_left -= rhythm;
                
                if (! updated_prev){            // if we didn't update the previous note, add this one to the measure
                
                    bool rest = (note.pitch == -1) ? true : false;
                    Note *n = new Note(duration2type(rhythm), how_much_left - rhythm, rhythm, note, rest);
                        current_measure->add_note(n);}
                    melody_note = melody_note->get_next();
                    count++;
                
            }
            p->add_bar(current_measure);
        }
}


//--------------------------------------------------------------------------------
//Function which returns a random note (pitch and octave) from the matrix master
//--------------------------------------------------------------------------------
Simple_Note Score_Maker::randomNote(int voice, vector<Simple_Note> previous_notes, int modality) {
    return mm->get_random_note(previous_notes, voice, modality);
}

//--------------------------------------------------------------------------------
//Function which returns a random rhythmic value from the matrix master
//--------------------------------------------------------------------------------
float Score_Maker::randomDuration(int voice, vector<string> previous_rhythms) {
    string ret = mm->get_random_duration(previous_rhythms, voice);
	return value_to_sub_div(ret);
}

//--------------------------------------------------------------------------------
//Function which returns a random end note (pitch and octave) from the matrix master
//--------------------------------------------------------------------------------
Simple_Note Score_Maker::randomendNote(int voice, vector<Simple_Note> previous_notes, int modality) {
    return mm->get_random_end_note(previous_notes, voice, modality);
}

//--------------------------------------------------------------------------------
//Function which returns a random end rhythmic value from the matrix master
//--------------------------------------------------------------------------------
float Score_Maker::randomendDuration(int voice, vector<string> previous_rhythms) {
    string ret = mm->get_random_end_duration(previous_rhythms, voice);
	return value_to_sub_div(ret);
}

