//
//  Global_Variables.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 13/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef Algorithmic_Composer_Global_Variables_h
#define Algorithmic_Composer_Global_Variables_h

//--------------------------------------------------------------------------------
//global constants used throughout the program
//--------------------------------------------------------------------------------

//error value used for an unrecognised key
static int ERROR_INT = 100;

//values for the generative grammar

static float GRAMMAR_ETA = 0.9; //threshold of detecting divergence in the RDS graph
static float GRAMMAR_ALPHA = 0.1; //significance test threshold
static int GRAMMAR_CONTEXT_SIZE = 4; //size of the context window used for search for Equivalence Class, usually set to 5 or 4, a value less 3 will mean that no equivalence class can be found
static float GRAMMAR_COVERAGE = 0.5; //threhold for bootstrapping Equivalence classes, usually set to 0.65. Higher values will result in less bootstrapping



//DO NOT CHANGE - USED TO DEFINE MAJOR AND MINOR FOR MATRICES
static int MAJOR = 0;
static int MINOR = 1;

//maximum interval a part can move melodically otherwise the octave will be modified
static int MAX_INTERVAL = 13;

//Default time signature and measure length for the creation of a new score (4/4)
static int TIME_SIG_TOP = 4;
static int TIME_SIG_BOTTOM = 4;
static int MAX_BEATS_IN_BAR = (TIME_SIG_TOP * ((4/TIME_SIG_BOTTOM)*4));
static float MAX_BEATS_IN_BAR_FLOAT = (TIME_SIG_TOP * ((4/TIME_SIG_BOTTOM)*4));

#endif
