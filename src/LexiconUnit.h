//--------------------------------------------------------------------------------
//This file is from the Modified adios algorithm on github by
//user Shabohou found at https://github.com/shaobohou/madios
//--------------------------------------------------------------------------------


#ifndef LEXICONUNIT_H
#define LEXICONUNIT_H

#include "Stringable.h"

class LexiconUnit: public Stringable
{
    public:
        virtual LexiconUnit* makeCopy() const = 0;
};

#endif
