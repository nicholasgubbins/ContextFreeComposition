Algorithmic Composer
======

I built this algorithmic musical composition program for my Master's Thesis at Imperial College London, for which I received Disinction. 
The general concept was to build a platform that can read in any amount of music in musicXML format, the common standard for music composition programs like Sibelius and Finale, and analyse the music in such a way that the program can compose new material without being trained in any music theory. As such, the program analyses each score, and develops multiple Markovian transition matrices for rhythm, pitch and harmony, as well as an induced grammar via the ADIOS algorithm. With this analysis in place, the program can compose new scores and output new musicXML files.

For a more in depth analysis, please read my Thesis report found in this repository!


This Repository
-----
    - /src - The source code for this project
    - /Xcode - The Xcode project (for compilation and execution)
    - /build - The source code along with makefile (for compilation and execution)
    - report.pdf - The written report for the thesis
    - /xml - sample musicXML files for use with the program



Source Code
-----

Please refer to Chapter 5 of the report for an overview of how the classes interact with one another and how the system works. 

The file structure found in src is as follows:

    - main.cpp

    - /Score_Data_Structure - this subdirectory contains the classes for Score representation. The Score is populated by data extracted from a musicXML file, and then analysed Markovianly by the Matrix_Master, and Grammatically by the Grammar_Parser.
        - Score.cpp/Score.h
        - Part.cpp/Part.h
        - Measure.cpp/Measure.h
        - Note.cpp/Measure.h
        - Chord.cpp/Chord.h
        - Chord_Sequence.cpp/Chord_Sequence.h
        - All_Chords.h
        - All_Part_Names.h
        - Implementation.cpp/Implementation.h
        - Global_Variables.h

    - /Markov - this subdirectory contains the different types of matrices, all of which instantiate the abstract class Matrix.cpp. The Matrix_Master serves as the interface and container for all matrices, including the interface for the Scores whose data populate the matrices, as well as the Score_Maker who requests new notes based on n-grams during composition.
        - Matrix_Master.cpp/Matrix_Master.h
        - Matrix.cpp/Matrix.h
        - Part_Matrix.cpp/Part_Matrix.h
        - Rhythmic_Matrix.cpp/Rhythmic_Matrix.h
        - Chord_Matrix.cpp/Chord_Matrix.h

    - /Grammar - this subdirectory contains the wrapper for the madios algorithm library
        - Grammar_Parser.cpp/Grammar_Parser.h

    - /Score_Creator - this subdirectory contains the classes which use the constructed grammars, as well as the Markov Matrices to compose a new Score. This Score is then translated into a musicXML file via XML_Creator
        - Score_Maker.cpp/Score_Maker.h
        - XML_Creator.cpp/XML_Creator.h

    - /Libraries - this subdirectory contains the madios algorithm (for grammar induction) and libmusicxml libraries (for interacting with musicXML files) 



Installation
-----

To build the program you either need Xcode and to import the Xcode project. Note the boost libraries needs to be installed on your machine and the libraries linked under build settings. All other files are included. The compiler that this project is set to use is under version LLVM 5.1 using c++ standard library libc++ and c++ dialect GNU++11
 
Otherwise, go to the directory build, and the makefile is provided. Note that BEFORE COMPILATION the boost libraries paths need to be amended in the Makefile on line 63 to suit your system. ALSO your compiler needs to support c++11 features (use lines 60 and 100 of Makefile accordingly). 
 
To run the program, type ./AlgorithmicComposer <inputdirectory> <outputdirectory> into the command line, replacing the directories appropriately. Then follow the instructions to compose on the command line new pieces. Scores can be found in the xml directory

Note that the output file will be a MusicXML file, and as such score editing software will be needed to open and listen to the product. I recommend downloading this [free copy of Finale NotePad](http://www.finalemusic.com/products/finale-notepad/resources/).

Thanks to shabohou for his [implementation of the ADIOS algorithm](https://github.com/shaobohou/madios) and to sourceforge for their [libmusicxml library](http://libmusicxml.sourceforge.net). 


