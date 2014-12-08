//--------------------------------------------------------------------------------
//This file is from the Modified adios algorithm on github by
//user Shabohou found at https://github.com/shaobohou/madios
//--------------------------------------------------------------------------------


#ifndef SPECIALLEXICONS_H
#define SPECIALLEXICONS_H

#include "LexiconUnit.h"

#include <string>

class StartSymbol: public LexiconUnit
{
    public:
        virtual LexiconUnit* makeCopy() const;
        virtual std::string toString() const;
};

class EndSymbol: public LexiconUnit
{
    public:
        virtual LexiconUnit* makeCopy() const;
        virtual std::string toString() const;
};

#endif
