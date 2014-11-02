//--------------------------------------------------------------------------------
//This file is from the Modified adios algorithm on github by
//user Shabohou found at https://github.com/shaobohou/madios
//--------------------------------------------------------------------------------


#ifndef STRINGABLE_H
#define STRINGABLE_H

#include <string>

class Stringable
{
    public:
        Stringable();
        virtual ~Stringable();

        virtual std::string toString() const = 0;
        friend std::ostream& operator<<(std::ostream &out, const Stringable &Stringable);
};

#endif
