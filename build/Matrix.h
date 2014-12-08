//
//  Matrix.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 01/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef __Algorithmic_Composer__Matrix__
#define __Algorithmic_Composer__Matrix__

#include <iostream>
#include "Part.h"

class Matrix{
    
//ATTRIBUTES*********************
protected:
    int order;
    
//METHODS*********************
public:
    Matrix(int _order);
    virtual void update(Part *x) =0;
   
};
#endif /* defined(__Algorithmic_Composer__Matrix__) */
