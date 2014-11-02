//--------------------------------------------------------------------------------
//This file is from the Modified adios algorithm on github by
//user Shabohou found at https://github.com/shaobohou/madios
//--------------------------------------------------------------------------------


#include "Stringable.h"

using std::ostream;

Stringable::Stringable()
{
}

Stringable::~Stringable()
{
}

ostream& operator<<(ostream &out, const Stringable &stringable)
{
    out << stringable.toString();
    return out;
}
