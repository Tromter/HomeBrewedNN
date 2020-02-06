//  MatrixToVector.hpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 11/7/19.
//  Copyright © 2019 Turner Romey. All rights reserved.
//

#ifndef MatrixToVector_hpp
#define MatrixToVector_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <assert.h>

#include "Matrix.hpp"

namespace utils
{    
    class MatrixToVector
    {
    public:
        MatrixToVector(Matrix *a);
        
        vector<double> *execute();
    private:
        Matrix *a;
        vector<double> *result;
    };
}

#endif /* MatrixToVector_hpp */
