//
//  MultiplyMatrix.hpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 11/7/19.
//  Copyright © 2019 Turner Romey. All rights reserved.
//

#ifndef MultiplyMatrix_hpp
#define MultiplyMatrix_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include "Matrix.hpp"

namespace utils
{
    class MultiplyMatrix
    {
    public:
        MultiplyMatrix(Matrix *a, Matrix *b);
        
        Matrix *execute();
    private:
        Matrix *a;
        Matrix *b;
        Matrix *c;
    };
}


#endif /* MultiplyMatrix_hpp */
