//--------------------------------------------------------------------------------
//This file is from the Modified adios algorithm on github by
//user Shabohou found at https://github.com/shaobohou/madios
//--------------------------------------------------------------------------------


#include "BasicSymbol.h"

using std::string;
using std::ostream;

BasicSymbol::BasicSymbol()
{
}

BasicSymbol::BasicSymbol(const string &symbol)
{
    this->symbol = symbol;
}

BasicSymbol::~BasicSymbol()
{
}

LexiconUnit* BasicSymbol::makeCopy() const
{
    return new BasicSymbol(*this);
}

string BasicSymbol::toString() const
{
    return symbol;
}

string BasicSymbol::getSymbol() const
{
    return symbol;
}
