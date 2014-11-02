//
//  Grammar_Parser.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 11/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//



//--------------------------------------------------------------------------------
//This class serves as a front end to the Modified adios algorithm from github by
//user Shabohou found at https://github.com/shaobohou/madios
//--------------------------------------------------------------------------------




#include "Grammar_Parser.h"
#include <fstream>
#include "Global_Variables.h"

using namespace std;


//--------------------------------------------------------------------------------
//Constructor takes in a filename to access the file with sentences in(grammar.txt)
//once the file is read in, the grammar is distilled and stored in the RDS graph.
//The values for the alpha size, context size, eta and coverage are all set and
//explained in Global_Variables.h
//--------------------------------------------------------------------------------

Grammar_Parser::Grammar_Parser(string filename){
    eta = GRAMMAR_ETA;
    alpha = GRAMMAR_ALPHA;
    context_size = GRAMMAR_CONTEXT_SIZE;
    coverage = GRAMMAR_COVERAGE;
    read(filename);
    graph = new RDSGraph(sequences);
    graph->distill(ADIOSParams(eta, alpha, context_size, coverage));
 
    //   graph->convert2PCFG(std::cout); <-- use this to print the grammar
}


//PRIVATE FUNCTIONS*********************

//--------------------------------------------------------------------------------
//splits the strings into tokens differentiating them by spaces, and signifying a
//new sentence and end of sentence by * and # respectively
//--------------------------------------------------------------------------------

void Grammar_Parser::read(string filename){
    vector<string> tokens;
    string token;

    ifstream instream(filename.c_str());
    if(!instream.is_open()){
        cout << "Unable to open file: " << filename << endl;
        return;}
    
    while(!instream.eof())
    {
        string line;
        getline(instream, line);

        if(line.size() > 0)
        {
            stringstream ss(line);
            while(!ss.eof())
            {
                ss >> token;
                if(token == "*")
                    tokens.clear();
                else if(token == "#"){
                    sequences.push_back(tokens);
                    break;}
                else
                    tokens.push_back(token);
            }
        }
    }
    instream.close();

}

//PUBLIC FUNCTIONS*********************

//--------------------------------------------------------------------------------
//traverses the grammar graph and creates a new sentence based on the
//alphabet and rules derived
//--------------------------------------------------------------------------------
vector<string> Grammar_Parser::generate_new(){return graph->generate();}

//--------------------------------------------------------------------------------
//destructor
//--------------------------------------------------------------------------------
Grammar_Parser::~Grammar_Parser(){delete graph;}

