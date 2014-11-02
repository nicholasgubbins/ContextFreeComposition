Algorithmic Composer
======

I built this algorithmic musical composition program for my Master's Thesis at Imperial College London, for which I received Disinction. The general concept was to build a platform that can read in any amount of music in musicXML format, the common standard for music composition programs like Sibelius and Finale, and analyse the music in such a way that the program can compose new material without being trained in any music theory. As such, the program analyses each score, and develops multiple Markovian transition matrices for rhythm, pitch and harmony, as well as an induced grammar via the ADIOS algorithm. With this analysis in place, the program can compose new scores and output new musicXML files.

For a more in depth analysis, please read my Thesis report found in this repository!


Files
-----

To build the program you either need Xcode and to import the Xcode project. Note the boost libraries needs to be installed on your machine and the libraries linked under build settings. All other files are included. The compiler that this project is set to use is under version LLVM 5.1 using c++ standard library libc++ and c++ dialect GNU++11
 
Otherwise, go to the directory src, and the makefile is provided. Note that BEFORE COMPILATION the boost libraries paths need to be amended in the Makefile on line 63 to suit your system. ALSO your compiler needs to support c++11 features (use lines 60 and 100 of Makefile accordingly). 
 
To run the program, type ./AlgorithmicComposer <inputdirectory> <outputdirectory> into the command line, replacing the directories appropriately. Then follow the instructions to compose on the command line new pieces. Scores can be found in the xml directory

Note that the output file will be a MusicXML file, and as such score editing software will be needed to open and listen to the product. I recommend downloading the free copy of Finale NotePad found at http://www.finalemusic.com/products/finale-notepad/resources/

Thanks to shabohou for his [implementation of the ADIOS algorithm](https://github.com/shaobohou/madios) and to sourceforge for their [libmusicxml library](http://libmusicxml.sourceforge.net). 


