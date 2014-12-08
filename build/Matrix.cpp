//
//  Matrix.cpp
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 01/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#include "Matrix.h"
#include<iostream>


using namespace std;

//-------------------------------------------------------------------
//abstract class for all markov matrices
//-------------------------------------------------------------------
Matrix::Matrix(int _order){order = _order;}