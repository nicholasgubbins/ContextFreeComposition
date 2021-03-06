//--------------------------------------------------------------------------------
//This file is from the Modified adios algorithm on github by
//user Shabohou found at https://github.com/shaobohou/madios
//--------------------------------------------------------------------------------


#ifndef BASICSYMBOL_H
#define BASICSYMBOL_H

#include "LexiconUnit.h"

class BasicSymbol: public LexiconUnit
{
    public:
        BasicSymbol();
        explicit BasicSymbol(const std::string &symbol);
        virtual ~BasicSymbol();

        virtual LexiconUnit* makeCopy() const;
        virtual std::string toString() const;
        std::string getSymbol() const;

    private:
        std::string symbol;
};

#endif
