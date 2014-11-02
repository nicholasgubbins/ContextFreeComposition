////
////  main.cpp
////  Algorithmic Composer
////
////  Created by Nicholas Gubbins on 04/07/2014.
////  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
////


#include <iostream>
#include <ctime>

#include "xml.h"
#include "xmlfile.h"
#include "xmlreader.h"
#include "xml_tree_browser.h"
#include "transposition.h"

#include "Implementation.h"

#include "Score.h"
#include "Score_Maker.h"

#include "Rhythmic_Matrix.h"
#include "Matrix_Master.h"
#include "Part_Matrix.h"
#include "Matrix.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>



using namespace std;
using namespace MusicXML2;
using namespace boost::filesystem;

static int get_key_main(Sxmlelement elt){
    ctree<xmlelement>::iterator iter = elt->begin();
    
    while (iter != elt->end()){
        Sxmlelement xml = *iter;
        if (xml){
            if (xml->getName() == "fifths")
                return stoi(xml->getValue());
        }
        iter++;
    }
    return ERROR_INT;
}


static void read_and_analyse_file(string f, Matrix_Master *mm){
    xmlreader r;
    SXMLFile file = r.read(f.c_str());
    if (file) {
        Sxmlelement elt = file->elements();
        if (elt) {
            int disp = get_key_main(elt);
            
            int dif;
            if (disp == ERROR_INT) {cerr<<"Error unreadable key"; return;}
            else if (disp == -1){dif = -5;}
            else if (disp == 1) {dif = 5;}
            else if (disp == 3) {dif = 3;}
            else if (disp == -3) {dif = -3;}
            else{dif = disp * -1;}
            cout << "Originally in " << disp << " transposing by " << dif << endl;
            transposition t(dif);
    		xml_tree_browser tb(&t);
    		tb.browse (*elt);
            Score* s = new Score(elt);
            disp = get_key_main(elt);
            if (disp != 0){
                cout << "Ignoring file" << endl;
                return;}
            if (s->delete_me() || s->how_many_voices() > 4){}
            else{
            mm->update(s);
            }
            delete s;
            cout << "Complete" << endl;
        }
        
    }
}



int main(int argc, char *argv[]) {
    cout << "Welcome. I am an algorithmic composer." << endl;
    cout << endl;
    srand(time(0));
    if (argc < 3 || !is_directory(argv[1]) || !is_directory(argv[2])){
        cerr << "No file(s) selected" << endl;
        cerr << "Usage:  ";
        cerr << "./Algorithmic\ Composer <input directory> <output directory>" << endl;
        return 0;
    }
    int count = 0;
    clock_t t;
    t = clock();
    string grammar_path = "grammar.txt";
  //  try { remove(grammar_path);}
   // catch(invalid_argument){}
    path gr = grammar_path;
    if (exists(gr)){
        boost::filesystem::remove(gr);
    }
    if (argc > 1) {
        path p = argv[1];
        cout << "What order matrix would you like? (Beween 1-8): ";
        string order;
        cin >> order;
        cout << endl;
        int order_int;
        try{ order_int = stoi(order);}
        catch(invalid_argument){ cout << "Incorrect choice, order = 4" << endl;order_int = 4;}
        order_int = (order_int < 1 || order_int > 8) ? 4 : order_int;
        Matrix_Master *mm = new Matrix_Master(order_int);
        
       
        //directory provided
        if (is_directory(p)){
            cout << "Directory provided" << endl;
            directory_iterator end;
            for (directory_iterator itr(p); itr != end; ++itr){
                path temp_p = itr->path();
                if (temp_p.extension() == ".xml"){
                    string fname = temp_p.string();
                    cout << "Analaysing " << temp_p.filename() << endl;
                    read_and_analyse_file(fname, mm);
                    count++;
                    cout << endl;

                }
                else{
                    string oname = temp_p.string();
                    cout << oname << " not a valid XML file" << endl;
                }
            }
        }
        else{
            cout << "Invalid filetype. Goodbye." << endl;
            return 0;
        }
        t = clock() - t;
        cout << endl;
        cout << endl;
        cout << "Analysis complete. ";
        cout << "I read " << count << " files in " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
        cout << endl;
        cout << endl;
        
        path out = argv[2];
        string output_location = out.string();
        if (output_location.back() != '/'){ output_location += "/";}
        Grammar_Parser *gp = new Grammar_Parser(grammar_path);
        Score_Maker sm(mm, gp, output_location);
        sm.create_new_score();
        boost::filesystem::remove(gr);
        delete mm;
        cout << "Thank you, goodbye!" << endl;
    }
    else cerr << "Error reading \"" << argv[1] << "\"" << endl;
    return 0;
};


