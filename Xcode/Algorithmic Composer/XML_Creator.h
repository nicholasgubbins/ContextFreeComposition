//
//  XML_Creator.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 11/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__XML_Creator__
#define __Algorithmic_Composer__XML_Creator__

#include <iostream>
#ifndef LIBMUSICXML
#define LIBMUSICXML
#include "libmusicxml.h"
#endif
#include "elements.h"
#include "Score.h"

#include "Implementation.h"


class XML_Creator {
    
//ATTRIBUTES*********************
private:
    Score *score;

//METHODS*********************
private:
    MusicXML2::TElement measure (MusicXML2::musicxmlfactory* f, int n, int voice, Measure *m);
    MusicXML2::TElement dynamic (MusicXML2::musicxmlfactory* f, int type);
    const char* duration2type(float dur);
    
public:
    XML_Creator(Score *_s);
    void create(string path);
};
#endif /* defined(__Algorithmic_Composer__XML_Creator__) */
